#ifndef _DOOR_H_
#define _DOOR_H_

#include "z3D/z3D.h"

/*------------------------------
|           EN_DOOR            |
------------------------------*/

struct EnDoor;

typedef void (*EnDoorActionFunc)(struct EnDoor* this, GlobalContext* globalCtx);

typedef struct EnDoor {
    Actor base;
    SkelAnime anime;
    char unk_228[444];
    EnDoorActionFunc action_fn;
    s16 lock_timer;
} EnDoor;

void EnDoor_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void EnDoor_Unlock(EnDoor* this);

/*------------------------------
|         DOOR_SHUTTER         |
------------------------------*/

struct DoorShutter;

typedef void (*DoorShutterActionFunc)(struct DoorShutter* this, GlobalContext* globalCtx);

typedef struct DoorShutter {
    /* 0x000 */ DynaPolyActor dyna;
    /* 0x1BC */ char unk_1BC[0x06];
    /* 0x1C2 */ s8 doorType;
    /* 0x1C3 */ char unk_1C3[0x03];
    /* 0x1C6 */ s8 unlockTimer;
    /* 0x1C7 */ char unk_1C7[0x05];
    /* 0x1CC */ f32 barsClosedAmount;
    /* 0x1D0 */ DoorShutterActionFunc actionFunc;
    /* 0x1D4 */ char unk_1D4[0x4C];
} DoorShutter;
_Static_assert(sizeof(DoorShutter) == 0x220, "DoorShutter size");

void DoorShutter_rInit(Actor* thisx, GlobalContext* globalCtx);
void DoorShutter_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void DoorShutter_Unlock(DoorShutter* this);

/*------------------------------
|         DOOR_GERUDO          |
------------------------------*/

struct DoorGerudo;

typedef void (*DoorGerudoActionFunc)(struct DoorGerudo* this, GlobalContext* globalCtx);

typedef struct DoorGerudo {
    Actor base;
    char dyna[24];
    char unk_1BC[2];
    s8 lock_timer;
    char unk_1BF[1];
    DoorGerudoActionFunc action_fn;
} DoorGerudo;

void DoorGerudo_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void DoorGerudo_Unlock(DoorGerudo* this);

#endif //_DOOR_H_
