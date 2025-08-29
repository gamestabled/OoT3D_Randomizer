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

typedef s16 (*Math_SmoothStepToS_proc)(s16* pValue, s16 target, s16 scale, s16 step, s16 minStep);
#define Math_SmoothStepToS ((Math_SmoothStepToS_proc)GAME_ADDR(0x375A18))

typedef f32 (*Math_SmoothStepToF_proc)(f32* pValue, f32 target, f32 fraction, f32 step, f32 minStep)
    __attribute__((pcs("aapcs-vfp")));
#define Math_SmoothStepToF ((Math_SmoothStepToF_proc)GAME_ADDR(0x36E168))

typedef f32 (*Math_Vec3f_DistXZ_proc)(Vec3f* a, Vec3f* b) __attribute__((pcs("aapcs-vfp")));
#define Math_Vec3f_DistXZ ((Math_Vec3f_DistXZ_proc)GAME_ADDR(0x36D260))

#endif
