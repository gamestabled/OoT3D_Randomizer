.arm

.section .patch_before_GlobalContext_Update
.global before_GlobalContext_Update_patch
before_GlobalContext_Update_patch:
    bl hook_before_GlobalContext_Update

.section .patch_after_GlobalContext_Update
.global after_GlobalContext_Update_patch
after_GlobalContext_Update_patch:
    b hook_after_GlobalContext_Update

.section .patch_Gfx_Update
.global GfX_Update_patch
GfX_Update_patch:
    b hook_Gfx_Update

.section .patch_IncomingGetItemID
.global IncomingGetItemID_patch
IncomingGetItemID_patch:
    str r5,[r4,#0x2B0]
    bl hook_IncomingGetItemID

.section .patch_SaveFile_Init
.global SaveFile_Init_patch
SaveFile_Init_patch:
    bl hook_SaveFile_Init

.section .patch_OverrideOcarinaSongs
.global OverrideOcarinaSongs_patch
OverrideOcarinaSongs_patch:
    bl Cutscene_OverrideOcarinaSongs

.section .patch_OverrideTextID
.global OverrideTextID_patch
OverrideTextID_patch:
    bl hook_OverrideTextID

.section .patch_OverrideItemID
.global OverrideItemID_patch
OverrideItemID_patch:
    bl hook_OverrideItemID

.section .patch_OverrideGraphicID_351B94
.global OverrideGraphicID_patch_351B94
OverrideGraphicID_patch_351B94:
    bl hook_OverrideGraphicID_351B94

.section .patch_OverrideGraphicID_35495C
.global OverrideGraphicID_patch_35495C
OverrideGraphicID_patch_35495C:
    bl hook_OverrideGraphicID_35495C

.section .patch_OverrideGraphicID_354BB8
.global OverrideGraphicID_patch_354BB8
OverrideGraphicID_patch_354BB8:
    bl hook_OverrideGraphicID_354BB8

.section .patch_OverrideGraphicID_4BC604
.global OverrideGraphicID_patch_4BC604
OverrideGraphicID_patch_4BC604:
    bl hook_OverrideGraphicID_351B94

.section .patch_OverrideGraphicID_4BD5D0
.global OverrideGraphicID_patch_4BD5D0
OverrideGraphicID_patch_4BD5D0:
    bl hook_OverrideGraphicID_351B94

.section .patch_NoLensOfTruthNaviText
    nop

.section .patch_NoSilverGauntletsCutsceneWarp
    b 0x2BC350

.section .patch_ChildShootingGallery
.global ChildShootingGallery_patch
ChildShootingGallery_patch:
    mov r0,#0x60
    nop

.section .patch_AdultShootingGallery
.global AdultShootingGallery_patch
AdultShootingGallery_patch:
    nop
    nop
    mov r0,#0x30
    b 0x38AB78

.section .patch_GerudoArcheryOne
.global GerudoArcheryOne_patch
GerudoArcheryOne_patch:
    mov r4,#0x30
    b 0x3AFA44
    nop
    nop

.section .patch_GerudoArcheryTwo
.global GerudoArcheryTwo_patch
GerudoArcheryTwo_patch:
    mov r5,#0x30
    b 0x3C2D90
    nop
    nop

.section .patch_ScrubStickUpgradeOne
.global ScrubStickUpgradeOne_patch
ScrubStickUpgradeOne_patch:
    nop

.section .patch_ScrubNutUpgradeOne
.global ScrubNutUpgradeOne_patch
ScrubNutUpgradeOne_patch:
    nop

.section .patch_ScrubStickUpgradeTwo
.global ScrubStickUpgradeTwo_patch
ScrubStickUpgradeTwo_patch:
    nop

.section .patch_ScrubNutUpgradeTwo
.global ScrubNutUpgradeTwo_patch
ScrubNutUpgradeTwo_patch:
    nop

.section .patch_ChildRollingGoron
.global ChildRollingGoron_patch
ChildRollingGoron_patch:
    mov r2,#0x34
    nop

.section .patch_AdultRollingGoronOne
.global AdultRollingGoronOne_patch
AdultRollingGoronOne_patch:
    b 0x19549C

.section .patch_AdultRollingGoronTwo
.global AdultRollingGoronTwo_patch
AdultRollingGoronTwo_patch:
    b hook_AdultRollingGoronTwo

.section .patch_DaruniaCheckStrength
.global DaruniaStrengthCheck_patch
DaruniaStrengthCheck_patch:
    b hook_DaruniaStrengthCheck

.section .patch_LostWoodsShootingGame
.global LostWoodsShootingGame_patch
LostWoodsShootingGame_patch:
    mov r2,#0x60
    nop

.section .patch_SkulltulaRewardOne
.global SkulltulaRewardOne_patch
SkulltulaRewardOne_patch:
    b 0x12CC9C

.section .patch_SkulltulaRewardTwo
.global SkulltulaRewardTwo_patch
SkulltulaRewardTwo_patch:
    b 0x12CD6C

.section .patch_KingZoraGiveTunic
.global KingZoraGiveTunic_patch
KingZoraGiveTunic_patch:
    mov r0,#0x4000
    add r0,r0,#0x12

.section .patch_KingZoraSecondTunic
.global KingZoraSecondTunic_patch
KingZoraSecondTunic_patch:
    b 0x1B6A40

.section .patch_DampeRollHigh
.global DampeRollHigh_patch
DampeRollHigh_patch:
    mov r0,#0x3
    b 0x3C3458

.section .patch_DampeCheckRewardFlag
.global DampeCheckRewardFlag_patch
DampeCheckRewardFlag_patch:
    cpyeq r0,r4
    bleq EnTk_SetRewardFlag

.section .patch_DampeSetCollectibleFlag
    .word 0x00000206

.section .patch_DampeCheckCollectibleFlag
.global DampeCheckCollectibleFlag_patch
DampeCheckCollectibleFlag_patch:
    bl hook_DampeCheckCollectibleFlag

.section .patch_DampeCheckCanDig1
.global DampeCheckCanDig1_patch
DampeCheckCanDig1_patch:
    mov r0,#0x01

.section .patch_DampeCheckCanDig2
.global DampeCheckCanDig2_patch
DampeCheckCanDig2_patch:
    mov r0,#0x01

.section .patch_TokenNoItemGive1
.global TokenNoItemGive1_patch
TokenNoItemGive1_patch:
    nop

.section .patch_TokenNoItemGive2
.global TokenNoItemGive2_patch
TokenNoItemGive2_patch:
    nop

.section .patch_GetToken1
.global GetToken1_patch
GetToken1_patch:
    bl hook_GetToken

.section .patch_GetToken2
.global GetToken2_patch
GetToken2_patch:
    bl hook_GetToken

.section .patch_GetCustomMessageEntryOne
.global GetCustomMessageEntryOne_patch
GetCustomMessageEntryOne_patch:
    bl Message_GetCustomEntry

.section .patch_GetCustomMessageEntryTwo
.global GetCustomMessageEntryTwo_patch
GetCustomMessageEntryTwo_patch:
    bl Message_GetCustomEntry

.section .patch_GetCustomMessageTextOne
.global GetCustomMessageTextOne_patch
GetCustomMessageTextOne_patch:
    bl Message_GetCustomText

.section .patch_GetCustomMessageTextTwo
.global GetCustomMessageTextTwo_patch
GetCustomMessageTextTwo_patch:
    bl Message_GetCustomText

.section .patch_FastChests
.global FastChests_patch
FastChests_patch:
    b 0x354D98

.section .patch_DampeChest
.global DampeChest_patch
DampeChest_patch:
    cpy r0,r4
    bl EnPoRelay_CheckChestFlag
    nop

.section .patch_RainbowBridge
.global RainbowBridge_patch
RainbowBridge_patch:
    push {r0-r12, lr}
    bl BgGjyoBridge_CheckCondition
    cmp r0,#0x0
    pop {r0-r12, lr}
    beq 0x3E7D70
    b 0x3E7CE0

.section .patch_ModelSpawnGetObjectStatus
.global ModelSpawnGetObjectStatus_patch
ModelSpawnGetObjectStatus_patch:
    bl hook_ModelSpawnGetObjectStatus

.section .patch_ExtendedObjectClear
.global ExtendedObjectClear_patch
ExtendedObjectClear_patch:
    bl ExtendedObject_Clear

.section .patch_SariasGift
.global SariasGift_patch
SariasGift_patch:
    bl ItemOverride_GiveSariasGift

.section .patch_DekuTheaterSkullMask
.global DekuTheaterSkullMask_patch
DekuTheaterSkullMask_patch:
    mov r0,#0x77
    nop

.section .patch_DekuTheaterMaskOfTruth
.global DekuTheaterMaskOfTruth_patch
DekuTheaterMaskOfTruth_patch:
    mov r0,#0x7A
    nop

.section .patch_PoeCollectorCheckPoints
.global PoeCollectorCheckPoints_patch
PoeCollectorCheckPoints_patch:
    bl hook_PoeCollectorCheckPoints

.section .patch_LACSConditionOne
.global LACSConditionOne_patch
LACSConditionOne_patch:
    nop

.section .patch_LACSConditionTwo
.global LACSConditionTwo_patch
LACSConditionTwo_patch:
    bl Cutscene_OverrideLACS
    nop
    nop
    nop
    nop

.section .patch_RequiemLocation
.global RequiemLocation_patch
RequiemLocation_patch:
    bl Cutscene_OverrideRequiem

.section .patch_NocturneLocation
.global NocturneLocation_patch
NocturneLocation_patch:
    bl Cutscene_OverrideNocturne
    b 0x44F180

.section .patch_BiggoronDayCheck
.global BiggoronDayCheck_patch
BiggoronDayCheck_patch:
    mov r0,#0x3

.section .patch_ItemEtceteraModelDraw
.global ItemEtceteraModelDraw_patch
ItemEtceteraModelDraw_patch:
    bl hook_ItemEtceteraModelDraw

.section .patch_KokiriCheckOpenForest
.global Kokiri_CheckOpenForest_patch
Kokiri_CheckOpenForest_patch:
    bl hook_KokiriCheckOpenForest

.section .patch_BombchuBowlingStaticReward
.global BombchuBowlingStaticReward_patch
BombchuBowlingStaticReward_patch:
    b 0x20618C

.section .patch_EnExItemModelDraw
.global EnExItemModelDraw_patch
EnExItemModelDraw_patch:
    bl hook_EnExItemModelDraw

.section .patch_loader
.global loader_patch

loader_patch:
    b hook_into_loader
