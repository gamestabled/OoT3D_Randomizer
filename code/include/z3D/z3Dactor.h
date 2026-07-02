#ifndef _Z3DACTOR_H_
#define _Z3DACTOR_H_

#include "s_types.h"
#include "s_actor_id.h"

#include "z3Dmath.h"
#include "z3Dcollision_check.h"
#include "z3Dbgcheck.h"

struct Actor;
struct GlobalContext;

struct LightMapper;
struct ZARInfo;

#define BGCHECKFLAG_GROUND (1 << 0)               // Standing on the ground
#define BGCHECKFLAG_GROUND_TOUCH (1 << 1)         // Has touched the ground (only active for 1 frame)
#define BGCHECKFLAG_GROUND_LEAVE (1 << 2)         // Has left the ground (only active for 1 frame)
#define BGCHECKFLAG_WALL (1 << 3)                 // Touching a wall
#define BGCHECKFLAG_CEILING (1 << 4)              // Touching a ceiling
#define BGCHECKFLAG_WATER (1 << 5)                // In water
#define BGCHECKFLAG_WATER_TOUCH (1 << 6)          // Has touched water (reset when leaving water)
#define BGCHECKFLAG_GROUND_STRICT (1 << 7)        // Strictly on ground (BGCHECKFLAG_GROUND has some leeway)
#define BGCHECKFLAG_CRUSHED (1 << 8)              // Crushed between a floor and ceiling (triggers a void for player)
#define BGCHECKFLAG_PLAYER_WALL_INTERACT (1 << 9) // Only set/used by player, related to interacting with walls

#define UPDBGCHECKINFO_WALL (1 << 0)        // check wall
#define UPDBGCHECKINFO_CEILING (1 << 1)     // check ceiling
#define UPDBGCHECKINFO_FLOOR_WATER (1 << 2) // check floor and water
#define UPDBGCHECKINFO_FLAG_3 (1 << 3)
#define UPDBGCHECKINFO_FLAG_4 (1 << 4)
#define UPDBGCHECKINFO_FLAG_5 (1 << 5) // unused
#define UPDBGCHECKINFO_FLAG_6 (1 << 6) // disable water ripples
#define UPDBGCHECKINFO_FLAG_7 (1 << 7) // alternate wall check?

#define ACTOR_FLAG_ATTENTION_ENABLED (1 << 0)
#define ACTOR_FLAG_INSIDE_CULLING_VOLUME (1 << 6)

struct SkeletonAnimationModel;
typedef void (*SkeletonAnimationModelFunc)(struct SkeletonAnimationModel*);

typedef struct {
    /* 0x00 */ char unk_00[0x4];
    /* 0x04 */ SkeletonAnimationModelFunc destroy;
    /* 0x04 */ SkeletonAnimationModelFunc draw;
} SkeletonAnimationModel_VTable;

typedef struct SkeletonAnimationModel_unk_10 {
    /* 0x00 */ struct CmbManager* cmbMan;
    /* 0x04 */ void* unk_04;
    /* 0x08 */ s32 unk_08;
    /* 0x0C */ s32 unk_0C;
    /* 0x10 */ s32 unk_10;
} SkeletonAnimationModel_unk_10;
_Static_assert(sizeof(SkeletonAnimationModel_unk_10) == 0x14, "SkeletonAnimationModel_unk_10 size");

typedef struct MaterialAnimation {
    /* 0x00 */ SkeletonAnimationModel_unk_10* subSAM10;
    /* 0x04 */ void* cmabManager;
    /* 0x08 */ f32 curFrame;
    /* 0x0C */ f32 animSpeed;
    /* 0x10 */ s8 animMode;
    /* 0x11 */ char unk_11[0x87];
} MaterialAnimation;
_Static_assert(sizeof(MaterialAnimation) == 0x98, "MaterialAnimation size");

typedef struct SkeletonAnimationModel_unk_14 {
    void* vtable_4EBD98;
    void* cmbManager;
    void* unk_08;
    void* unk_0C;
    void* unkAutoClass1;
} SkeletonAnimationModel_unk_14;

typedef struct SkeletonAnimationModel {
    /* 0x00 */ SkeletonAnimationModel_VTable* vtbl;
    /* 0x04 */ char unk_04[0x08];
    /* 0x0C */ MaterialAnimation* matAnim;
    /* 0x10 */ SkeletonAnimationModel_unk_10* subSAM10;
    /* 0x14 */ SkeletonAnimationModel_unk_14* subSAM14;
    /* 0x18 */ char unk_18[0x64];
    /* 0x7C */ nn_math_MTX34 mtx;
    /* 0xAC */ s8 unk_AC;
    /* 0xAD */ char unk_AD[0x03];
} SkeletonAnimationModel;
_Static_assert(sizeof(SkeletonAnimationModel) == 0xB0, "SkeletonAnimationModel size");

typedef struct FaceAnimation {
    /* 0x00 */ s8 flags[3];
    /* 0x04 */ MaterialAnimation matAnims[3];
} FaceAnimation;

typedef struct UnkSubSkelAnime_20 {
    /* 0x00 */ char unk_00[0x04];
    /* 0x04 */ struct Actor* actor;
    /* 0x08 */ char unk_08[0x08];
    /* 0x10 */ void* overrideLimbDraw;
    /* 0x14 */ void* postLimbDraw;
    // ... size unknown
} UnkSubSkelAnime_20;

typedef struct SkelAnime {
    /* 0x00 */ struct CmbManager* cmbMan;
    /* 0x04 */ struct ZARInfo* zarInfo;
    /* 0x08 */ char unk_08[0x08];
    /* 0x10 */ struct GlobalContext* globalCtx;
    /* 0x14 */ char unk_14[0x0C];
    /* 0x20 */ UnkSubSkelAnime_20* sub20;
    /* 0x24 */ char unk_24[0x04];
    /* 0x28 */ struct SkeletonAnimationModel* saModel;
    /* 0x2C */ char unk_2C[0x4];
    /* 0x30 */ s32 animIndex;
    /* 0x34 */ char unk_34[0x8];
    /* 0x3C */ f32 curFrame;
    /* 0x40 */ f32 playSpeed;
    /* 0x44 */ f32 startFrame;
    /* 0x48 */ f32 endFrame;
    /* 0x4C */ f32 animLength;
    /* 0x50 */ char unk_50[0x20];
    /* 0x70 */ s32 animMode;
    /* 0x74 */ u8 limbCount;
    /* 0x75 */ char unk_75[0x03];
    /* 0x78 */ void* jointTable;
    /* 0x7C */ void* morphTable;
    /* 0x80 */ char unk_80[0x02];
    /* 0x82 */ u8 dynamicTables;
    /* 0x83 */ char unk_83[0x01];
} SkelAnime;
_Static_assert(sizeof(SkelAnime) == 0x84, "SkelAnime size");

typedef struct FlameModelData {
    SkeletonAnimationModel* saModel;
    struct CMBManager* cmbMan;
    MaterialAnimation* matAnim;
} FlameModelData;
_Static_assert(sizeof(FlameModelData) == 0xC, "FlameModelData size");

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
    /* 0x00 */ Vec3s rot; // Current actor shape rotation
    /* 0x06 */ s16 face;
    /* 0x08 */ f32 yOffset; // Model y axis offset. Represents model space units. collision mesh related
    /* 0x0C */ void (*shadowDrawFunc)(struct Actor*, struct LightMapper*, struct GlobalContext*);
    /* 0x10 */ f32 shadowScale;
    /* 0x14 */ u8 shadowAlpha;
    /* 0x15 */ u8 feetFloorFlag;
    /* 0x16 */ char unk_16[2]; // Required padding?
    /* 0x18 */ Vec3f feetPos[2];
} ActorShape; // size = 0x30
_Static_assert(sizeof(ActorShape) == 0x30, "ActorShape size");

typedef struct Actor {
    /* 0x000 */ s16 id;        // Actor Id
    /* 0x002 */ u8 type;       // Actor Type. Refer to the corresponding enum for values
    /* 0x003 */ s8 room;       // Room number the actor is in. -1 denotes that the actor won't despawn on a room change
    /* 0x004 */ u32 flags;     // Flags used for various purposes
    /* 0x008 */ PosRot home;   // Initial position/rotation when spawned. Can be used for other purposes
    /* 0x01C */ s16 params;    // Configurable variable set by the actor's spawn data; original name: "args_data"
    /* 0x01E */ s8 objectSlot; // Object slot corresponding to the actor's object; original name: "bank"
    /* 0x01F */ s8 targetMode; // Controls how far the actor can be targeted from and how far it can stay locked on
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
    /* 0x088 */ f32 depthInWater; // Distance to the surface of active waterbox. Negative value means above water
    /* 0x08C */ f32 waterBoxYSurface;
    /* 0x090 */ u16 bgCheckFlags;
    /* 0x092 */ s16 yawTowardsPlayer;          // Y rotation difference between the actor and the player
    /* 0x094 */ f32 xyzDistToPlayerSq;         // Squared distance between the actor and the player in the x,y,z axis
    /* 0x098 */ f32 xzDistToPlayer;            // Distance between the actor and the player in the XZ plane
    /* 0x09C */ f32 yDistToPlayer;             // Dist is negative if the actor is above the player
    /* 0x0A0 */ CollisionCheckInfo colChkInfo; // Variables related to the Collision Check system
    /* 0x0BC */ ActorShape shape;              // Variables related to the physical shape of the actor
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
_Static_assert(sizeof(Actor) == 0x1A4, "Actor size");

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

struct Player;

typedef void (*PlayerActionFunc)(struct Player*, struct GlobalContext*);

typedef struct Player {
    /* 0x0000 */ Actor actor;
    /* 0x01A4 */ s8 currentTunic;
    /* 0x01A5 */ s8 currentSword;
    /* 0x01A6 */ s8 currentShield;
    /* 0x01A7 */ s8 currentBoots;
    /* 0x01A8 */ s8 heldItemButton;
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
    /* 0x0244 */ SkeletonAnimationModel* giModels[2];
    /* 0x024C */ void* giDrawSpace;
    /* 0x0250 */ char unk_250[0x0004];
    /* 0x0254 */ struct SkelAnime skelAnime;
    /* 0x02D8 */ char jointTable[0x514];
    /* 0x07EC */ char morphTable[0x514];
    /* 0x0D00 */ char unk_2D8[0x0524];
    /* 0x1224 */ Actor* heldActor;
    /* 0x1228 */ char unk_1228[0x84];
    /* 0x12AC */ u8 getItemId;
    /* 0x12AD */ char unk_12AD[0x0001];
    /* 0x12AE */ u16 getItemDirection;
    /* 0x12B0 */ Actor* interactRangeActor;
    /* 0x12B4 */ char unk_12B4[0x5C];
    /* 0x1310 */ ColliderCylinder cylinder;
    /* 0x1368 */ ColliderQuad meleeWeaponQuads[4];
    /* 0x1568 */ ColliderQuad shieldQuad;
    /* 0x15E8 */ Collider unkMeleeWeaponCollider;
    /* 0x1600 */ char unk_1600[0x108];
    /* 0x1708 */ PlayerActionFunc actionFunc;
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
    /* 0x224A */ char unk_224A[0x0002];
    /* 0x224C */ u8 darkLinkAdjustedSpawnPos;
    /* 0x224D */ char unk_224D[0x0001];
    /* 0x224E */ s16 giDrawIdPlusOne; // used to change mesh for rupee models
    /* 0x2250 */ char unk_2250[0x0030];
    /* 0x2280 */ s16 fallStartHeight;
    /* 0x2282 */ s16 fallDistance;
    /* 0x2284 */ char unk_2284[0x0204];
    /* 0x2488 */ s8 invincibilityTimer; // prevents damage when nonzero
                                        // (positive = visible, counts towards zero each frame)
    /* 0x2489 */ char unk_2489[0x0053];
    /* 0x24DC */ void* cmbMan;
    /* 0x24E0 */ void* zarInfo;
    /* 0x24E4 */ char unk_24E4[0x0220];
    /* 0x2704 */ MaterialAnimation tunicTexAnim;
    /* 0x279C */ MaterialAnimation fireMirroShieldTexAnim;
    /* 0x2834 */ MaterialAnimation iceMirroShieldTexAnim;
    /* 0x28CC */ char unk_28CC[0x180];
} Player; // total size (from init vars): 2A4C
_Static_assert(sizeof(Player) == 0x2A4C, "Player size");

extern s32 sFloorType;

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
    /* 0x0B */ ACTORTYPE_CHEST,
    /* 0x0C */ ACTORTYPE_MAX,
} ActorType;

typedef struct ActorHeapNode {
    u16 magic;
    u16 free;
    u32 size;
    struct ActorHeapNode* next;
    struct ActorHeapNode* prev;
} ActorHeapNode;

extern ActorOverlay gActorOverlayTable[];

void Actor_Kill(Actor* actor);

u32 Actor_HasParent(Actor* actor, struct GlobalContext* globalCtx);
f32 Actor_WorldDistXYZToActor(Actor* a, Actor* b) __attribute__((pcs("aapcs-vfp")));
void ActorShape_Init(ActorShape* shape, f32 yOffset, void* shadowDrawFunc, f32 shadowScale)
    __attribute__((pcs("aapcs-vfp")));
void Actor_SetFeetPos(Actor* actor, nn_math_MTX34* mtx, int param_3, int param_4, Vec3f* param_5, int param_6,
                      Vec3f* param_7);
void Actor_UpdateBgCheckInfo(struct GlobalContext* globalCtx, Actor* actor, f32 wallCheckHeight, f32 wallCheckRadius,
                             f32 ceilingCheckHeight, s32 flags) __attribute__((pcs("aapcs-vfp")));
s32 Player_InCsMode(struct GlobalContext* globalCtx);
Actor* Actor_FindNearby(struct GlobalContext* globalCtx, Actor* ref_actor, s16 actorId, u8 actor_category, f32 range);
void ActorShadow_DrawFeet(Actor* actor, void* lights, struct GlobalContext* globalCtx);
// limbCount param is ignored, the function takes the value from the cmb
void SkelAnime_Init(Actor* actor, struct GlobalContext* globalCtx, SkelAnime* skelAnime, s32 cmbIndex, s32 csabIndex,
                    void* jointTable, void* morphTable, s32 limbCount);
void SkelAnime_Destroy(SkelAnime* anime);
s32 SkelAnime_Update(SkelAnime* skelAnime);
s32 Animation_GetLastFrame(SkelAnime* anime, s32 animation_index);
void Animation_Change(SkelAnime* anime, s32 animationIndex, f32 playSpeed, f32 startFrame, f32 endFrame, s32 mode,
                      f32 morphFrames) __attribute__((pcs("aapcs-vfp")));
void LinkAnimation_Change(SkelAnime* skelAnime, struct GlobalContext* play, u32 animation, f32 playSpeed,
                          f32 startFrame, f32 endFrame, u8 mode, f32 morphFrames) __attribute__((pcs("aapcs-vfp")));
// Variadic arguments are pairs of a model and a CMB index; last argument must always be NULL.
struct ZARInfo* Actor_CreateSkelModels(Actor* actor, struct GlobalContext* globalCtx,
                                       SkeletonAnimationModel** firstSAModel, u32 firstCmbIndex, ...)
    __attribute__((sentinel));
// Variadic arguments are models; last argument must always be NULL.
struct ZARInfo* Actor_DestroySkelModels(Actor* actor, SkeletonAnimationModel** firstSAModel, ...)
    __attribute__((sentinel));
struct ZARInfo* Actor_CreateSkelModelsArray(Actor* actor, struct GlobalContext* globalCtx, s32 modelCount,
                                            SkeletonAnimationModel** models, s32* cmbIndices);
struct ZARInfo* Actor_DestroySkelModelsArray(Actor* actor, s32 modelCount, SkeletonAnimationModel** models);
void ZAR_Init(struct ZARInfo* zarInfo, void* buf, s32 size, s8 unkParam);
void ZAR_Destroy(struct ZARInfo* zarInfo);
void* ZAR_GetCMBByIndex(struct ZARInfo* zarInfo, u32 index);
void* ZAR_GetCMABByIndex(struct ZARInfo* zarInfo, u32 index);
void MatAnim_Init(MaterialAnimation* matAnim, void* cmabMan);
void MatAnim_Destroy(MaterialAnimation* matAnim);
void FaceAnim_Init(FaceAnimation* faceAnim, SkelAnime* skelAnime, s32 cmabIdx1, s32 cmabIdx2, s32 cmabIdx3);
void FaceAnim_Destroy(FaceAnimation* faceAnim);
void FaceAnim_SetFrame(FaceAnimation* faceAnim, s32 matAnimIdx, s32 animFrame);
void FaceAnim_35E330(FaceAnimation* faceAnim);
void FlameModel_Init(FlameModelData* modelData, struct GlobalContext* globalCtx, s32 unk, u32 cmabIndex);
void FlameModel_Destroy(FlameModelData* model);

#endif
