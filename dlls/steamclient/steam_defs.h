
typedef int bool;

typedef int EAccountType;
typedef int EUniverse;
typedef int ENotificationPosition;
typedef int ESteamAPICallFailure;
typedef int EGamepadTextInputMode;
typedef int EGamepadTextInputLineMode;
typedef int EVoiceResult;
typedef int EBeginAuthSessionResult;
typedef int EUserHasLicenseForAppResult;

/* these are 64-bit PODs */
typedef struct CSteamID { unsigned char a[8]; } CSteamID;
typedef struct CGameID { unsigned char a[8]; } CGameID;

typedef int ISteamUser; /* TODO */
typedef int ISteamGameServer; /* TODO */
typedef int ISteamFriends; /* TODO */
typedef int ISteamUtils; /* TODO */
typedef int ISteamMatchmaking; /* TODO */
typedef int ISteamMatchmakingServers; /* TODO */
typedef int ISteamUserStats; /* TODO */
typedef int ISteamGameServerStats; /* TODO */
typedef int ISteamApps; /* TODO */
typedef int ISteamX; /* TODO */

/* FIXME: we don't care about fn pointer types, just pass 'em through */
typedef void *SteamAPI_CheckCallbackRegistered_t;
typedef void *SteamAPIWarningMessageHook_t;
typedef void *SteamAPI_PostAPIResultInProcess_t;

typedef unsigned char uint8;
typedef unsigned char uint8;
typedef signed char int8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long long int64;
typedef unsigned long long uint64;
typedef int64 lint64;
typedef uint64 ulint64;
typedef uint8 Salt_t[8];
typedef uint64 GID_t;
typedef uint64 JobID_t;
typedef GID_t TxnID_t;
typedef uint32 PackageId_t;
typedef uint32 BundleId_t;
typedef uint32 AppId_t;
typedef uint64 AssetClassId_t;
typedef uint32 PhysicalItemId_t;
typedef uint32 DepotId_t;
typedef uint32 RTime32;
typedef uint32 CellID_t;
typedef uint64 SteamAPICall_t;
typedef uint32 AccountID_t;
typedef uint32 PartnerId_t;
typedef uint64 ManifestId_t;
typedef uint32 HAuthTicket;
typedef void * BREAKPAD_HANDLE;
typedef char compile_time_assert_type[1];
typedef int32 HSteamPipe;
typedef int32 HSteamUser;
typedef int16 FriendsGroupID_t;
typedef void * HServerListRequest;
typedef int HServerQuery;
typedef uint64 UGCHandle_t;
typedef uint64 PublishedFileUpdateHandle_t;
