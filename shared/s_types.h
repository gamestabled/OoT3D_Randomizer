#pragma once
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

typedef struct Vec2f {
    f32 x, y;
} Vec2f;

typedef struct Vec3f {
    f32 x, y, z;
} Vec3f;

typedef struct Vec3s {
    s16 x, y, z;
} Vec3s;

typedef struct Vec3i {
    s32 x, y, z;
} Vec3i;

typedef struct PosRot {
    Vec3f pos;
    Vec3s rot;
} PosRot; // size = 0x14
