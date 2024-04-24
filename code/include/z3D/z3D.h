#ifndef _Z3D_H_
#define _Z3D_H_

#include "z3Dactor.h"
#include "z3Dvec.h"
// #include "z3Dequipment.h"
#include "z3Dcutscene.h"
#include "z3Ditem.h"
#include "z3Dmath.h"

// #include "hid.h"

#define TRUE 1
#define FALSE 0

typedef struct {
    /* 0x00 */ u8 buttonItems[5]; // B,Y,X,I,II
    /* 0x05 */ u8 buttonSlots[4]; // Y,X,I,II
    /* 0x0A */ u16 equipment;
} ItemEquips; // size = 0x0C

typedef struct {
    /* 0x00 */ u32 chest;
    /* 0x04 */ u32 swch;
    /* 0x08 */ u32 clear;
    /* 0x0C */ u32 collect;
    /* 0x10 */ u32 unk;
    /* 0x14 */ u32 rooms1;
    /* 0x18 */ u32 rooms2;
} SaveSceneFlags; // size = 0x1C

typedef struct {
    /* 0x00 */ s16 scene;
    /* 0x02 */ Vec3s pos;
    /* 0x08 */ s16 angle;
} HorseData; // size = 0x0A

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ s16 yaw;
    /* 0x0E */ s16 playerParams;
    /* 0x10 */ s16 entranceIndex;
    /* 0x12 */ u8 roomIndex;
    /* 0x13 */ u8 data;
    /* 0x14 */ u32 tempSwchFlags;
    /* 0x18 */ u32 tempCollectFlags;
} RespawnData; // size = 0x1C

typedef enum {
    /* 0x00 */ RESPAWN_MODE_DOWN,   /* Normal Void Outs */
    /* 0x01 */ RESPAWN_MODE_RETURN, /* Grotto Returnpoints */
    /* 0x02 */ RESPAWN_MODE_TOP     /* Farore's Wind */
} RespawnMode;

typedef enum {
    /* 0x00 */ BTN_ENABLED,
    /* 0xFF */ BTN_DISABLED = 0xFF
} ButtonStatus;

// Save Context (ram start: 0x00587958)
typedef struct {
    /* 0x0000 */ s32 entranceIndex;
    /* 0x0004 */ s32 linkAge; // 0: Adult; 1: Child
    /* 0x0008 */ s32 cutsceneIndex;
    /* 0x000C */ u16 dayTime; // "zelda_time"
    /* 0x000E */ u8 masterQuestFlag;
    /* 0x000F */ u8 motionControlSetting;
    /* 0x0010 */ s32 nightFlag;
    /* 0x0014 */ s32 unk_14;
    /* 0x0018 */ s32 unk_18;
    /* 0x001C */ s16 playerName[0x8];
    /* 0x002C */ u8 playerNameLength;
    /* 0x002D */ u8 zTargetingSetting;
    /* 0x002E */ s16 unk_2E;
    /* 0x0030 */ char newf[6]; // string "ZELDAZ"
    /* 0x0036 */ u16 saveCount;
    /* 0x0038 */ char unk_38[0x000A];
    /* 0x0042 */ u16 healthCapacity; // "max_life"
    /* 0x0044 */ s16 health;         // "now_life"
    /* 0x0046 */ s8 magicLevel;
    /* 0x0047 */ s8 magic;
    /* 0x0048 */ s16 rupees;
    /* 0x004A */ u16 bgsHitsLeft;
    /* 0x004C */ u16 naviTimer;
    /* 0x004E */ u8 magicAcquired;
    /* 0x004F */ char unk_4F[0x0001];
    /* 0x0050 */ u8 doubleMagic;
    /* 0x0051 */ u8 doubleDefense;
    /* 0x0052 */ s8 bgsFlag;
    /* 0x0054 */ ItemEquips childEquips;
    /* 0x0060 */ ItemEquips adultEquips;
    /* 0x006C */ char unk_6C[0x0012];
    /* 0x007E */ u16 sceneIndex;
    /* 0x0080 */ ItemEquips equips;
    /* 0x008C */ u8 items[26];
    /* 0x00A6 */ s8 ammo[15];
    /* 0x00B5 */ u8 magic_beans_available; // counts bought
    /* 0x00B6 */ u16 equipment;            // bits: swords 0-3, shields 4-6, tunics 8-10, boots 12-14
    /* 0x00B8 */ u32 upgrades;   // bits: quiver 0-2, bombs 3-5, strength 6-8, dive 9-11, wallet 12-13, seeds 14-16,
                                 // sticks 17-19, nuts 20-22
    /* 0x00BC */ u32 questItems; // bits: medallions 0-5, warp songs 6-11, songs 12-17, stones 18-20, shard 21, token
                                 // 22, skull 23, heart pieces 24-31
    /* 0x00C0 */ u8 dungeonItems[20]; // bits: boss key 0, compass 1, map 2
    /* 0x00D4 */ s8 dungeonKeys[19];
    /* 0x00E7 */ char unk_E7[0x0001]; // in oot: defenseHearts. seems not here.
    /* 0x00E8 */ s16 gsTokens;
    /* 0x00EC */ SaveSceneFlags sceneFlags[124];
    struct {
        /* 0x0E7C */ Vec3i pos;
        /* 0x0E88 */ s32 yaw;
        /* 0x0E8C */ s32 playerParams;
        /* 0x0E90 */ s32 entranceIndex;
        /* 0x0E94 */ s32 roomIndex;
        /* 0x0E98 */ s32 set;
        /* 0x0E9C */ s32 tempSwchFlags;
        /* 0x0EA0 */ s32 tempCollectFlags;
    } fw;
    /* 0x0EA4 */ char unk_EA4[0x0010];
    /* 0x0EB4 */ u8 gsFlags[22];       // due to reordering, array is smaller
    /* 0x0ECA */ char unk_ECA[0x0006]; // the extra two bytes move here
    /* 0x0ED0 */ u32 unk_ED0;          // horseback archery highscore?
    /* 0x0ED4 */ u32 bigPoePoints;     // number of big poes sold * 100
    struct {
        /* 0x0ED4 */ u8 recordFishChild; // seems to be unique ID of fish, this is copied into adult value if player has
                                         // not yet fished as adult
        /* 0x0ED5 */ u8 flags; // bits: 0 - ever fished as child, 1 - ever fished as adult, 2 - caught record as child,
                               // 3 - caught record as adult
        /* 0x0ED6 */ u8 timesPaidToFish;
        /* 0x0ED7 */ u8 recordFishAdult; // seems to be unique ID of fish
    } fishingStats;
    /* 0x0EDC */ u32 unk_EDC; // horse race record time?
    /* 0x0EE0 */ u32 unk_EE0; // marathon race record time?
    /* 0x0EE4 */ char unk_EE4[0x0008];
    /* 0x0EEC */ u16 eventChkInf[14]; // "event_chk_inf"
    /* 0x0F08 */ u16 itemGetInf[4];   // "item_get_inf"
    /* 0x0F10 */ u16 infTable[30];    // "inf_table"
    /* 0x0F4C */ char unk_F34[0x0004];
    /* 0x0F50 */ u32 worldMapAreaData; // "area_arrival"
    /* 0x0F54 */ char unk_F54[0x0410]; // TODO: scarecrow's song
    /* 0x1364 */ HorseData horseData;
    /* 0x136E */ char unk_136E[0x0002];
    /* 0x1370 */ u8 itemSlotDataRecords[26];
    /* 0x138A */ u8 itemMenuChild[24];
    /* 0x13A2 */ u8 itemMenuAdult[24];
    /* 0x13BA */ char unk_13BA[0x0002];
    struct {
        /* 0x13BC */ u32 year;
        /* 0x13C0 */ u32 month;
        /* 0x13C4 */ u32 day;
        /* 0x13C8 */ u32 hour;
        /* 0x13CC */ u32 minute;
    } saveTime;
    /* 0x13D0 */ char unk_13D0[0x0004];
    /* 0x13D4 */ u8 otherNewEventFlags; // Club Moblin cutscene and Sheikah Stone Navi message
    /* 0x13D5 */ char unk_13D5[0x0003];
    /* 0x13D8 */ u8 cameraControlSetting;
    /* 0x13D9 */ char unk_13D9[0x0077];
    /* 0x1450 */ u32 bossBattleVictories[9];
    /* 0x1474 */ u32 bossBattleScores[9];
    /* 0x1498 */ char unk_1498[0x0040]; // sheikah stone flags?
    /* 0x14D8 */ u16 checksum;          // "check_sum"
    /* 0x14DC */ s32 fileNum;           // "file_no"
    /* 0x14E0 */ char unk_14E0[0x0004];
    /* 0x14E4 */ s32 gameMode;
    /* 0x14E8 */ s32 sceneSetupIndex;
    /* 0x14EC */ s32 respawnFlag;        // "restart_flag"
    /* 0x14F0 */ RespawnData respawn[3]; // "restart_data"
    /* 0x1544 */ char unk_1544[0x000E];
    /* 0x1552 */ s16 nayrusLoveTimer;
    /* 0x1554 */ char unk_1554[0x0008];
    /* 0x155C */ s16 rupeeAccumulator;
    /* 0x155E */ s16 timer1State;
    /* 0x1560 */ s16 timer1Value;
    /* 0x1562 */ s16 timer2State;
    /* 0x1564 */ s16 timer2Value;
    /* 0x1566 */ s16 timerX[2]; // changing these doesn't seem to actually move the timer?
    /* 0x156A */ s16 timerY[2]; // changing these doesn't seem to actually move the timer?
    /* 0x156E */ u8 nightSeqIndex;
    /* 0x156F */ u8 buttonStatus[5];
    /* 0x1574 */ char unk_1574[0x000B];
    /* 0x1580 */ s16 magicState;
    /* 0x1582 */ char unk_1582[0x0002];
    /* 0x1584 */ u16 magicMeterSize;
    /* 0x1586 */ char unk_1586[0x0002];
    /* 0x1588 */ s16 magicTarget;
    /* 0x158A */ u16 eventInf[4];
    /* 0x1592 */ u16 dungeonIndex;
    /* 0x1594 */ char unk_1594[0x000C];
    /* 0x15A0 */ u16 nextCutsceneIndex;
    /* 0x15A2 */ u8 cutsceneTrigger;
    /* 0x15A3 */ u8 chamberCutsceneNum;
    /* 0x15A4 */ u16 nextDayTime; // "next_zelda_time"
    /* 0x15A6 */ u8 transFadeDuration;
    /* 0x15A7 */ u8 transWipeSpeed;
    /* 0x15A8 */ u16 skyboxTime;
    /* 0x15AA */ u8 dogIsLost;
    /* 0x15AB */ u8 nextTransition;
    /* 0x15AC */ char unk_15AC[0x006];
    /* 0x15B2 */ s16 healthAccumulator;

    // stuff below is from z64.h
    /* skipped over */
    // /* 0x0022 */ s16          deaths;
    // /* 0x002C */ s16          n64ddFlag;
    // /* 0x0072 */ char         unk_72[0x0002];
    // /* 0x00CF */ s8           defenseHearts;
    // /* 0x0F3C */ char         unk_F3C[0x040C];
    // /* 0x13BC */ char         unk_13BC[0x0008];
    // /* 0x13C4 */ s16          dogParams;
    // /* 0x13C6 */ char         unk_13C6[0x0001];
    // /* 0x13C7 */ u8           unk_13C7;

    /* still to compare */
    // /* 0x13CA */ char         unk_13CA[0x0002];

    // /* 0x13DE */ char         unk_13DE[0x0002];
    // /* 0x13E0 */ u8           seqIndex;
    // /* 0x13E1 */ u8           nightSeqIndex;
    // /* 0x13E2 */ u8           buttonStatus[5];
    // /* 0x13E7 */ u8           unk_13E7;
    // /* 0x13E8 */ u16          unk_13E8; // alpha type?
    // /* 0x13EA */ u16          unk_13EA; // also alpha type?
    // /* 0x13EC */ u16          unk_13EC; // alpha type counter?
    // /* 0x13EE */ u16          unk_13EE; // previous alpha type?
    // /* 0x13F0 */ s16          unk_13F0;
    // /* 0x13F2 */ s16          unk_13F2;
    // /* 0x13F4 */ s16          unk_13F4;
    // /* 0x13F6 */ s16          unk_13F6;
    // /* 0x13F8 */ s16          unk_13F8;
    // /* 0x13FA */ u16          eventInf[4]; // "event_inf"
    // /* 0x1404 */ u16          minigameState;
    // /* 0x1406 */ u16          minigameScore; // "yabusame_total"
    // /* 0x1408 */ char         unk_1408[0x0001];
    // /* 0x1409 */ u8           language;
    // /* 0x140A */ u8           audioSetting;
    // /* 0x140B */ char         unk_140B[0x0001];
    // /* 0x140C */ u8           zTargetingSetting; // 0: Switch; 1: Hold
    // /* 0x140E */ u16          unk_140E; // bgm related
    // /* 0x1410 */ u8           unk_1410;
    // /* 0x1411 */ u8           unk_1411;
    // /* 0x1412 */ u16          nextCutsceneIndex;
    // /* 0x1414 */ u8           cutsceneTrigger;
    // /* 0x1415 */ u8           chamberCutsceneNum;
    // /* 0x1416 */ u16          nextDayTime; // "next_zelda_time"
    // /* 0x1418 */ u8           fadeDuration;
    // /* 0x1419 */ u8           unk_1419; // transition related
    // /* 0x141A */ u16          environmentTime;
    // /* 0x141C */ u8           dogIsLost;
    // /* 0x141D */ u8           nextTransition;
    // /* 0x141E */ char         unk_141E[0x0002];
    // /* 0x1420 */ s16          worldMapArea;
    // /* 0x1422 */ s16          unk_1422; // day time related
} SaveContext; // size = 0x15C4

typedef struct GraphicsContext GraphicsContext; // TODO
typedef struct GlobalContext GlobalContext;
typedef struct {
    /* 0x000 */ char unk_000[0x080];
    /* 0x080 */ Vec3f at;
    /* 0x08C */ Vec3f eye;
    /* 0x098 */ Vec3f up;
    /* 0x0A4 */ Vec3f eyeNext;
    /* 0x0B0 */ Vec3f skyboxOffset;
    /* 0x0BC */ char unk_0BC[0x018];
    /* 0x0D4 */ GlobalContext* globalCtx;
    /* 0x0D8 */ Player* player;
    /* 0x0DC */ PosRot playerPosRot;
    /* 0x0F0 */ Actor* target;
    /* 0x0F4 */ PosRot targetPosRot;
    /* 0x108 */ f32 rUpdateRateInv;
    /* 0x10C */ f32 pitchUpdateRateInv;
    /* 0x110 */ f32 yawUpdateRateInv;
    /* 0x114 */ f32 xzOffsetUpdateRate;
    /* 0x118 */ f32 yOffsetUpdateRate;
    /* 0x11C */ f32 fovUpdateRate;
    /* 0x120 */ f32 xzSpeed;
    /* 0x124 */ f32 dist;
    /* 0x128 */ f32 speedRatio;
    /* 0x12C */ Vec3f playerToAtOffset;
    /* 0x138 */ Vec3f playerPosDelta;
    /* 0x144 */ f32 fov;
    /* 0x148 */ f32 atLERPStepScale;
    /* 0x14C */ f32 playerGroundY;
    /* 0x150 */ Vec3f floorNorm;
    /* 0x15C */ f32 waterYPos;
    /* 0x160 */ s32 waterPrevCamIdx;
    /* 0x164 */ s32 waterPrevCamSetting;
    /* 0x168 */ s32 waterQuakeIdx;
    /* 0x16C */ char unk_16C[0x00C];
    /* 0x178 */ s16 uid;
    /* 0x17A */ char unk_17A[0x002];
    /* 0x17C */ Vec3s inputDir;
    /* 0x182 */ Vec3s camDir;
    /* 0x188 */ s16 status;
    /* 0x18A */ s16 setting;
    /* 0x18C */ s16 mode;
    /* 0x18E */ s16 bgCheckId;
    /* 0x190 */ s16 camDataIdx;
    /* 0x192 */ s16 behaviorFlags;
    /* 0x194 */ s16 stateFlags;
    /* 0x196 */ s16 childCamIdx;
    /* 0x198 */ s16 waterDistortionTimer;
    /* 0x19A */ s16 distortionFlags;
    /* 0x19C */ s16 prevSetting;
    /* 0x19E */ s16 nextCamDataIdx;
    /* 0x1A0 */ s16 nextBgCheckId;
    /* 0x1A2 */ s16 roll;
    /* 0x1A4 */ s16 paramFlags;
    /* 0x1A6 */ s16 animState;
    /* 0x1A8 */ s16 timer;
    /* 0x1AA */ s16 parentCamIdx;
    /* 0x1AC */ s16 thisIdx;
    /* 0x1AE */ s16 prevCamDataIdx;
    /* 0x1B0 */ s16 csId;
    /* 0x1B2 */ char unk_1B2[0x00A];
} Camera; // size = 0x1BC

typedef struct {
    /* 0x0 */ u16 setting;
    /* 0x2 */ s16 count;
    /* 0x4 */ Vec3s* camFuncData;
} CamData; // size = 0x8

typedef struct {
    /* 0x00 */ Vec3f atOffset;
    /* 0x0C */ Vec3f eyeOffset;
    /* 0x18 */ s16 upPitchOffset;
    /* 0x1A */ s16 upYawOffset;
    /* 0x1C */ s16 fovOffset;
    /* 0x20 */ f32 maxOffset;
} ShakeInfo; // size = 0x24

typedef struct {
    /* 0x00 */ char unk_00[0x04];
    /* 0x04 */ Vec3s minBounds;
    /* 0x0A */ Vec3s maxBounds;
    /* 0x10 */ u16 numVertices;
    /* 0x12 */ u16 numPolygons;
    /* 0x14 */ u16 numWaterboxes;
    /* 0x18 */ Vec3s* vtxList;
    /* 0x1C */ CollisionPoly* polyList;
    /* 0x20 */ void* surfaceTypeList;
    /* 0x24 */ CamData* camDataList;
    /* 0x28 */ void* waterboxes;
} CollisionHeader; // size = 0x2C

typedef struct {
    /* 0x00 */ CollisionHeader* colHeader;
    /* 0x04 */ char unk_04[0x4C];
} StaticCollisionContext; // size = 0x50

typedef struct {
    /* 0x00 */ Actor* actor;
    /* 0x04 */ CollisionHeader* colHeader;
    /* 0x08 */ char unk_04[0x0C];
    /* 0x14 */ Vec3f scale1;
    /* 0x20 */ Vec3s rot1;
    /* 0x28 */ Vec3f pos1;
    /* 0x34 */ Vec3f scale2;
    /* 0x40 */ Vec3s rot2;
    /* 0x48 */ Vec3f pos2;
    /* 0x54 */ char unk_54[0x18];
} ActorMesh; // size = 0x6C

typedef struct {
    /* 0x0000 */ char unk_00[0x04];
    /* 0x0004 */ ActorMesh actorMeshArr[50];
    /* 0x151C */ u16 flags[50];
    /* 0x1580 */ char unk_13F0[0x24];
} DynaCollisionContext; // size = 0x15A4

typedef struct {
    /* 0x0000 */ StaticCollisionContext stat;
    /* 0x0050 */ DynaCollisionContext dyna;
} CollisionContext; // size = 0x15F4

typedef struct {
    /* 0x00 */ u8* texture;
    /* 0x04 */ s16 x;
    /* 0x06 */ s16 y;
    /* 0x08 */ s16 width;
    /* 0x0A */ s16 height;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ u8 durationTimer;
    /* 0x11 */ u8 delayTimer;
    /* 0x12 */ s16 alpha;
    /* 0x14 */ s16 intensity;
    /* 0x16 */ s16 unk_16;
} TitleCardContext; // size = 0x18

typedef struct {
    /* 0x00 */ u32 length;   // number of actors loaded of this type
    /* 0x04 */ Actor* first; // pointer to first actor of this type
} ActorListEntry;            // size = 0x08

typedef struct {
    /* 0x00 */ u32 swch;
    /* 0x04 */ u32 tempSwch;
    /* 0x08 */ u32 unk0;
    /* 0x0C */ u32 unk1;
    /* 0x10 */ u32 chest;
    /* 0x14 */ u32 clear;
    /* 0x18 */ u32 tempClear;
    /* 0x1C */ u32 collect;
    /* 0x20 */ u32 tempCollect;
} ActorFlags; // size = 0x24

typedef struct {
    /* 0x0000 */ u8 unk_00;
    /* 0x0001 */ char unk_01[0x01];
    /* 0x0002 */ u8 hammerQuakeFlag;
    /* 0x0003 */ u8 unk_03;
    /* 0x0004 */ char unk_04[0x04];
    /* 0x0008 */ u8 total; // total number of actors loaded
    /* 0x0009 */ char unk_09[0x03];
    /* 0x000C */ ActorListEntry actorList[12];
    // /* 0x006C */ TargetContext targetCtx;
    /* 0x006C */ char unk_6C[0x130];
    /* 0x019C */ ActorFlags flags;
    /* 0x01C0 */ TitleCardContext titleCtx;
} ActorContext; // TODO: size = 0x1D8

typedef struct CutsceneContext {
    /* 0x00 */ char unk_00[0x4];
    /* 0x04 */ void* segment;
    /* 0x08 */ u8 state;
    /* 0x09 */ char unk_09[0x13];
    /* 0x1C */ f32 unk_1C;
    /* 0x20 */ u16 frames;
    /* 0x22 */ u16 unk_22;
    /* 0x24 */ s32 unk_24;
    /* 0x28 */ char unk_28[0x18];
    /* 0x40 */ CsCmdActorAction* linkAction;
    /* 0x44 */ CsCmdActorAction* actorActions[10]; // "npcdemopnt"
} CutsceneContext;                                 // size = 0x6C

typedef struct Sub_118_C {
    s32 data[4];
} Sub_118_C;

typedef struct SubGlobalContext_118 {
    /* 0x00 */ char unk_00[0x0C];
    /* 0x0C */ Sub_118_C* sub0C; // an array of these
    /* 0x10 */ char unk_10[0x24];
    /* 0x34 */ s32 indexInto0C;
    /* 0x38 */ char unk_38[0x28];
    /* 0x60 */ void** unk_60; // seems to point to an array of cutscene pointers, maybe?
} SubGlobalContext_118;       // size = at least 0x64

typedef struct OcLine OcLine; // TODO
#define COLLISION_CHECK_AT_MAX 50
#define COLLISION_CHECK_AC_MAX 60
#define COLLISION_CHECK_OC_MAX 50
#define COLLISION_CHECK_OC_LINE_MAX 3

typedef struct CollisionCheckContext {
    /* 0x000 */ s16 colAtCount;
    /* 0x002 */ u16 sacFlags;
    /* 0x004 */ Collider* colAt[COLLISION_CHECK_AT_MAX];
    /* 0x0CC */ s32 colAcCount;
    /* 0x0D0 */ Collider* colAc[COLLISION_CHECK_AC_MAX];
    /* 0x1C0 */ s32 colOcCount;
    /* 0x1C4 */ Collider* colOc[COLLISION_CHECK_OC_MAX];
    /* 0x28C */ s32 colOcLineCount;
    /* 0x290 */ OcLine* colOcLine[COLLISION_CHECK_OC_LINE_MAX];

} CollisionCheckContext; // size = 0x29C
// _Static_assert(sizeof(CollisionCheckContext) == 0x29C, "CollisionCheckContext size");

typedef struct {
    /* 0x00 */ Vec3f pos;
    /* 0x0C */ Vec3f norm;
    /* 0x18 */ CollisionPoly* poly;
    struct {
        /* 0x1C */ f32 radius;
        /* 0x20 */ s16 pitch;
        /* 0x22 */ s16 yaw;
    } geoNorm;
    /* 0x24 */ s32 bgId;
} CamColChk; // size = 0x28

#define OBJECT_EXCHANGE_BANK_MAX 19
#define OBJECT_ID_MAX 417

typedef struct ZARInfo {
    /* 0x00 */ void* buf;
    /* 0x04 */ char unk_04[0x48];
    /* 0x4C */ void*** cmbPtrs;  /* Really, this is a pointer to an array of pointers to CMB managers,
                                    the first member of which is a pointer to the CMB data */
    /* 0x50 */ void*** csabPtrs; /* Same as above but for CSAB */
    /* 0x54 */ char unk_54[0x04];
    /* 0x58 */ void*** cmabPtrs; /* Same as above but for CMAB */
    /* 0x5C */ char unk_5C[0x14];
} ZARInfo; // size = 0x70

typedef struct {
    /* 0x00 */ s16 id;
    /* 0x02 */ char unk_02[0x0E];
    /* 0x10 */ ZARInfo zarInfo;
} ObjectStatus; // size = 0x80

typedef struct {
    /* 0x000 */ u8 num;
    /* 0x001 */ char unk_01[0x3];
    /* 0x004 */ ObjectStatus status[OBJECT_EXCHANGE_BANK_MAX];
} ObjectContext; // size = 0x984

typedef struct {
    /* 0x00 */ char filename[0x40];
    /* 0x40 */ u32 size;
} ObjectFile;

typedef struct {
    /* 0x00 */ s16 id;
    /* 0x02 */ Vec3s pos;
    /* 0x08 */ Vec3s rot;
    /* 0x0E */ s16 params;
} ActorEntry; // size = 0x10

typedef struct {
    /* 0x00 */ u8 spawn;
    /* 0x01 */ u8 room;
} EntranceEntry;

typedef struct GameState {
    /* 0x00 */ GraphicsContext* gfxCtx;
    /* 0x04 */ void (*main)(struct GameState*);
    /* 0x08 */ void (*destroy)(struct GameState*); // "cleanup"
    /* 0x0C */ void (*init)(struct GameState*);
    // TODO
} GameState;

// Global Context (ram start: 0871E840)
typedef struct GlobalContext {
    // /* 0x0000 */ GameState state;
    /* 0x0000 */ char unk_0[0x0104];
    /* 0x0104 */ s16 sceneNum;
    /* 0x0106 */ char unk_106[0x0012];
    /* 0x0118 */ SubGlobalContext_118 sub118;
    /* 0x017C */ char unk_17C[0x000C];
    struct {
        /* 0x0188 */ s32 topY;
        /* 0x018C */ s32 bottomY;
        /* 0x0190 */ s32 leftX;
        /* 0x0194 */ s32 rightX;
        /* 0x0198 */ f32 fovY;
        /* 0x019C */ f32 zNear;
        /* 0x01A0 */ f32 zFar;
        /* 0x01A4 */ f32 scale;
        /* 0x01A8 */ char unk_01A8[0x0010];
        /* 0x01B8 */ Vec3f eye;
        /* 0x01C4 */ Vec3f at;
        /* 0x01D0 */ Vec3f up;
        /* 0x01DC */ char unk_01DC[0x0150];
        /* 0x032C */ Vec3f distortionOrientation;
        /* 0x0338 */ Vec3f distortionScale;
        /* 0x0344 */ char unk_0344[0x0018];
        /* 0x035C */ f32 distortionSpeed;
        /* 0x0360 */ char unk_0360[0x0004];
    } view;
    /* 0x0364 */ Camera mainCamera;
    /* 0x0520 */ Camera subCameras[3];
    /* 0x0A54 */ Camera* cameraPtrs[4];
    /* 0x0A64 */ s16 activeCamera;
    /* 0x0A66 */ char unk_A66[0x0032];
    /* 0x0A98 */ CollisionContext colCtx;
    /* 0x208C */ ActorContext actorCtx;
    /* 0x2264 */ char unk_2264[0x0034];
    /* 0x2298 */ CutsceneContext csCtx; // "demo_play"
    /* 0x2304 */ char unk_2304[0x078C];
    /* 0x2A90 */ u8 msgMode; // seems to be used primarily for the ocarina
    /* 0x2A91 */ char unk_2A91[0xEB];
    /* 0x2B7C */ u16 lastPlayedSong;
    /* 0x2B7E */ s16 unk_2B7E; // msgCtx.unk_E3EE in OoT
    /* 0x2B80 */ char unk_2B80[0x06B0];
    /* 0x3230 */ u32 lightSettingsList_addr;
    /* 0x3234 */ char unk_3234[0x0824];
    /* 0x3A58 */ ObjectContext objectCtx;
    /* 0x43DC */ char unk_43DC[0x0854];
    /* 0x4C30 */ s8 roomNum;
    /* 0x4C31 */ char unk_4C31[0x0FCB];
    /* 0x5BFC */ u32 gameplayFrames;
    /* 0x5C00 */ u8 linkAgeOnLoad;
    /* 0x5C01 */ u8 unk_5C01;
    /* 0x5C02 */ u8 curSpawn;
    /* 0x5C03 */ char unk_5C03[0x0006];
    /* 0x5C09 */ ActorEntry* linkActorEntry;
    /* 0x5C0D */ char unk_5C0D[0x0008];
    /* 0x5C19 */ EntranceEntry* setupEntranceList;
    /* 0x5C1C */ s16* setupExitList;
    /* 0x5C20 */ char unk_5C20[0x000D];
    /* 0x5C2D */ s8 sceneLoadFlag; // "fade_direction"
    /* 0x5C2E */ char unk_5C2E[0x0004];
    /* 0x5C32 */ s16 nextEntranceIndex;
    /* 0x5C34 */ char unk_5C34[0x0042];
    /* 0x5C76 */ u8 fadeOutTransition;
    /* 0x5C78 */ CollisionCheckContext colChkCtx;
    // TODO
} GlobalContext; // size = 0x5F14 TODO
_Static_assert(sizeof(GlobalContext) == 0x5F14, "Global Context size");

typedef struct StaticContext {
    /* 0x0000 */ char unk_0[0x0D38];
    /* 0x0D38 */ s16 dekuNutFlash; // set to -1 to trigger flash
    /* 0x0D3A */ char unk_D3A[0x0126];
    /* 0x0E60 */ u16 spawnOnEpona;
    /* 0x0E62 */ char unk_E72[0x0010];
    /* 0x0E72 */ u16 collisionDisplay;
    /* 0x0E74 */ char unk_E74[0x015C];
    /* 0x0FD0 */ u16 renderGeometryDisable;
    /* 0x0FD2 */ char unk_FD2[0x0602];
} StaticContext; // size 0x15D4
// _Static_assert(sizeof(StaticContext) == 0x15D4, "Static Context size");

typedef struct {
    /* 0x00 */ s8 scene;
    /* 0x01 */ s8 spawn;
    /* 0x02 */ u16 field;
} EntranceInfo; // size = 0x4

typedef struct {
    /* 0x00 */ char infoFilename[0x44];
    /* 0x44 */ char filename[0x44];
    /* 0x88 */ char unk_88[0x01];
    /* 0x89 */ u8 config;
    /* 0x8A */ char unk_8A[0x02];
} Scene; // size = 0x8C

typedef struct {
    /* 0x00 */ s16 objectId;
    /* 0x02 */ u8 objectModelIdx;
    /* 0x03 */ u8 cmabIndex;
    /* 0x04 */ u8 objectModelIdx2;
    /* 0x05 */ u8 cmabIndex2;
} DrawItemTableEntry;

typedef struct {
    /* 0x00 */ u8 scene;
    /* 0x01 */ u8 flags1;
    /* 0x02 */ u8 flags2;
    /* 0x03 */ u8 flags3;
} RestrictionFlags;

typedef struct TargetIndicatorModels {
    /* 0x00 */ SkeletonAnimationModel* pointer;                 // arrow above targetable actor
    /* 0x04 */ SkeletonAnimationModel* reticle[4];              // four arrows circling around target
    /* 0x14 */ SkeletonAnimationModel* reticleAfterimageOne[4]; // four arrows trailing behind `reticle`
    /* 0x24 */ SkeletonAnimationModel* reticleAfterimageTwo[4]; // four arrows trailing behind `reticleAfterimageOne`
} TargetIndicatorModels;

typedef struct TargetContext {
    /* 0x000 */ char unk_000[0x4E];
    /* 0x04E */ u8 reticleActorType;
    /* 0x04F */ char unk_04F[0x61];
    /* 0x0B0 */ TargetIndicatorModels visibleTargetIndicators; // culled when behind a wall
    /* 0x0E4 */ TargetIndicatorModels hiddenTargetIndicators;  // drawn even when behind walls
    /* 0x118 */ char unk_118[0x08];
    /* 0x120 */ ZARInfo* zarInfo;
    /* 0x124 */ char unk_120[0x04];
    /* 0x128 */ u32 pointerActorType;
    // ... size unknown
} TargetContext;

typedef struct SAModelListEntry {
    SkeletonAnimationModel* saModel;
    u32 unk;
} SAModelListEntry;

typedef struct SubMainClass_180 {
    /* 0x000 */ char unk_00[0x8];
    /* 0x008 */ s32 saModelsCount1;
    /* 0x00C */ s32 saModelsCount2;
    /* 0x010 */ char unk_10[0x10];
    /* 0x020 */ SAModelListEntry* saModelsList1; // 3D models
    /* 0x024 */ SAModelListEntry* saModelsList2; // 2D billboards
    /* ... size unknown*/
} SubMainClass_180;

typedef struct MainClass {
    /* 0x000 */ char unk_00[0x180];
    /* 0x180 */ SubMainClass_180 sub180;
    /* ... size unknown*/
} MainClass;

extern GlobalContext* gGlobalContext;
extern const u32 ItemSlots[];
extern const char DungeonNames[][25];
#define gSaveContext (*(SaveContext*)0x00587958)
#define gStaticContext (*(StaticContext*)0x08080010)
#define gObjectTable ((ObjectFile*)0x53CCF4)
#define gEntranceTable ((EntranceInfo*)0x543BB8)
#define gItemUsabilityTable ((u8*)0x506C58)
#define gGearUsabilityTable ((u32*)0x4D47C8)
#define gDungeonSceneTable ((Scene*)0x4DC400)
#define gMQDungeonSceneTable ((Scene*)0x4DCBA8)
#define gSceneTable ((Scene*)0x545484)
#define gRandInt (*(u32*)0x50C0C4)
#define gRandFloat (*(f32*)0x50C0C8)
#define gDrawItemTable ((DrawItemTableEntry*)0x4D88C8)
#define gRestrictionFlags ((RestrictionFlags*)0x539DC4)
#define PLAYER ((Player*)gGlobalContext->actorCtx.actorList[ACTORTYPE_PLAYER].first)
#define gMainClass ((MainClass*)0x5BE5B8)
#define gIsBottomScreenDimmed (*(s32*)0x5043EC)

#define GearSlot(X) (X - ITEM_SWORD_KOKIRI)

typedef enum {
    DUNGEON_DEKU_TREE = 0,
    DUNGEON_DODONGOS_CAVERN,
    DUNGEON_JABUJABUS_BELLY,
    DUNGEON_FOREST_TEMPLE,
    DUNGEON_FIRE_TEMPLE,
    DUNGEON_WATER_TEMPLE,
    DUNGEON_SPIRIT_TEMPLE,
    DUNGEON_SHADOW_TEMPLE,
    DUNGEON_BOTTOM_OF_THE_WELL,
    DUNGEON_ICE_CAVERN,
    DUNGEON_GANONS_TOWER,
    DUNGEON_GERUDO_TRAINING_GROUNDS,
    DUNGEON_THIEVES_HIDEOUT,
    DUNGEON_INSIDE_GANONS_CASTLE,
    DUNGEON_GANONS_TOWER_COLLAPSING_INTERIOR,
    DUNGEON_GANONS_CASTLE_COLLAPSING,
    DUNGEON_TREASURE_CHEST_SHOP,
    DUNGEON_DEKU_TREE_BOSS_ROOM,
    DUNGEON_DODONGOS_CAVERN_BOSS_ROOM,
    DUNGEON_JABUJABUS_BELLY_BOSS_ROOM,
    DUNGEON_FOREST_TEMPLE_BOSS_ROOM,
    DUNGEON_FIRE_TEMPLE_BOSS_ROOM,
    DUNGEON_WATER_TEMPLE_BOSS_ROOM,
    DUNGEON_SPIRIT_TEMPLE_BOSS_ROOM,
    DUNGEON_SHADOW_TEMPLE_BOSS_ROOM,
} DungeonId;

#define SCENE_LINK_HOUSE 52

/* TODO: figure out what to do with this stuff */
#define real_hid_addr 0x10002000
#define real_hid (*(hid_mem_t*)real_hid_addr)

#define Z3D_TOP_SCREEN_LEFT_1 0x14313890
#define Z3D_TOP_SCREEN_LEFT_2 0x14359DA0
#define Z3D_TOP_SCREEN_RIGHT_1 0x14410AD0
#define Z3D_TOP_SCREEN_RIGHT_2 0x14456FE0
#define Z3D_BOTTOM_SCREEN_1 0x143A02B0
#define Z3D_BOTTOM_SCREEN_2 0x143D86C0

typedef void (*Item_Give_proc)(GlobalContext* globalCtx, u8 item);
#define Item_Give_addr 0x376A78
#define Item_Give ((Item_Give_proc)Item_Give_addr)

typedef void (*DisplayTextbox_proc)(GlobalContext* globalCtx, u16 textId, Actor* actor);
#define DisplayTextbox_addr 0x367C7C
#define DisplayTextbox ((DisplayTextbox_proc)DisplayTextbox_addr)

typedef u32 (*EventCheck_proc)(u32 flag);
#define EventCheck_addr 0x350CF4
#define EventCheck ((EventCheck_proc)EventCheck_addr)

typedef void (*EventSet_proc)(u32 flag);
#define EventSet_addr 0x34CBF8
#define EventSet ((EventSet_proc)EventSet_addr)

typedef void (*Rupees_ChangeBy_proc)(s16 rupeeChange);
#define Rupees_ChangeBy_addr 0x376A60
#define Rupees_ChangeBy ((Rupees_ChangeBy_proc)Rupees_ChangeBy_addr)

typedef void (*LinkDamage_proc)(GlobalContext* globalCtx, Player* player, s32 arg2, f32 arg3, f32 arg4, s16 arg5,
                                s32 arg6);
#define LinkDamage_addr 0x35D304
#define LinkDamage ((LinkDamage_proc)LinkDamage_addr)

typedef u32 (*Inventory_HasEmptyBottle_proc)(void);
#define Inventory_HasEmptyBottle_addr 0x377A04
#define Inventory_HasEmptyBottle ((Inventory_HasEmptyBottle_proc)Inventory_HasEmptyBottle_addr)

typedef void (*PlaySound_proc)(u32);
#define PlaySound_addr 0x35C528
// This function plays sound effects and music tracks, overlaid on top of the current BGM
#define PlaySound ((PlaySound_proc)PlaySound_addr)

typedef Actor* (*Actor_Spawn_proc)(ActorContext* actorCtx, GlobalContext* globalCtx, s16 actorId, float posX,
                                   float posY, float posZ, s16 rotX, s16 rotY, s16 rotZ, s16 params,
                                   s32 initImmediately) __attribute__((pcs("aapcs-vfp")));
#define Actor_Spawn_addr 0x3738D0
#define Actor_Spawn ((Actor_Spawn_proc)Actor_Spawn_addr)

typedef Actor* (*Actor_Find_proc)(ActorContext* actorCtx, s16 actorId, u8 actorType);
#define Actor_Find_addr 0x372D64
#define Actor_Find ((Actor_Find_proc)Actor_Find_addr)

typedef void (*Actor_GetScreenPos_proc)(GlobalContext* globalCtx, Actor* actor, s16* outX, s16* outY);
#define Actor_GetScreenPos_addr 0x363A20
#define Actor_GetScreenPos ((Actor_GetScreenPos_proc)Actor_GetScreenPos_addr)

typedef void (*FireDamage_proc)(Actor* player, GlobalContext* globalCtx, int flamesColor);
#define FireDamage_addr 0x35D8D8
#define FireDamage ((FireDamage_proc)FireDamage_addr)

typedef void (*Flags_SetEnv_proc)(GlobalContext* globalCtx, s16 flag);
#define Flags_SetEnv_addr 0x366704
#define Flags_SetEnv ((Flags_SetEnv_proc)Flags_SetEnv_addr)

typedef void (*GiveItem_proc)(Actor* actor, GlobalContext* globalCtx, s32 getItemId, f32 xzRange, f32 yRange)
    __attribute__((pcs("aapcs-vfp")));
#define GiveItem_addr 0x3724DC
#define GiveItem ((GiveItem_proc)GiveItem_addr)

typedef void (*Message_CloseTextbox_proc)(GlobalContext* globalCtx);
#define Message_CloseTextbox_addr 0x3725E0
#define Message_CloseTextbox ((Message_CloseTextbox_proc)Message_CloseTextbox_addr)

typedef void (*SetupItemInWater_proc)(Player* player, GlobalContext* globalCtx);
#define SetupItemInWater_addr 0x354894
#define SetupItemInWater ((SetupItemInWater_proc)SetupItemInWater_addr)

typedef void (*Health_ChangeBy_proc)(GlobalContext* arg1, u32 arg2);
#define Health_ChangeBy_addr 0x352DBC
#define Health_ChangeBy ((Health_ChangeBy_proc)Health_ChangeBy_addr)

typedef void (*PlaySFX_proc)(u32 sfxId, Vec3f* pos, u32 token, f32* freqScale, f32* a4, s8* reverbAdd);
#define PlaySFX_addr 0x37547C
#define PlaySFX ((PlaySFX_proc)PlaySFX_addr)

typedef void (*Flags_SetSwitch_proc)(GlobalContext* globalCtx, u32 flag);
#define Flags_SetSwitch_addr 0x375C10
#define Flags_SetSwitch ((Flags_SetSwitch_proc)Flags_SetSwitch_addr)

typedef u32 (*Flags_GetSwitch_proc)(GlobalContext* globalCtx, u32 flag);
#define Flags_GetSwitch_addr 0x36E864
#define Flags_GetSwitch ((Flags_GetSwitch_proc)Flags_GetSwitch_addr)

typedef u32 (*Flags_GetCollectible_proc)(GlobalContext* globalCtx, u32 flag);
#define Flags_GetCollectible_addr 0x36405C
#define Flags_GetCollectible ((Flags_GetCollectible_proc)Flags_GetCollectible_addr)

typedef void (*Player_SetEquipmentData_proc)(GlobalContext* globalCtx, Player* player);
#define Player_SetEquipmentData_addr 0x34913C
#define Player_SetEquipmentData ((Player_SetEquipmentData_proc)Player_SetEquipmentData_addr)

typedef s32 (*BossChallenge_IsActive_proc)(void);
#define BossChallenge_IsActive_addr 0x35B164
#define BossChallenge_IsActive ((BossChallenge_IsActive_proc)BossChallenge_IsActive_addr)

typedef s32 (*Audio_PlayActorSfx2_proc)(Actor* actor, s32 sfxID);
#define Audio_PlayActorSfx2_addr 0x375BCC
#define Audio_PlayActorSfx2 ((Audio_PlayActorSfx2_proc)Audio_PlayActorSfx2_addr)

typedef s32 (*Model_GetMeshGroupCount_proc)(SkeletonAnimationModel* skelAnimeModel);
#define Model_GetMeshGroupCount ((Model_GetMeshGroupCount_proc)0x2BB71C)

typedef s32 (*Model_IsMeshGroupUsed_proc)(SkeletonAnimationModel* skelAnimeModel, s32 param);
#define Model_IsMeshGroupUsed ((Model_IsMeshGroupUsed_proc)0x4C6880)

typedef void (*Model_EnableMeshGroupByIndex_proc)(SkeletonAnimationModel* skel, u32 index);
#define Model_EnableMeshGroupByIndex ((Model_EnableMeshGroupByIndex_proc)0x37266C)

typedef void (*Model_DisableMeshGroupByIndex_proc)(SkeletonAnimationModel* skel, u32 index);
#define Model_DisableMeshGroupByIndex ((Model_DisableMeshGroupByIndex_proc)0x36932C)

typedef s32 (*Player_InBlockingCsMode_proc)(GlobalContext* globalCtx, Player* player);
#define Player_InBlockingCsMode ((Player_InBlockingCsMode_proc)0x35DB20)

typedef u32 (*PauseContext_GetState_proc)(void);
#define PauseContext_GetState ((PauseContext_GetState_proc)0x3695F8)

typedef s32 (*Camera_CheckWater_proc)(Camera* camera);
#define Camera_CheckWater ((Camera_CheckWater_proc)0x2D06A0)

typedef void (*Camera_UpdateInterface_proc)(u32 flags);
#define Camera_UpdateInterface ((Camera_UpdateInterface_proc)0x330D84)

typedef f32 (*Camera_BGCheckInfo_proc)(Camera* camera, Vec3f* from, CamColChk* to);
#define Camera_BGCheckInfo ((Camera_BGCheckInfo_proc)0x3553FC)

typedef s32 (*Quake_Update_proc)(Camera* camera, ShakeInfo* camShake);
#ifdef Version_EUR
    #define Quake_Update_addr 0x4787E8
#else
    #define Quake_Update_addr 0x4787C8
#endif
#define Quake_Update ((Quake_Update_proc)Quake_Update_addr)

typedef s16 (*Camera_GetCamDataId_proc)(CollisionContext* colCtx, CollisionPoly* poly, s32 bgId);
#ifdef Version_EUR
    #define Camera_GetCamDataId_addr 0x47BFF8
#else
    #define Camera_GetCamDataId_addr 0x47BFD8
#endif
#define Camera_GetCamDataId ((Camera_GetCamDataId_proc)Camera_GetCamDataId_addr)

typedef s32 (*Animation_GetLastFrame_proc)(SkelAnime* anime, s32 animation_index);
#define Animation_GetLastFrame_addr 0x36AE14
#define Animation_GetLastFrame ((Animation_GetLastFrame_proc)Animation_GetLastFrame_addr)

typedef void (*Animation_Change_proc)(SkelAnime* anime, s32 animation_index, f32 play_speed, f32 start_frame,
                                      f32 end_frame, f32 morph_frames, s32 mode) __attribute__((pcs("aapcs-vfp")));
#define Animation_Change_addr 0x375C08
#define Animation_Change ((Animation_Change_proc)Animation_Change_addr)

typedef void (*EffectSsDeadDb_Spawn_proc)(GlobalContext* globalCtx, Vec3f* position, Vec3f* velocity,
                                          Vec3f* acceleration, s16 scale, s16 scale_step, s16 prim_r, s16 prim_g,
                                          s16 prim_b, s16 prim_a, s16 env_r, s16 env_g, s16 env_b, s16 unused,
                                          s32 frame_duration, s16 play_sound);
#define EffectSsDeadDb_Spawn_addr 0x3642F4
#define EffectSsDeadDb_Spawn ((EffectSsDeadDb_Spawn_proc)EffectSsDeadDb_Spawn_addr)

typedef void (*SaveGame_proc)(GlobalContext* globalCtx, u8 isSaveFileCreation);
#define SaveGame_addr 0x2FDAC8
#define SaveGame ((SaveGame_proc)SaveGame_addr)

typedef s32 (*Message_GetState_proc)(void);
#define Message_GetState ((Message_GetState_proc)0x3769d8)

#endif //_Z3D_H_
