#ifndef _BEAN_PLANT_H_
#define _BEAN_PLANT_H_

#include "z3D/z3D.h"

struct ObjBean;

typedef void (*ObjBeanActionFunc)(struct ObjBean* this, GlobalContext* globalCtx);

typedef struct ObjBean {
    Actor base;
    char dyna[24];
    ObjBeanActionFunc action_fn;
    char collider[88];
    char unk_218[16];
    s16 timer;
    char unk_22A[65];
    u8 unk_bitfield;
} ObjBean;

// These are used for multiplayer actor syncing to store the values of the adult bean plant.
// This trick works since there never is more than one plant per room/scene.
extern PosRot lastBeanPlant_Home;
extern s16 lastBeanPlant_Params;

void ObjBean_rInit(Actor* thisx, GlobalContext* globalCtx);
void ObjBean_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void ObjBean_StartGrowth(ObjBean* this);

#endif //_BEAN_PLANT_H_
