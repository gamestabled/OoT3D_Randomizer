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
    Actor base;
    char dyna[24];
    char unk_1BC[6];
    s8 door_type_maybe;
    char unk_1C3[3];
    s8 lock_timer;
    char unk_1C7[9];
    DoorShutterActionFunc action_fn;
} DoorShutter;

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
