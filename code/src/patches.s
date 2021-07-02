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
    b hook_OverrideTextID

.section .patch_OverrideItemID
.global OverrideItemID_patch
OverrideItemID_patch:
    b hook_OverrideItemID

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

.section .patch_EditDrawGetItemBeforeModelSpawn
.global EditDrawGetItemBeforeModelSpawn_patch
EditDrawGetItemBeforeModelSpawn_patch:
    bl hook_EditDrawGetItemBeforeModelSpawn

.section .patch_EditDrawGetItemAfterModelSpawn
.global EditDrawGetItemAfterModelSpawn_patch
EditDrawGetItemAfterModelSpawn_patch:
    bl hook_EditDrawDetItemAfterModelSpawn

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
    bl hook_FastChests

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

.section .patch_ChestGetIceTrapObjectStatus
.global ChestGetIceTrapObjectStatus_patch
ChestGetIceTrapObjectStatus_patch:
    bl hook_ChestGetIceTrapObjectStatus

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
    b 0x44F180

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

# Save context + 0x4F is normally unused
# We will use it to denote Biggoron's reward
.section .patch_BiggoronCheckGivenRewardOne
.global BiggoronCheckGivenRewardOne_patch
BiggoronCheckGivenRewardOne_patch:
    ldrb r0,[r0,#0x4F]

.section .patch_BiggoronCheckGivenRewardTwo
.global BiggoronCheckGivenRewardTwo_patch
BiggoronCheckGivenRewardTwo_patch:
    ldrb r1,[r1,#0x4F]

.section .patch_BiggoronCheckGivenRewardThree
.global BiggoronCheckGivenRewardThree_patch
BiggoronCheckGivenRewardThree_patch:
    ldreqb r0,[r0,#0x4F]

.section .patch_BiggoronSetGivenReward
.global BiggoronSetGivenReward_patch
BiggoronSetGivenReward_patch:
    streqb r5,[r0,#0x4F]

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

.section .patch_DekuTreeItemGive
.global DekuTreeItemGive_patch
DekuTreeItemGive_patch:
    nop

.section .patch_DekuTreeCutsceneOverride
.global DekuTreeCutsceneOverride_patch
DekuTreeCutsceneOverride_patch:
    bl Cutscene_OverrideDekuTree
    nop

.section .patch_DodongosCavernItemGive
.global DodongosCavernItemGive_patch
DodongosCavernItemGive_patch:
    nop

.section .patch_DodongosCavernCutsceneOverride
.global DodongosCavernCutsceneOverride_patch
DodongosCavernCutsceneOverride_patch:
    bl Custcene_OverrideDodongosCavern
    nop

.section .patch_JabuJabuItemGive
.global JabuJabuItemGive_patch
JabuJabuItemGive_patch:
    nop

.section .patch_JabuJabuCutsceneOverride
.global JabuJabuCutsceneOverride_patch
JabuJabuCutsceneOverride_patch:
    bl Custcene_OverrideJabuJabusBelly
    nop
    nop

.section .patch_ForestTempleItemGive
.global ForestTempleItemGive_patch
ForestTempleItemGive_patch:
    nop

.section .patch_ForestTempleItemGiveTwo
.global ForestTempleItemGiveTwo_patch
ForestTempleItemGiveTwo_patch:
    nop

.section .patch_ForestTempleItemGiveThree
.global ForestTempleItemGiveThree_patch
ForestTempleItemGiveThree_patch:
    nop

.section .patch_ForestTempleCutsceneOverride
.global ForestTempleCutsceneOverride_patch
ForestTempleCutsceneOverride_patch:
    bl Custcene_OverrideForestTemple
    nop
    nop

.section .patch_FireTempleItemGive
.global FireTempleItemGive_patch
FireTempleItemGive_patch:
    nop

.section .patch_FireTempleItemGiveTwo
.global FireTempleItemGiveTwo_patch
FireTempleItemGiveTwo_patch:
    nop

.section .patch_FireTempleItemGiveThree
.global FireTempleItemGiveThree_patch
FireTempleItemGiveThree_patch:
    nop

.section .patch_FireTempleItemGiveFour
.global FireTempleItemGiveFour_patch
FireTempleItemGiveFour_patch:
    nop

.section .patch_FireTempleCutsceneOverride
.global FireTempleCutsceneOverride_patch
FireTempleCutsceneOverride_patch:
    bl Cutscene_OverrideFireTemple
    nop
    nop

.section .patch_WaterTempleItemGive
.global WaterTempleItemGive_patch
WaterTempleItemGive_patch:
    nop

.section .patch_WaterTempleItemGiveTwo
.global WaterTempleItemGiveTwo_patch
WaterTempleItemGiveTwo_patch:
    nop

.section .patch_WaterTempleItemGiveThree
.global WaterTempleItemGiveThree_patch
WaterTempleItemGiveThree_patch:
    nop

.section .patch_WaterTempleCutsceneOverride
.global WaterTempleCutsceneOverride_patch
WaterTempleCutsceneOverride_patch:
    bl Custcene_OverrideWaterTemple
    nop
    nop
    nop

.section .patch_SpiritTempleItemGive
.global SpiritTempleItemGive_patch
SpiritTempleItemGive_patch:
    nop

.section .patch_SpiritTempleItemGiveTwo
.global SpiritTempleItemGiveTwo_patch
SpiritTempleItemGiveTwo_patch:
    nop

.section .patch_SpiritTempleItemGiveThree
.global SpiritTempleItemGiveThree_patch
SpiritTempleItemGiveThree_patch:
    nop

.section .patch_SpiritTempleCompleteCheck
.global SpiritTempleCompleteCheck_patch
SpiritTempleCompleteCheck_patch:
    nop

.section .patch_SpiritTempleCutsceneOverride
.global SpiritTempleCutsceneOverride_patch
SpiritTempleCutsceneOverride_patch:
    bl Custcene_OverrideSpiritTemple
    nop

.section .patch_ShadowTempleItemGive
.global ShadowTempleItemGive_patch
ShadowTempleItemGive_patch:
    nop

.section .patch_ShadowTempleItemGiveTwo
.global ShadowTempleItemGiveTwo_patch
ShadowTempleItemGiveTwo_patch:
    nop

.section .patch_ShadowTempleItemGiveThree
.global ShadowTempleItemGiveThree_patch
ShadowTempleItemGiveThree_patch:
    nop

.section .patch_ShadowTempleCompleteCheck
.global ShadowTempleCompleteCheck_patch
ShadowTempleCompleteCheck_patch:
    nop

.section .patch_ShadowTempleCutsceneOverride
.global ShadowTempleCutsceneOverride_patch
ShadowTempleCutsceneOverride_patch:
    bl Custcene_OverrideShadowTemple
    nop

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
    b 0x28A6A0

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
    nop

.section .patch_ISGCrouchStab
.global ISGCrouchStab_patch
ISGCrouchStab_patch:
    nop

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

.section .patch_FishingStoreTempB
.global FishingStoreTempB_patch
FishingStoreTempB_patch:
    bl hook_FishingStoreTempB

.section .patch_FishingRestoreTempB
.global FishingRestoreTempB_patch
FishingRestoreTempB_patch:
    bl hook_FishingRestoreTempB

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
    .word 0x40800000

.section .patch_FireBlockCooldownTimer
.global FireBlockCooldownTimer_patch
FireBlockCooldownTimer_patch:
    mov r0,#0x1

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
    beq 0x179444

.section .patch_FrogReward
.global FrogReward_patch
FrogReward_patch:
    b hook_FrogReward

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
    nop

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
    bl hook_CheckCurrentDungeonMode

.section .patch_TalonGetCastleTextbox
.global TalonGetCastleTextbox_patch
TalonGetCastleTextbox_patch:
    bl hook_TalonGetCastleTextbox

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

.section .patch_MidoCheckDekuTreeClearFive
.global MidoCheckDekuTreeClearFive_patch
MidoCheckDekuTreeClearFive_patch:
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

.section .patch_GossipStoneAddSariaHint
.global GossipStoneAddSariaHint_patch
GossipStoneAddSariaHint_patch:
    bl hook_GossipStoneAddSariaHint

.section .patch_DecoratedChest
.global DecoratedChest_patch
DecoratedChest_patch:
    bl hook_DecoratedChest

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

.section .patch_SetSavewarpEntrance
.global SetSavewarpEntrance_patch
SetSavewarpEntrance_patch:
    bl hook_SetSavewarpEntrance
    b  0x44FCE0

.section .patch_SetGameOverEntrance
.global SetGameOverEntrance_patch
SetGameOverEntrance_patch:
    bl hook_SetGameOverEntrance
    b  0x458EC8

.section .patch_SariasSongHintsOne
.global SariasSongHintsOne_patch
SariasSongHintsOne_patch:
    bl Hints_GetNextSariasSongHint

.section .patch_SariasSongHintsTwo
.global SariasSongHintsTwo_patch
SariasSongHintsTwo_patch:
    bl Hints_GetNextSariasSongHint

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

.section .patch_MedigoronSetFlag
.global MedigoronSetFlag_patch
MedigoronSetFlag_patch:
    bl hook_MedigoronSetFlag

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

.section .patch_loader
.global loader_patch

loader_patch:
    b hook_into_loader
