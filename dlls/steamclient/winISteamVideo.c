/* This file is auto-generated, do not edit. */

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

#include "cppISteamVideo_STEAMVIDEO_INTERFACE_V001.h"

typedef struct __winISteamVideo_STEAMVIDEO_INTERFACE_V001 {
    vtable_ptr *vtable;
    void *linux_side;
} winISteamVideo_STEAMVIDEO_INTERFACE_V001;

DEFINE_THISCALL_WRAPPER(winISteamVideo_STEAMVIDEO_INTERFACE_V001_GetVideoURL, 8)
void __thiscall winISteamVideo_STEAMVIDEO_INTERFACE_V001_GetVideoURL(winISteamVideo_STEAMVIDEO_INTERFACE_V001 *_this, AppId_t unVideoAppID)
{
    TRACE("%p\n", _this);
    cppISteamVideo_STEAMVIDEO_INTERFACE_V001_GetVideoURL(_this->linux_side, unVideoAppID);
}

DEFINE_THISCALL_WRAPPER(winISteamVideo_STEAMVIDEO_INTERFACE_V001_IsBroadcasting, 8)
bool __thiscall winISteamVideo_STEAMVIDEO_INTERFACE_V001_IsBroadcasting(winISteamVideo_STEAMVIDEO_INTERFACE_V001 *_this, int * pnNumViewers)
{
    TRACE("%p\n", _this);
    return cppISteamVideo_STEAMVIDEO_INTERFACE_V001_IsBroadcasting(_this->linux_side, pnNumViewers);
}

extern vtable_ptr winISteamVideo_STEAMVIDEO_INTERFACE_V001_vtable;

#ifndef __GNUC__
void __asm_dummy_vtables(void) {
#endif
    __ASM_VTABLE(winISteamVideo_STEAMVIDEO_INTERFACE_V001,
        VTABLE_ADD_FUNC(winISteamVideo_STEAMVIDEO_INTERFACE_V001_GetVideoURL)
        VTABLE_ADD_FUNC(winISteamVideo_STEAMVIDEO_INTERFACE_V001_IsBroadcasting)
    );
#ifndef __GNUC__
}
#endif

winISteamVideo_STEAMVIDEO_INTERFACE_V001 *create_winISteamVideo_STEAMVIDEO_INTERFACE_V001(void *linux_side)
{
    winISteamVideo_STEAMVIDEO_INTERFACE_V001 *r = HeapAlloc(GetProcessHeap(), 0, sizeof(winISteamVideo_STEAMVIDEO_INTERFACE_V001));
    TRACE("-> %p\n", r);
    r->vtable = &winISteamVideo_STEAMVIDEO_INTERFACE_V001_vtable;
    r->linux_side = linux_side;
    return r;
}

