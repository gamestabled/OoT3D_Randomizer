#ifndef _Z3DMATH_H_
#define _Z3DMATH_H_

typedef f32 (*Math_SinS_proc)(s16 angle) __attribute__((pcs("aapcs-vfp")));
#define Math_SinS ((Math_SinS_proc)0x2CFCA0)

typedef f32 (*Math_CosS_proc)(s16 angle) __attribute__((pcs("aapcs-vfp")));
#define Math_CosS ((Math_CosS_proc)0x338F60)

typedef void (*Matrix_Multiply_proc)(nn_math_MTX34* dst, nn_math_MTX34* lhs, nn_math_MTX44* rhs)
    __attribute__((pcs("aapcs-vfp")));
#define Matrix_Multiply_addr 0x36C174
#define Matrix_Multiply ((Matrix_Multiply_proc)Matrix_Multiply_addr)

typedef void (*Matrix_UpdatePosition_proc)(nn_math_MTX34* dst, nn_math_MTX34* src, Vec3f* vec)
    __attribute__((pcs("aapcs-vfp")));
#define Matrix_UpdatePosition_addr 0x372070
#define Matrix_UpdatePosition ((Matrix_UpdatePosition_proc)Matrix_UpdatePosition_addr)

#endif
