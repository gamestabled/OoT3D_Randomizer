#ifndef _Z3DBGCHECK_H
#define _Z3DBGCHECK_H

#include "z3Dvec.h"

struct GlobalContext;
struct Actor;

#define BG_ACTOR_MAX 50

#define BGCHECK_Y_MIN -32000.0f

typedef struct ScaleRotPos {
    /* 0x00 */ Vec3f scale;
    /* 0x0C */ Vec3f rot;
    /* 0x14 */ Vec3f pos;
} ScaleRotPos; // size = 0x20

typedef struct CollisionPoly {
    /* 0x00 */ u16 type;
    /* 0x02 */ u16 vtxData[3]; // id for each vertex in the vtxList
    /* 0x08 */ char unk_08[0x2];
    /* 0x0A */ Vec3s norm; // Normal vector
    /* 0x10 */ f32 dist;   // Plane distance from origin
} CollisionPoly;           // size = 0x14
_Static_assert(sizeof(CollisionPoly) == 0x14, "CollisionPoly size");

typedef struct DynaCollisionPoly {
    /* 0x00 */ CollisionPoly colPoly;
    /* 0x14 */ Vec3f normF32; // Normal vector with floats
} DynaCollisionPoly;          // size = 0x20
_Static_assert(sizeof(DynaCollisionPoly) == 0x20, "DynaCollisionPoly size");

typedef struct SurfaceType {
    u32 data[2];
} SurfaceType;
_Static_assert(sizeof(SurfaceType) == 0x8, "SurfaceType size");

#define SurfaceType_CanHookshot(surfaceType) ((surfaceType.data[1] >> 17) & 1)
#define SurfaceType_GetWallType(surfaceType) ((surfaceType.data[0] >> 21) & 0x1F)
#define SurfaceType_GetFloorProperty(surfaceType) ((surfaceType.data[0] >> 26) & 0xF)
#define SurfaceType_GetExitIndex(surfaceType) ((surfaceType.data[0] >> 8) & 0x1F)
#define SurfaceType_GetFloorType(surfaceType) ((surfaceType.data[0] >> 13) & 0x1F)
#define SurfaceType_GetWallDamage(surfaceType) ((surfaceType.data[1] >> 27) & 0x1)
#define SurfaceType_GetFloorEffect(surfaceType) ((surfaceType.data[1] >> 4) & 0x3)

#define SurfaceType_IsLoadingZoneOrVoidPlane(surfaceType)                                                    \
    (SurfaceType_GetFloorProperty(surfaceType) == 0x5 || SurfaceType_GetFloorProperty(surfaceType) == 0xC || \
     SurfaceType_GetExitIndex(surfaceType) != 0x0 || SurfaceType_GetFloorType(surfaceType) == 0x9)

typedef struct BgCamInfo {
    /* 0x0 */ u16 setting;
    /* 0x2 */ s16 count;
    /* 0x4 */ Vec3s* bgCamFuncData;
} BgCamInfo; // size = 0x8

typedef struct CollisionHeader {
    /* 0x00 */ Vec3s minBounds; // minimum coordinates of poly bounding box
    /* 0x06 */ Vec3s maxBounds; // maximum coordinates of poly bounding box
    /* 0x0C */ u16 numVertices;
    /* 0x0E */ u16 numPolygons;
    /* 0x10 */ u16 numSurfaceTypes;
    /* 0x12 */ u16 numBgCams;
    /* 0x14 */ u16 numWaterBoxes;
    /* 0x18 */ Vec3s* vtxList;
    /* 0x1C */ CollisionPoly* polyList;
    /* 0x20 */ SurfaceType* surfaceTypeList;
    /* 0x24 */ BgCamInfo* bgCamList; // BgCamInfo*
    /* 0x28 */ void* waterBoxes;     // WaterBox*
} CollisionHeader;                   // original name: BGDataInfo
_Static_assert(sizeof(CollisionHeader) == 0x2C, "CollisionHeader size");

typedef struct SSNode {
    s16 polyId;
    u16 next; // next SSNode index
} SSNode;

typedef struct SSList {
    u16 head; // first SSNode index
} SSList;

typedef struct SSNodeList {
    /* 0x00 */ u16 max;          // original name: short_slist_node_size
    /* 0x02 */ u16 count;        // original name: short_slist_node_last_index
    /* 0x04 */ SSNode* tbl;      // original name: short_slist_node_tbl
    /* 0x08 */ u8* polyCheckTbl; // points to an array of bytes, one per static poly. Zero initialized when starting a
                                 // bg check, and set to 1 if that poly has already been tested.
} SSNodeList;

typedef struct DynaSSNodeList {
    SSNode* tbl;
    s32 count;
    s32 max;
} DynaSSNodeList;

typedef struct StaticLookup {
    SSList floor;
    SSList wall;
    SSList ceiling;
} StaticLookup;

typedef struct DynaLookup {
    u16 polyStartIndex; // useful only for bgActors[i].colHeader->polyList, and not for dynaColCtx.polyList
    SSList ceiling;
    SSList wall;
    SSList floor;
} DynaLookup;

typedef struct BgActor {
    /* 0x00 */ struct Actor* actor;
    /* 0x04 */ CollisionHeader* colHeader;
    /* 0x08 */ DynaLookup dynaLookup;
    /* 0x10 */ u16 vtxStartIndex; // useful only for bgActors[i].colHeader->vtxList, and not for dynaColCtx.vtxList
    /* 0x12 */ ScaleRotPos prevTransform;
    /* 0x36 */ ScaleRotPos curTransform;
    /* 0x5A */ Sphere16 boundingSphere;
    /* 0x64 */ f32 minY;
    /* 0x68 */ f32 maxY;
} BgActor; // size = 0x6C
_Static_assert(sizeof(BgActor) == 0x6C, "BgActor size");

#define BGACTOR_IN_USE (1 << 0) // The bgActor entry is in use

typedef struct StaticCollisionContext {
    /* 0x00 */ CollisionHeader* colHeader; // scene's static collision
    /* 0x04 */ Vec3f minBounds;            // minimum coordinates of collision bounding box
    /* 0x10 */ Vec3f maxBounds;            // maximum coordinates of collision bounding box
    /* 0x1C */ Vec3i subdivAmount;         // x, y, z subdivisions of the scene's static collision
    /* 0x28 */ Vec3f subdivLength;         // x, y, z subdivision worldspace lengths
    /* 0x34 */ Vec3f subdivLengthInv;      // inverse of subdivision length
    /* 0x40 */ StaticLookup* lookupTbl;    // 3d array of length subdivAmount
    /* 0x44 */ SSNodeList polyNodes;
} StaticCollisionContext; // size = 0x50
_Static_assert(sizeof(StaticCollisionContext) == 0x50, "StaticCollisionContext size");

typedef struct DynaCollisionContext {
    /* 0x0000 */ u8 bitFlag;
    /* 0x0004 */ BgActor bgActors[BG_ACTOR_MAX];
    /* 0x151C */ u16 bgActorFlags[BG_ACTOR_MAX];
    /* 0x1580 */ DynaCollisionPoly* polyList;
    /* 0x1584 */ Vec3f* vtxList;
    /* 0x1588 */ DynaSSNodeList polyNodes;
    /* 0x1594 */ s32 polyNodesMax;
    /* 0x1598 */ s32 polyListMax;
    /* 0x159C */ s32 vtxListMax;
    /* 0x15A0 */ char unk_15A0[0x4];
} DynaCollisionContext; // size = 0x15A4
_Static_assert(sizeof(DynaCollisionContext) == 0x15A4, "DynaCollisionContext size");

typedef struct CollisionContext {
    /* 0x0000 */ StaticCollisionContext stat;
    /* 0x0050 */ DynaCollisionContext dyna;
} CollisionContext; // size = 0x15F4

typedef s32 (*WaterBox_GetSurfaceImpl_proc)(struct GlobalContext* globalCtx, CollisionContext* colCtx, f32 x, f32 z,
                                            f32* ySurface, void** outWaterBox) __attribute__((pcs("aapcs-vfp")));
// Returns true if point is within the xz boundaries of an active water box, else false
#define WaterBox_GetSurfaceImpl ((WaterBox_GetSurfaceImpl_proc)GAME_ADDR(0x35E8A0))

typedef f32 (*BgCheck_RaycastDown1_proc)(CollisionContext* colCtx, CollisionPoly* outGroundPoly, Vec3f* pos)
    __attribute__((pcs("aapcs-vfp")));
// Returns the yIntersect of the nearest poly found directly below `pos`, or BGCHECK_Y_MIN if no floor detected
#define BgCheck_RaycastDown1 ((BgCheck_RaycastDown1_proc)GAME_ADDR(0x257054))

typedef s32 (*BgCheck_EntityLineTest1_proc)(CollisionContext* colCtx, Vec3f* posA, Vec3f* posB, Vec3f* posResult,
                                            CollisionPoly** outPoly, s32 chkWall, s32 chkFloor, s32 chkCeil,
                                            s32 chkOneFace, s32* bgId);
#define BgCheck_EntityLineTest1 ((BgCheck_EntityLineTest1_proc)GAME_ADDR(0x369F9C))

#endif //_Z3DBGCHECK_H
