#ifndef _Z3DCOLLISION_CHECK_H_
#define _Z3DCOLLISION_CHECK_H_

#include "z3Dvec.h"

struct GlobalContext;
struct CollisionCheckContext;

typedef struct {
    /* 0x00 */ struct Actor* actor; // Attached actor
    /* 0x04 */ struct Actor* at;    // Actor attached to what it collided with as an AT collider.
    /* 0x08 */ struct Actor* ac;    // Actor attached to what it collided with as an AC collider.
    /* 0x0C */ struct Actor* oc;    // Actor attached to what it collided with as an OC collider.
    /* 0x10 */ u8 atFlags;          // Information flags for AT collisions.
    /* 0x11 */ u8 acFlags;          // Information flags for AC collisions.
    /* 0x12 */ u8 ocFlags1;         // Information flags for OC collisions.
    /* 0x13 */ u8 ocFlags2;         // Flags related to which colliders it can OC collide with.
    /* 0x14 */ u8 colType;          // Determines hitmarks and sound effects during AC collisions.
    /* 0x15 */ u8 shape;            // JntSph, Cylinder, Tris, or Quad
} Collider;                         // size = 0x18
_Static_assert(sizeof(Collider) == 0x18, "Collider size");

typedef struct {
    /* 0x00 */ u32 damageFlags;
    /* 0x04 */ u8 effect;
    /* 0x05 */ u8 damage;
} ColliderTouch; // size = 0x8
_Static_assert(sizeof(ColliderTouch) == 0x8, "ColliderTouch size");

typedef struct {
    /* 0x00 */ u32 damageFlags;
    /* 0x04 */ u8 effect;
    /* 0x05 */ u8 defense;
    /* 0x06 */ Vec3s hitPos;
} ColliderBump; // size = 0xC
_Static_assert(sizeof(ColliderBump) == 0xC, "ColliderBump size");

typedef struct {
    /* 0x00 */ ColliderTouch toucher;
    /* 0x08 */ ColliderBump bumper;
    /* 0x14 */ u8 elementType;
    /* 0x15 */ u8 toucherFlags;
    /* 0x16 */ u8 bumperFlags;
    /* 0x17 */ u8 ocElementFlags;
    /* 0x18 */ Collider* at_hit;
    /* 0x1C */ Collider* ac_hit;
    /* 0x20 */ Collider* at_hit_info;
    /* 0x24 */ Collider* ac_hit_info;
} ColliderInfo; // size = 0x28
_Static_assert(sizeof(ColliderInfo) == 0x28, "ColliderInfo size");

typedef struct {
    /* 0x00 */ f32 radius;
    /* 0x04 */ f32 height;
    /* 0x08 */ f32 yShift;
    /* 0x0C */ Vec3f position;
} Cylinderf; // size = 0x18
_Static_assert(sizeof(Cylinderf) == 0x18, "Cylinderf size");

typedef struct {
    /* 0x00 */ Collider base;
    /* 0x18 */ ColliderInfo info;
    /* 0x40 */ Cylinderf dim;
} ColliderCylinder; // size = 0x58
_Static_assert(sizeof(ColliderCylinder) == 0x58, "ColliderCylinder size");

typedef struct {
    /* 0x00 */ u8 type;
    /* 0x01 */ u8 atFlags;
    /* 0x02 */ u8 acFlags;
    /* 0x03 */ u8 maskA;
    /* 0x04 */ u8 maskB;
    /* 0x05 */ u8 shape;
} ColliderInit; // size = 0x6
_Static_assert(sizeof(ColliderInit) == 0x6, "ColliderInit size");

typedef struct {
    /* 0x00 */ u32 damageFlags;
    /* 0x04 */ u8 effect;
    /* 0x05 */ u8 defense;
} ColliderBumpInit; // size = 0x8
_Static_assert(sizeof(ColliderBumpInit) == 0x8, "ColliderBumpInit size");

typedef struct {
    /* 0x00 */ u8 elementType;
    /* 0x04 */ ColliderTouch toucher;
    /* 0x0C */ ColliderBumpInit bumper;
    /* 0x14 */ u8 toucherFlags;
    /* 0x15 */ u8 bumperFlags;
    /* 0x16 */ u8 ocElementFlags;
} ColliderInfoInit; // size = 0x18
_Static_assert(sizeof(ColliderInfoInit) == 0x18, "ColliderInfoInit size");

typedef struct {
    /* 0x00 */ ColliderInit base;
    /* 0x08 */ ColliderInfoInit info;
    /* 0x20 */ Cylinderf dim;
} ColliderCylinderInit; // size = 0x58
_Static_assert(sizeof(ColliderCylinderInit) == 0x38, "ColliderCylinderInit size");

typedef void (*Collider_InitCylinder_proc)(struct GlobalContext* globalCtx, ColliderCylinder* collider);
#define Collider_InitCylinder ((Collider_InitCylinder_proc)0x353DD0)

typedef void (*Collider_SetCylinder_proc)(struct GlobalContext* globalCtx, ColliderCylinder* collider,
                                          struct Actor* actor, void* cylinderInitData);
#define Collider_SetCylinder ((Collider_SetCylinder_proc)0x353D24)

typedef void (*Collider_UpdateCylinder_proc)(struct Actor* actor, ColliderCylinder* collider);
#define Collider_UpdateCylinder ((Collider_UpdateCylinder_proc)0x37632C)

typedef void (*CollisionCheck_SetOC_proc)(struct GlobalContext* globalCtx, struct CollisionCheckContext* colChkCtx,
                                          void* collider);
#define CollisionCheck_SetOC ((CollisionCheck_SetOC_proc)0x3762A4)

typedef void (*CollisionCheck_SetAC_proc)(struct GlobalContext* globalCtx, struct CollisionCheckContext* colChkCtx,
                                          void* collider);
#define CollisionCheck_SetAC ((CollisionCheck_SetAC_proc)0x376168)

#endif //_Z3DCOLLISION_CHECK_H_
