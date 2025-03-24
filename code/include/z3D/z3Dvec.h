#ifndef _Z3DVEC_H_
#define _Z3DVEC_H_

#include <stdint.h>

typedef float f32;
typedef int8_t s8;
typedef uint8_t u8;
typedef int16_t s16;
typedef uint16_t u16;
typedef int32_t s32;
typedef uint32_t u32;
typedef int64_t s64;
typedef uint64_t u64;

typedef struct {
    f32 x, y;
} Vec2f;

typedef struct {
    f32 x, y, z;
} Vec3f;

typedef struct {
    s16 x, y, z;
} Vec3s;

typedef struct {
    s32 x, y, z;
} Vec3i;

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

#endif
