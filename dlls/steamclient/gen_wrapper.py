#!/usr/bin/python2
import pprint
import sys
import clang.cindex
import os
import re

sdk_versions = [
    "138a",
    "138",
    "137",
    "136",
    "135a",
    "135",
    "134",
    "133b",
    "133a",
    "133",
    "132",
    "131",
    "130",
    "129a",
    "129",
    "128",
    "127",
    "126a",
    "126",
    "125",
    "124",
    "123a",
    "123",
    "122",
    "121",
    "120",
    "119",
    "118",
    "117",
    "116",
    "115",
    "114",
    "113",
    "112",
    "111",
    "110",
    "109",
    "108",
#clang++ has troubles with the following, skip for now
#    "107",
#    "106",
#    "105",
#    "104",
#    "103",
#    "102",
#    "101",
#    "100",
]

files = [
    ("steam_api.h", [
        "ISteamApps",
        "ISteamClient",
        "ISteamFriends",
        "ISteamHTTP",
        "ISteamMatchmaking",
        "ISteamMatchmakingServers",
        "ISteamNetworking",
        "ISteamRemoteStorage",
        "ISteamScreenshots",
        "ISteamUnifiedMessages",
        "ISteamUser",
        "ISteamUserStats",
        "ISteamUtils"
    ]),
    ("isteamappticket.h", [
        "ISteamAppTicket"
    ]),
]

print_sizes = [ "RemoteStorageUpdatePublishedFileRequest_t" ]

#files = [
#    # header file to parse, classes to generate from that header, addl headers needed for CPP files
#    ("isteamapps", ["ISteamApps"], []),
#    ("isteamappticket", ["ISteamAppTicket"], ["isteamappticket.h"]),
#    ("isteamclient", ["ISteamClient"], []),
#    ("isteamfriends", ["ISteamFriends"], []),
#    ("isteammatchmaking", ["ISteamMatchmaking", "ISteamMatchmakingServers"], []),
#    ("isteamnetworking", ["ISteamNetworking"], []),
#    ("isteamuser", ["ISteamUser"], []),
#    ("isteamuserstats", ["ISteamUserStats"], []),
#    ("isteamutils", ["ISteamUtils"], []),
#]

class_versions = {}

def handle_method(cfile, classname, winclassname, cppname, method, cpp, cpp_h, existing_methods):
    used_name = method.spelling
    idx = '2'
    while used_name in existing_methods:
        used_name = "%s_%s" % (method.spelling, idx)
        idx = chr(ord(idx) + 1)
    returns_record = method.result_type.get_canonical().kind == clang.cindex.TypeKind.RECORD
    if returns_record:
        parambytes = 8 #_this + return pointer
    else:
        parambytes = 4 #_this
    for param in list(method.get_children()):
        if param.kind == clang.cindex.CursorKind.PARM_DECL:
            parambytes += param.type.get_size()
    cfile.write("DEFINE_THISCALL_WRAPPER(%s_%s, %s)\n" % (winclassname, used_name, parambytes))
    cpp_h.write("extern ")
    if method.result_type.spelling.startswith("ISteam"):
        cfile.write("win%s " % (method.result_type.spelling))
        cpp.write("void *")
        cpp_h.write("void *")
    elif returns_record:
        cfile.write("%s *" % method.result_type.spelling)
        cpp.write("%s " % (method.result_type.spelling))
        cpp_h.write("%s " % (method.result_type.spelling))
    else:
        cfile.write("%s " % (method.result_type.spelling))
        cpp.write("%s " % (method.result_type.spelling))
        cpp_h.write("%s " % (method.result_type.spelling))
    cfile.write('__thiscall %s_%s(%s *_this' % (winclassname, used_name, winclassname))
    cpp.write("%s_%s(void *linux_side" % (cppname, used_name))
    cpp_h.write("%s_%s(void *" % (cppname, used_name))
    if returns_record:
        cfile.write(", %s *_r" % method.result_type.spelling)
    unnamed = 'a'
    for param in list(method.get_children()):
        if param.kind == clang.cindex.CursorKind.PARM_DECL:
            if param.spelling == "":
                cfile.write(", %s _%s" % (param.type.spelling, unnamed))
                cpp.write(", %s _%s" % (param.type.spelling, unnamed))
                cpp_h.write(", %s" % param.type.spelling)
                unnamed = chr(ord(unnamed) + 1)
            else:
                cfile.write(", %s %s" % (param.type.spelling, param.spelling))
                cpp.write(", %s %s" % (param.type.spelling, param.spelling))
                cpp_h.write(", %s" % (param.type.spelling))
    cfile.write(")\n{\n")
    cpp.write(")\n{\n")
    cpp_h.write(");\n")
    cfile.write("    TRACE(\"%p\\n\", _this);\n")
    if method.result_type.kind == clang.cindex.TypeKind.VOID:
        cfile.write("    ")
        cpp.write("    ")
    elif returns_record:
        cfile.write("    *_r = ")
        cpp.write("    return ")
    else:
        cfile.write("    return ")
        cpp.write("    return ")

    should_gen_wrapper = method.result_type.spelling.startswith("ISteam") or \
            used_name.startswith("GetISteamGenericInterface")
    if should_gen_wrapper:
        cfile.write("create_win_interface(pchVersion,\n        ")

    cfile.write("%s_%s(_this->linux_side" % (cppname, used_name))
    cpp.write("((%s*)linux_side)->%s(" % (classname, method.spelling))
    unnamed = 'a'
    first = True
    for param in list(method.get_children()):
        if param.kind == clang.cindex.CursorKind.PARM_DECL:
            # TODO see above
            if not first:
                cpp.write(", ")
            else:
                first = False
            if param.spelling == "":
                cfile.write(", _%s" % unnamed)
                cpp.write("_%s" % unnamed)
                unnamed = chr(ord(unnamed) + 1)
            else:
                cfile.write(", %s" % param.spelling)
                cpp.write("%s" % param.spelling)
    if should_gen_wrapper:
        cfile.write(")")
    cfile.write(");\n")
    cpp.write(");\n")
    if returns_record:
        cfile.write("    return _r;\n")
    cfile.write("}\n\n")
    cpp.write("}\n\n")
    return used_name

def get_iface_version(classname):
    # ISteamClient -> STEAMCLIENT_INTERFACE_VERSION
    defname = "%s_INTERFACE_VERSION" % classname[1:].upper()
    if defname in iface_versions.keys():
        ver = iface_versions[defname]
    else:
        ver = "UNVERSIONED"
    if classname in class_versions.keys() and ver in class_versions[classname]:
        return (ver, True)
    if not classname in class_versions.keys():
        class_versions[classname] = []
    class_versions[classname].append(ver)
    return (ver, False)

def handle_class(sdkver, classnode):
  children = list(classnode.get_children())
  if len(children) == 0:
    return
  (iface_version, already_generated) = get_iface_version(classnode.spelling)
  if already_generated:
    return
  winname = "win%s" % classnode.spelling
  if not winname in generated_c_files:
      generated_c_files.append(winname)
  cppname = "cpp%s_%s" % (classnode.spelling, iface_version)
  generated_cpp_files.append(cppname)

  file_exists = os.path.isfile("%s.c" % winname)
  cfile = open("%s.c" % winname, "a")
  if not file_exists:
    cfile.write("""/* This file is auto-generated, do not edit. */

#include "config.h"
#include "wine/port.h"

#include <stdarg.h>

#include "windef.h"
#include "winbase.h"
#include "wine/debug.h"

#include "cxx.h"

#include "steam_defs.h"

#include "steamclient_private.h"

WINE_DEFAULT_DEBUG_CHANNEL(steamclient);

""")

  cpp = open("%s.cpp" % cppname, "w")
  cpp.write("#include \"steamclient_private.h\"\n")
  cpp.write("#include \"steamworks_sdk_%s/steam_api.h\"\n" % sdkver)
  if not fname == "steam_api.h":
    cpp.write("#include \"steamworks_sdk_%s/%s\"\n" % (sdkver, fname))
  cpp.write("#include \"%s.h\"\n" % cppname)
  cpp.write("#ifdef __cplusplus\nextern \"C\" {\n#endif\n")

  cpp_h = open("%s.h" % cppname, "w")
  cpp_h.write("#ifdef __cplusplus\nextern \"C\" {\n#endif\n")

  winclassname = "win%s_%s" % (classnode.spelling, iface_version)
  cfile.write("#include \"%s.h\"\n\n" % cppname)
  cfile.write("typedef struct __%s {\n" % winclassname)
  cfile.write("    vtable_ptr *vtable;\n")
  cfile.write("    void *linux_side;\n")
  cfile.write("} %s;\n\n" % winclassname)
  methods = []
  protected = True
  for child in children:
    if child.kind == clang.cindex.CursorKind.CXX_METHOD:
       if protected:
          # kind of a hack, won't work if the first method is protected
          methods.append("%s /* protected: %s */" % (methods[0], child.spelling))
       else:
          methods.append(handle_method(cfile, classnode.spelling, winclassname, cppname, child, cpp, cpp_h, methods))
    elif child.kind == clang.cindex.CursorKind.CXX_ACCESS_SPEC_DECL:
       if child.access_specifier == clang.cindex.AccessSpecifier.PROTECTED or \
             child.access_specifier == clang.cindex.AccessSpecifier.PRIVATE:
          protected = True;
       elif child.access_specifier == clang.cindex.AccessSpecifier.PUBLIC:
          protected = False;

  cfile.write("extern vtable_ptr %s_vtable;\n\n" % winclassname)
  cfile.write("#ifndef __GNUC__\n")
  cfile.write("void __asm_dummy_vtables(void) {\n")
  cfile.write("#endif\n")
  cfile.write("    __ASM_VTABLE(%s,\n" % winclassname)
  for method in methods:
    cfile.write("        VTABLE_ADD_FUNC(%s_%s)\n" % (winclassname, method))
  cfile.write("    );\n")
  cfile.write("#ifndef __GNUC__\n")
  cfile.write("}\n")
  cfile.write("#endif\n\n")
  cfile.write("%s *create_%s(void *linux_side)\n{\n" % (winclassname, winclassname))
  cfile.write("    %s *r = HeapAlloc(GetProcessHeap(), 0, sizeof(%s));\n" % (winclassname, winclassname))
  cfile.write("    TRACE(\"-> %p\\n\", r);\n")
  cfile.write("    r->vtable = &%s_vtable;\n" % winclassname)
  cfile.write("    r->linux_side = linux_side;\n")
  cfile.write("    return r;\n}\n\n")

  cpp.write("#ifdef __cplusplus\n}\n#endif\n")
  cpp_h.write("#ifdef __cplusplus\n}\n#endif\n")

  constructors = open("win_constructors.h", "a")
  constructors.write("extern void *create_%s(void *);\n" % winclassname)

  constructors = open("win_constructors_table.dat", "a")
  constructors.write("    {\"%s\", &create_%s},\n" % (iface_version, winclassname))





#clang.cindex.Config.set_library_file("/usr/lib/llvm-3.8/lib/libclang-3.8.so.1");

generated_c_files = []
generated_cpp_files = []

prog = re.compile("^#define\s*(\w*)\s*\"(.*)\"")
for sdkver in sdk_versions:
    iface_versions = {}
    for f in os.listdir("steamworks_sdk_%s" % sdkver):
        x = open("steamworks_sdk_%s/%s" % (sdkver, f), "r")
        for l in x:
            if "INTERFACE_VERSION" in l:
                result = prog.match(l)
                if result:
                    iface, version = result.group(1, 2)
                    iface_versions[iface] = version

    for fname, classes in files:
        # Parse as 32-bit C++
        input_name = "steamworks_sdk_%s/%s" % (sdkver, fname)
        sys.stdout.write("about to parse %s\n" % input_name)
        if not os.path.isfile(input_name):
            continue
        index = clang.cindex.Index.create()
        tu = index.parse(input_name, args=['-x', 'c++', '-m32', '-Isteamworks_sdk_%s/' % sdkver, '-I/usr/lib/clang/3.9.0/include/'])

        diagnostics = list(tu.diagnostics)
        if len(diagnostics) > 0:
            print 'There were parse errors'
            pprint.pprint(diagnostics)
        else:
            children = list(tu.cursor.get_children())
            for child in children:
                if child.kind == clang.cindex.CursorKind.CLASS_DECL and child.displayname in classes:
                    handle_class(sdkver, child)
                if child.displayname in print_sizes:
                    sys.stdout.write("size of %s is %u\n" % (child.displayname, child.type.get_size()))

#todo
m = open("Makefile.in", "a")
for f in generated_c_files:
    m.write("\t%s.c \\\n" % f)
m.write("\nCPP_SRCS = \\\n")
for f in generated_cpp_files:
    m.write("\t%s.cpp \\\n" % f)
