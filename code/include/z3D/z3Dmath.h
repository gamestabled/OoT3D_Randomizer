#ifndef _Z3DMATH_H_
#define _Z3DMATH_H_

#include "s_types.h"

typedef struct {
    f32 data[3][4];
} nn_math_MTX34;

typedef struct {
    f32 data[4][4];
} nn_math_MTX44;

typedef struct Sphere16 {
    Vec3s center;
    s16 radius;
} Sphere16; // size = 0x08

typedef struct Spheref {
    Vec3f center;
    f32 radius;
} Spheref; // size = 0x10

f32 Math_SinS(s16 angle) __attribute__((pcs("aapcs-vfp")));
f32 Math_CosS(s16 angle) __attribute__((pcs("aapcs-vfp")));
void Matrix_Multiply(nn_math_MTX34* dst, nn_math_MTX34* lhs, nn_math_MTX44* rhs) __attribute__((pcs("aapcs-vfp")));
void Matrix_UpdatePosition(nn_math_MTX34* dst, nn_math_MTX34* src, Vec3f* vec) __attribute__((pcs("aapcs-vfp")));
s16 Math_SmoothStepToS(s16* pValue, s16 target, s16 scale, s16 step, s16 minStep);
f32 Math_SmoothStepToF(f32* pValue, f32 target, f32 fraction, f32 step, f32 minStep) __attribute__((pcs("aapcs-vfp")));
f32 Math_Vec3f_DistXZ(Vec3f* a, Vec3f* b) __attribute__((pcs("aapcs-vfp")));

#endif
