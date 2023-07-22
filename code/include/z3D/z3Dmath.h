#ifndef _Z3DMATH_H_
#define _Z3DMATH_H_

typedef f32 (*Math_SinS_proc)(s16 angle) __attribute__((pcs("aapcs-vfp")));
#define Math_SinS ((Math_SinS_proc)0x2CFCA0)

typedef f32 (*Math_CosS_proc)(s16 angle) __attribute__((pcs("aapcs-vfp")));
#define Math_CosS ((Math_CosS_proc)0x338F60)

#endif
