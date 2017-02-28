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

#include "cppISteamInventory_STEAMINVENTORY_INTERFACE_V001.h"

typedef struct __winISteamInventory_STEAMINVENTORY_INTERFACE_V001 {
    vtable_ptr *vtable;
    void *linux_side;
} winISteamInventory_STEAMINVENTORY_INTERFACE_V001;

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetResultStatus, 8)
EResult __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetResultStatus(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t resultHandle)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetResultStatus(_this->linux_side, resultHandle);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetResultItems, 16)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetResultItems(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t resultHandle, SteamItemDetails_t * pOutItemsArray, uint32 * punOutItemsArraySize)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetResultItems(_this->linux_side, resultHandle, pOutItemsArray, punOutItemsArraySize);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetResultTimestamp, 8)
uint32 __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetResultTimestamp(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t resultHandle)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetResultTimestamp(_this->linux_side, resultHandle);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_CheckResultSteamID, 16)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_CheckResultSteamID(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t resultHandle, CSteamID steamIDExpected)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_CheckResultSteamID(_this->linux_side, resultHandle, steamIDExpected);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_DestroyResult, 8)
void __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_DestroyResult(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t resultHandle)
{
    TRACE("%p\n", _this);
    cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_DestroyResult(_this->linux_side, resultHandle);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetAllItems, 8)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetAllItems(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t * pResultHandle)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetAllItems(_this->linux_side, pResultHandle);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetItemsByID, 16)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetItemsByID(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t * pResultHandle, const SteamItemInstanceID_t * pInstanceIDs, uint32 unCountInstanceIDs)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetItemsByID(_this->linux_side, pResultHandle, pInstanceIDs, unCountInstanceIDs);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_SerializeResult, 16)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_SerializeResult(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t resultHandle, void * pOutBuffer, uint32 * punOutBufferSize)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_SerializeResult(_this->linux_side, resultHandle, pOutBuffer, punOutBufferSize);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_DeserializeResult, 17)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_DeserializeResult(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t * pOutResultHandle, const void * pBuffer, uint32 unBufferSize, bool bRESERVED_MUST_BE_FALSE)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_DeserializeResult(_this->linux_side, pOutResultHandle, pBuffer, unBufferSize, bRESERVED_MUST_BE_FALSE);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GenerateItems, 20)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GenerateItems(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t * pResultHandle, const SteamItemDef_t * pArrayItemDefs, const uint32 * punArrayQuantity, uint32 unArrayLength)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_GenerateItems(_this->linux_side, pResultHandle, pArrayItemDefs, punArrayQuantity, unArrayLength);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GrantPromoItems, 8)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GrantPromoItems(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t * pResultHandle)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_GrantPromoItems(_this->linux_side, pResultHandle);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_AddPromoItem, 12)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_AddPromoItem(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t * pResultHandle, SteamItemDef_t itemDef)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_AddPromoItem(_this->linux_side, pResultHandle, itemDef);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_AddPromoItems, 16)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_AddPromoItems(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t * pResultHandle, const SteamItemDef_t * pArrayItemDefs, uint32 unArrayLength)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_AddPromoItems(_this->linux_side, pResultHandle, pArrayItemDefs, unArrayLength);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_ConsumeItem, 20)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_ConsumeItem(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t * pResultHandle, SteamItemInstanceID_t itemConsume, uint32 unQuantity)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_ConsumeItem(_this->linux_side, pResultHandle, itemConsume, unQuantity);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_ExchangeItems, 32)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_ExchangeItems(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t * pResultHandle, const SteamItemDef_t * pArrayGenerate, const uint32 * punArrayGenerateQuantity, uint32 unArrayGenerateLength, const SteamItemInstanceID_t * pArrayDestroy, const uint32 * punArrayDestroyQuantity, uint32 unArrayDestroyLength)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_ExchangeItems(_this->linux_side, pResultHandle, pArrayGenerate, punArrayGenerateQuantity, unArrayGenerateLength, pArrayDestroy, punArrayDestroyQuantity, unArrayDestroyLength);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_TransferItemQuantity, 28)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_TransferItemQuantity(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t * pResultHandle, SteamItemInstanceID_t itemIdSource, uint32 unQuantity, SteamItemInstanceID_t itemIdDest)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_TransferItemQuantity(_this->linux_side, pResultHandle, itemIdSource, unQuantity, itemIdDest);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_SendItemDropHeartbeat, 4)
void __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_SendItemDropHeartbeat(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this)
{
    TRACE("%p\n", _this);
    cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_SendItemDropHeartbeat(_this->linux_side);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_TriggerItemDrop, 12)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_TriggerItemDrop(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t * pResultHandle, SteamItemDef_t dropListDefinition)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_TriggerItemDrop(_this->linux_side, pResultHandle, dropListDefinition);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_TradeItems, 40)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_TradeItems(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamInventoryResult_t * pResultHandle, CSteamID steamIDTradePartner, const SteamItemInstanceID_t * pArrayGive, const uint32 * pArrayGiveQuantity, uint32 nArrayGiveLength, const SteamItemInstanceID_t * pArrayGet, const uint32 * pArrayGetQuantity, uint32 nArrayGetLength)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_TradeItems(_this->linux_side, pResultHandle, steamIDTradePartner, pArrayGive, pArrayGiveQuantity, nArrayGiveLength, pArrayGet, pArrayGetQuantity, nArrayGetLength);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_LoadItemDefinitions, 4)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_LoadItemDefinitions(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_LoadItemDefinitions(_this->linux_side);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetItemDefinitionIDs, 12)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetItemDefinitionIDs(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamItemDef_t * pItemDefIDs, uint32 * punItemDefIDsArraySize)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetItemDefinitionIDs(_this->linux_side, pItemDefIDs, punItemDefIDsArraySize);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetItemDefinitionProperty, 20)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetItemDefinitionProperty(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, SteamItemDef_t iDefinition, const char * pchPropertyName, char * pchValueBuffer, uint32 * punValueBufferSizeOut)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetItemDefinitionProperty(_this->linux_side, iDefinition, pchPropertyName, pchValueBuffer, punValueBufferSizeOut);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_RequestEligiblePromoItemDefinitionsIDs, 12)
SteamAPICall_t __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_RequestEligiblePromoItemDefinitionsIDs(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, CSteamID steamID)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_RequestEligiblePromoItemDefinitionsIDs(_this->linux_side, steamID);
}

DEFINE_THISCALL_WRAPPER(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetEligiblePromoItemDefinitionIDs, 20)
bool __thiscall winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetEligiblePromoItemDefinitionIDs(winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *_this, CSteamID steamID, SteamItemDef_t * pItemDefIDs, uint32 * punItemDefIDsArraySize)
{
    TRACE("%p\n", _this);
    return cppISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetEligiblePromoItemDefinitionIDs(_this->linux_side, steamID, pItemDefIDs, punItemDefIDsArraySize);
}

extern vtable_ptr winISteamInventory_STEAMINVENTORY_INTERFACE_V001_vtable;

#ifndef __GNUC__
void __asm_dummy_vtables(void) {
#endif
    __ASM_VTABLE(winISteamInventory_STEAMINVENTORY_INTERFACE_V001,
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetResultStatus)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetResultItems)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetResultTimestamp)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_CheckResultSteamID)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_DestroyResult)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetAllItems)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetItemsByID)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_SerializeResult)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_DeserializeResult)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GenerateItems)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GrantPromoItems)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_AddPromoItem)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_AddPromoItems)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_ConsumeItem)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_ExchangeItems)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_TransferItemQuantity)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_SendItemDropHeartbeat)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_TriggerItemDrop)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_TradeItems)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_LoadItemDefinitions)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetItemDefinitionIDs)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetItemDefinitionProperty)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_RequestEligiblePromoItemDefinitionsIDs)
        VTABLE_ADD_FUNC(winISteamInventory_STEAMINVENTORY_INTERFACE_V001_GetEligiblePromoItemDefinitionIDs)
    );
#ifndef __GNUC__
}
#endif

winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *create_winISteamInventory_STEAMINVENTORY_INTERFACE_V001(void *linux_side)
{
    winISteamInventory_STEAMINVENTORY_INTERFACE_V001 *r = HeapAlloc(GetProcessHeap(), 0, sizeof(winISteamInventory_STEAMINVENTORY_INTERFACE_V001));
    TRACE("-> %p\n", r);
    r->vtable = &winISteamInventory_STEAMINVENTORY_INTERFACE_V001_vtable;
    r->linux_side = linux_side;
    return r;
}

