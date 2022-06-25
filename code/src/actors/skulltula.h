#ifndef _SKULLTULA_H_
#define _SKULLTULA_H_

#include "z3D/z3D.h"

/* Bit usage of "params" for Gold Skulltula:
 *   0-7: Bit in gsFlags
 *  8-12: Index of gsFlags
 * 13-15: Attributes? If any is set, the Skulltula is Gold
 *        13: ?
 *        14: Hides during day, appears at night
 *        15: Plays the correct chime when spawned
 */

typedef struct {
    Actor base;
    SkelAnime anime;
    char unk_228[1144];
    void* action_fn;
    char collider[32];
    char jnt_sph_element[80];
    char unk_714[46];
    s16 unk_word1;
    char unk_744[6];
    s16 unk_word2;
    s16 deathTimer_maybe;
    char unk_74E[106];
    f32 unk_float1;
} EnSw;

void EnSw_rUpdate(Actor* thisx, GlobalContext* globalCtx);
void EnSw_Kill(EnSw* this, GlobalContext* globalCtx);

#endif //_SKULLTULA_H_
