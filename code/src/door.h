#ifndef _DOOR_H_
#define _DOOR_H_

#include "z3D/z3D.h"

typedef struct {
    Actor base;
    SkelAnime anime;
    char unk_228[444];
    void* action_fn;
    s16 lock_timer;
} EnDoor;

void EnDoor_rUpdate(EnDoor* thisx, GlobalContext* globalCtx);
void EnDoor_Unlock(EnDoor* thisx);

typedef struct {
    Actor base;
    char dyna[24];
    char unk_1BC[6];
    s8 door_type_maybe;
    char unk_1C3[3];
    s8 lock_timer;
    char unk_1C7[9];
    void* action_fn;
} DoorShutter;

void DoorShutter_rInit(Actor* thisx, GlobalContext* globalCtx);
void DoorShutter_rUpdate(DoorShutter* thisx, GlobalContext* globalCtx);
void DoorShutter_Unlock(DoorShutter* thisx);

typedef struct {
    Actor base;
    char dyna[24];
    char unk_1BC[2];
    s8 lock_timer;
    char unk_1BF[1];
    void* action_fn;
} DoorGerudo;

void DoorGerudo_rUpdate(DoorGerudo* thisx, GlobalContext* globalCtx);
void DoorGerudo_Unlock(DoorGerudo* thisx);

#endif //_DOOR_H_
