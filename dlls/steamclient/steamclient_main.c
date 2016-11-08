#include "config.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <limits.h>

#include "windef.h"
#include "winbase.h"
#include "wine/debug.h"
#include "wine/library.h"

#include "steamclient_private.h"

WINE_DEFAULT_DEBUG_CHANNEL(steamclient);

BOOL WINAPI DllMain(HINSTANCE instance, DWORD reason, void *reserved)
{
    TRACE("(%p, %u, %p)\n", instance, reason, reserved);

    switch (reason)
    {
        case DLL_WINE_PREATTACH:
            return FALSE;    /* prefer native version */
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(instance);
            break;
    }

    return TRUE;
}

#include "win_constructors.h"

static const struct {
    const char *iface_version;
    void *(*ctor)(void *);
} constructors[] = {
#include "win_constructors_table.dat"
};

void *create_win_interface(const char *name, void *linux_side)
{
    int i;

    if(!linux_side)
        return NULL;

    for(i = 0; i < sizeof(constructors) / sizeof(*constructors); ++i){
        if(!strcmp(name, constructors[i].iface_version))
            return constructors[i].ctor(linux_side);
    }

    ERR("Don't recognize interface name: %s\n", name);

    return NULL;
}

static void *steamclient_lib;
static void *(*steamclient_factory)(const char *name, int *return_code);

void *WINAPI CreateInterface(const char *name, int *return_code)
{
    TRACE("name: %s, return_code: %p\n", name, return_code);

    if(!steamclient_lib){
        char path[PATH_MAX];
#ifdef _WIN64
        snprintf(path, PATH_MAX, "%s/.steam/sdk64/steamclient.so", getenv("HOME"));
#else
        snprintf(path, PATH_MAX, "%s/.steam/sdk32/steamclient.so", getenv("HOME"));
#endif
        steamclient_lib = wine_dlopen(path, RTLD_NOW, NULL, 0);
        if(!steamclient_lib){
            ERR("unable to load steamclient.so\n");
            return NULL;
        }

        steamclient_factory = wine_dlsym(steamclient_lib, "CreateInterface", NULL, 0);
        if(!steamclient_factory){
            ERR("unable to load class factory method\n");
            return NULL;
        }
    }

    return create_win_interface(name, steamclient_factory(name, return_code));
}
