#include "config.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>
#include <limits.h>
#include <stdint.h>

#include "windef.h"
#include "winbase.h"
#include "wine/debug.h"
#include "wine/library.h"
#include "steam_defs.h"

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
static void *(*steamclient_CreateInterface)(const char *name, int *return_code);
static bool (*steamclient_BGetCallback)(HSteamPipe a, CallbackMsg_t *b, int32 *c);
static bool (*steamclient_GetAPICallResult)(HSteamPipe, SteamAPICall_t, void *, int, int, bool *);
static bool (*steamclient_FreeLastCallback)(HSteamPipe);

static int load_steamclient(void)
{
    char path[PATH_MAX];

    if(steamclient_lib)
        return 1;

#ifdef _WIN64
    snprintf(path, PATH_MAX, "%s/.steam/sdk64/steamclient.so", getenv("HOME"));
#else
    snprintf(path, PATH_MAX, "%s/.steam/sdk32/steamclient.so", getenv("HOME"));
#endif
    steamclient_lib = wine_dlopen(path, RTLD_NOW, NULL, 0);
    if(!steamclient_lib){
        ERR("unable to load steamclient.so\n");
        return 0;
    }

    steamclient_CreateInterface = wine_dlsym(steamclient_lib, "CreateInterface", NULL, 0);
    if(!steamclient_CreateInterface){
        ERR("unable to load CreateInterface method\n");
        return 0;
    }

    steamclient_BGetCallback = wine_dlsym(steamclient_lib, "Steam_BGetCallback", NULL, 0);
    if(!steamclient_BGetCallback){
        ERR("unable to load BGetCallback method\n");
        return 0;
    }

    steamclient_GetAPICallResult = wine_dlsym(steamclient_lib, "Steam_GetAPICallResult", NULL, 0);
    if(!steamclient_GetAPICallResult){
        ERR("unable to load GetAPICallResult method\n");
        return 0;
    }

    steamclient_FreeLastCallback = wine_dlsym(steamclient_lib, "Steam_FreeLastCallback", NULL, 0);
    if(!steamclient_FreeLastCallback){
        ERR("unable to load FreeLastCallback method\n");
        return 0;
    }

    return 1;
}

void *CDECL CreateInterface(const char *name, int *return_code)
{
    TRACE("name: %s, return_code: %p\n", name, return_code);

    if(!load_steamclient())
        return NULL;

    return create_win_interface(name, steamclient_CreateInterface(name, return_code));
}

bool CDECL Steam_BGetCallback(HSteamPipe pipe, CallbackMsg_t *msg, int32 *ignored)
{
    TRACE("%u, %p, %p\n", pipe, msg, ignored);

    if(!load_steamclient())
        return 0;

    return steamclient_BGetCallback(pipe, msg, ignored);
}

bool CDECL Steam_GetAPICallResult(HSteamPipe pipe, SteamAPICall_t call,
        void *callback, int callback_len, int cb_expected, bool *failed)
{
    TRACE("%u, x, %p, %u, %u, %p\n", pipe, callback, callback_len, cb_expected, failed);

    if(!load_steamclient())
        return 0;

    return steamclient_GetAPICallResult(pipe, call, callback, callback_len, cb_expected, failed);
}

bool CDECL Steam_FreeLastCallback(HSteamPipe pipe)
{
    TRACE("%u\n", pipe);

    if(!load_steamclient())
        return 0;

    return steamclient_FreeLastCallback(pipe);
}
