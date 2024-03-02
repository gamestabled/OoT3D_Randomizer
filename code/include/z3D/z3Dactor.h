#ifndef _Z3DACTOR_H_
#define _Z3DACTOR_H_

#include "z3Dvec.h"

struct Actor;
struct GlobalContext;

struct LightMapper;
struct ZARInfo;

typedef struct {
    Vec3f pos;
    Vec3s rot;
} PosRot; // size = 0x14

typedef struct {
    /* 0x00 */ char unk_00[0x8];
    /* 0x08 */ Vec3s norm; // Normal vector
    /* 0x0E */ s16 dist;   // Plane distance from origin
} CollisionPoly;           // size = 0x10

struct SkeletonAnimationModel;
typedef void (*SkeletonAnimationModelFunc)(struct SkeletonAnimationModel*);

typedef struct {
    /* 0x00 */ char unk_00[0x4];
    /* 0x04 */ SkeletonAnimationModelFunc destroy;
} SkeletonAnimationModel_VTable;

typedef struct SkeletonAnimationModel_unk_10 {
    /* 0x00 */ char unk_00[0x14];
} SkeletonAnimationModel_unk_10; // size = 0x14

typedef struct SkeletonAnimationModel_unk_0C {
    /* 0x00 */ SkeletonAnimationModel_unk_10* unk_00;
    /* 0x04 */ void* cmabManager;
    /* 0x08 */ f32 curFrame;
    /* 0x0C */ f32 animSpeed;
    /* 0x10 */ s8 animMode;
    /* 0x11 */ char unk_11[0x87];
} SkeletonAnimationModel_unk_0C; // size = 0x98

typedef struct SkeletonAnimationModel {
    /* 0x00 */ SkeletonAnimationModel_VTable* vtbl;
    /* 0x04 */ char unk_04[0x08];
    /* 0x0C */ SkeletonAnimationModel_unk_0C* unk_0C;
    /* 0x10 */ SkeletonAnimationModel_unk_10* unk_10;
    /* 0x14 */ void* unk_draw_struct_14;
    /* 0x18 */ char unk_18[0x64];
    /* 0x7C */ nn_math_MTX34 mtx;
    /* 0xAC */ s8 unk_AC;
    /* 0xAD */ char unk_AD[0x03];
} SkeletonAnimationModel; // size = 0xB0

typedef struct SkelAnime {
    /* 0x00 */ void* unk_00;
    /* 0x04 */ struct ZARInfo* zarInfo;
    /* 0x08 */ char unk_08[0x08];
    /* 0x10 */ struct GlobalContext* globalCtx;
    /* 0x14 */ char unk_14[0x14];
    /* 0x28 */ struct SkeletonAnimationModel* unk_28;
    /* 0x2C */ char unk_2C[0x4];
    /* 0x30 */ s32 animationType;
    /* 0x34 */ char unk_34[0x8];
    /* 0x3C */ f32 curFrame;
    /* 0x40 */ f32 playSpeed;
    /* 0x44 */ f32 startFrame;
    /* 0x48 */ f32 endFrame;
    /* 0x4C */ f32 animLength;
    /* 0x50 */ char unk_50[0x24];
    /* 0x74 */ u8 limbCount;
    /* 0x75 */ char unk_75[0x03];
    /* 0x78 */ void* jointTable;
    /* 0x7C */ void* morphTable;
    /* 0x80 */ char unk_80[0x02];
    /* 0x82 */ u8 tablesAllocated;
    /* 0x83 */ char unk_83[0x01];
} SkelAnime; // size = 0x84

typedef void (*ActorFunc)(struct Actor*, struct GlobalContext*);

typedef struct {
    /* 0x00 */ s16 id;
    /* 0x02 */ u8 type; // Classifies actor and determines when actor will execute
    /* 0x03 */ u8 room; // Room instance was spawned in. If value set to FF in rom,
                        // instance does not despawn when swapping rooms
    /* 0x04 */ u32 flags;
    /* 0x08 */ s16 objectId;
    /* 0x0C */ u32 instanceSize;
    /* 0x10 */ ActorFunc init;    // Constructor
    /* 0x14 */ ActorFunc destroy; // Destructor
    /* 0x18 */ ActorFunc update;  // Main Update Function
    /* 0x1C */ ActorFunc draw;    // Draw function
} ActorInit;                      // size = 0x20

typedef enum {
    ALLOCTYPE_NORMAL,
    ALLOCTYPE_ABSOLUTE,
    ALLOCTYPE_PERMANENT
} AllocType;

typedef struct {
    /* 0x00 */ u32 vromStart;       // unused?
    /* 0x04 */ u32 vromEnd;         // unused?
    /* 0x08 */ void* vramStart;     // unused?
    /* 0x0C */ void* vramEnd;       // unused?
    /* 0x10 */ void* loadedRamAddr; // unused?
    /* 0x14 */ ActorInit* initInfo;
    /* 0x18 */ char* name;    // unused?
    /* 0x1C */ u16 allocType; // unused?
    /* 0x1E */ s8 nbLoaded;   // unused?
} ActorOverlay;               // size = 0x20

typedef struct {
    struct {
        char damage : 4;
        char effect : 4;
    } attack[32];
} ActorDamageChart;

typedef struct {
    /* 0x00 */ ActorDamageChart* damageChart; // For actors which contain a damage chart (example: Stalfos)...
    /* 0x04 */ Vec3f displacement;            // Amount to correct velocity (0x5C) by when colliding into a body
    /* 0x10 */ s16 unk_10;
    /* 0x12 */ s16 unk_12;
    /* 0x14 */ u16 unk_14;
    /* 0x16 */ u8 mass; // Used to compute displacement, 50 is common value, 0xFF for infinite mass/unmoveable
    /* 0x17 */ u8 health;
    /* 0x18 */ u8 damage;       // Amount to decrement health by
    /* 0x19 */ u8 damageEffect; // Stores what effect should occur when hit by a weapon
    /* 0x1A */ u8 atHitEffect;
    /* 0x1B */ u8 acHitEffect;
} CollisionCheckInfo; // size = 0x1C

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

typedef struct {
    /* 0x00 */ Collider base;
    /* 0x18 */      // ColliderInfo info;
    /* 0x40 */      // Cylinderf dim;
} ColliderCylinder; // size = 0x58

typedef struct {
    /* 0x00 */ Vec3s rot; // Current actor shape rotation
    /* 0x06 */ u8 unk_06;
    /* 0x08 */ f32 unk_08; // Model y axis offset. Represents model space units. collision mesh related
    /* 0x0C */ void (*shadowDrawFunc)(struct Actor*, struct LightMapper*, struct GlobalContext*);
    /* 0x10 */ f32 unk_10;
    /* 0x14 */ u8 unk_14;
    /* 0x15 */ u8 unk_15;
} ActorShape; // size = 0x18

typedef struct Actor {
    /* 0x000 */ s16 id;      // Actor Id
    /* 0x002 */ u8 type;     // Actor Type. Refer to the corresponding enum for values
    /* 0x003 */ s8 room;     // Room number the actor is in. -1 denotes that the actor won't despawn on a room change
    /* 0x004 */ u32 flags;   // Flags used for various purposes
    /* 0x008 */ PosRot home; // Initial position/rotation when spawned. Can be used for other purposes
    /* 0x01C */ s16 params;  // Configurable variable set by the actor's spawn data; original name: "args_data"
    /* 0x01E */ s8 objBankIndex; // Object bank index of the actor's object dependency; original name: "bank"
    /* 0x01F */ s8 targetMode;   // Controls how far the actor can be targeted from and how far it can stay locked on
    /* 0x020 */ u8 unk_20;
    /* 0x021 */ char unk_21[0x3];
    /* 0x024 */ u32 sfx; // SFX ID to play. Sound plays when value is set, then is cleared the following update cycle
    /* 0x028 */ PosRot world; // Position/rotation in the world
    /* 0x03C */ PosRot focus; // Target reticle focuses on this position. For player this represents head pos and rot
    /* 0x050 */ f32 targetArrowOffset;    // Height offset of the target arrow relative to `focus` position
    /* 0x054 */ Vec3f scale;              // Scale of the actor in each axis
    /* 0x060 */ Vec3f velocity;           // Velocity of the actor in each axis
    /* 0x06C */ f32 speedXZ;              // How fast the actor is traveling along the XZ plane
    /* 0x070 */ f32 gravity;              // Acceleration due to gravity. Value is added to Y velocity every frame
    /* 0x074 */ f32 minVelocityY;         // Sets the lower bounds cap on velocity along the Y axis
    /* 0x078 */ CollisionPoly* wallPoly;  // Wall polygon an actor is touching
    /* 0x07C */ CollisionPoly* floorPoly; // Floor polygon directly below the actor
    /* 0x080 */ u8 wallBgId;              // Bg ID of the wall polygon the actor is touching
    /* 0x081 */ u8 floorBgId;             // Bg ID of the floor polygon directly below the actor
    /* 0x082 */ s16 wallYaw;              // Y rotation of the wall polygon the actor is touching
    /* 0x084 */ f32 floorHeight;          // Y position of the floor polygon directly below the actor
    /* 0x088 */ f32 yDistToWater; // Distance to the surface of active waterbox. Negative value means above water
    /* 0x08C */ f32 waterBoxYSurface;
    /* 0x090 */ u16 bgCheckFlags;
    /* 0x092 */ s16 yawTowardsPlayer;          // Y rotation difference between the actor and the player
    /* 0x094 */ f32 xyzDistToPlayerSq;         // Squared distance between the actor and the player in the x,y,z axis
    /* 0x098 */ f32 xzDistToPlayer;            // Distance between the actor and the player in the XZ plane
    /* 0x09C */ f32 yDistToPlayer;             // Dist is negative if the actor is above the player
    /* 0x0A0 */ CollisionCheckInfo colChkInfo; // Variables related to the Collision Check system
    /* 0x0BC */ ActorShape shape;              // Variables related to the physical shape of the actor
    /* 0x0D4 */ Vec3f unk_D4[2];
    /* 0x0EC */ Vec3f unk_EC; // Stores result of some vector transformation involving actor xyz vector, and a matrix at
                              // Global Context + 11D60
    /* 0x0F8 */ f32 unk_F8;   // Related to above
    /* 0x0FC */ f32 uncullZoneForward;  // Amount to increase the uncull zone forward by (in projected space)
    /* 0x100 */ f32 uncullZoneScale;    // Amount to increase the uncull zone scale by (in projected space)
    /* 0x104 */ f32 uncullZoneDownward; // Amount to increase uncull zone downward by (in projected space)
    /* 0x108 */ Vec3f prevPos;          // World position from the previous update cycle
    /* 0x114 */ u8 isTargeted;          // Set to true if the actor is currently being targeted by the player
    /* 0x115 */ u8 targetPriority;      // Lower values have higher priority. Resets to 0 when player stops targeting
    /* 0x116 */ u16 textId;             // Text ID to pass to link/display when interacting with the actor
    /* 0x118 */ u16 freezeTimer;        // Actor does not update when set. Timer decrements automatically
    /* 0x11A */ s16 colorFilterTimer;
    /* 0x11C */ u32 colorFilterParams;
    /* 0x120 */ char unk_120;
    /* 0x121 */ u8 isDrawn;     // Set to true if the actor is currently being drawn. Always stays false for lens actors
    /* 0x122 */ u8 unk_122;     // Set within a routine that deals with collision
    /* 0x123 */ u8 naviEnemyId; // Sets what 0600 dialog to display when talking to navi. Default 0xFF
    /* 0x124 */ struct Actor* parent;       // Usage is actor specific. Set if actor is spawned via `Actor_SpawnAsChild`
    /* 0x128 */ struct Actor* child;        // Usage is actor specific. Set if actor is spawned via `Actor_SpawnAsChild`
    /* 0x12C */ struct Actor* prev;         // Previous actor of this category
    /* 0x130 */ struct Actor* next;         // Next actor of this category
    /* 0x134 */ ActorFunc init;             // Initialization Routine. Called by `Actor_Init` or `Actor_UpdateAll`
    /* 0x138 */ ActorFunc destroy;          // Destruction Routine. Called by `Actor_Destroy`
    /* 0x13C */ ActorFunc update;           // Update Routine. Called by `Actor_UpdateAll`
    /* 0x140 */ ActorFunc draw;             // Draw Routine. Called by `Actor_Draw`
    /* 0x144 */ ActorOverlay* overlayEntry; // Pointer to the overlay table entry for this actor
    /* 0x148 */ nn_math_MTX34 modelMtx;     // Transforms model space coordinates to world coordinates
    /* 0x178 */ void* unk_178;              // Unknown pointer type
    /* 0x17C */ void* unk_17C[6];           // Unknown pointer type
    /* 0x194 */ u32 unk_194;
    /* 0x198 */ u8 unk_198;
    /* 0x199 */ char unk_199[0x3];
    /* 0x19C */ u16 unk_19C;
    /* 0x19E */ char unk_19E[0x2];
    /* 0x1A0 */ f32 unk_1A0;
    /* From here on, the structure and size varies for each actor */
} Actor; // size = 0x1A4

typedef struct DynaPolyActor {
    /* 0x000 */ struct Actor actor;
    /* 0x1A4 */ s32 bgId;
    /* 0x1A8 */ f32 unk_1A8;
    /* 0x1AC */ f32 unk_1AC;
    /* 0x1B0 */ s16 unk_1B0;
    /* 0x1B2 */ u16 unk_1B2;
    /* 0x1B4 */ u32 unk_1B4;
    /* 0x1B8 */ u8 unk_1B8;
    /* 0x1BA */ s16 unk_1BA;
} DynaPolyActor; // size = 0x1BC

typedef struct {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ char unk_148[0x0005];
    /* 0x01A9 */ s8 heldItemActionParam;
    /* 0x01AA */ u8 heldItemId;
    /* 0x01AB */ char unk_1AB[0x1];
    /* 0x01AC */ s8 itemActionParam;
    /* 0x01AD */ char unk_1AD[0x0003];
    /* 0x01B0 */ u8 modelGroup;
    /* 0x01B1 */ u8 nextModelGroup;
    /* 0x01B2 */ s8 unk_1B2;
    /* 0x01B3 */ u8 modelAnimType;
    /* 0x01B4 */ u8 leftHandType;
    /* 0x01B5 */ u8 rightHandType;
    /* 0x01B6 */ u8 sheathType;
    /* 0x01B7 */ u8 currentMask;
    /* 0x01B8 */ char unk_1B8[0x0004];
    /* 0x01BC */ void* rightHandDLists;
    /* 0x01C0 */ void* leftHandDLists;
    /* 0x01C4 */ void* sheathDLists;
    /* 0x01C8 */ void* waistDLists;
    /* 0x01CC */ char unk_1CC[0x78];
    /* 0x0244 */ SkeletonAnimationModel* giModel1;
    /* 0x0248 */ SkeletonAnimationModel* giModel2;
    /* 0x024C */ void* giDrawSpace;
    /* 0x0250 */ char unk_250[0x0004];
    /* 0x0254 */ struct SkelAnime skelAnime;
    /* 0x02D8 */ char unk_2D8[0x0F4C];
    /* 0x1224 */ Actor* heldActor;
    /* 0x1228 */ char unk_1228[0x84];
    /* 0x12AC */ u8 getItemId;
    /* 0x12AD */ char unk_12AD[0x0001];
    /* 0x12AE */ u16 getItemDirection;
    /* 0x12B0 */ Actor* interactRangeActor;
    /* 0x12B4 */ char unk_12B4[0x0454];
    /* 0x1708 */ void* stateFuncPtr;
    /* 0x170C */ char unk_170C[0x0004];
    /* 0x1710 */ u32 stateFlags1;
    /* 0x1714 */ u32 stateFlags2;
    /* 0x1718 */ Actor* unk_1718;
    /* 0x171C */ Actor* boomerangActor;
    /* 0x1720 */ Actor* unk_1720;
    /* 0x1724 */ Actor* naviActor;
    /* 0x1728 */ s16 naviTextId;
    /* 0x172A */ u8 stateFlags3;
    /* 0x172B */ s8 exchangeItemId;
    /* 0x172C */ char unk_172C[0x0AF0];
    /* 0x221C */ float xzSpeed; // probably
    /* 0x2220 */ char unk_2220[0x0007];
    /* 0x2227 */ s8 meleeWeaponState;
    /* 0x2228 */ char unk_2228[0x0020];
    /* 0x2248 */ s16 fishingState; // 1: casting line, 2: can reel, 3: holding catch
    /* 0x224A */ char unk_224A[0x0004];
    /* 0x224E */ s16 giDrawIdPlusOne; // used to change mesh for rupee models
    /* 0x2250 */ char unk_2250[0x0238];
    /* 0x2488 */ s8 invincibilityTimer; // prevents damage when nonzero
                                        // (positive = visible, counts towards zero each frame)
    /* 0x2489 */ char unk_2489[0x27B];
    /* 0x2704 */ struct SkeletonAnimationModel_unk_0C* bodyTexAnim;
} Player; // total size (from init vars): 2A4C

typedef enum {
    /* 0x00 */ ACTORTYPE_SWITCH,
    /* 0x01 */ ACTORTYPE_BG,
    /* 0x02 */ ACTORTYPE_PLAYER,
    /* 0x03 */ ACTORTYPE_EXPLOSIVES,
    /* 0x04 */ ACTORTYPE_NPC,
    /* 0x05 */ ACTORTYPE_ENEMY,
    /* 0x06 */ ACTORTYPE_PROP,
    /* 0x07 */ ACTORTYPE_ITEMACTION,
    /* 0x08 */ ACTORTYPE_MISC,
    /* 0x09 */ ACTORTYPE_BOSS,
    /* 0x0A */ ACTORTYPE_DOOR,
    /* 0x0B */ ACTORTYPE_CHEST
} ActorType;

typedef struct ActorHeapNode {
    u16 magic;
    u16 free;
    u32 size;
    struct ActorHeapNode* next;
    struct ActorHeapNode* prev;
} ActorHeapNode;

void Actor_Kill(Actor* actor);
#define gActorOverlayTable ((ActorOverlay*)0x50CD84)

typedef u32 (*Actor_HasParent_proc)(Actor* actor, struct GlobalContext* globalCtx);
#define Actor_HasParent_addr 0x371E40
#define Actor_HasParent ((Actor_HasParent_proc)Actor_HasParent_addr)

typedef f32 (*Actor_WorldDistXYZToActor_proc)(Actor* a, Actor* b) __attribute__((pcs("aapcs-vfp")));
#define Actor_WorldDistXYZToActor ((Actor_WorldDistXYZToActor_proc)0x3306C4)

#endif
