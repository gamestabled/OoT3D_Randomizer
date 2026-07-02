#ifndef _Z3DCMB_H_
#define _Z3DCMB_H_

#include "s_types.h"
#include "s_colors.h"

typedef struct CMB_HEAD {
    /* 0x00 */ char magic[4];
    /* 0x04 */ u32 filesize;
    /* 0x08 */ u32 version;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ char name[16];
    /* 0x20 */ u32 indicesCount;
    /* 0x24 */ s32 SKLOffset;
    /* 0x28 */ s32 MATSOffset;
    /* 0x2C */ s32 TEXOffset;
    /* 0x30 */ s32 SKLMOffset;
    /* 0x34 */ s32 LUTSOffset;
    /* 0x38 */ s32 VATROffset;
    /* 0x3C */ u32 indicesOffset;
    /* 0x40 */ u32 textureDataOffset;
} CMB_HEAD;

typedef struct TextureMappers {
    char unk_00[0x18];
} TextureMappers;

typedef struct TextureCoords {
    char unk_00[0x18];
} TextureCoords;

typedef struct Fragment {
    char unk_00[0x3C];
} Fragment;

typedef struct Material {
    u8 isFragmentLightingEnabled;
    u8 isVertexLightingEnabled;
    u8 isHemiSphereLightingEnabled;
    u8 isHemiSphereOcclusionEnabled;
    u8 culling;
    u8 isPolygonOffsetEnabled;
    s16 polygonOffsetValue;
    u32 textureMappersUsed;
    u32 textureCoordsUsed;
    TextureMappers textureMapper[3];
    TextureCoords textureCoord[3];
    Color_RGBA8 emission;
    Color_RGBA8 ambient;
    Color_RGBA8 diffuse;
    Color_RGBA8 specular0;
    Color_RGBA8 specular1;
    Color_RGBA8 constant0;
    Color_RGBA8 constant1;
    Color_RGBA8 constant2;
    Color_RGBA8 constant3;
    Color_RGBA8 constant4;
    Color_RGBA8 constant5;
    Color_RGBAf bufferColor;
    u16 bumpTexture;
    u16 bumpMode;
    u8 isBumpRenormalize;
    Fragment fragLighting;
    u32 texEnvStageUsed;
    s16 texEnvStagesIndices[6]; // indices for the combiner list
    u8 alphaTestEnabled;
    u8 alphaTestReferenceValue;
    u16 alphaTestFunction;
    u8 depthTestEnabled;
    u8 depthWriteEnabled;
    u16 depthTestFunction;
    u32 blendMode;
    u16 alphaSrcFunc;
    u16 alphaDstFunc;
    u32 alphaEquation;
    u16 colorSrcFunc;
    u16 colorDstFunc;
    u32 colorEquation;
    Color_RGBAf blendColor;
} Material;

typedef enum CombinerMode : u16 {
    COMBINERMODE_REPLACE         = 0x1E01,
    COMBINERMODE_MODULATE        = 0x2100,
    COMBINERMODE_ADD             = 0x0104,
    COMBINERMODE_ADDSIGNED       = 0x8574,
    COMBINERMODE_INTERPOLATE     = 0x8575,
    COMBINERMODE_SUBTRACT        = 0x84E7,
    COMBINERMODE_DOTPRODUCT3RGB  = 0x86AE,
    COMBINERMODE_DOTPRODUCT3RGBA = 0x86AF,
    COMBINERMODE_MULTADD         = 0x6401,
    COMBINERMODE_ADDMULT         = 0x6402,
} CombinerMode;

typedef enum CombinerSrc : u16 {
    COMBINERSRC_PRIMARYCOLOR           = 0x8577,
    COMBINERSRC_FRAGMENTPRIMARYCOLOR   = 0x6210,
    COMBINERSRC_FRAGMENTSECONDARYCOLOR = 0x6211,
    COMBINERSRC_TEXTURE_0              = 0x84C0,
    COMBINERSRC_TEXTURE_1              = 0x84C1,
    COMBINERSRC_TEXTURE_2              = 0x84C2,
    COMBINERSRC_TEXTURE_3              = 0x84C3,
    COMBINERSRC_PREVIOUSBUFFER         = 0x8579,
    COMBINERSRC_CONSTANTCOL            = 0x8576,
    COMBINERSRC_PREVIOUS               = 0x8578,
} CombinerSrc;

typedef enum CombinerOp : u16 {
    COMBINEROP_COLOR         = 0x0300,
    COMBINEROP_ONEMINUSCOLOR = 0x0301,
    COMBINEROP_ALPHA         = 0x0302,
    COMBINEROP_ONEMINUSALPHA = 0x0303,
    COMBINEROP_RED           = 0x8580,
    COMBINEROP_ONEMINUSRED   = 0x8583,
    COMBINEROP_GREEN         = 0x8581,
    COMBINEROP_ONEMINUSGREEN = 0x8584,
    COMBINEROP_BLUE          = 0x8582,
    COMBINEROP_ONEMINUSBLUE  = 0x8585,
} CombinerOp;

typedef struct Combiner {
    CombinerMode combinerModeColor;
    CombinerMode combinerModeAlpha;
    s16 scaleColor;
    s16 scaleAlpha;
    CombinerSrc bufferColor;
    CombinerSrc bufferAlpha;
    CombinerSrc sourceColors[3];
    CombinerOp operandColors[3];
    CombinerSrc sourceAlphas[3];
    CombinerOp operandAlphas[3];
    u32 constantColorIndex;
} Combiner;
_Static_assert(sizeof(Combiner) == 0x28, "Combiner size");

typedef struct CMB_MATS {
    /* 0x00 */ char magic[4];
    /* 0x04 */ u32 size;
    /* 0x08 */ u32 materialCount;
    /* 0x0C */ Material materials[];
    //         Combiner combiners[];
} CMB_MATS;

static inline CMB_MATS* Cmb_GetMatsChunk(void* cmb) {
    return (CMB_MATS*)(((u32)cmb) + ((CMB_HEAD*)cmb)->MATSOffset);
}

static inline Combiner* Cmb_GetCombiners(CMB_MATS* cmbMats) {
    return (Combiner*)&cmbMats->materials[cmbMats->materialCount];
}

typedef enum TextureFormatGL : u32 {
    ETC1     = 0x0000675A,
    ETC1A4   = 0x0000675B,
    RGB8     = 0x14016754,
    RGBA8    = 0x14016752,
    RGBA4444 = 0x80336752,
    RGBA5551 = 0x80346752,
    RGB565   = 0x83636754,
    A8       = 0x14016756,
    A4       = 0x67616756,
    L8       = 0x14016757,
    L4       = 0x67616757,
    LA8      = 0x14016758,
    LA4      = 0x67606758,
    HILO8    = 0x14016759,
} TextureFormatGL;

typedef struct TextureEntry {
    /* 0x00 */ u32 dataLength;
    /* 0x04 */ u16 mipMapCount;
    /* 0x06 */ u8 isETC1;
    /* 0x07 */ u8 isCubeMap;
    /* 0x08 */ u16 width;
    /* 0x0A */ u16 height;
    /* 0x0C */ union {
        TextureFormatGL textureFormatGL;
        struct {
            u16 imageFormat;
            u16 dataType;
        };
    };
    /* 0x10 */ u32 dataOffset;
    /* 0x14 */ char name[16];
} TextureEntry;

typedef struct CMB_TEX {
    /* 0x00 */ char magic[4];
    /* 0x04 */ u32 size;
    /* 0x08 */ u32 textureCount;
    /* 0x0C */ TextureEntry entries[];
} CMB_TEX;

static inline CMB_TEX* Cmb_GetTexChunk(void* cmb) {
    return (CMB_TEX*)(((u32)cmb) + ((CMB_HEAD*)cmb)->TEXOffset);
}

typedef struct Mesh {
    u16 sepdIndex;
    u8 materialIndex;
    u8 id;
} Mesh;

typedef struct CMB_MSHS {
    /* 0x00 */ char magic[4];
    /* 0x04 */ u32 size;
    /* 0x08 */ u32 meshCount;
    /* 0x0C */ u16 opaqueMeshCount; // The remainder of "OpaqueMeshCount" are transparent meshes
    /* 0x0E */ u16 idCount;
    /* 0x10 */ Mesh meshes[];
} CMB_MSHS;

typedef struct CMB_SHP {
    /* 0x00 */ char magic[4];
    /* 0x04 */ u32 size;
    /* 0x08 */ u32 sepdCount;
    /* 0x0C */ u32 flags;
    //         SEPD chunks of variable size
} CMB_SHP;

typedef struct CMB_SKLM {
    /* 0x00 */ char magic[4];
    /* 0x04 */ u32 size;
    /* 0x08 */ u32 mshsOffset;
    /* 0x0C */ u32 shpOffset;
    /* 0x10 */ CMB_MSHS mshs;
    //         CMB_SHP shp;
} CMB_SKLM;

static inline CMB_MSHS* Cmb_GetMeshesChunk(void* cmb) {
    CMB_SKLM* sklmChunk = (CMB_SKLM*)(((u32)cmb) + ((CMB_HEAD*)cmb)->SKLMOffset);
    return &sklmChunk->mshs;
}

typedef struct CmbManager {
    /* 0x00 */ void* cmbChunk;
    /* 0x04 */ u32 unk_04;
    /* 0x08 */ u32 unk_08;
    /* 0x0C */ u32 unk_0C;
    /* 0x10 */ u32 unk_10;
    /* 0x14 */ u32 unk_14;
    /* 0x18 */ u32 unk_18;
    /* 0x1C */ u32 unk_1C;
    /* 0x20 */ u32 unk_20;
    /* 0x24 */ u32 unk_24;
    /* 0x28 */ u32 unk_28;
    /* 0x2C */ u32 unk_2C;
    /* 0x30 */ u32 unk_30;
    /* 0x34 */ u32 unk_34;
    /* 0x38 */ u32 unk_38;
    /* 0x3C */ u32 cmbChunkSize;
    /* 0x40 */ u32 unk_40;
    /* 0x44 */ u32 unk_44;
} CmbManager;

struct SubStaticClass_55A19C_44;
typedef void (*VTable_4ECA6C_Func)(struct SubStaticClass_55A19C_44* this, CmbManager* cmbMan);
typedef struct VTable_4ECA6C {
    VTable_4ECA6C_Func func0;
    VTable_4ECA6C_Func func1;
    VTable_4ECA6C_Func func2;
    VTable_4ECA6C_Func func3;
    VTable_4ECA6C_Func destroyCmb;
    VTable_4ECA6C_Func func5;
    VTable_4ECA6C_Func func6;
} VTable_4ECA6C;

typedef struct SubStaticClass_55A19C_44 {
    /* 0x010 */ VTable_4ECA6C* vTable;
    // ... size unknown
} SubStaticClass_55A19C_44;

typedef struct StaticClass_55A19C {
    /* 0x000 */ char unk_000[0x044];
    /* 0x044 */ SubStaticClass_55A19C_44* sub44;
    // ... size unknown
} StaticClass_55A19C;

extern StaticClass_55A19C gStaticClass_55A19C;

CmbManager* CmbManager_Destroy(CmbManager* cmbMan);

#endif //_Z3DCMB_H_
