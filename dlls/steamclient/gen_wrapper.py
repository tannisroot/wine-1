#!/usr/bin/python2
import pprint
import sys
import clang.cindex
import os

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
    # header file to parse, classes to generate from that header, addl headers needed for CPP files
    ("isteamclient", ["ISteamClient"], []),
    ("isteamuser", ["ISteamUser"], []),
    ("isteamutils", ["ISteamUtils"], []),
    ("isteamappticket", ["ISteamAppTicket"], ["isteamappticket.h"]),
]

class_versions = {}

def handle_method(classname, winclassname, cppname, method, cpp, cpp_h):
    returns_record = method.result_type.get_canonical().kind == clang.cindex.TypeKind.RECORD
    if returns_record:
        parambytes = 8 #_this + return pointer
    else:
        parambytes = 4 #_this
    for param in list(method.get_children()):
        if param.kind == clang.cindex.CursorKind.PARM_DECL:
            parambytes += param.type.get_size()
    if returns_record:
        f.write("DEFINE_THISCALL_WRAPPER_RECORD(%s_%s, %s)\n" % (winclassname, method.spelling, parambytes))
    else:
        f.write("DEFINE_THISCALL_WRAPPER(%s_%s, %s)\n" % (winclassname, method.spelling, parambytes))
    cpp_h.write("extern ")
    if method.result_type.spelling.startswith("ISteam"):
        f.write("win%s " % (method.result_type.spelling))
        cpp.write("void *")
        cpp_h.write("void *")
    elif returns_record:
        f.write("void ")
        cpp.write("%s " % (method.result_type.spelling))
        cpp_h.write("%s " % (method.result_type.spelling))
    else:
        f.write("%s " % (method.result_type.spelling))
        cpp.write("%s " % (method.result_type.spelling))
        cpp_h.write("%s " % (method.result_type.spelling))
    f.write('__thiscall %s_%s(%s *_this' % (winclassname, method.spelling, winclassname))
    cpp.write("%s_%s(void *linux_side" % (cppname, method.spelling))
    cpp_h.write("%s_%s(void *" % (cppname, method.spelling))
    if returns_record:
        f.write(", %s *_r" % method.result_type.spelling)
    unnamed = 'a'
    for param in list(method.get_children()):
        if param.kind == clang.cindex.CursorKind.PARM_DECL:
            # they don't give names for some fn pointer args, so just void * them since
            # we don't dereference them anyway
            # TODO: probably need to fix this so linux can call into win32 code
            if param.type.kind == clang.cindex.TypeKind.POINTER and param.spelling == "":
                f.write(", void *%s" % unnamed)
                cpp.write(", void *%s" % unnamed)
                cpp_h.write(", void *")
                unnamed = chr(ord(unnamed) + 1)
            else:
                f.write(", %s %s" % (param.type.spelling, param.spelling))
                cpp.write(", %s %s" % (param.type.spelling, param.spelling))
                cpp_h.write(", %s" % (param.type.spelling))
    f.write(")\n{\n")
    cpp.write(")\n{\n")
    cpp_h.write(");\n")
    f.write("    TRACE(\"%p\\n\", _this);\n")
    if method.result_type.kind == clang.cindex.TypeKind.VOID:
        f.write("    ")
        cpp.write("    ")
    elif returns_record:
        f.write("    *_r = ")
        cpp.write("    return ")
    else:
        f.write("    return ")
        cpp.write("    return ")

    should_gen_wrapper = method.result_type.spelling.startswith("ISteam") or \
            method.spelling.startswith("GetISteamGenericInterface")
    if should_gen_wrapper:
        f.write("create_win_interface(pchVersion,\n        ")

    f.write("%s_%s(_this->linux_side" % (cppname, method.spelling))
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
            if param.type.kind == clang.cindex.TypeKind.POINTER and param.spelling == "":
                f.write(", %s" % unnamed)
                cpp.write("%s" % unnamed)
                unnamed = chr(ord(unnamed) + 1)
            else:
                f.write(", %s" % param.spelling)
                cpp.write("%s" % param.spelling)
    if should_gen_wrapper:
        f.write(")")
    f.write(");\n")
    cpp.write(");\n")
    f.write("}\n\n")
    cpp.write("}\n\n")

def get_iface_version(header_path, classname):
    # ISteamClient -> STEAMCLIENT_INTERFACE_VERSION
    defname = "%s_INTERFACE_VERSION" % classname[1:].upper()
    f = open(header_path, "r")
    for l in f:
        if defname in l:
            # pull version out of #define line
            ver = l.split("\"")[1]
            if classname in class_versions.keys() and ver in class_versions[classname]:
                return (ver, True)
            if not classname in class_versions.keys():
                class_versions[classname] = []
            class_versions[classname].append(ver)
            return (ver, False)

def handle_class(sdkver, header_path, addl_headers, classnode):
  children = list(classnode.get_children())
  if len(children) == 0:
    return
  (iface_version, already_generated) = get_iface_version(header_path, classnode.spelling)
  if already_generated:
    return
  cppname = "cpp%s_%s" % (classnode.spelling, iface_version)
  m = open("Makefile.in", "a")
  m.write("\t%s.cpp \\\n" % cppname)

  cpp = open("%s.cpp" % cppname, "w")
  cpp.write("#include \"steamclient_private.h\"\n")
  cpp.write("#include \"steamworks_sdk_%s/steam_api.h\"\n" % sdkver)
  for hdr in addl_headers:
    cpp.write("#include \"steamworks_sdk_%s/%s\"\n" % (sdkver, hdr))
  cpp.write("#include \"%s.h\"\n" % cppname)
  cpp.write("#ifdef __cplusplus\nextern \"C\" {\n#endif\n")

  cpp_h = open("%s.h" % cppname, "w")
  cpp_h.write("#ifdef __cplusplus\nextern \"C\" {\n#endif\n")

  winclassname = "win%s_%s" % (classnode.spelling, iface_version)
  f.write("#include \"%s.h\"\n\n" % cppname)
  f.write("typedef struct __%s {\n" % winclassname)
  f.write("    vtable_ptr *vtable;\n")
  f.write("    void *linux_side;\n")
  f.write("} %s;\n\n" % winclassname)
  methods = []
  protected = True
  for child in children:
    if child.kind == clang.cindex.CursorKind.CXX_METHOD:
       if protected:
          # kind of a hack, won't work if the first method is protected
          methods.append("%s /* protected: %s */" % (methods[0], child.spelling))
       else:
          handle_method(classnode.spelling, winclassname, cppname, child, cpp, cpp_h)
          methods.append(child.spelling)
    elif child.kind == clang.cindex.CursorKind.CXX_ACCESS_SPEC_DECL:
       if child.access_specifier == clang.cindex.AccessSpecifier.PROTECTED or \
             child.access_specifier == clang.cindex.AccessSpecifier.PRIVATE:
          protected = True;
       elif child.access_specifier == clang.cindex.AccessSpecifier.PUBLIC:
          protected = False;

  f.write("extern vtable_ptr %s_vtable;\n\n" % winclassname)
  f.write("#ifndef __GNUC__\n")
  f.write("void __asm_dummy_vtables(void) {\n")
  f.write("#endif\n")
  f.write("    __ASM_VTABLE(%s,\n" % winclassname)
  for method in methods:
    f.write("        VTABLE_ADD_FUNC(%s_%s)\n" % (winclassname, method))
  f.write("    );\n")
  f.write("#ifndef __GNUC__\n")
  f.write("}\n")
  f.write("#endif\n\n")
  f.write("%s *create_%s(void *linux_side)\n{\n" % (winclassname, winclassname))
  f.write("    %s *r = HeapAlloc(GetProcessHeap(), 0, sizeof(%s));\n" % (winclassname, winclassname))
  f.write("    TRACE(\"-> %p\\n\", r);\n")
  f.write("    r->vtable = &%s_vtable;\n" % winclassname)
  f.write("    r->linux_side = linux_side;\n")
  f.write("    return r;\n}\n\n")

  cpp.write("#ifdef __cplusplus\n}\n#endif\n")
  cpp_h.write("#ifdef __cplusplus\n}\n#endif\n")

  constructors = open("win_constructors.h", "a")
  constructors.write("extern void *create_%s(void *);\n" % winclassname)

  constructors = open("win_constructors_table.dat", "a")
  constructors.write("    {\"%s\", &create_%s},\n" % (iface_version, winclassname))

def visitor(sdkver, header_path, addl_headers, f, cursor, classes):
  children = list(cursor.get_children())
  for child in children:
    if child.kind == clang.cindex.CursorKind.CLASS_DECL and child.displayname in classes:
      handle_class(sdkver, header_path, addl_headers, child)

#clang.cindex.Config.set_library_file("/usr/lib/llvm-3.8/lib/libclang-3.8.so.1");

for sdkver in sdk_versions:
    for fname, classes, addl_headers in files:
        # Parse as 32-bit C++
        input_name = "steamworks_sdk_%s/%s.h" % (sdkver, fname)
        if not os.path.isfile(input_name):
            continue
        sys.stdout.write("about to parse %s\n" % input_name)
        index = clang.cindex.Index.create()
        tu = index.parse(input_name, args=['-x', 'c++', '-m32', '-Isteamworks_sdk_%s/' % sdkver])
    
        diagnostics = list(tu.diagnostics)
        if len(diagnostics) > 0:
            print 'There were parse errors'
            pprint.pprint(diagnostics)
        else:
            output_name = "win_%s.c" % fname
            file_exists = os.path.isfile(output_name)
            f = open("win_%s.c" % fname, "a")
            if not file_exists:
                f.write("""/* This file is auto-generated, do not edit. */

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
            visitor(sdkver, input_name, addl_headers, f, tu.cursor, classes)
