.arm

.macro PATCH name
    .section .patch_\name
    .global \name\()_patch
\name\()_patch:
.endm

PATCH loader
    bl hook_into_loader

PATCH before_GlobalContext_Update
    bl hook_before_GlobalContext_Update

PATCH after_GlobalContext_Update
    b hook_after_GlobalContext_Update

PATCH Gfx_Update
    b hook_Gfx_Update

PATCH IncomingGetItemID
    str r5,[r4,#0x2B0]
    bl hook_IncomingGetItemID

PATCH SaveFile_Init
    bl hook_SaveFile_Init

PATCH OverrideTextID
    b hook_OverrideTextID

PATCH OverrideItemID
    b hook_OverrideItemID

PATCH OverrideDrawItemOne
    b hook_OverrideDrawItemOne

PATCH OverrideDrawItemTwo
    bl hook_OverrideDrawItemTwo

PATCH OverrideDrawItemThree
    bl hook_OverrideDrawItemThree

PATCH OverrideGiDrawIdPlusOne_Ground
    bl hook_OverrideGiDrawIdPlusOne

PATCH OverrideGiDrawIdPlusOne_Water
    bl hook_OverrideGiDrawIdPlusOne

PATCH EditDrawGetItemBeforeModelSpawn
    bl hook_EditDrawGetItemBeforeModelSpawn

PATCH EditDrawGetItemAfterModelSpawn
    bl hook_EditDrawDetItemAfterModelSpawn

PATCH EditDrawGetItemAfterMatrixUpdate
    bl hook_EditDrawGetItemAfterMatrixUpdate

PATCH NoLensOfTruthNaviText
    nop

PATCH NoSilverGauntletsCutsceneWarp
    b 0x2BC350

PATCH ChildShootingGallery
    mov r0,#0x60
    nop

PATCH AdultShootingGallery
    nop
    mov r0,#0x30
    b 0x38AB78

PATCH GerudoArcheryOne
    mov r4,#0x30
    b 0x3AFA44
    nop
    nop

PATCH GerudoArcheryTwo
    mov r5,#0x30
    b 0x3C2D90
    nop
    nop

PATCH ScrubStickUpgradeOne
    nop

PATCH ScrubNutUpgradeOne
    nop

PATCH ScrubStickUpgradeTwo
    nop

PATCH ScrubNutUpgradeTwo
    nop

PATCH ChildRollingGoron
    mov r2,#0x34
    nop

PATCH ChildRollingGoronDontCheckBombBag
    nop

PATCH AdultRollingGoronIgnoreMedallion
    b 0x19546C

PATCH AdultRollingGoronOne
    b 0x19549C

PATCH AdultRollingGoronTwo
    b hook_AdultRollingGoronTwo

PATCH DaruniaCheckStrength
    b hook_DaruniaStrengthCheck

PATCH LostWoodsShootingGame
    mov r2,#0x60
    nop

PATCH LostWoodsShootingGameTwo
    mov r2,#0x60
    nop

PATCH SkulltulaRewardOne
    b 0x12CC9C

PATCH SkulltulaRewardTwo
    b 0x12CD6C

PATCH KingZoraGiveTunic
    mov r0,#0x4000
    add r0,r0,#0x12

PATCH KingZoraSecondTunic
    b 0x1B6A40

PATCH KingZoraCheckMovedFlag
    bl hook_KingZoraCheckMovedFlag

PATCH KingZoraIgnoreSapphire
    nop
    nop

PATCH DampeRollHigh
    mov r0,#0x3
    b 0x3C3458

PATCH DampeCheckRewardFlag
    cpyeq r0,r4
    bleq EnTk_SetRewardFlag

PATCH DampeSetCollectibleFlag
    .word 0x00000806

PATCH DampeCheckCanDig1
    mov r0,#0x01

PATCH DampeCheckCanDig2
    mov r0,#0x01

PATCH TokenNoItemGive1
    nop

PATCH TokenNoItemGive2
    nop

PATCH GetToken1
    bl hook_GetToken

PATCH GetToken2
    bl hook_GetToken

PATCH GetCustomMessageEntryOne
    bl Message_GetCustomEntry

PATCH GetCustomMessageEntryTwo
    bl Message_GetCustomEntry

PATCH GetCustomMessageTextOne
    bl Message_GetCustomText

PATCH GetCustomMessageTextTwo
    bl Message_GetCustomText

PATCH FastChests
    bl hook_FastChests

PATCH FastChestsTwo
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

PATCH DampeChest
    cpy r0,r4
    bl EnPoRelay_CheckChestFlag
    nop

PATCH RainbowBridge
    push {r0-r12, lr}
    bl BgGjyoBridge_CheckCondition
    cmp r0,#0x0
    pop {r0-r12, lr}
    beq 0x3E7D70
    b 0x3E7D34

PATCH ExtendedObjectClear
    bl ExtendedObject_Clear

PATCH SariasGift
    bl ItemOverride_GiveSariasGift
    nop
    nop

PATCH DekuTheaterSkullMask
    mov r0,#0x77
    nop

PATCH DekuTheaterMaskOfTruth
    mov r0,#0x7A
    nop

PATCH PoeCollectorCheckPoints
    bl hook_PoeCollectorCheckPoints

PATCH LACSConditionOne
    nop

PATCH LACSConditionTwo
    bl Cutscene_OverrideLACS
    nop
    nop
    nop
    nop

PATCH MinuetLocation
    bl Cutscene_OverrideMinuet
    b 0x26C47C

PATCH BoleroLocation
    bl Cutscene_OverrideBolero
    b 0x26C47C

PATCH SerenadeCheckChestFlag
    bl hook_SerenadeCheckChestFlag

PATCH SerenadeLocation
    bl Cutscene_OverrideSerenade
    b 0x2B25A8

PATCH RequiemLocation
    nop
    nop
    bl Cutscene_OverrideRequiem

PATCH NocturneLocation
    bl Cutscene_OverrideNocturne
    b ret_NocturneLocation

PATCH FreeScarecrow
    bl hook_ScarecrowCheckToBeActivated

PATCH MasterSwordAlwaysDrop
    nop

PATCH PreludeLocation
    bl Cutscene_OverridePrelude
    cmp r0,#0x0
    beq 0x18DAD0
    b 0x18DA38

PATCH LullabyLocation
    bl Cutscene_OverrideLullaby
    b 0x3A0AC8

PATCH EponasSongCheckFlag
    bl hook_EponasSongCheckFlag

PATCH EponasSongCheckFlagTwo
    bl hook_EponasSongCheckFlag

PATCH EponasSongLocation
    bl Cutscene_OverrideEponasSong
    b 0x3C61CC

PATCH MalonNextAction
    .word 0x3D2A14

PATCH SariasSongCheckFlag
    bl hook_SariasSongCheckFlag

PATCH SariasSongItemGive
    nop

PATCH SariasSongLocation
    bl Cutscene_OverrideSariasSong
    b 0x12C92C

PATCH SunsSongLocation
    bl Cutscene_OverrideSunsSong
    b 0x2888F0

PATCH SongOfTimeLocation
    cpy r0,r5
    bl Cutscene_OverrideSongOfTime
    b 0x3C3780

PATCH SongOfStormsLocation
    bl Cutscene_OverrideSongOfStorms
    b 0x1427F8

PATCH BiggoronDayCheck
    mov r0,#0x3

PATCH BiggoronGetTextId
    bl EnGo2_rGetTextIdGoronDmtBiggoron
    b 0x195524

PATCH BiggoronCheckBGSFlag
    nop
    nop
    nop

PATCH BiggoronDontSetBGSFlag
    nop

PATCH BiggoronSetTextId
    push {r0-r12, lr}
    cpy r0,r4
    bl EnGo2_rBiggoronSetTextId
    pop {r0-r12, lr}
    b 0x1D8B80

PATCH BiggoronAfterGiveItem
    .word EnGo2_AfterGiveItem

PATCH ItemEtceteraModelDraw
    bl hook_ItemEtceteraModelDraw

PATCH KokiriCheckOpenForest
    bl hook_KokiriCheckOpenForest

PATCH BombchuBowlingStaticReward
    b 0x20618C

PATCH ChildBlueWarpOverride
    push {r0-r12, lr}
    bl Cutscene_BlueWarpOverride
    pop {r0-r12, lr}
    b 0x3F58A8

PATCH RutoBlueWarpOverride
    push {r0-r12, lr}
    bl Cutscene_BlueWarpOverride
    pop {r0-r12, lr}
    b 0x1A1944

PATCH AdultBlueWarpOverride
    push {r0-r12, lr}
    bl Cutscene_BlueWarpOverride
    pop {r0-r12, lr}
    b 0x1E4274

PATCH EnExItemModelDraw
    bl hook_EnExItemModelDraw

PATCH DemoEffectMedallionDraw
    b hook_DemoEffectMedallionDraw

PATCH DemoEffectStoneDraw
    b hook_DemoEffectStoneDraw

PATCH DekuSproutCheckForest
    ldr r0, [r0,#0xEF4]
    nop
    tst r0,#0x100

PATCH EnKoInitCheckForest_165834
    bl hook_EnKoInitCheckForest
    nop
    nop

PATCH EnKoInitCheckForest_165878
    bl hook_EnKoInitCheckForest
    nop
    nop

PATCH EnKoInitCheckForest_1658C0
    bl hook_EnKoInitCheckForest
    nop
    nop

PATCH EnKoInitCheckForest_1658F0
    bl hook_EnKoInitCheckForest
    nop
    nop

PATCH FireArrowCheckChestFlagOne
    bl hook_FireArrowCheckChestFlag

PATCH FireArrowCheckChestFlagTwo
    bl hook_FireArrowCheckChestFlag

PATCH FireArrowRequirement
    ldr r2, [r1,#0xEF4]
    nop
    tst r2,#0x400

PATCH BusinessScrubCheckFlags
    cpy r0,r4
    bl EnShopnnuts_rCheckFlags
    cmp r0,#0x0

PATCH BusinessScrubTable
    .word rScrubTable

PATCH KakarikoGateCheck
    bl hook_KakarikoGateCheck

PATCH FairyReward
    cpy r0,r4
    bl Cutscene_OverrideFairyReward
    b 0x3E75F8

PATCH PoeCollectorGetFirstTextbox
    bl hook_PoeCollectorGetFirstTextbox

PATCH OcarinaMinigameRewardsOrder
    .word 0x76
    .word 0x4D
    .word 0x4E

PATCH OcarinaMinigameEndAfterWin
    nop

PATCH ISGPutaway
    bl hook_RestoreISG

PATCH ISGCrouchStab
    bl hook_RestoreISG

PATCH ApplyDamageMultiplier
    bl hook_ApplyDamageMultiplier

PATCH SceneInitAfterCopyScenes
    b hook_SceneInitAfterCopyScenes

PATCH StoreChildBButtonEquip
    b hook_StoreChildBButtonEquip

PATCH AlwaysRestoreChildEquips
    nop

PATCH ChildDontEquipSwordSlotByDefault
    push {r1-r12, lr}
    bl SaveFile_RestoreChildEquips
    pop {r1-r12, lr}
    nop

PATCH LullabyCheckFlag
    bl hook_LullabyCheckFlag

PATCH FishingIgnoreTempBOne
    b hook_FishingIgnoreTempBOne

PATCH FishingIgnoreTempBTwo
    b hook_FishingIgnoreTempBTwo

PATCH ItemGiveBombchuDropOne
    mov r1,#0x96

PATCH ItemGiveBombchuDropTwo
    mov r1,#0x96

PATCH ConvertBombDropOne
    b hook_ConvertBombDropOne

PATCH ConvertBombDropTwo
    b hook_ConvertBombDropTwo

PATCH BeanDaddyModifyBeansBought
    bl hook_BeanDaddyModifyBeansBought

PATCH BeanDaddyModifyPrice
    bl hook_BeanDaddyModifyPrice

PATCH BeanDaddyPurchase
    bl EnMs_Purchase

PATCH CheckGerudoToken_18B368
    push {r1-r12, lr}
    bl SaveFile_CheckGerudoToken
    pop {r1-r12, lr}
    cmp r0,#0x0

PATCH CheckGerudoToken_18B3A0
    push {r1-r12, lr}
    bl SaveFile_CheckGerudoToken
    pop {r1-r12, lr}
    cmp r0,#0x0

PATCH CheckGerudoToken_18B3C0
    push {r1-r12, lr}
    bl SaveFile_CheckGerudoToken
    pop {r1-r12, lr}
    cmp r0,#0x0

PATCH CheckGerudoToken_18B448
    push {r1-r12, lr}
    bl SaveFile_CheckGerudoToken
    pop {r1-r12, lr}
    cmp r0,#0x0

PATCH CheckGerudoToken_18B6F4
    bl hook_CheckGerudoToken
    cmp r0,#0x1

PATCH CheckGerudoToken_18B710
    bl hook_CheckGerudoToken
    cmp r0,#0x1

PATCH CheckGerudoToken_1D7AD4
    bl hook_CheckGerudoToken
    cmp r0,#0x1

PATCH CheckGerudoToken_269884
    bl hook_CheckGerudoToken
    cmp r0,#0x1

PATCH MovableBlockSpeed
    .word 0x40800000

PATCH MovableBlockCooldownTimer
    mov r0,#0x1

PATCH MilkCrateSpeed
    .word 0x40800000

PATCH MilkCrateCooldownTimer
    mov r0,#0x1

PATCH AmyBlockSpeed
    .word 0x40800000

PATCH AmyBlockCooldownTimer
    mov r1,#0x1

PATCH FireBlockSpeed
    .word 0x3DCCCCCD

PATCH ArmosPushSpeed
    .word 0x3F800000

PATCH ArmosCooldownTimer
    mov r0,#0xC

PATCH ForestTempleBasementPuzzleDelay
    cmp r0,#0x1

PATCH CowBottleCheck
    bl hook_CowBottleCheck

PATCH CowItemOverride
    b hook_CowItemOverride

PATCH AnjuCheckCuccoAmount
    b hook_AnjuCheckCuccoAmount

PATCH FrogReward
    b hook_FrogReward

PATCH FrogRewardPurple
    beq hook_FrogReward

PATCH CanPlayBombchuBowlingOne
    bl hook_CanPlayBombchuBowling

PATCH CanPlayBombchuBowlingTwo
    bl hook_CanPlayBombchuBowling

PATCH BombchuBowlingAlwaysFirstPrize
    mov r0,#0x0

PATCH BombchuBowlingPrizeOrder
    .word 0x0021CAFC
    .word 0x0021CB0C
    .word 0x0021CAF4

PATCH CourtyardCheckForVisitedZeldaOne
    ldreqh r0,[r0,#0xF4]

PATCH CourtyardCheckForVisitedZeldaTwo
    ldreqh r0,[r0,#0xF4]

PATCH ImpaInCourtyardCheckForVisitedZelda
    ldrh r2,[r1,#0xF4]

PATCH LikeLikeNeverEatTunic
    b 0x355C48

PATCH SwapFaroresWind
    bl SaveFile_SwapFaroresWind
    nop

PATCH BombchuShopAlwaysOpen
    nop

PATCH BombchuCheapestPriceOne
    .word 0x0063FFFF

PATCH BombchuCheapestPriceTwo
    .word 0x0063FFFF

PATCH BombchuCheapestPriceThree
    .word 0x0063FFFF

PATCH BombchuCheapestPriceFour
    .word 0x0063FFFF

PATCH BombchuPurchaseableCheck
    bl Shop_CheckCanBuyBombchus
    nop
    nop
    nop

PATCH BombPurchaseableCheck
    nop

PATCH BombchuShopInfinitePurchases
    b hook_BombchuShopInfinitePurchases

PATCH GanonBattleDeathWarp
    bl Entrance_DeathInGanonBattle

PATCH SlidingDoorDestroyCustomModels
    bl hook_SlidingDoorDestroyCustomModels

PATCH HandleDoorDestroyCustomModels
    bl hook_HandleDoorDestroyCustomModels

PATCH DoorOfTimeOpenCutscene
    add r0,r6,#0x100
    ldrh r0,[r0,#0x4]
    cmp r0,#0x43

PATCH DungeonCheckJabuMQBox
    bl hook_DungeonCheckJabuMQBox
    nop

PATCH JabuSwitchRutoCheck
    bl hook_JabuSwitchRutoCheck

PATCH JabuBoxCheckRuto
    bl hook_JabuBoxCheckRuto

PATCH TalonGetCastleTextbox
    bl hook_TalonGetCastleTextbox

PATCH MidoCheckSpawn
    bl hook_MidoCheckSpawn
    beq 0x1661B8
    b 0x1661A8

PATCH MidoForestDialog
    nop
    nop
    nop
    nop
    bl hook_MidoForestDialog

PATCH MidoCheckDekuTreeClearOne
    nop
    nop
    bl hook_CheckDekuTreeClear

PATCH MidoCheckDekuTreeClearTwo
    nop
    nop
    bl hook_CheckDekuTreeClear

PATCH MidoCheckDekuTreeClearThree
    nop
    nop
    bl hook_CheckDekuTreeClear

PATCH MidoCheckDekuTreeClearFour
    nop
    nop
    bl hook_CheckDekuTreeClear

PATCH CorrectCompassChests
    bl hook_CheckCurrentDungeonMode

PATCH CorrectCompassChestsTwo
    bl hook_CheckCurrentDungeonMode

PATCH FishingNewRecord
    mov r0,#0x0
    cmp r0,#0x1

PATCH FishingSizeIgnoreChild
    nop

PATCH FishingSizeIgnoreAdult
    nop

PATCH TycoonWalletSize
    .word 0x03E701F4

PATCH ReadGossipStoneHints
    bl hook_CanReadHints
    nop
    nop
    nop
    nop

PATCH GossipStoneAddSariaHint
    bl hook_GossipStoneAddSariaHint

PATCH GoronShopPurchaseableCheck
    nop

PATCH PlayerEditAndRetrieveCMB
    bl Player_EditAndRetrieveCMB

PATCH PlayerGetCustomTunicCMAB
    bl Player_GetCustomTunicCMAB

PATCH SetChildCustomTunic
    bne hook_SetChildCustomTunic

PATCH FastOwlCutscenes
    bl hook_FastOwlCutscenes

PATCH ShopItemDontSetAnimSpeedOne
    nop

PATCH ShopItemDontSetAnimSpeedTwo
    nop

PATCH BugsRecatchable
    nop

PATCH SkipDaruniaDanceOne
    nop

PATCH SkipDaruniaDanceTwo
    nop

PATCH SkipDaruniaDanceThree
    nop

PATCH ShortenRainbowBridgeCS
    bl hook_ShortenRainbowBridgeCS

PATCH RemoveWaterfallCS
    nop
    cpy r0,r10
    add r1,r10,#0x800
    add r1,r1,#0x2E8
    ldr r2,[r6,#0x1A4]
    bl 0x36B940

PATCH OwlMagicCheck
    mov r0,#0x1

PATCH ChestIceSmoke
    b hook_Chest_OverrideIceSmoke

PATCH EnableFW
    bl hook_EnableFW

PATCH FWKeepWarpPoint
    blmi hook_FWUnset

PATCH FWLoadSet
    ldr r2,[r1,#-0x668]

PATCH FWGetSet
    b hook_FWGetSet

PATCH SetSavewarpEntrance
    bl hook_SetSavewarpEntrance
    b ret_SetSavewarpEntrance

PATCH SetGameOverEntrance
    bl hook_SetGameOverEntrance
    b ret_SetGameOverEntrance

PATCH SetGameOverRespawnFlag
    bl hook_SetGameOverRespawnFlag

PATCH SetSunsSongRespawnFlag
    bl hook_SetSunsSongRespawnFlag

PATCH SunsSongEndCloseTextbox
    beq hook_SunsSongEndCloseTextbox

PATCH SetSpecialVoidOutRespawnFlag
    bl hook_SetSpecialVoidOutRespawnFlag

PATCH SariasSongHintsOne
    bl Hints_GetNextSariasSongHint

PATCH SariasSongHintsTwo
    bl Hints_GetNextSariasSongHint

PATCH ActorUpdate
    bl hook_ActorUpdate

PATCH TitleCardUpdate
    bl TitleCard_rUpdate

PATCH NoHealFromHealthUpgrades
    bl hook_NoHealFromHealthUpgrades

PATCH NoHealFromBombchuBowlingPrize
    bl hook_NoHealFromBombchuBowlingPrize

PATCH FairyPickupHealAmount
    bl hook_FairyPickupHealAmount

PATCH FairyReviveHealAmount
    bl hook_FairyReviveHealAmount

PATCH FairyUseHealAmount
    bl hook_FairyUseHealAmount

PATCH MedigoronCheckFlagOne
    b hook_MedigoronCheckFlagOne

PATCH MedigoronCheckFlagTwo
    b hook_MedigoronCheckFlagTwo

PATCH MedigoronSetRewardFlag
    b hook_MedigoronSetRewardFlag

PATCH MedigoronGetCustomText
    b hook_MedigoronGetCustomText
    nop

PATCH MedigoronItemOverrideOne
    b hook_MedigoronItemOverrideOne

PATCH MedigoronItemOverrideTwo
    b hook_MedigoronItemOverrideTwo

PATCH CarpetSalesmanCheckFlagOne
    bl hook_CarpetSalesmanCheckFlagOne

PATCH CarpetSalesmanCheckFlagTwo
    bl hook_CarpetSalesmanCheckFlagTwo

PATCH CarpetSalesmanSetFlag
    bl hook_CarpetSalesmanSetFlag

PATCH DoorOfTimeCheck
    bl hook_DoorOfTimeCheck

PATCH SongOfTimeJingle
    bl hook_SongOfTimeJingle

PATCH GKSetDurability
    b hook_GKSetDurability

PATCH TurboTextAdvance
    bl hook_TurboTextAdvance

PATCH TurboTextClose
    bl hook_TurboTextClose

PATCH TurboTextSignalNPC
    bl hook_TurboTextSignalNPC

PATCH SkipSongReplays_TimeBlocksFix
    b hook_SkipSongReplays_TimeBlocksFix

PATCH ItemsMenuNumSprites
    mov r1,#0x19

PATCH ItemsMenuDraw
    bl hook_ItemsMenuDraw

PATCH GearMenuEmptySlot
    b hook_GearMenuEmptySlot

PATCH PreSwapBuffers
    bl hook_Draw_PreSwapBuffers

PATCH SleepQueryCallback
    b hook_Gfx_SleepQueryCallback

PATCH AwakeCallback
    b hook_Gfx_AwakeCallback

PATCH AnjuGiveCojiro
    .word EnNiwLady_rGiveCojiro

PATCH GrogCheckForShouldDespawn
    push {r0-r12, lr}
    cpy r0,r4
    bl EnHs_CheckForShouldDespawn
    pop {r0-r12, lr}
    nop

PATCH GrogSetTradedCojiroFlag
    .word EnHs_SetTradedCojiroFlag

PATCH CheckFadoCanSpawnInLostWoods
    push {r1-r12, lr}
    bl EnKo_CheckFadoCanSpawnInLostWoods
    pop {r1-r12, lr}

PATCH CarpenterBossSetTradedSawFlag
    bl hook_CarpenterBossSetTradedSawFlag

PATCH CarpenterBossDontNullExchangeItem
    nop

PATCH LabScientistDontStartTimerAndSetFlag
    nop
    push {r0-r12, lr}
    bl EnMk_SetTradedEyeballFrogFlag
    pop {r0-r12, lr}
    nop

PATCH LabScientistIgnoreEyedropsInInventory
    b 0x3F0B5C

PATCH KingZoraDontStartTimer
    nop
    nop
    nop
    nop
    nop

PATCH KingZoraSetTradedPrescriptionFlag
    beq hook_KingZoraSetTradedPrescriptionFlag

PATCH CheckForWeirdEggHatchGameplayInit
    bl SaveFile_CheckForWeirdEggHatch

PATCH CheckForPocketCuccoHatchGameplayInit
    bl SaveFile_CheckForPocketCuccoHatch

PATCH CheckForWeirdEggHatchKankyo
    bl SaveFile_CheckForWeirdEggHatch

PATCH CheckForPocketCuccoHatchKankyo
    bl SaveFile_CheckForPocketCuccoHatch

PATCH SkipSongReplays_WarpBlocksFix
    b hook_SkipSongReplays_WarpBlocksFix

PATCH Audio_PlayFanfare
    b hook_Audio_PlayFanfare

PATCH SetBGMEntrance
    b hook_SetBGMEntrance

PATCH SetBGMDayNight
    b hook_SetBGMDayNight

PATCH SetBGMEvent
    b hook_SetBGMEvent

PATCH SetSFX
    b hook_SetSFX

PATCH GiantsKnifeWithoutKokiriSword
    cmp r3,#0x8
    blt 0x376C54

PATCH SkipTimeTravelCutsceneOne
    b hook_SkipTimeTravelCutsceneOne

PATCH SkipTimeTravelCutsceneTwo
    bl hook_SkipTimeTravelCutsceneTwo

PATCH SwapAgeIgnoreSceneSetup
    nop

PATCH SkipMasterSwordFanfare
    bl hook_SkipMasterSwordFanfare

PATCH GameOverDontSpoilTradeItems
    b ret_GameOverDontSpoilTradeItems

PATCH InterfaceDrawDontSpoilTradeItems
    b ret_InterfaceDrawDontSpoilTradeItems

PATCH OpenSaveDontSpoilTradeItems
    b ret_OpenSaveDontSpoilTradeItems

PATCH EnteredLocation
    bl hook_EnteredLocation

PATCH LostWoodsBridgeMusic
    bl hook_LostWoodsBridgeMusic

PATCH BeforeLoadGame
    b hook_BeforeLoadGame

PATCH AfterLoadGame
    b hook_AfterLoadGame

PATCH FileSelect_CopyFile
    bl hook_FileSelect_CopyFile

PATCH SaveGame
    b hook_SaveGame

PATCH DontSetMotionSetting
    nop

PATCH SaveMenuIgnoreOpen
    bl hook_SaveMenuIgnoreOpen

PATCH GameOverStart
    bl hook_GameOverStart

PATCH PermadeathSkipMenu
    bl hook_PermadeathSkipMenu

PATCH PermadeathForceQuit
    bl hook_PermadeathForceQuit

PATCH OverrideFogDuringGameplayInit
    bl hook_OverrideFogDuringGameplayInit

PATCH KotakeDontPlayBattleMusic
    nop

PATCH SkipTwinrovaQuarrelCutsceneOne
    sub r1,r1,#0x500

PATCH SkipTwinrovaQuarrelCutsceneTwo
    bl hook_SkipTwinrovaQuarrelCutscene

PATCH FixItemsMenuSlotDuplication
    b hook_FixItemsMenuSlotDuplication

PATCH PlayEntranceCutscene
    bl hook_PlayEntranceCutscene

PATCH SkipJabuOpeningCutscene
    bl hook_SkipJabuOpeningCutscene

PATCH MultiplyPlayerSpeed
    bl hook_MultiplyPlayerSpeed

PATCH RunAnimationSpeed
    bl hook_RunAnimationSpeed

PATCH NaviNotifications
    bl hook_NaviNotifications

PATCH ChestMinigame_RewardChestVisibility
    .word 0x00000EC0
    .word 0x00000EA0

PATCH ChestMinigame_KeyChestVisibility
    bl hook_ChestMinigame_KeyChestVisibility

PATCH ChestMinigame_DontOpenChestsOnInit
    bl hook_ChestMinigame_DontOpenChestsOnInit

PATCH GameplayDestroy
    bl hook_GameplayDestroy

PATCH SceneExitOverride
    bl hook_SceneExitOverride

PATCH SceneExitDynamicOverride
    bl hook_SceneExitDynamicOverride

PATCH OverrideGrottoActorEntrance
    b hook_OverrideGrottoActorEntrance

PATCH ReturnFW
    bl hook_ReturnFW

PATCH WarpSongEntranceOverride
    bl hook_WarpSongEntranceOverride

PATCH DMTOwlEntranceOverride
    b hook_OwlEntranceOverride

PATCH LHOwlEntranceOverride
    b hook_OwlEntranceOverride

PATCH SavewarpSetRespawnFlag
    bl hook_SavewarpSetRespawnFlag

PATCH AdultItemsCMABsAsChild
    bl hook_AdultItemsCMABsAsChild

PATCH Model_EnableMeshGroupByIndex
    b hook_Model_EnableMeshGroupByIndex

PATCH NockArrow
    bl hook_ArrowsOrSeeds

PATCH DecreaseArrowCount
    bl hook_ArrowsOrSeeds

PATCH HookshotDrawChain
    b hook_HookshotDrawChain

PATCH HookshotRotation
    bl hook_HookshotRotation

PATCH LinkReflection
    b hook_LinkReflection

PATCH ChildCanOpenBowSubMenu
    b hook_ChildCanOpenBowSubMenu

PATCH RedBoulderExplode
    b hook_RedBoulderExplode

PATCH Multiplayer_UpdatePrevActorFlags
    bl hook_Multiplayer_UpdatePrevActorFlags

PATCH Multiplayer_OnLoadFile
    bl hook_Multiplayer_OnLoadFile

PATCH SendDroppedBottleContents
    bl hook_SendDroppedBottleContents

PATCH IgnoreMaskReaction
    b hook_IgnoreMaskReaction

PATCH MasterQuestGoldSkulltulaCheck
    b hook_MasterQuestGoldSkulltulaCheck

PATCH WaterSpoutMasterQuestCheck
    bl hook_WaterSpoutMasterQuestCheck

PATCH PierreSoftlockFixOne
    pop {r3-r7,lr}
    bx lr

PATCH PierreSoftlockFixTwo
    bl hook_PierreSoftlockFixTwo

PATCH PierreSoftlockFixThree
    nop
    nop
    nop
    nop

PATCH StoreTargetActorType
    bl hook_StoreTargetActorType

PATCH SwordTrailDurationGrezzoFix
    nop

PATCH ForceTrailEffectUpdate
    blne hook_ForceTrailEffectUpdate

PATCH RainbowSwordTrail
    bl hook_RainbowSwordTrail

PATCH BoomerangTrailEffect
    bl hook_BoomerangTrailEffect

PATCH RainbowChuTrailOne
    bl hook_RainbowChuTrail

PATCH RainbowChuTrailTwo
    bl hook_RainbowChuTrail

PATCH FWandWarpSongTimerDepletion
    push {lr}
    bl hook_FWandWarpSongTimerDepletion
    pop {lr}

PATCH TimerExpiration
    bl hook_TimerExpiration

PATCH Timer2TickSound
    bl hook_Timer2TickSound

PATCH CurseTrapDizzyStick
    bl hook_CurseTrapDizzyStick

PATCH CurseTrapDizzyButtons
    bl hook_CurseTrapDizzyButtons

PATCH CrouchStabHitbox
    bl hook_CrouchStabHitbox

PATCH MasterSwordTimerCheck
    nop

PATCH BossChallenge_Enter
    bl hook_BossChallenge_Enter

PATCH BossChallenge_ExitMenu
    bl hook_BossChallenge_ExitMenu

PATCH TruthSpinnerSpeed
    cmp r2,#0x20
    strh r2,[r4,#0xC4]
    movgt r2,#0x20

PATCH LostWoodsTargetCutscene
    nop

PATCH LostWoodsTargetTimer
    mov r0,#0x1

PATCH GrannyTextID
    bl hook_GrannyTextID

PATCH GrannyBottleCheck
    bl hook_GrannyBottleCheck

PATCH GrannyItemOverrideOne
    bl hook_GrannyItemOverride

PATCH GrannyItemOverrideTwo
    b hook_GrannyItemOverride

PATCH GrannySetRewardFlag
    bl hook_GrannySetRewardFlag

PATCH BecomeAdult
    push {lr}
    bl hook_BecomeAdult
    pop {lr}

PATCH PickUpMasterSword
    bl Pedestal_PickUpMasterSword

PATCH SaveFileSwordless
    push {lr}
    bl hook_HandleBButton
    pop {lr}

PATCH LoadFileSwordless
    bl hook_LoadFileSwordless

PATCH DeathHandleBButton
    push {lr}
    bl hook_HandleBButton
    pop {lr}

PATCH GanonCSEquipMS
    bl Ganon_CSEquipMS
    nop
    nop
    nop

PATCH GanonRestoreMSOnDeath
    bl hook_GanonRestoreMSOnDeath

PATCH GanonGiveMSMidFight
    bl Ganon_GiveMSMidFight

PATCH GiveItemMasterSword
    push {r0-r12,lr}
    bl ItemEffect_EquipMasterSword
    pop {r0-r12,lr}
    nop
    nop
    nop
    nop

PATCH CriticalHealthCheckOne
    bl hook_CriticalHealthCheck
    nop
    nop
    nop
    nop

PATCH CriticalHealthCheckTwo
    bl hook_CriticalHealthCheck
    nop
    nop
    nop
    nop

PATCH CriticalHealthCheckThree
    push {lr}
    bl hook_CriticalHealthCheck
    pop {lr}
    nop
    nop

PATCH InitSceneMirrorWorld
    bl hook_InitSceneMirrorWorld

PATCH InitSceneEntranceOverride
    bl hook_InitSceneEntranceOverride

PATCH CollisionATvsAC
    bl hook_CollisionATvsAC

PATCH CollisionCheck_SetAC_Once
    bl hook_CollisionCheck_SetAll_Once

PATCH CollisionCheck_SetAT_Once
    bl hook_CollisionCheck_SetAll_Once

PATCH CollisionCheck_SetOC_Once
    bl hook_CollisionCheck_SetAll_Once

PATCH GanonDrawMasterSword
    bl hook_GanonDrawMasterSword

PATCH SetFWPlayerParams
    bl hook_SetFWPlayerParams

PATCH AboutToPickUpActor
    bl hook_AboutToPickUpActor

PATCH TargetReticleColor
    bl hook_TargetReticleColor

PATCH TargetPointerColor
    bl hook_TargetPointerColor

PATCH ShadowShip_CSTimer
    .word 0xC3

PATCH ShadowShip_Speed
    bl hook_ShadowShip_Speed

PATCH MaskSalesmanCheckNoMaskOne
    push {r0,r1,r4-r12,lr}
    bl SaveFile_MaskSlotValue

PATCH MaskSalesmanCheckNoMaskTwo
    cpy r2,r0
    pop {r0,r1,r4-r12,lr}

PATCH MaskSalesmanBorrowMask
    bl hook_MaskSalesmanBorrowMask

PATCH MaskSalesmanGiveMaskOfTruth
    bl hook_MaskSalesmanGiveMaskOfTruth

PATCH OoBBombchuOne
    bl hook_OoBBombchuOne

PATCH OoBBombchuTwo
    bl hook_OoBBombchuTwo

PATCH OoBBombchuThree
    bl hook_OoBBombchuThree

PATCH CamRoll
    bl hook_CamRoll

PATCH CamUpdate
    bl hook_CamUpdate

PATCH Sheik_GetTextID
    b hook_Sheik_GetTextID

PATCH OnActorSetup_SceneChange
    bl hook_OnActorSetup_SceneChange

PATCH AfterActorSetup_SceneChange
    bl hook_AfterActorSetup_SceneChange

PATCH OnActorSetup_RoomChange
    bl hook_OnActorSetup_RoomChange

PATCH AfterActorSetup_RoomChange
    bl hook_AfterActorSetup_RoomChange

PATCH RandomGsLoc_CustomTangibilityCheck
    b hook_RandomGsLoc_CustomTangibilityCheck

PATCH RandomGsLoc_CustomTokenSpawnOffset
    bl hook_RandomGsLoc_CustomTokenSpawnOffset

PATCH RandomGsLoc_BlockSpawn_Crate
    bl hook_RandomGsLoc_BlockSpawn_Crate

PATCH RandomGsLoc_BlockSpawn_Tree
    bl hook_RandomGsLoc_BlockSpawn_Tree

PATCH RandomGsLoc_BlockSpawn_Soil
    bl hook_RandomGsLoc_BlockSpawn_Soil

PATCH RandomGsLoc_SkipSoilJingle
    bl hook_RandomGsLoc_SkipSoilJingle

PATCH ActorDraw
    bl hook_ActorDraw

PATCH FlyingPotCollision
    bl hook_FlyingPotCollision

PATCH FlyingTileCollision
    bl hook_FlyingTileCollision

PATCH ShabomAfterDamagePlayer
    bl hook_ShabomAfterDamagePlayer

PATCH DodongoAfterSwallowBomb
    bl hook_DodongoAfterSwallowBomb

PATCH BabyDodongoAfterSwallowBomb
    bl hook_BabyDodongoAfterSwallowBomb

PATCH OcarinaNoteButtonsDraw
    push {lr}
    bl hook_OcarinaNoteButtonsDraw
    pop {lr}

PATCH OcarinaNoteButtonsPress
    bl hook_OcarinaNoteButtonsPress

PATCH HandleTextControlCode
    bl hook_HandleTextControlCode

PATCH CheckForTextControlCode
    bl hook_CheckForTextControlCode

PATCH PlayInit
    bl hook_PlayInit

PATCH TitleLinkObject
    .word 0xFFFF0014

PATCH ExtendObjectGetSlot
    b hook_ExtendObjectGetSlot

PATCH OverrideObjectIsLoaded
    b hook_OverrideObjectIsLoaded

PATCH Cutscene_CheckObjectLoaded
    bl hook_OverrideObjectIsLoadedForCutscenes

PATCH AfterObjectListCommand
    bl hook_AfterObjectListCommand

PATCH GetObjectEntry_33AB24
    bl hook_GetObjectEntry_33AB24

PATCH GetObjectEntry_353CE4
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_36A96C
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_372F7C
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_EnSiInit
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_EnXcInit
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_ObjSwitchInit
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_34FE68
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_352F28
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_33A950
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_EnTiteInit
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_339DFC
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_EnGomaInit_One
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_EnGomaInit_Two
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_EnRdInit_One
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_EnRdInit_Two
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_34F270
    b hook_GetObjectEntry_34F270

PATCH GetObjectEntry_1F85B0
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_164BC8
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_EnDekunutsInit
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_EnNutsballInit
    bl hook_GetObjectEntry_Generic

PATCH GetObjectEntry_EnHintnutsInit
    bl hook_GetObjectEntry_Generic

PATCH AltHeadersCommand
    bl hook_AltHeadersCommand

PATCH GohmaLarvaDeathSignalParent
    bl hook_GohmaLarvaDeathSignalParent

PATCH GohmaEggDeathSignalParent
    bl hook_GohmaEggDeathSignalParent

PATCH StalchildDespawn_13DB68
    bl hook_StalchildDespawn_13DB68

PATCH StalchildDespawn_366338
    bl hook_StalchildDespawn_366338

PATCH SkullwalltulaAttack_35F834
    bl hook_SkullwalltulaAttack_35F834

PATCH SkullwalltulaAttack_35F328
    bl hook_SkullwalltulaAttack_35F328

PATCH SkullwalltulaTargetRotation
    bl hook_SkullwalltulaTargetRotation

PATCH AnubisFlameCircleCheck
    @ check alpha instead of timer
    ldrb r1,[r1,#0xAB]

PATCH SkullKidPoacherSawCheck
    bl hook_SkullKidPoacherSawCheck

PATCH LeeverSandCheck_Init
    bl hook_LeeverSandCheck

PATCH LeeverSandCheck_Small
    bl hook_LeeverSandCheck

PATCH LeeverSandCheck_Big
    bl hook_LeeverSandCheck

PATCH LeeverAfterSink
    blt hook_LeeverAfterSink

PATCH LeeverAfterDie
    bl hook_LeeverAfterDie

PATCH LeeverDontChangeCategory
    @ Big Leevers change category from Misc to Enemy in OoT.
    @ But in OoT3D they're already in the Enemy category
    @ from the start, so changing it is useless and can
    @ trigger room clears during Enemy Randomizer.
    nop

PATCH FlyingPotDontChangeCategory
    nop

PATCH PlayerCheckVoidOut
    bl hook_PlayerCheckVoidOut

PATCH EnBlkobj_SpawnDarkLink
    bl hook_EnBlkobj_SpawnDarkLink

PATCH EnBlkobj_FindDarkLink
    bl hook_EnBlkobj_FindDarkLink

PATCH EnEncount1_SpawnStalchildWolfos
    bl hook_EnEncount1_SpawnStalchildWolfos

PATCH EnEncount1_SpawnLeever
    bl hook_EnEncount1_SpawnLeever

PATCH EnEncount1_SetLeeverAimType
    bl hook_EnEncount1_SetLeeverAimType

PATCH DarkLinkPlayerRecoil
    bl hook_DarkLinkPlayerRecoil

PATCH BabyDodongoWallCheck
    bl hook_BabyDodongoWallCheck

PATCH PeahatLarvaGroundCheck
    bl hook_PeahatLarvaGroundCheck

PATCH RedeadCanFreezePlayer
    bl hook_RedeadCanFreezePlayer

PATCH DeadHandHandCanGrabPlayer
    bl hook_DeadHandHandCanGrabPlayer

PATCH GerudoBattleMusic
    bl hook_GerudoBattleMusic

PATCH FixActorKillLoop
    bl hook_FixActorKillLoop

PATCH AfterInvalidatingRoomObjects
    bl hook_AfterInvalidatingRoomObjects

PATCH DrawHeartIcon
    bl hook_DrawHeartIcon

PATCH OcarinaNoteSound_Player
    b hook_OcarinaNoteSound_Player

PATCH OcarinaNoteSound_Npc
    bl hook_OcarinaNoteSound_Npc

PATCH Item00GiveAutomaticItemDrop
    bl hook_Item00GiveAutomaticItemDrop

PATCH Item00GiveCollectedItemDrop
    bl hook_Item00GiveCollectedItemDrop

PATCH GanonFinalBlow
    bl hook_GanonFinalBlow

PATCH PlayerBonk
    bl hook_PlayerBonk
