#ifndef _Z3DMATH_H_
#define _Z3DMATH_H_

typedef f32 (*Math_SinS_proc)(s16 angle) __attribute__((pcs("aapcs-vfp")));
#define Math_SinS ((Math_SinS_proc)GAME_ADDR(0x2CFCA0))

typedef f32 (*Math_CosS_proc)(s16 angle) __attribute__((pcs("aapcs-vfp")));
#define Math_CosS ((Math_CosS_proc)GAME_ADDR(0x338F60))

typedef void (*Matrix_Multiply_proc)(nn_math_MTX34* dst, nn_math_MTX34* lhs, nn_math_MTX44* rhs)
    __attribute__((pcs("aapcs-vfp")));
#define Matrix_Multiply ((Matrix_Multiply_proc)GAME_ADDR(0x36C174))

typedef void (*Matrix_UpdatePosition_proc)(nn_math_MTX34* dst, nn_math_MTX34* src, Vec3f* vec)
    __attribute__((pcs("aapcs-vfp")));
#define Matrix_UpdatePosition ((Matrix_UpdatePosition_proc)GAME_ADDR(0x372070))

#endif
