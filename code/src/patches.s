.arm

.section .patch_loader
.global loader_patch
loader_patch:
    b hook_into_loader

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
    b hook_OverrideTextID

.section .patch_OverrideItemID
.global OverrideItemID_patch
OverrideItemID_patch:
    b hook_OverrideItemID

.section .patch_OverrideDrawItemOne
.global OverrideDrawItemOne_patch
OverrideDrawItemOne_patch:
    b hook_OverrideDrawItemOne

.section .patch_OverrideDrawItemTwo
.global OverrideDrawItemTwo_patch
OverrideDrawItemTwo_patch:
    bl hook_OverrideDrawItemTwo

.section .patch_OverrideDrawItemThree
.global OverrideDrawItemThree_patch
OverrideDrawItemThree_patch:
    bl hook_OverrideDrawItemThree

.section .patch_OverrideGiDrawIdPlusOne_Ground
.global OverrideGiDrawIdPlusOne_Ground_patch
OverrideGiDrawIdPlusOne_Ground_patch:
    bl hook_OverrideGiDrawIdPlusOne

.section .patch_OverrideGiDrawIdPlusOne_Water
.global OverrideGiDrawIdPlusOne_Water_patch
OverrideGiDrawIdPlusOne_Water_patch:
    bl hook_OverrideGiDrawIdPlusOne

.section .patch_EditDrawGetItemBeforeModelSpawn
.global EditDrawGetItemBeforeModelSpawn_patch
EditDrawGetItemBeforeModelSpawn_patch:
    bl hook_EditDrawGetItemBeforeModelSpawn

.section .patch_EditDrawGetItemAfterModelSpawn
.global EditDrawGetItemAfterModelSpawn_patch
EditDrawGetItemAfterModelSpawn_patch:
    bl hook_EditDrawDetItemAfterModelSpawn

.section .patch_EditDrawGetItemAfterMatrixUpdate
.global EditDrawGetItemAfterMatrixUpdate_patch
EditDrawGetItemAfterMatrixUpdate_patch:
    bl hook_EditDrawGetItemAfterMatrixUpdate

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

.section .patch_ChildRollingGoronDontCheckBombBag
.global ChildRollingGoronDontCheckBombBag_patch
ChildRollingGoronDontCheckBombBag_patch:
    nop

.section .patch_AdultRollingGoronIgnoreMedallion
.global AdultRollingGoronIgnoreMedallion_patch
AdultRollingGoronIgnoreMedallion_patch:
    b 0x19546C

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

.section .patch_LostWoodsShootingGameTwo
.global LostWoodsShootingGameTwo_patch
LostWoodsShootingGameTwo_patch:
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

.section .patch_KingZoraCheckMovedFlag
.global KingZoraCheckMovedFlag_patch
KingZoraCheckMovedFlag_patch:
    bl hook_KingZoraCheckMovedFlag

.section .patch_KingZoraIgnoreSapphire
.global KingZoraIgnoreSapphire_patch
KingZoraIgnoreSapphire_patch:
    nop
    nop

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
    .word 0x00000806

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
    bl hook_FastChests

.section .patch_FastChestsTwo
    bl hook_FastChests
    bne 0x3F10B0
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop

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
    b 0x3E7D34

.section .patch_ExtendedObjectClear
.global ExtendedObjectClear_patch
ExtendedObjectClear_patch:
    bl ExtendedObject_Clear

.section .patch_SariasGift
.global SariasGift_patch
SariasGift_patch:
    bl ItemOverride_GiveSariasGift
    nop
    nop

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

.section .patch_MinuetLocation
.global MinuetLocation_patch
MinuetLocation_patch:
    bl Cutscene_OverrideMinuet
    b 0x26C47C

.section .patch_BoleroLocation
.global BoleroLocation_patch
BoleroLocation_patch:
    bl Cutscene_OverrideBolero
    b 0x26C47C

.section .patch_SerenadeCheckChestFlag
.global SerenadeCheckChestFlag_patch
SerenadeCheckChestFlag_patch:
    bl hook_SerenadeCheckChestFlag

.section .patch_SerenadeLocation
.global SerenadeLocation_patch
SerenadeLocation_patch:
    bl Cutscene_OverrideSerenade
    b 0x2B25A8

.section .patch_RequiemLocation
.global RequiemLocation_patch
RequiemLocation_patch:
    nop
    nop
    bl Cutscene_OverrideRequiem

.section .patch_NocturneLocation
.global NocturneLocation_patch
NocturneLocation_patch:
    bl Cutscene_OverrideNocturne
.if _EUR_==1
    b 0x44F1A0
.else
    b 0x44F180
.endif

.section .patch_FreeScarecrow
.global FreeScarecrow_patch
FreeScarecrow_patch:
    bl hook_ScarecrowCheckToBeActivated

.section .patch_MasterSwordAlwaysDrop
.global MasterSwordAlwaysDrop_patch
MasterSwordAlwaysDrop_patch:
    nop

.section .patch_PreludeLocation
.global PreludeLocation_patch
PreludeLocation_patch:
    bl Cutscene_OverridePrelude
    cmp r0,#0x0
    beq 0x18DAD0
    b 0x18DA38

.section .patch_LullabyLocation
.global LullabyLocation_patch
LullabyLocation_patch:
    bl Cutscene_OverrideLullaby
    b 0x3A0AC8

.section .patch_EponasSongCheckFlag
.global EponasSongCheckFlag_patch
EponasSongCheckFlag_patch:
    bl hook_EponasSongCheckFlag

.section .patch_EponasSongCheckFlagTwo
.global EponasSongCheckFlagTwo_patch
EponasSongCheckFlagTwo_patch:
    bl hook_EponasSongCheckFlag

.section .patch_EponasSongLocation
.global EponasSongLocation_patch
EponasSongLocation_patch:
    bl Cutscene_OverrideEponasSong
    b 0x3C61CC

.section .patch_MalonNextAction
.global MalonNextAction_patch
MalonNextAction_patch:
    .word 0x3D2A14

.section .patch_SariasSongCheckFlag
.global SariasSongCheckFlag_patch
SariasSongCheckFlag_patch:
    bl hook_SariasSongCheckFlag

.section .patch_SariasSongItemGive
.global SariasSongItemGive_patch
SariasSongItemGive_patch:
    nop

.section .patch_SariasSongLocation
.global SariasSongLocation_patch
SariasSongLocation_patch:
    bl Cutscene_OverrideSariasSong
    b 0x12C92C

.section .patch_SunsSongLocation
.global SunsSongLocation_patch
SunsSongLocation_patch:
    bl Cutscene_OverrideSunsSong
    b 0x2888F0

.section .patch_SongOfTimeLocation
.global SongOfTimeLocation_patch
SongOfTimeLocation_patch:
    cpy r0,r5
    bl Cutscene_OverrideSongOfTime
    b 0x3C3780

.section .patch_SongOfStormsLocation
.global SongOfStormsLocation_patch
SongOfStormsLocation_patch:
    bl Cutscene_OverrideSongOfStorms
    b 0x1427F8

.section .patch_BiggoronDayCheck
.global BiggoronDayCheck_patch
BiggoronDayCheck_patch:
    mov r0,#0x3

.section .patch_BiggoronGetTextId
.global BiggoronGetTextId_patch
BiggoronGetTextId_patch:
    bl EnGo2_rGetTextIdGoronDmtBiggoron
    b 0x195524

.section .patch_BiggoronCheckBGSFlag
.global BiggoronCheckBGSFlag_patch
BiggoronCheckBGSFlag_patch:
    nop
    nop
    nop

.section .patch_BiggoronDontSetBGSFlag
.global BiggoronDontSetBGSFlag_patch
BiggoronDontSetBGSFlag_patch:
    nop

.section .patch_BiggoronSetTextId
.global BiggoronSetTextId_patch
BiggoronSetTextId_patch:
    push {r0-r12, lr}
    cpy r0,r4
    bl EnGo2_rBiggoronSetTextId
    pop {r0-r12, lr}
    b 0x1D8B80

.section .patch_BiggoronAfterGiveItem
.global BiggoronAfterGiveItem_patch
BiggoronAfterGiveItem_patch:
    .word EnGo2_AfterGiveItem

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

.section .patch_ChildBlueWarpOverride
.global ChildBlueWarpOverride_patch
ChildBlueWarpOverride_patch:
    push {r0-r12, lr}
    bl Cutscene_BlueWarpOverride
    pop {r0-r12, lr}
    b 0x3F58A8

.section .patch_RutoBlueWarpOverride
.global RutoBlueWarpOverride_patch
RutoBlueWarpOverride_patch:
    push {r0-r12, lr}
    bl Cutscene_BlueWarpOverride
    pop {r0-r12, lr}
    b 0x1A1944

.section .patch_AdultBlueWarpOverride
.global AdultBlueWarpOverride_patch
AdultBlueWarpOverride_patch:
    push {r0-r12, lr}
    bl Cutscene_BlueWarpOverride
    pop {r0-r12, lr}
    b 0x1E4274

.section .patch_EnExItemModelDraw
.global EnExItemModelDraw_patch
EnExItemModelDraw_patch:
    bl hook_EnExItemModelDraw

.section .patch_DemoEffectMedallionDraw
.global DemoEffectMedallionDraw_patch
DemoEffectMedallionDraw_patch:
    b hook_DemoEffectMedallionDraw

.section .patch_DemoEffectStoneDraw
.global DemoEffectStoneDraw_patch
DemoEffectStoneDraw_patch:
    b hook_DemoEffectStoneDraw

.section .patch_DekuSproutCheckForest
.global DekuSproutCheckForest_patch
DekuSproutCheckForest_patch:
    ldr r0, [r0,#0xEF4]
    nop
    tst r0,#0x100

.section .patch_EnKoInitCheckForest_165834
.global EnKoInitCheckForest_165834_patch
EnKoInitCheckForest_165834_patch:
    bl hook_EnKoInitCheckForest
    nop
    nop

.section .patch_EnKoInitCheckForest_165878
.global EnKoInitCheckForest_165878_patch
EnKoInitCheckForest_165878_patch:
    bl hook_EnKoInitCheckForest
    nop
    nop

.section .patch_EnKoInitCheckForest_1658C0
.global EnKoInitCheckForest_1658C0_patch
EnKoInitCheckForest_1658C0_patch:
    bl hook_EnKoInitCheckForest
    nop
    nop

.section .patch_EnKoInitCheckForest_1658F0
.global EnKoInitCheckForest_1658F0_patch
EnKoInitCheckForest_1658F0_patch:
    bl hook_EnKoInitCheckForest
    nop
    nop

.section .patch_FireArrowCheckChestFlagOne
.global FireArrowCheckChestFlagOne_patch
FireArrowCheckChestFlagOne_patch:
    bl hook_FireArrowCheckChestFlag

.section .patch_FireArrowCheckChestFlagTwo
.global FireArrowCheckChestFlagTwo_patch
FireArrowCheckChestFlagTwo_patch:
    bl hook_FireArrowCheckChestFlag

.section .patch_FireArrowRequirement
.global FireArrowRequirement_patch
FireArrowRequirement_patch:
    ldr r2, [r1,#0xEF4]
    nop
    tst r2,#0x400

.section .patch_BusinessScrubCheckFlags
.global BusinessScrubCheckFlags_patch
BusinessScrubCheckFlags_patch:
    cpy r0,r4
    bl EnShopnnuts_rCheckFlags
    cmp r0,#0x0

.section .patch_BusinessScrubTable
.global BusinessScrubTable_patch
.global rScrubTable
BusinessScrubTable_patch:
    .word rScrubTable

.section .patch_KakarikoGateCheck
.global KakarikoGateCheck_patch
KakarikoGateCheck_patch:
    bl hook_KakarikoGateCheck

.section .patch_FairyReward
.global FairyReward_patch
FairyReward_patch:
    cpy r0,r4
    bl Cutscene_OverrideFairyReward
    b 0x3E75F8

.section .patch_PoeCollectorGetFirstTextbox
.global PoeCollectorGetFirstTextbox_patch
PoeCollectorGetFirstTextbox_patch:
    bl hook_PoeCollectorGetFirstTextbox

.section .patch_OcarinaMinigameRewardsOrder
.global OcarinaMinigameRewardsOrder_patch
OcarinaMinigameRewardsOrder_patch:
    .word 0x76
    .word 0x4D
    .word 0x4E

.section .patch_OcarinaMinigameEndAfterWin
.global OcarinaMinigameEndAfterWin_patch
OcarinaMinigameEndAfterWin_patch:
    nop

.section .patch_ISGPutaway
.global ISGPutaway_patch
ISGPutaway_patch:
    bl hook_RestoreISG

.section .patch_ISGCrouchStab
.global ISGCrouchStab_patch
ISGCrouchStab_patch:
    bl hook_RestoreISG

.section .patch_ApplyDamageMultiplier
.global ApplyDamageMultiplier_patch
ApplyDamageMultiplier_patch:
    bl hook_ApplyDamageMultiplier

.section .patch_SceneInitAfterCopyScenes
.global SceneInitAfterCopyScenes_patch
SceneInitAfterCopyScenes_patch:
    b hook_SceneInitAfterCopyScenes

.section .patch_StoreChildBButtonEquip
.global StoreChildBButtonEquip_patch
StoreChildBButtonEquip_patch:
    b hook_StoreChildBButtonEquip

.section .patch_AlwaysRestoreChildEquips
.global AlwaysRestoreChildEquips_patch
AlwaysRestoreChildEquips_patch:
    nop

.section .patch_ChildDontEquipSwordSlotByDefault
.global ChildDontEquipSwordSlotByDefault_patch
ChildDontEquipSwordSlotByDefault_patch:
    push {r1-r12, lr}
    bl SaveFile_RestoreChildEquips
    pop {r1-r12, lr}
    nop

.section .patch_LullabyCheckFlag
.global LullabyCheckFlag_patch
LullabyCheckFlag_patch:
    bl hook_LullabyCheckFlag

.section .patch_FishingIgnoreTempBOne
.global FishingIgnoreTempBOne_patch
FishingIgnoreTempBOne_patch:
    b hook_FishingIgnoreTempBOne

.section .patch_FishingIgnoreTempBTwo
.global FishingIgnoreTempBTwo_patch
FishingIgnoreTempBTwo_patch:
    b hook_FishingIgnoreTempBTwo

.section .patch_ItemGiveBombchuDropOne
.global ItemGiveBombchuDropOne_patch
ItemGiveBombchuDropOne_patch:
    mov r1,#0x96

.section .patch_ItemGiveBombchuDropTwo
.global ItemGiveBombchuDropTwo_patch
ItemGiveBombchuDropTwo_patch:
    mov r1,#0x96

.section .patch_ConvertBombDropOne
.global ConvertBombDropOne_patch
ConvertBombDropOne_patch:
    b hook_ConvertBombDropOne

.section .patch_ConvertBombDropTwo
.global ConvertBombDropTwo_patch
ConvertBombDropTwo_patch:
    b hook_ConvertBombDropTwo

.section .patch_BeanDaddyModifyBeansBought
.global BeanDaddyModifyBeansBought_patch
BeanDaddyModifyBeansBought_patch:
    bl hook_BeanDaddyModifyBeansBought

.section .patch_BeanDaddyModifyPrice
.global BeanDaddyModifyPrice_patch
BeanDaddyModifyPrice_patch:
    bl hook_BeanDaddyModifyPrice

.section .patch_BeanDaddyPurchase
.global BeanDaddyPurchase_patch
BeanDaddyTakeRupees_patch:
    bl EnMs_Purchase

.section .patch_CheckGerudoToken_18B368
.global CheckGerudoToken_18B368_patch
CheckGerudoToken_18B368_patch:
    push {r1-r12, lr}
    bl SaveFile_CheckGerudoToken
    pop {r1-r12, lr}
    cmp r0,#0x0

.section .patch_CheckGerudoToken_18B3A0
.global CheckGerudoToken_18B3A0_patch
CheckGerudoToken_18B3A0_patch:
    push {r1-r12, lr}
    bl SaveFile_CheckGerudoToken
    pop {r1-r12, lr}
    cmp r0,#0x0

.section .patch_CheckGerudoToken_18B3C0
.global CheckGerudoToken_18B3C0_patch
CheckGerudoToken_18B3C0_patch:
    push {r1-r12, lr}
    bl SaveFile_CheckGerudoToken
    pop {r1-r12, lr}
    cmp r0,#0x0

.section .patch_CheckGerudoToken_18B448
.global CheckGerudoToken_18B448_patch
CheckGerudoToken_18B448_patch:
    push {r1-r12, lr}
    bl SaveFile_CheckGerudoToken
    pop {r1-r12, lr}
    cmp r0,#0x0

.section .patch_CheckGerudoToken_18B6F4
.global CheckGerudoToken_18B6F4_patch
CheckGerudoToken_18B6F4_patch:
    bl hook_CheckGerudoToken
    cmp r0,#0x1

.section .patch_CheckGerudoToken_18B710
.global CheckGerudoToken_18B710_patch
CheckGerudoToken_18B710_patch:
    bl hook_CheckGerudoToken
    cmp r0,#0x1

.section .patch_CheckGerudoToken_1D7AD4
.global CheckGerudoToken_1D7AD4_patch
CheckGerudoToken_1D7AD4_patch:
    bl hook_CheckGerudoToken
    cmp r0,#0x1

.section .patch_CheckGerudoToken_269884
.global CheckGerudoToken_269884_patch
CheckGerudoToken_269884_patch:
    bl hook_CheckGerudoToken
    cmp r0,#0x1

.section .patch_MovableBlockSpeed
    .word 0x40800000

.section .patch_MovableBlockCooldownTimer
.global MovableBlockCooldownTimer_patch
MovableBlockCooldownTimer_patch:
    mov r0,#0x1

.section .patch_MilkCrateSpeed
    .word 0x40800000

.section .patch_MilkCrateCooldownTimer
.global MilkCrateCooldownTimer_patch
MilkCrateCooldownTimer_patch:
    mov r0,#0x1

.section .patch_AmyBlockSpeed
    .word 0x40800000

.section .patch_AmyBlockCooldownTimer
.global AmyBlockCooldownTimer_patch
AmyBlockCooldownTimer_patch:
    mov r1,#0x1

.section .patch_FireBlockSpeed
    .word 0x3DCCCCCD

.section .patch_ArmosPushSpeed
    .word 0x3F800000

.section .patch_ArmosCooldownTimer
    mov r0,#0xC

.section .patch_ForestTempleBasementPuzzleDelay
.global ForestTempleBasementPuzzleDelay_patch
ForestTempleBasementPuzzleDelay_patch:
    cmp r0,#0x1

.section .patch_CowBottleCheck
.global CowBottleCheck_patch
CowBottleCheck_patch:
    bl hook_CowBottleCheck

.section .patch_CowItemOverride
.global CowItemOverride_patch
CowItemOverride_patch:
    b hook_CowItemOverride

.section .patch_AnjuCheckCuccoAmount
.global AnjuCheckCuccoAmount_patch
AnjuCheckCuccoAmount_patch:
    b hook_AnjuCheckCuccoAmount

.section .patch_FrogReward
.global FrogReward_patch
FrogReward_patch:
    b hook_FrogReward

.section .patch_FrogRewardPurple
.global FrogRewardPurple_patch
FrogRewardPurple_patch:
    beq hook_FrogReward

.section .patch_CanPlayBombchuBowlingOne
.global CanPlayBombchuBowlingOne_patch
CanPlayBombchuBowlingOne_patch:
    bl hook_CanPlayBombchuBowling

.section .patch_CanPlayBombchuBowlingTwo
.global CanPlayBombchuBowlingTwo_patch
CanPlayBombchuBowlingTwo_patch:
    bl hook_CanPlayBombchuBowling

.section .patch_BombchuBowlingAlwaysFirstPrize
.global BombchuBowlingAlwaysFirstPrize_patch
BombchuBowlingAlwaysFirstPrize_patch:
    mov r0,#0x0

.section .patch_BombchuBowlingPrizeOrder
.global BombchuBowlingPrizeOrder_patch
BombchuBowlingPrizeOrder_patch:
    .word 0x0021CAFC
    .word 0x0021CB0C
    .word 0x0021CAF4

.section .patch_CourtyardCheckForVisitedZeldaOne
.global CourtyardCheckForVisitedZeldaOne_patch
CourtyardCheckForVisitedZeldaOne_patch:
    ldreqh r0,[r0,#0xF4]

.section .patch_CourtyardCheckForVisitedZeldaTwo
.global CourtyardCheckForVisitedZeldaTwo_patch
CourtyardCheckForVisitedZeldaTwo_patch:
    ldreqh r0,[r0,#0xF4]

.section .patch_ImpaInCourtyardCheckForVisitedZelda
.global ImpaInCourtyardCheckForVisitedZelda_patch
ImpaInCourtyardCheckForVisitedZelda_patch:
    ldrh r2,[r1,#0xF4]

.section .patch_LikeLikeNeverEatTunic
.global LikeLikeNeverEatTunic_patch
LikeLikeNeverEatTunic_patch:
    b 0x355C48

.section .patch_SwapFaroresWind
.global SwapFaroresWind_patch
SwapFaroresWind_patch:
    bl SaveFile_SwapFaroresWind
    nop

.section .patch_BombchuShopAlwaysOpen
.global BombchuShopAlwaysOpen_patch
BombchuShopAlwaysOpen_patch:
    nop

.section .patch_BombchuCheapestPriceOne
    .word 0x0063FFFF

.section .patch_BombchuCheapestPriceTwo
    .word 0x0063FFFF

.section .patch_BombchuCheapestPriceThree
    .word 0x0063FFFF

.section .patch_BombchuCheapestPriceFour
    .word 0x0063FFFF

.section .patch_BombchuPurchaseableCheck
.global BombchuPurchaseableCheck_patch
BombchuPurchaseableCheck_patch:
    bl Shop_CheckCanBuyBombchus
    nop
    nop
    nop

.section .patch_BombPurchaseableCheck
.global BombPurchaseableCheck_patch
BombPurchaseableCheck_patch:
    nop

.section .patch_BombchuShopInfinitePurchases
.global BombchuShopInfinitePurchases_patch
BombchuShopInfinitePurchases_patch:
    b hook_BombchuShopInfinitePurchases

.section .patch_GanonBattleDeathWarp
.global GanonBattleDeathWarp_patch
GanonBattleDeathWarp_patch:
    bl Entrance_DeathInGanonBattle

.section .patch_SlidingDoorDestroyCustomModels
.global SlidingDoorDestroyCustomModels_patch
SlidingDoorDestroyCustomModels_patch:
    bl hook_SlidingDoorDestroyCustomModels

.section .patch_HandleDoorDestroyCustomModels
.global HandleDoorDestroyCustomModels_patch
HandleDoorDestroyCustomModels_patch:
    bl hook_HandleDoorDestroyCustomModels

.section .patch_DoorOfTimeOpenCutscene
.global DoorOfTimeOpenCutscene_patch
DoorOfTimeOpenCutscene_patch:
    add r0,r6,#0x100
    ldrh r0,[r0,#0x4]
    cmp r0,#0x43

.section .patch_DungeonCheckJabuMQBox
.global DungeonCheckJabuMQBox_patch
DungeonCheckJabuMQBox_patch:
    bl hook_DungeonCheckJabuMQBox
    nop

.section .patch_JabuSwitchRutoCheck
.global JabuSwitchRutoCheck_patch
JabuSwitchRutoCheck_patch:
    bl hook_JabuSwitchRutoCheck

.section .patch_JabuBoxCheckRuto
.global JabuBoxCheckRuto_patch
JabuBoxCheckRuto_patch:
    bl hook_JabuBoxCheckRuto

.section .patch_TalonGetCastleTextbox
.global TalonGetCastleTextbox_patch
TalonGetCastleTextbox_patch:
    bl hook_TalonGetCastleTextbox

.section .patch_MidoCheckSpawn
.global MidoCheckSpawn_patch
MidoCheckSpawn_patch:
    bl hook_MidoCheckSpawn
    beq 0x1661B8
    b 0x1661A8

.section .patch_MidoForestDialog
.global MidoForestDialog_patch
MidoForestDialog_patch:
    nop
    nop
    nop
    nop
    bl hook_MidoForestDialog

.section .patch_MidoCheckDekuTreeClearOne
.global MidoCheckDekuTreeClearOne_patch
MidoCheckDekuTreeClearOne_patch:
    nop
    nop
    bl hook_CheckDekuTreeClear

.section .patch_MidoCheckDekuTreeClearTwo
.global MidoCheckDekuTreeClearTwo_patch
MidoCheckDekuTreeClearTwo_patch:
    nop
    nop
    bl hook_CheckDekuTreeClear

.section .patch_MidoCheckDekuTreeClearThree
.global MidoCheckDekuTreeClearThree_patch
MidoCheckDekuTreeClearThree_patch:
    nop
    nop
    bl hook_CheckDekuTreeClear

.section .patch_MidoCheckDekuTreeClearFour
.global MidoCheckDekuTreeClearFour_patch
MidoCheckDekuTreeClearFour_patch:
    nop
    nop
    bl hook_CheckDekuTreeClear

.section .patch_CorrectCompassChests
.global CorrectCompassChests_patch
CorrectCompassChests_patch:
    bl hook_CheckCurrentDungeonMode

.section .patch_CorrectCompassChestsTwo
.global CorrectCompassChestsTwo_patch
CorrectCompassChestsTwo_patch:
    bl hook_CheckCurrentDungeonMode

.section .patch_FishingNewRecord
.global FishingNewRecord_patch
FishingNewRecord_patch:
    mov r0,#0x0
    cmp r0,#0x1

.section .patch_FishingSizeIgnoreChild
.global FishingSizeIgnoreChild_patch
FishingSizeIgnoreChild_patch:
    nop

.section .patch_FishingSizeIgnoreAdult
.global FishingSizeIgnoreAdult_patch
FishingSizeIgnoreAdult_patch:
    nop

.section .patch_TycoonWalletSize
    .word 0x03E701F4

.section .patch_ReadGossipStoneHints
.global ReadGossipStoneHints_patch
ReadGossipStoneHints_patch:
    bl hook_CanReadHints
    nop
    nop
    nop
    nop

.section .patch_GossipStoneAddSariaHint
.global GossipStoneAddSariaHint_patch
GossipStoneAddSariaHint_patch:
    bl hook_GossipStoneAddSariaHint

.section .patch_GoronShopPurchaseableCheck
.global GoronShopPurchaseableCheck_patch
GoronShopPurchaseableCheck_patch:
    nop

.section .patch_PlayerEditAndRetrieveCMB
.global PlayerEditAndRetrieveCMB_patch
PlayerEditAndRetrieveCMB_patch:
    bl Player_EditAndRetrieveCMB

.section .patch_PlayerGetCustomTunicCMAB
.global PlayerGetCustomTunicCMAB_patch
PlayerGetCustomTunicCMAB_patch:
    bl Player_GetCustomTunicCMAB

.section .patch_SetChildCustomTunic
.global SetChildCustomTunic_patch
SetChildCustomTunic_patch:
    bne hook_SetChildCustomTunic

.section .patch_FastOwlCutscenes
.global FastOwlCutscenes_patch
FastOwlCutscenes_patch:
    bl hook_FastOwlCutscenes

.section .patch_ShopItemDontSetAnimSpeedOne
    nop

.section .patch_ShopItemDontSetAnimSpeedTwo
    nop

.section .patch_BugsRecatchable
.global BugsRecatchable_patch
BugsRecatchable_patch:
    nop

.section .patch_SkipDaruniaDanceOne
.global SkipDaruniaDanceOne_patch
SkipDaruniaDanceOne_patch:
    nop

.section .patch_SkipDaruniaDanceTwo
.global SkipDaruniaDanceTwo_patch
SkipDaruniaDanceTwo_patch:
    nop

.section .patch_SkipDaruniaDanceThree
.global SkipDaruniaDanceThree_patch
SkipDaruniaDanceThree_patch:
    nop

.section .patch_ShortenRainbowBridgeCS
.global ShortenRainbowBridgeCS_patch
ShortenRainbowBridgeCS_patch:
    bl hook_ShortenRainbowBridgeCS

.section .patch_RemoveWaterfallCS
.global RemoveWaterfallCS_patch
RemoveWaterfallCS_patch:
    nop
    cpy r0,r10
    add r1,r10,#0x800
    add r1,r1,#0x2E8
    ldr r2,[r6,#0x1A4]
    bl 0x36B940

.section .patch_OwlMagicCheck
.global OwlMagicCheck_patch
OwlMagicCheck_patch:
    mov r0,#0x1

.section .patch_ChestIceSmoke
.global ChestIceSmoke_patch
ChestIceSmoke_patch:
    b hook_Chest_OverrideIceSmoke

.section .patch_EnableFW
.global EnableFW_patch
EnableFW_patch:
    bl hook_EnableFW

.section .patch_FWKeepWarpPoint
.global FWKeepWarpPoint_patch
FWKeepWarpPoint_patch:
    blmi hook_FWUnset

.section .patch_FWLoadSet
.global FWLoadSet_patch
FWLoadSet_patch:
    ldr r2,[r1,#-0x668]

.section .patch_FWGetSet
.global FWGetSet_patch
FWGetSet_patch:
    b hook_FWGetSet

.section .patch_SetSavewarpEntrance
.global SetSavewarpEntrance_patch
SetSavewarpEntrance_patch:
    bl hook_SetSavewarpEntrance
.if _EUR_==1
    b  0x44FD00
.else
    b  0x44FCE0
.endif

.section .patch_SetGameOverEntrance
.global SetGameOverEntrance_patch
SetGameOverEntrance_patch:
    bl hook_SetGameOverEntrance
.if _EUR_==1
    b  0x458EE8
.else
    b  0x458EC8
.endif

.section .patch_SetGameOverRespawnFlag
.global SetGameOverRespawnFlag_patch
SetGameOverRespawnFlag_patch:
    bl hook_SetGameOverRespawnFlag

.section .patch_SetSunsSongRespawnFlag
.global SetSunsSongRespawnFlag_patch
SetSunsSongRespawnFlag_patch:
    bl hook_SetSunsSongRespawnFlag

.section .patch_SunsSongEndCloseTextbox
.global SunsSongsEndCloseTextbox_patch
SunsSongsEndCloseTextbox_patch:
    beq hook_SunsSongEndCloseTextbox

.section .patch_SetSpecialVoidOutRespawnFlag
.global SetSpecialVoidOutRespawnFlag_patch
SetSpecialVoidOutRespawnFlag_patch:
    bl hook_SetSpecialVoidOutRespawnFlag

.section .patch_SariasSongHintsOne
.global SariasSongHintsOne_patch
SariasSongHintsOne_patch:
    bl Hints_GetNextSariasSongHint

.section .patch_SariasSongHintsTwo
.global SariasSongHintsTwo_patch
SariasSongHintsTwo_patch:
    bl Hints_GetNextSariasSongHint

.section .patch_ActorUpdate
.global ActorUpdate_patch
ActorUpdate_patch:
    bl hook_ActorUpdate

.section .patch_TitleCardUpdate
.global TitleCardUpdate_patch
TitleCardUpdate_patch:
    bl TitleCard_rUpdate

.section .patch_NoHealFromHealthUpgrades
.global NoHealFromHealthUpgrades_patch
NoHealFromHealthUpgrades_patch:
    bl hook_NoHealFromHealthUpgrades

.section .patch_NoHealFromBombchuBowlingPrize
.global NoHealFromBombchuBowlingPrize_patch
NoHealFromBombchuBowlingPrize_patch:
    bl hook_NoHealFromBombchuBowlingPrize

.section .patch_FairyPickupHealAmount
.global FairyPickupHealAmount_patch
FairyPickupHealAmount_patch:
    bl hook_FairyPickupHealAmount

.section .patch_FairyReviveHealAmount
.global FairyReviveHealAmount_patch
FairyReviveHealAmount_patch:
    bl hook_FairyReviveHealAmount

.section .patch_FairyUseHealAmount
.global FairyUseHealAmount_patch
FairyUseHealAmount_patch:
    bl hook_FairyUseHealAmount

.section .patch_MedigoronCheckFlagOne
.global MedigoronCheckFlagOne_patch
MedigoronCheckFlagOne_patch:
    b hook_MedigoronCheckFlagOne

.section .patch_MedigoronCheckFlagTwo
.global MedigoronCheckFlagTwo_patch
MedigoronCheckFlagTwo_patch:
    b hook_MedigoronCheckFlagTwo

.section .patch_MedigoronSetRewardFlag
.global MedigoronSetRewardFlag_patch
MedigoronSetRewardFlag_patch:
    b hook_MedigoronSetRewardFlag

.section .patch_MedigoronGetCustomText
.global MedigoronGetCustomText_patch
MedigoronGetCustomText_patch:
    b hook_MedigoronGetCustomText
    nop

.section .patch_MedigoronItemOverrideOne
.global MedigoronItemOverrideOne_patch
MedigoronItemOverrideOne_patch:
    b hook_MedigoronItemOverrideOne

.section .patch_MedigoronItemOverrideTwo
.global MedigoronItemOverrideTwo_patch
MedigoronItemOverrideTwo_patch:
    b hook_MedigoronItemOverrideTwo

.section .patch_CarpetSalesmanCheckFlagOne
.global CarpetSalesmanCheckFlagOne_patch
CarpetSalesmanCheckFlagOne_patch:
    bl hook_CarpetSalesmanCheckFlagOne

.section .patch_CarpetSalesmanCheckFlagTwo
.global CarpetSalesmanCheckFlagTwo_patch
CarpetSalesmanCheckFlagTwo_patch:
    bl hook_CarpetSalesmanCheckFlagTwo

.section .patch_CarpetSalesmanSetFlag
.global CarpetSalesmanSetFlag_patch
CarpetSalesmanSetFlag_patch:
    bl hook_CarpetSalesmanSetFlag

.section .patch_DoorOfTimeCheck
.global DoorOfTimeCheck_patch
DoorOfTimeCheck_patch:
    bl hook_DoorOfTimeCheck

.section .patch_SongOfTimeJingle
.global SongOfTimeJingle_patch
SongOfTimeJingle_patch:
    bl hook_SongOfTimeJingle

.section .patch_GKSetDurability
.global GKSetDurability_patch
GKSetDurability_patch:
    b hook_GKSetDurability

.section .patch_TurboTextAdvance
.global TurboTextAdvance_patch
TurboTextAdvance_patch:
    bl hook_TurboTextAdvance

.section .patch_TurboTextClose
.global TurboTextClose_patch
TurboTextClose_patch:
    bl hook_TurboTextClose

.section .patch_TurboTextSignalNPC
.global TurboTextSignalNPC_patch
TurboTextSignalNPC_patch:
    bl hook_TurboTextSignalNPC

.section .patch_SkipSongReplays_TimeBlocksFix
.global SkipSongReplays_TimeBlocksFix_patch
SkipSongReplays_TimeBlocksFix_patch:
    b hook_SkipSongReplays_TimeBlocksFix

.section .patch_ItemsMenuNumSprites
.global ItemsMenuNumSprites_patch
ItemsMenuNumSprites_patch:
    mov r1,#0x19

.section .patch_ItemsMenuDraw
.global ItemsMenuDraw_patch
ItemsMenuDraw_patch:
    bl hook_ItemsMenuDraw

.section .patch_GearMenuEmptySlot
.global GearMenuEmptySlot_patch
GearMenuEmptySlot_patch:
    b hook_GearMenuEmptySlot

.section .patch_PreSwapBuffers
.global PreSwapBuffers_patch
PreSwapBuffers_patch:
    bl hook_Draw_PreSwapBuffers

.section .patch_SleepQueryCallback
.global SleepQueryCallback_patch
SleepQueryCallback_patch:
    b hook_Gfx_SleepQueryCallback

.section .patch_AwakeCallback
.global AwakeCallback_patch
AwakeCallback_patch:
    b hook_Gfx_AwakeCallback

.section .patch_AnjuGiveCojiro
.global AnjuGiveCojiro_patch
AnjuGiveCojiro_patch:
    .word EnNiwLady_rGiveCojiro

.section .patch_GrogCheckForShouldDespawn
.global GrogCheckForShouldDespawn_patch
GrogCheckForShouldDespawn_patch:
    push {r0-r12, lr}
    cpy r0,r4
    bl EnHs_CheckForShouldDespawn
    pop {r0-r12, lr}
    nop

.section .patch_GrogSetTradedCojiroFlag
.global GrogSetTradedCojiroFlag_patch
GrogSetTradedCojiroFlag_patch:
    .word EnHs_SetTradedCojiroFlag

.section .patch_CheckFadoCanSpawnInLostWoods
.global CheckFadoCanSpawnInLostWoods_patch
CheckFadoCanSpawnInLostWoods_patch:
    push {r1-r12, lr}
    bl EnKo_CheckFadoCanSpawnInLostWoods
    pop {r1-r12, lr}

.section .patch_CarpenterBossSetTradedSawFlag
.global CarpenterBossSetTradedSawFlag_patch
CarpenterBossSetTradedSawFlag_patch:
    bl hook_CarpenterBossSetTradedSawFlag

.section .patch_CarpenterBossDontNullExchangeItem
.global CarpenterBossDontNullExchangeItem_patch
CarpenterBossDontNullExchangeItem_patch:
    nop

.section .patch_LabScientistDontStartTimerAndSetFlag
.global LabScientistDontStartTimerAndSetFlag_patch
LabScientistDontStartTimerAndSetFlag_patch:
    nop
    push {r0-r12, lr}
    bl EnMk_SetTradedEyeballFrogFlag
    pop {r0-r12, lr}
    nop

.section .patch_LabScientistIgnoreEyedropsInInventory
.global LabScientistIgnoreEyedropsInInventory_patch
LabScientistIgnoreEyedropsInInventory_patch:
    b 0x3F0B5C

.section .patch_KingZoraDontStartTimer
.global KingZoraDontStartTimer_patch
KingZoraDontStartTimer_patch:
    nop
    nop
    nop
    nop
    nop

.section .patch_KingZoraSetTradedPrescriptionFlag
.global KingZoraSetTradedPrescriptionFlag_patch
KingZoraSetTradedPrescriptionFlag_patch:
    beq hook_KingZoraSetTradedPrescriptionFlag

.section .patch_CheckForWeirdEggHatchGameplayInit
.global CheckForWeirdEggHatchGameplayInit_patch
CheckForWeirdEggHatchGameplayInit_patch:
    bl SaveFile_CheckForWeirdEggHatch

.section .patch_CheckForPocketCuccoHatchGameplayInit
.global CheckForPocketCuccoHatchGameplayInit_patch
CheckForPocketCuccoHatchGameplayInit_patch:
    bl SaveFile_CheckForPocketCuccoHatch

.section .patch_CheckForWeirdEggHatchKankyo
.global CheckForWeirdEggHatchKankyo_patch
CheckForWeirdEggHatchKankyo_patch:
    bl SaveFile_CheckForWeirdEggHatch

.section .patch_CheckForPocketCuccoHatchKankyo
.global CheckForPocketCuccoHatchKankyo_patch
CheckForPocketCuccoHatchKankyo_patch:
    bl SaveFile_CheckForPocketCuccoHatch

.section .patch_SkipSongReplays_WarpBlocksFix
.global SkipSongReplays_WarpBlocksFix_patch
SkipSongReplays_WarpBlocksFix_patch:
    b hook_SkipSongReplays_WarpBlocksFix

.section .patch_PlaySound
.global PlaySound_patch
PlaySound_patch:
    b hook_PlaySound

.section .patch_SetBGMEntrance
.global SetBGMEntrance_patch
SetBGMEntrance_patch:
    b hook_SetBGMEntrance

.section .patch_SetBGMDayNight
.global SetBGMDayNight_patch
SetBGMDayNight_patch:
    b hook_SetBGMDayNight

.section .patch_SetBGMEvent
.global SetBGMEvent_patch
SetBGMEvent_patch:
    b hook_SetBGMEvent

.section .patch_SetSFX
.global SetSFX_patch
SetSFX_patch:
    b hook_SetSFX

.section .patch_GiantsKnifeWithoutKokiriSword
.global GiantsKnifeWithoutKokiriSword_patch
GiantsKnifeWithoutKokiriSword_patch:
    cmp r3,#0x8
    blt 0x376C54

.section .patch_SkipTimeTravelCutsceneOne
.global SkipTimeTravelCutsceneOne_patch
SkipTimeTravelCutsceneOne_patch:
    b hook_SkipTimeTravelCutsceneOne

.section .patch_SkipTimeTravelCutsceneTwo
.global SkipTimeTravelCutsceneTwo_patch
SkipTimeTravelCutsceneTwo_patch:
    bl hook_SkipTimeTravelCutsceneTwo

.section .patch_SwapAgeIgnoreSceneSetup
.global SwapAgeIgnoreSceneSetup_patch
SwapAgeIgnoreSceneSetup_patch:
    nop

.section .patch_SkipMasterSwordFanfare
.global SkipMasterSwordFanfare_patch
SkipMasterSwordFanfare_patch:
    bl hook_SkipMasterSwordFanfare

.section .patch_GameOverDontSpoilTradeItems
.global GameOverDontSpoilTradeItems_patch
GameOverDontSpoilTradeItems_patch:
.if _EUR_==1
    b 0x458CC0
.else
    b 0x458CA0
.endif

.section .patch_InterfaceDrawDontSpoilTradeItems
.global InterfaceDrawDontSpoilTradeItems_patch
InterfaceDrawDontSpoilTradeItems_patch:
.if _EUR_==1
    b 0x45A230
.else
    b 0x45A210
.endif

.section .patch_OpenSaveDontSpoilTradeItems
.global OpenSaveDontSpoilTradeItems_patch
OpenSaveDontSpoilTradeItems_patch:
.if _EUR_==1
    b 0x44FED8
.else
    b 0x44FEB8
.endif

.section .patch_EnteredLocation
.global EnteredLocation_patch
EnteredLocation_patch:
    bl hook_EnteredLocation

.section .patch_LostWoodsBridgeMusic
.global LostWoodsBridgeMusic_patch
LostWoodsBridgeMusic_patch:
    bl hook_LostWoodsBridgeMusic

.section .patch_BeforeLoadGame
.global BeforeLoadGame_patch
BeforeLoadGame_patch:
    b hook_BeforeLoadGame

.section .patch_AfterLoadGame
.global AfterLoadGame_patch
AfterLoadGame_patch:
    b hook_AfterLoadGame

.section .patch_FileSelect_CopyFile
.global FileSelect_CopyFile_patch
FileSelect_CopyFile_patch:
    bl hook_FileSelect_CopyFile

.section .patch_SaveGame
.global .SaveGame_patch
SaveGame_patch:
    b hook_SaveGame

.section .patch_DontSetMotionSetting
.global .DontSetMotionSetting_patch
DontSetMotionSetting_patch:
    nop

.section .patch_SaveMenuIgnoreOpen
.global SaveMenuIgnoreOpen_patch
SaveMenuIgnoreOpen_patch:
    bl hook_SaveMenuIgnoreOpen

.section .patch_GameOverStart
.global GameOverStart_patch
GameOverStart_patch:
    bl hook_GameOverStart

.section .patch_PermadeathSkipMenu
.global PermadeathSkipMenu_patch
PermadeathSkipMenu_patch:
    bl hook_PermadeathSkipMenu

.section .patch_PermadeathForceQuit
.global PermadeathForceQuit_patch
PermadeathForceQuit_patch:
    bl hook_PermadeathForceQuit

.section .patch_OverrideFogDuringGameplayInit
.global OverrideFogDuringGameplayInit_patch
OverrideFogDuringGameplayInit_patch:
    bl hook_OverrideFogDuringGameplayInit

.section .patch_KotakeDontPlayBattleMusic
.global KotakeDontPlayBattleMusic_patch
KotakeDontPlayBattleMusic_patch:
    nop

.section .patch_SkipTwinrovaQuarrelCutsceneOne
.global SkipTwinrovaQuarrelCutsceneOne_patch
SkipTwinrovaQuarrelCutsceneOne_patch:
    sub r1,r1,#0x500

.section .patch_SkipTwinrovaQuarrelCutsceneTwo
.global SkipTwinrovaQuarrelCutsceneTwo_patch
SkipTwinrovaQuarrelCutsceneTwo_patch:
    bl hook_SkipTwinrovaQuarrelCutscene

.section .patch_FixItemsMenuSlotDuplication
.global FixItemsMenuSlotDuplication_patch
FixItemsMenuSlotDuplication_patch:
    b hook_FixItemsMenuSlotDuplication

.section .patch_PlayEntranceCutscene
.global PlayEntranceCutscene_patch
PlayEntranceCutscene_patch:
    b hook_PlayEntranceCutscene

.section .patch_SkipJabuOpeningCutscene
.global SkipJabuOpeningCutscene_patch
SkipJabuOpeningCutscene_patch:
    bl hook_SkipJabuOpeningCutscene

.section .patch_MultiplyPlayerSpeed
.global MultiplyPlayerSpeed_patch
MultiplyPlayerSpeed_patch:
    bl hook_MultiplyPlayerSpeed

.section .patch_RunAnimationSpeed
.global RunAnimationSpeed_patch
RunAnimationSpeed_patch:
    bl hook_RunAnimationSpeed

.section .patch_NaviNotifications
.global NaviNotifications_patch
NaviNotifications_patch:
    bl hook_NaviNotifications

.section .patch_ChestMinigame_RewardChestVisibility
.global ChestMinigame_RewardChestVisibility_patch
ChestMinigame_RewardChestVisibility_patch:
    .word 0x00000EC0
    .word 0x00000EA0

.section .patch_ChestMinigame_KeyChestVisibility
.global ChestMinigame_KeyChestVisibility_patch
ChestMinigame_KeyChestVisibility_patch:
    bl hook_ChestMinigame_KeyChestVisibility

.section .patch_ChestMinigame_DontOpenChestsOnInit
.global ChestMinigame_DontOpenChestsOnInit_patch
ChestMinigame_DontOpenChestsOnInit_patch:
    bl hook_ChestMinigame_DontOpenChestsOnInit

.section .patch_GameplayDestroy
.global GameplayDestroy_patch
GameplayDestroy_patch:
    bl hook_GameplayDestroy

.section .patch_SceneExitOverride
.global SceneExitOverride_patch
SceneExitOverride_patch:
    bl hook_SceneExitOverride

.section .patch_SceneExitDynamicOverride
.global SceneExitDynamicOverride_patch
SceneExitDynamicOverride_patch:
    bl hook_SceneExitDynamicOverride

.section .patch_OverrideGrottoActorEntrance
.global OverrideGrottoActorEntrance_patch
OverrideGrottoActorEntrance_patch:
    b hook_OverrideGrottoActorEntrance

.section .patch_ReturnFW
.global ReturnFW_patch
ReturnFW_patch:
    bl hook_ReturnFW

.section .patch_WarpSongEntranceOverride
.global WarpSongEntranceOverride_patch
WarpSongEntranceOverride_patch:
    bl hook_WarpSongEntranceOverride

.section .patch_DMTOwlEntranceOverride
.global DMTOwlEntranceOverride_patch
DMTOwlEntranceOverride_patch:
    b hook_OwlEntranceOverride

.section .patch_LHOwlEntranceOverride
.global LHOwlEntranceOverride_patch
LHOwlEntranceOverride_patch:
    b hook_OwlEntranceOverride

.section .patch_SavewarpSetRespawnFlag
.global SavewarpSetRespawnFlag_patch
SavewarpSetRespawnFlag_patch:
    bl hook_SavewarpSetRespawnFlag

.section .patch_AdultItemsCMABsAsChild
.global AdultItemsCMABsAsChild_patch
AdultItemsCMABsAsChild_patch:
    bl hook_AdultItemsCMABsAsChild

.section .patch_Model_EnableMeshGroupByIndex
.global Model_EnableMeshGroupByIndex_patch
Model_EnableMeshGroupByIndex_patch:
    b hook_Model_EnableMeshGroupByIndex

.section .patch_NockArrow
.global NockArrow_patch
NockArrow_patch:
    bl hook_ArrowsOrSeeds

.section .patch_DecreaseArrowCount
.global DecreaseArrowCount_patch
DecreaseArrowCount_patch:
    bl hook_ArrowsOrSeeds

.section .patch_HookshotDrawChain
.global HookshotDrawChain_patch
HookshotDrawChain_patch:
    b hook_HookshotDrawChain

.section .patch_HookshotRotation
.global HookshotRotation_patch
HookshotRotation_patch:
    bl hook_HookshotRotation

.section .patch_LinkReflection
.global LinkReflection_patch
LinkReflection_patch:
    b hook_LinkReflection

.section .patch_ChildCanOpenBowSubMenu
.global ChildCanOpenBowSubMenu_patch
ChildCanOpenBowSubMenu_patch:
    b hook_ChildCanOpenBowSubMenu

.section .patch_RedBoulderExplode
.global RedBoulderExplode_patch
RedBoulderExplode_patch:
    b hook_RedBoulderExplode

.section .patch_Multiplayer_UpdatePrevActorFlags
.global Multiplayer_UpdatePrevActorFlags_patch
Multiplayer_UpdatePrevActorFlags_patch:
    bl hook_Multiplayer_UpdatePrevActorFlags

.section .patch_Multiplayer_OnLoadFile
.global Multiplayer_OnLoadFile_patch
Multiplayer_OnLoadFile_patch:
    b hook_Multiplayer_OnLoadFile

.section .patch_SendDroppedBottleContents
.global SendDroppedBottleContents_patch
SendDroppedBottleContents_patch:
    bl hook_SendDroppedBottleContents

.section .patch_IgnoreMaskReaction
.global IgnoreMaskReaction_patch
IgnoreMaskReaction_patch:
    b hook_IgnoreMaskReaction

.section .patch_MasterQuestGoldSkulltulaCheck
.global MasterQuestGoldSkulltulaCheck_patch
MasterQuestGoldSkulltulaCheck_patch:
    b hook_MasterQuestGoldSkulltulaCheck

.section .patch_WaterSpoutMasterQuestCheck
.global WaterSpoutMasterQuestCheck_patch
WaterSpoutMasterQuestCheck_patch:
    bl hook_WaterSpoutMasterQuestCheck

.section .patch_PierreSoftlockFixOne
.global PierreSoftlockFixOne_patch
PierreSoftlockFixOne_patch:
    pop {r3-r7,lr}
    bx lr

.section .patch_PierreSoftlockFixTwo
.global PierreSoftlockFixTwo_patch
PierreSoftlockFixTwo_patch:
    bl hook_PierreSoftlockFixTwo

.section .patch_PierreSoftlockFixThree
.global PierreSoftlockFixThree_patch
PierreSoftlockFixThree_patch:
    nop
    nop
    nop
    nop

.section .patch_StoreTargetActorType
.global StoreTargetActorType_patch
StoreTargetActorType_patch:
    bl hook_StoreTargetActorType

.section .patch_SwordTrailDurationGrezzoFix
.global SwordTrailDurationGrezzoFix_patch
SwordTrailDurationGrezzoPatch_patch:
    nop

.section .patch_ForceTrailEffectUpdate
.global ForceTrailEffectUpdate_patch
ForceTrailEffectUpdate_patch:
    blne hook_ForceTrailEffectUpdate

.section .patch_RainbowSwordTrail
.global RainbowSwordTrail_patch
RainbowSwordTrail_patch:
    bl hook_RainbowSwordTrail

.section .patch_BoomerangTrailEffect
.global BoomerangTrailEffect_patch
BoomerangTrailEffect_patch:
    bl hook_BoomerangTrailEffect

.section .patch_RainbowChuTrailOne
.global RainbowChuTrailOne_patch
RainbowChuTrailOne_patch:
    bl hook_RainbowChuTrail

.section .patch_RainbowChuTrailTwo
.global RainbowChuTrailTwo_patch
RainbowChuTrailTwo_patch:
    bl hook_RainbowChuTrail

.section .patch_FWandWarpSongTimerDepletion
.global FWandWarpSongTimerDepletion_patch
FWandWarpSongTimerDepletion_patch:
    push {lr}
    bl hook_FWandWarpSongTimerDepletion
    pop {lr}

.section .patch_TimerExpiration
.global TimerExpiration_patch
TimerExpiration_patch:
    bl hook_TimerExpiration

.section .patch_Timer2TickSound
.global Timer2TickSound_patch
Timer2TickSound_patch:
    bl hook_Timer2TickSound

.section .patch_CurseTrapDizzyStick
.global CurseTrapDizzyStick_patch
CurseTrapDizzyStick_patch:
    bl hook_CurseTrapDizzyStick

.section .patch_CurseTrapDizzyButtons
.global CurseTrapDizzyButtons_patch
CurseTrapDizzyButtons_patch:
    b hook_CurseTrapDizzyButtons

.section .patch_CrouchStabHitbox
.global CrouchStabHitbox_patch
CrouchStabHitbox_patch:
    bl hook_CrouchStabHitbox

.section .patch_MasterSwordTimerCheck
.global MasterSwordTimerCheck_patch
MasterSwordTimerCheck_patch:
    nop

.section .patch_BossChallenge_Enter
.global BossChallenge_Enter_patch
BossChallenge_Enter_patch:
    bl hook_BossChallenge_Enter

.section .patch_BossChallenge_ExitMenu
.global BossChallenge_ExitMenu_patch
BossChallenge_ExitMenu_patch:
    bl hook_BossChallenge_ExitMenu

.section .patch_TruthSpinnerSpeed
.global TruthSpinnerSpeed_patch
TruthSpinnerSpeed_patch:
    cmp r2,#0x20
    strh r2,[r4,#0xC4]
    movgt r2,#0x20

.section .patch_LostWoodsTargetCutscene
.global LostWoodsTargetCutscene_patch
LostWoodsTargetCutscene_patch:
    nop

.section .patch_LostWoodsTargetTimer
.global LostWoodsTargetTimer_patch
LostWoodsTargetTimer_patch:
    mov r0,#0x1

.section .patch_GrannyTextID
.global GrannyTextID_patch
GrannyTextID_patch:
    bl hook_GrannyTextID

.section .patch_GrannyBottleCheck
.global GrannyBottleCheck_patch
GrannyBottleCheck_patch:
    bl hook_GrannyBottleCheck

.section .patch_GrannyItemOverrideOne
.global GrannyItemOverrideOne_patch
GrannyItemOverrideOne_patch:
    bl hook_GrannyItemOverride

.section .patch_GrannyItemOverrideTwo
.global GrannyItemOverrideTwo_patch
GrannyItemOverrideTwo_patch:
    b hook_GrannyItemOverride

.section .patch_GrannySetRewardFlag
.global GrannySetRewardFlag_patch
GrannySetRewardFlag_patch:
    bl hook_GrannySetRewardFlag

.section .patch_BecomeAdult
.global BecomeAdult_patch
BecomeAdult_patch:
    push {lr}
    bl hook_BecomeAdult
    pop {lr}

.section .patch_PickUpMasterSword
.global PickUpMasterSword_patch
PickUpMasterSword_patch:
    bl Pedestal_PickUpMasterSword

.section .patch_SaveFileSwordless
.global SaveFileSwordless_patch
SaveFileSwordless_patch:
    push {lr}
    bl hook_HandleBButton
    pop {lr}

.section .patch_LoadFileSwordless
.global LoadFileSwordless_patch
LoadFileSwordless_patch:
    bl hook_LoadFileSwordless

.section .patch_DeathHandleBButton
.global DeathHandleBButton_patch
DeathHandleBButton_patch:
    push {lr}
    bl hook_HandleBButton
    pop {lr}

.section .patch_GanonCSEquipMS
.global GanonCSEquipMS_patch
GanonCSEquipMS_patch:
    bl Ganon_CSEquipMS
    nop
    nop
    nop

.section .patch_GanonRestoreMSOnDeath
.global GanonRestoreMSOnDeath_patch
GanonRestoreMSOnDeath_patch:
    bl hook_GanonRestoreMSOnDeath

.section .patch_GanonGiveMSMidFight
.global GanonGiveMSMidFight_patch
GanonGiveMSMidFight_patch:
    bl Ganon_GiveMSMidFight

.section .patch_GiveItemMasterSword
.global GiveItemMasterSword_patch
GiveItemMasterSword_patch:
    push {r0-r12,lr}
    bl ItemEffect_EquipMasterSword
    pop {r0-r12,lr}
    nop
    nop
    nop
    nop

.section .patch_CriticalHealthCheckOne
.global CriticalHealthCheckOne_Patch
CriticalHealthCheckOne_patch:
    bl hook_CriticalHealthCheck
    nop
    nop
    nop
    nop

.section .patch_CriticalHealthCheckTwo
.global CriticalHealthCheckTwo_patch
CriticalHealthCheckTwo_patch:
    bl hook_CriticalHealthCheck
    nop
    nop
    nop
    nop

.section .patch_CriticalHealthCheckThree
.global CriticalHealthCheckThree_patch
CriticalHealthCheckThree_patch:
    push {lr}
    bl hook_CriticalHealthCheck
    pop {lr}
    nop
    nop

.section .patch_InitSceneMirrorWorld
.global InitSceneMirrorWorld_patch
InitSceneMirrorWorld_patch:
    bl hook_InitSceneMirrorWorld

.section .patch_InitSceneEntranceOverride
.global InitSceneEntranceOverride_patch
InitSceneEntranceOverride_patch:
    bl hook_InitSceneEntranceOverride

.section .patch_CollisionATvsAC
.global CollisionATvsAC_patch
CollisionATvsAC_patch:
    bl hook_CollisionATvsAC

.section .patch_CollisionCheck_SetAC_Once
.global CollisionCheck_SetAC_Once_patch
CollisionCheck_SetAC_Once_patch:
    bl hook_CollisionCheck_SetAll_Once

.section .patch_CollisionCheck_SetAT_Once
.global CollisionCheck_SetAT_Once_patch
CollisionCheck_SetAT_Once_patch:
    bl hook_CollisionCheck_SetAll_Once

.section .patch_CollisionCheck_SetOC_Once
.global CollisionCheck_SetOC_Once_patch
CollisionCheck_SetOC_Once_patch:
    bl hook_CollisionCheck_SetAll_Once

.section .patch_GanonDrawMasterSword
.global GanonDrawMasterSword_patch
GanonDrawMasterSword_patch:
    bl hook_GanonDrawMasterSword

.section .patch_SetFWPlayerParams
.global SetFWPlayerParams_patch
SetFWPlayerParams_patch:
    bl hook_SetFWPlayerParams

.section .patch_AboutToPickUpActor
.global AboutToPickUpActor_patch
AboutToPickUpActor_patch:
    bl hook_AboutToPickUpActor

.section .patch_TargetReticleColor
.global TargetReticleColor_patch
TargetReticleColor_patch:
    bl hook_TargetReticleColor

.section .patch_TargetPointerColor
.global TargetPointerColor_patch
TargetPointerColor_patch:
    bl hook_TargetPointerColor

.section .patch_ShadowShip_CSTimer
.global ShadowShip_CSTimer_patch
ShadowShip_CSTimer_patch:
    .word 0xC3

.section .patch_ShadowShip_Speed
.global ShadowShip_Speed_patch
ShadowShip_Speed_patch:
    bl hook_ShadowShip_Speed

.section .patch_MaskSalesmanCheckNoMaskOne
.global MaskSalesmanCheckNoMaskOne_patch
MaskSalesmanCheckNoMaskOne_patch:
    push {r0,r1,r4-r12,lr}
    bl SaveFile_MaskSlotValue

.section .patch_MaskSalesmanCheckNoMaskTwo
.global MaskSalesmanCheckNoMaskTwo_patch
MaskSalesmanCheckNoMaskTwo_patch:
    cpy r2,r0
    pop {r0,r1,r4-r12,lr}

.section .patch_MaskSalesmanBorrowMask
.global MaskSalesmanBorrowMask_patch
MaskSalesmanBorrowMask_patch:
    bl hook_MaskSalesmanBorrowMask

.section .patch_MaskSalesmanGiveMaskOfTruth
.global MaskSalesmanGiveMaskOfTruth_patch
MaskSalesmanGiveMaskOfTruth_patch:
    bl hook_MaskSalesmanGiveMaskOfTruth

.section .patch_OoBBombchuOne
.global OoBBombchuOne_patch
OoBBombchuOne_patch:
    bl hook_OoBBombchuOne

.section .patch_OoBBombchuTwo
.global OoBBombchuTwo_patch
OoBBombchuTwo_patch:
    bl hook_OoBBombchuTwo

.section .patch_OoBBombchuThree
.global OoBBombchuThree_patch
OoBBombchuThree_patch:
    bl hook_OoBBombchuThree

.section .patch_CamRoll
.global CamRoll_patch
CamRoll_patch:
    bl hook_CamRoll

.section .patch_CamUpdate
.global CamUpdate_patch
CamUpdate_patch:
    bl hook_CamUpdate

.section .patch_Sheik_GetTextID
.global Sheik_GetTextID_patch
Sheik_GetTextID_patch:
    b hook_Sheik_GetTextID

.section .patch_OnActorSetup_SceneChange
.global OnActorSetup_SceneChange_patch
OnActorSetup_SceneChange_patch:
    bl hook_OnActorSetup_SceneChange

.section .patch_AfterActorSetup_SceneChange
.global AfterActorSetup_SceneChange_patch
AfterActorSetup_SceneChange_patch:
    b hook_AfterActorSetup_SceneChange

.section .patch_OnActorSetup_RoomChange
.global OnActorSetup_RoomChange_patch
OnActorSetup_RoomChange_patch:
    bl hook_OnActorSetup_RoomChange

.section .patch_AfterActorSetup_RoomChange
.global AfterActorSetup_RoomChange_patch
AfterActorSetup_RoomChange_patch:
    b hook_AfterActorSetup_RoomChange

.section .patch_RandomGsLoc_CustomTangibilityCheck
.global RandomGsLoc_CustomTangibilityCheck_patch
RandomGsLoc_CustomTangibilityCheck_patch:
    b hook_RandomGsLoc_CustomTangibilityCheck

.section .patch_RandomGsLoc_CustomTokenSpawnOffset
.global RandomGsLoc_CustomTokenSpawnOffset_patch
RandomGsLoc_CustomTokenSpawnOffset_patch:
    bl hook_RandomGsLoc_CustomTokenSpawnOffset

.section .patch_RandomGsLoc_BlockSpawn_Crate
.global RandomGsLoc_BlockSpawn_Crate_patch
RandomGsLoc_BlockSpawn_Crate_patch:
    bl hook_RandomGsLoc_BlockSpawn_Crate

.section .patch_RandomGsLoc_BlockSpawn_Tree
.global RandomGsLoc_BlockSpawn_Tree_patch
RandomGsLoc_BlockSpawn_Tree_patch:
    bl hook_RandomGsLoc_BlockSpawn_Tree

.section .patch_RandomGsLoc_BlockSpawn_Soil
.global RandomGsLoc_BlockSpawn_Soil_patch
RandomGsLoc_BlockSpawn_Soil_patch:
    bl hook_RandomGsLoc_BlockSpawn_Soil

.section .patch_RandomGsLoc_SkipSoilJingle
.global RandomGsLoc_SkipSoilJingle_patch
RandomGsLoc_SkipSoilJingle_patch:
    bl hook_RandomGsLoc_SkipSoilJingle

.section .patch_ActorDraw
.global ActorDraw_patch
ActorDraw_patch:
    bl hook_ActorDraw

.section .patch_FlyingPotCollision
.global FlyingPotCollision_patch
FlyingPotCollision_patch:
    bl hook_FlyingPotCollision

.section .patch_FlyingTileCollision
.global FlyingTileCollision_patch
FlyingTileCollision_patch:
    bl hook_FlyingTileCollision

.section .patch_ShabomAfterDamagePlayer
.global ShabomAfterDamagePlayer_patch
ShabomAfterDamagePlayer_patch:
    bl hook_ShabomAfterDamagePlayer

.section .patch_DodongoAfterSwallowBomb
.global DodongoAfterSwallowBomb_patch
DodongoAfterSwallowBomb_patch:
    bl hook_DodongoAfterSwallowBomb

.section .patch_BabyDodongoAfterSwallowBomb
.global BabyDodongoAfterSwallowBomb_patch
BabyDodongoAfterSwallowBomb_patch:
    bl hook_BabyDodongoAfterSwallowBomb

.section .patch_OcarinaNoteButtonsDraw
.global OcarinaNoteButtonsDraw_patch
OcarinaNoteButtonsDraw_patch:
    push {lr}
    bl hook_OcarinaNoteButtonsDraw
    pop {lr}

.section .patch_OcarinaNoteButtonsPress
.global OcarinaNoteButtonsPress_patch
OcarinaNoteButtonsPress_patch:
    bl hook_OcarinaNoteButtonsPress

.section .patch_HandleTextControlCode
.global HandleTextControlCode_patch
HandleTextControlCode_patch:
    bl hook_HandleTextControlCode

.section .patch_CheckForTextControlCode
.global CheckForTextControlCode_patch
CheckForTextControlCode_patch:
    bl hook_CheckForTextControlCode

.section .patch_PlayInit
.global PlayInit_patch
PlayInit_patch:
    bl hook_PlayInit

.section .patch_TitleLinkObject
.global TitleLinkObject_patch
TitleLinkObject_patch:
    .word 0xFFFF0014

.section .patch_ExtendObjectGetSlot
.global ExtendObjectGetSlot_patch
ExtendObjectGetSlot_patch:
    b hook_ExtendObjectGetSlot

.section .patch_OverrideObjectIsLoaded
.global OverrideObjectIsLoaded_patch
OverrideObjectIsLoaded_patch:
    b hook_OverrideObjectIsLoaded

.section .patch_Cutscene_CheckObjectLoaded
.global Cutscene_CheckObjectLoaded_patch
Cutscene_CheckObjectLoaded_patch:
    bl hook_OverrideObjectIsLoadedForCutscenes

.section .patch_AfterObjectListCommand
.global AfterObjectListCommand_patch
AfterObjectListCommand_patch:
    bl hook_AfterObjectListCommand

.section .patch_GetObjectEntry_33AB24
.global GetObjectEntry_33AB24_patch
GetObjectEntry_33AB24_patch:
    bl hook_GetObjectEntry_33AB24

.section .patch_GetObjectEntry_353CE4
.global GetObjectEntry_353CE4_patch
GetObjectEntry_353CE4_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_36A96C
.global GetObjectEntry_36A96C_patch
GetObjectEntry_36A96C_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_372F7C
.global GetObjectEntry_372F7C_patch
GetObjectEntry_372F7C_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_EnSiInit
.global GetObjectEntry_EnSiInit_patch
GetObjectEntry_EnSiInit_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_EnXcInit
.global GetObjectEntry_EnXcInit_patch
GetObjectEntry_EnXcInit_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_ObjSwitchInit
.global GetObjectEntry_ObjSwitchInit_patch
GetObjectEntry_ObjSwitchInit_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_34FE68
.global GetObjectEntry_34FE68_patch
GetObjectEntry_34FE68_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_352F28
.global GetObjectEntry_352F28_patch
GetObjectEntry_352F28_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_33A950
.global GetObjectEntry_33A950_patch
GetObjectEntry_33A950_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_EnTiteInit
.global GetObjectEntry_EnTiteInit_patch
GetObjectEntry_EnTiteInit_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_339DFC
.global GetObjectEntry_339DFC_patch
GetObjectEntry_339DFC_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_EnGomaInit_One
.global GetObjectEntry_EnGomaInit_One_patch
GetObjectEntry_EnGomaInit_One_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_EnGomaInit_Two
.global GetObjectEntry_EnGomaInit_Two_patch
GetObjectEntry_EnGomaInit_Two_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_EnRdInit_One
.global GetObjectEntry_EnRdInit_One_patch
GetObjectEntry_EnRdInit_One_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_EnRdInit_Two
.global GetObjectEntry_EnRdInit_Two_patch
GetObjectEntry_EnRdInit_Two_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_34F270
.global GetObjectEntry_34F270_patch
GetObjectEntry_34F270_patch:
    b hook_GetObjectEntry_34F270

.section .patch_GetObjectEntry_1F85B0
.global GetObjectEntry_1F85B0_patch
GetObjectEntry_1F85B0_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_164BC8
.global GetObjectEntry_164BC8_patch
GetObjectEntry_164BC8_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_EnDekunutsInit
.global GetObjectEntry_EnDekunutsInit_patch
GetObjectEntry_EnDekunutsInit_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_EnNutsballInit
.global GetObjectEntry_EnNutsballInit_patch
GetObjectEntry_EnNutsballInit_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_GetObjectEntry_EnHintnutsInit
.global GetObjectEntry_EnHintnutsInit_patch
GetObjectEntry_EnHintnutsInit_patch:
    bl hook_GetObjectEntry_Generic

.section .patch_AltHeadersCommand
.global AltHeadersCommand_patch
AltHeadersCommand_patch:
    bl hook_AltHeadersCommand

.section .patch_GohmaLarvaDeathSignalParent
.global GohmaLarvaDeathSignalParent_patch
GohmaLarvaDeathSignalParent_patch:
    bl hook_GohmaLarvaDeathSignalParent

.section .patch_GohmaEggDeathSignalParent
.global GohmaEggDeathSignalParent_patch
GohmaEggDeathSignalParent_patch:
    bl hook_GohmaEggDeathSignalParent

.section .patch_StalchildDespawn_13DB68
.global StalchildDespawn_13DB68_patch
StalchildDespawn_13DB68_patch:
    bl hook_StalchildDespawn_13DB68

.section .patch_StalchildDespawn_366338
.global StalchildDespawn_366338_patch
StalchildDespawn_366338_patch:
    bl hook_StalchildDespawn_366338

.section .patch_SkullwalltulaAttack_35F834
.global SkullwalltulaAttack_35F834_patch
SkullwalltulaAttack_35F834_patch:
    bl hook_SkullwalltulaAttack_35F834

.section .patch_SkullwalltulaAttack_35F328
.global SkullwalltulaAttack_35F328_patch
SkullwalltulaAttack_35F328_patch:
    bl hook_SkullwalltulaAttack_35F328

.section .patch_SkullwalltulaTargetRotation
.global SkullwalltulaTargetRotation_patch
SkullwalltulaTargetRotation_patch:
    bl hook_SkullwalltulaTargetRotation

.section .patch_AnubisFlameCircleCheck
.global AnubisFlameCircleCheck_patch
AnubisFlameCircleCheck_patch:
    @ check alpha instead of timer
    ldrb r1,[r1,#0xAB]

.section .patch_SkullKidPoacherSawCheck
.global SkullKidPoacherSawCheck_patch
SkullKidPoacherSawCheck_patch:
    bl hook_SkullKidPoacherSawCheck

.section .patch_LeeverSandCheck_Init
.global LeeverSandCheck_Init_patch
LeeverSandCheck_Init_patch:
    bl hook_LeeverSandCheck

.section .patch_LeeverSandCheck_Small
.global LeeverSandCheck_Small_patch
LeeverSandCheck_Small_patch:
    bl hook_LeeverSandCheck

.section .patch_LeeverSandCheck_Big
.global LeeverSandCheck_Big_patch
LeeverSandCheck_Big_patch:
    bl hook_LeeverSandCheck

.section .patch_LeeverAfterSink
.global LeeverAfterSink_patch
LeeverAfterSink_patch:
    blt hook_LeeverAfterSink

.section .patch_LeeverAfterDie
.global LeeverAfterDie_patch
LeeverAfterDie_patch:
    bl hook_LeeverAfterDie

.section .patch_LeeverDontChangeCategory
.global LeeverDontChangeCategory_patch
LeeverDontChangeCategory_patch:
    @ Big Leevers change category from Misc to Enemy in OoT.
    @ But in OoT3D they're already in the Enemy category
    @ from the start, so changing it is useless and can
    @ trigger room clears during Enemy Randomizer.
    nop

.section .patch_FlyingPotDontChangeCategory
.global FlyingPotDontChangeCategory_patch
FlyingPotDontChangeCategory_patch:
    nop

.section .patch_PlayerCheckVoidOut
.global PlayerCheckVoidOut_patch
PlayerCheckVoidOut_patch:
    bl hook_PlayerCheckVoidOut

.section .patch_EnBlkobj_SpawnDarkLink
.global EnBlkobj_SpawnDarkLink_patch
EnBlkobj_SpawnDarkLink_patch:
    bl hook_EnBlkobj_SpawnDarkLink

.section .patch_EnBlkobj_FindDarkLink
.global EnBlkobj_FindDarkLink_patch
EnBlkobj_FindDarkLink_patch:
    bl hook_EnBlkobj_FindDarkLink

.section .patch_EnEncount1_SpawnStalchildWolfos
.global EnEncount1_SpawnStalchildWolfos_patch
EnEncount1_SpawnStalchildWolfos_patch:
    bl hook_EnEncount1_SpawnStalchildWolfos

.section .patch_EnEncount1_SpawnLeever
.global EnEncount1_SpawnLeever_patch
EnEncount1_SpawnLeever_patch:
    bl hook_EnEncount1_SpawnLeever

.section .patch_EnEncount1_SetLeeverAimType
.global EnEncount1_SetLeeverAimType_patch
EnEncount1_SetLeeverAimType_patch:
    bl hook_EnEncount1_SetLeeverAimType

.section .patch_DarkLinkPlayerRecoil
.global DarkLinkPlayerRecoil_patch
DarkLinkPlayerRecoil_patch:
    bl hook_DarkLinkPlayerRecoil

.section .patch_BabyDodongoWallCheck
.global BabyDodongoWallCheck_patch
BabyDodongoWallCheck_patch:
    bl hook_BabyDodongoWallCheck

.section .patch_PeahatLarvaGroundCheck
.global PeahatLarvaGroundCheck_patch
PeahatLarvaGroundCheck_patch:
    bl hook_PeahatLarvaGroundCheck

.section .patch_RedeadCanFreezePlayer
.global RedeadCanFreezePlayer_patch
RedeadCanFreezePlayer_patch:
    bl hook_RedeadCanFreezePlayer

.section .patch_DeadHandHandCanGrabPlayer
.global DeadHandHandCanGrabPlayer_patch
DeadHandHandCanGrabPlayer_patch:
    bl hook_DeadHandHandCanGrabPlayer

.section .patch_GerudoBattleMusic
.global GerudoBattleMusic_patch
GerudoBattleMusic_patch:
    bl hook_GerudoBattleMusic

.section .patch_FixActorKillLoop
.global FixActorKillLoop_patch
FixActorKillLoop_patch:
    bl hook_FixActorKillLoop

.section .patch_AfterInvalidatingRoomObjects
.global AfterInvalidatingRoomObjects_patch
AfterInvalidatingRoomObjects_patch:
    bl hook_AfterInvalidatingRoomObjects

.section .patch_DrawHeartIcon
.global DrawHeartIcon_patch
DrawHeartIcon_patch:
    bl hook_DrawHeartIcon
    
.section .patch_Item00GiveAutomaticItemDrop
.global Item00GiveAutomaticItemDrop_patch
Item00GiveAutomaticItemDrop_patch:
    bl hook_Item00GiveAutomaticItemDrop

.section .patch_Item00GiveCollectedItemDrop
.global Item00GiveCollectedItemDrop_patch
Item00GiveCollectedItemDrop_patch:
    bl hook_Item00GiveCollectedItemDrop
