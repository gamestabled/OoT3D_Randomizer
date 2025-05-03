#ifndef _PEAHAT_H_
#define _PEAHAT_H_

#include "z3D/z3D.h"

struct EnPeehat;

typedef void (*EnPeehatActionFunc)(struct EnPeehat*, GlobalContext*);

typedef struct EnPeehat {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ SkelAnime skelAnime;
    /* 0x0228 */ char unk_228[0x414];
    /* 0x063C */ s32 state;
    /* 0x0640 */ char unk_640[0x004];
    /* 0x0644 */ EnPeehatActionFunc actionFunc;
    /* 0x0648 */ char unk_648[0x10C];
    /* 0x0754 */ Collider colliderQuadBase;
    /* 0x076C */ char unk_76C[0x068];
} EnPeehat;
_Static_assert(sizeof(EnPeehat) == 0x7D4, "EnPeehat size");

void EnPeehat_rUpdate(Actor* thisx, GlobalContext* globalCtx);

#endif //_PEAHAT_H_
