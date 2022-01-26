OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(loader_patch)
SECTIONS
{
	. = 0x100000;
	.patch_loader 0x100000 : {
		*(.patch_loader)
	}

	.patch_GrogSetTradedCojiroFlag 0x104C50 : {
		*(.patch_GrogSetTradedCojiroFlag)
	}

	.patch_MidoCheckDekuTreeClearTwo 0x105CD4 : {
		*(.patch_MidoCheckDekuTreeClearTwo)
	}

	.patch_ShortenRainbowBridgeCS 0x10B904 : {
		*(.patch_ShortenRainbowBridgeCS)
	}

	.patch_LabScientistDontStartTimerAndSetFlag 0x112440 : {
		*(.patch_LabScientistDontStartTimerAndSetFlag)
	}

	.patch_BombchuPurchaseableCheck 0x112ED0 : {
		*(.patch_BombchuPurchaseableCheck)
	}

	.patch_PoeCollectorGetFirstTextbox 0x113844 : {
		*(.patch_PoeCollectorGetFirstTextbox)
	}

	.patch_ItemEtceteraModelDraw 0x117080 : {
		*(.patch_ItemEtceteraModelDraw)
	}

	.patch_SariasSongItemGive 0x12C84C : {
		*(.patch_SariasSongItemGive)
	}

	.patch_SariasSongLocation 0x12C8F8 : {
		*(.patch_SariasSongLocation)
	}

	.patch_SkulltulaRewardOne 0x12CC68 : {
		*(.patch_SkulltulaRewardOne)
	}

	.patch_SkulltulaRewardTwo 0x12CD38 : {
		*(.patch_SkulltulaRewardTwo)
	}

	.patch_MedigoronCheckFlagOne 0x13024C : {
		*(.patch_MedigoronCheckFlagOne)
	}

	.patch_MedigoronGetCustomText 0x130258 : {
		*(.patch_MedigoronGetCustomText)
	}

	.patch_MedigoronCheckFlagTwo 0x1302C4 : {
		*(.patch_MedigoronCheckFlagTwo)
	}

	.patch_BeanDaddyModifyBeansBought 0x130CEC : {
		*(.patch_BeanDaddyModifyBeansBought)
	}

	.patch_BiggoronDontSetBGSFlag 0x133F7C : {
		*(.patch_BiggoronDontSetBGSFlag)
	}

	.patch_KingZoraDontStartTimer 0x134D7C : {
		*(.patch_KingZoraDontStartTimer)
	}

	.patch_SongOfStormsLocation 0x1427E0 : {
		*(.patch_SongOfStormsLocation)
	}

	.patch_JabuSwitchRutoCheck 0x143AC8 : {
	  *(.patch_JabuSwitchRutoCheck)
	}

	.patch_OwlMagicCheck 0x144B44 : {
		*(.patch_OwlMagicCheck)
	}

	.patch_MedigoronItemOverrideOne 0x14D95C : {
		*(.patch_MedigoronItemOverrideOne)
	}

	.patch_BeanDaddyPurchase 0x14EDA8 : {
		*(.patch_BeanDaddyPurchase)
	}

	.patch_BeanDaddyModifyPrice 0x14EE98 : {
		*(.patch_BeanDaddyModifyPrice)
	}

	.patch_SkipTwinrovaQuarrelCutsceneOne 0x15273C : {
		*(.patch_SkipTwinrovaQuarrelCutsceneOne)
	}

	.patch_FairyPickupHealAmount 0x15CA4C : {
		*(.patch_FairyPickupHealAmount)
	}

	.patch_ScrubStickUpgradeOne 0x161898 : {
		*(.patch_ScrubStickUpgradeOne)
	}

	.patch_ScrubNutUpgradeOne 0x1618EC : {
		*(.patch_ScrubNutUpgradeOne)
	}

	.patch_EnKoInitCheckForest_165834 0x165834 : {
		*(.patch_EnKoInitCheckForest_165834)
	}

	.patch_EnKoInitCheckForest_165878 0x165878 : {
		*(.patch_EnKoInitCheckForest_165878)
	}

	.patch_EnKoInitCheckForest_1658C0 0x1658C0 : {
		*(.patch_EnKoInitCheckForest_1658C0)
	}

	.patch_EnKoInitCheckForest_1658F0 0x1658F0 : {
		*(.patch_EnKoInitCheckForest_1658F0)
	}

	.patch_KingZoraCheckMovedFlag 0x165A60 : {
		*(.patch_KingZoraCheckMovedFlag)
	}

	.patch_MidoCheckSpawn 0x166154 : {
		*(.patch_MidoCheckSpawn)
	}

	.patch_MidoCheckDekuTreeClearOne 0x16623C : {
		*(.patch_MidoCheckDekuTreeClearOne)
	}

	.patch_SariasSongCheckFlag 0x1686A0 : {
		*(.patch_SariasSongCheckFlag)
	}

	.patch_GrogCheckForShouldDespawn 0x16485C : {
		*(.patch_GrogCheckForShouldDespawn)
	}

	.patch_CheckFadoCanSpawnInLostWoods 0x1657EC : {
		*(.patch_CheckFadoCanSpawnInLostWoods)
	}

	.patch_MedigoronSetRewardFlag 0x16C918 : {
		*(.patch_MedigoronSetRewardFlag)
	}

	.patch_MedigoronItemOverrideTwo 0x16C9BC : {
		*(.patch_MedigoronItemOverrideTwo)
	}

	.patch_KingZoraIgnoreSapphire 0x1736B8 : {
		*(.patch_KingZoraIgnoreSapphire)
	}

	.patch_MidoForestDialog 0x173944 : {
		*(.patch_MidoForestDialog)
	}

	.patch_SkipTimeTravelCutsceneOne 0x174DEC : {
		*(.patch_SkipTimeTravelCutsceneOne)
	}

	.patch_SkipTwinrovaQuarrelCutsceneTwo 0x176110 : {
		*(.patch_SkipTwinrovaQuarrelCutsceneTwo)
	}

	.patch_CarpenterBossDontNullExchangeItem 0x178BE4 : {
		*(.patch_CarpenterBossDontNullExchangeItem)
	}

	.patch_CarpenterBossSetTradedSawFlag 0x178D58 : {
		*(.patch_CarpenterBossSetTradedSawFlag)
	}

	.patch_AnjuCheckCuccoAmount 0x179420 : {
		*(.patch_AnjuCheckCuccoAmount)
	}

	.patch_FastOwlCutscenes 0x188584 : {
		*(.patch_FastOwlCutscenes)
	}

	.patch_BombchuShopInfinitePurchases 0x188D4C : {
		*(.patch_BombchuShopInfinitePurchases)
	}

	.patch_DecoratedChest 0x189E88 : {
		*(.patch_DecoratedChest)
	}

	.patch_BusinessScrubTable 0x18A634 : {
		*(.patch_BusinessScrubTable)
	}

	.patch_CheckGerudoToken_18B368 0x18B368 : {
		*(.patch_CheckGerudoToken_18B368)
	}

	.patch_CheckGerudoToken_18B3A0 0x18B3A0 : {
		*(.patch_CheckGerudoToken_18B3A0)
	}

	.patch_CheckGerudoToken_18B3C0 0x18B3C0 : {
		*(.patch_CheckGerudoToken_18B3C0)
	}

	.patch_CheckGerudoToken_18B448 0x18B448 : {
		*(.patch_CheckGerudoToken_18B448)
	}

	.patch_CheckGerudoToken_18B6F4 0x18B6F4 : {
		*(.patch_CheckGerudoToken_18B6F4)
	}

	.patch_CheckGerudoToken_18B710 0x18B710 : {
		*(.patch_CheckGerudoToken_18B710)
	}

	.patch_EponasSongCheckFlag 0x18C56C : {
		*(.patch_EponasSongCheckFlag)
	}

	.patch_PreludeLocation 0x18D9FC : {
		*(.patch_PreludeLocation)
	}

	.patch_PoeCollectorCheckPoints 0x19091C : {
		*(.patch_PoeCollectorCheckPoints)
	}

	.patch_GoronShopPurchaseableCheck 0x19120C : {
		*(.patch_GoronShopPurchaseableCheck)
	}

	.patch_PlayerEditAndRetrieveCMB 0x191970 : {
		*(.patch_PlayerEditAndRetrieveCMB)
	}

	.patch_SetChildCustomTunic 0x191DB0 : {
		*(.patch_SetChildCustomTunic)
	}

	.patch_PlayerGetCustomTunicCMAB 0x191DD4 : {
		*(.patch_PlayerGetCustomTunicCMAB)
	}

	.patch_SkipDaruniaDanceOne 0x19493C : {
		*(.patch_SkipDaruniaDanceOne)
	}

	.patch_SkipDaruniaDanceTwo 0x194944 : {
		*(.patch_SkipDaruniaDanceTwo)
	}

	.patch_ChildRollingGoron 0x194B18 : {
		*(.patch_ChildRollingGoron)
	}

	.patch_BiggoronCheckBGSFlag 0x194DA0 : {
		*(.patch_BiggoronCheckBGSFlag)
	}

	.patch_ChildRollingGoronDontCheckBombBag 0x195414 : {
		*(.patch_ChildRollingGoronDontCheckBombBag)
	}

	.patch_AdultRollingGoronIgnoreMedallion 0x195450 : {
		*(.patch_AdultRollingGoronIgnoreMedallion)
	}

	.patch_AdultRollingGoronOne 0x195480 : {
		*(.patch_AdultRollingGoronOne)
	}

	.patch_AdultRollingGoronTwo 0x1954AC : {
		*(.patch_AdultRollingGoronTwo)
	}

	.patch_BiggoronGetTextId 0x1954F8 : {
		*(.patch_BiggoronGetTextId)
	}

	.patch_EponasSongCheckFlagTwo 0x195CFC : {
		*(.patch_EponasSongCheckFlagTwo)
	}

	.patch_AmyBlockCooldownTimer 0x196ECC : {
		*(.patch_AmyBlockCooldownTimer)
	}

	.patch_AmyBlockSpeed 0x196F3C : {
		*(.patch_AmyBlockSpeed)
	}

	.patch_DampeChest 0x19A420 : {
		*(.patch_DampeChest)
	}

	.patch_JabuJabuItemGive 0x1A1918 : {
		*(.patch_JabuJabuItemGive)
	}

	.patch_JabuJabuCutsceneOverride 0x1A192C : {
		*(.patch_JabuJabuCutsceneOverride)
	}

	.patch_KotakeDontPlayBattleMusic 0x1A8218 : {
		*(.patch_KotakeDontPlayBattleMusic)
	}

	.patch_GossipStoneAddSariaHint 0x1B398C : {
		*(.patch_GossipStoneAddSariaHint)
	}

	.patch_ReadGossipStoneHints 0x1B3A44 : {
		*(.patch_ReadGossipStoneHints)
	}

	.patch_SkipJabuOpeningCutscene 0x1B583C : {
		*(.patch_SkipJabuOpeningCutscene)
	}

	.patch_KingZoraSecondTunic 0x1B6A18 : {
		*(.patch_KingZoraSecondTunic)
	}

	.patch_KingZoraGiveTunic 0x1B6A64 : {
		*(.patch_KingZoraGiveTunic)
	}

	.patch_MidoCheckDekuTreeClearThree 0x1B7414 : {
		*(.patch_MidoCheckDekuTreeClearThree)
	}

	.patch_FishingNewRecord 0x1C3AA4 : {
		*(.patch_FishingNewRecord)
	}

	.patch_FishingSizeIgnoreChild 0x1C3DFC : {
		*(.patch_FishingSizeIgnoreChild)
	}

	.patch_FishingSizeIgnoreAdult 0x1C3E40 : {
		*(.patch_FishingSizeIgnoreAdult)
	}

	.patch_BiggoronAfterGiveItem 0x1C4E4C : {
		*(.patch_BiggoronAfterGiveItem)
	}

	.patch_KingZoraSetTradedPrescriptionFlag 0x1C52A0 : {
		*(.patch_KingZoraSetTradedPrescriptionFlag)
	}

	.patch_DemoEffectStoneDraw 0x1D209C : {
		*(.patch_DemoEffectStoneDraw)
	}

	.patch_ChestIceSmoke 0x1D5E5C : {
		*(.patch_ChestIceSmoke)
	}

	.patch_CheckGerudoToken_1D7AD4 0x1D7AD4 : {
		*(.patch_CheckGerudoToken_1D7AD4)
	}

	.patch_BiggoronSetTextId 0x1D8A10 : {
		*(.patch_BiggoronSetTextId)
	}

	.patch_BombchuShopAlwaysOpen 0x1DC6B0 : {
		*(.patch_BombchuShopAlwaysOpen)
	}

	.patch_ForestTempleItemGive 0x1E3F84 : {
		*(.patch_ForestTempleItemGive)
	}

	.patch_ForestTempleCutsceneOverride 0x1E3F98 : {
		*(.patch_ForestTempleCutsceneOverride)
	}

	.patch_FireTempleItemGive 0x1E4010 : {
		*(.patch_FireTempleItemGive)
	}

	.patch_FireTempleCutsceneOverride 0x1E4024 : {
		*(.patch_FireTempleCutsceneOverride)
	}

	.patch_WaterTempleItemGive 0x1E40D8 : {
		*(.patch_WaterTempleItemGive)
	}

	.patch_WaterTempleCutsceneOverride 0x1E40EC : {
		*(.patch_WaterTempleCutsceneOverride)
	}

	.patch_SpiritTempleCompleteCheck 0x1E415C : {
		*(.patch_SpiritTempleCompleteCheck)
	}

	.patch_SpiritTempleItemGive 0x1E4168 : {
		*(.patch_SpiritTempleItemGive)
	}

	.patch_SpiritTempleCutsceneOverride 0x1E417C : {
		*(.patch_SpiritTempleCutsceneOverride)
	}

	.patch_ShadowTempleCompleteCheck 0x1E41E4 : {
		*(.patch_ShadowTempleCompleteCheck)
	}

	.patch_ShadowTempleItemGive 0x1E41F0 : {
		*(.patch_ShadowTempleItemGive)
	}

	.patch_ShadowTempleCutsceneOverride 0x1E4204 : {
		*(.patch_ShadowTempleCutsceneOverride)
	}

	.patch_DaruniaCheckStrength 0x1E489C : {
		*(.patch_DaruniaCheckStrength)
	}

	.patch_CanPlayBombchuBowlingTwo 0x1EA1D4 : {
		*(.patch_CanPlayBombchuBowlingTwo)
	}

	.patch_ItemGiveBombchuDropOne 0x1F6F70 : {
		*(.patch_ItemGiveBombchuDropOne)
	}

	.patch_BombchuBowlingStaticReward 0x206150 : {
		*(.patch_BombchuBowlingStaticReward)
	}

	.patch_SkipSongReplays_TimeBlocksFix 0x208004 : {
		*(.patch_SkipSongReplays_TimeBlocksFix)
	}

	.patch_SkipSongReplays_WarpBlocksFix 0x208068 : {
		*(.patch_SkipSongReplays_WarpBlocksFix)
	}

	.patch_ShopItemDontSetAnimSpeedOne 0x2101BC : {
		*(.patch_ShopItemDontSetAnimSpeedOne)
	}

	.patch_ShopItemDontSetAnimSpeedTwo 0x2101CC : {
		*(.patch_ShopItemDontSetAnimSpeedTwo)
	}

	.patch_CourtyardCheckForVisitedZeldaOne 0x210C4C : {
		*(.patch_CourtyardCheckForVisitedZeldaOne)
	}

	.patch_CourtyardCheckForVisitedZeldaTwo 0x210C78 : {
		*(.patch_CourtyardCheckForVisitedZeldaTwo)
	}

	.patch_BugsRecatchable 0x212090 : {
		*(.patch_BugsRecatchable)
	}

	.patch_DekuSproutCheckForest 0x2153A4 : {
		*(.patch_DekuSproutCheckForest)
	}

	.patch_DungeonCheckJabuMQBox 0x21590C : {
	  *(.patch_DungeonCheckJabuMQBox)
	}

	.patch_JabuBoxCheckRuto 0x215934 : {
	  *(.patch_JabuBoxCheckRuto)
	}

	.patch_DekuTheaterMaskOfTruth 0x21CA30 : {
		*(.patch_DekuTheaterMaskOfTruth)
	}

	.patch_BombchuBowlingPrizeOrder 0x21CAD4 : {
		*(.patch_BombchuBowlingPrizeOrder)
	}

	.patch_NoHealFromBombchuBowlingPrize 0x21D170 : {
		*(.patch_NoHealFromBombchuBowlingPrize)
	}

	.patch_patch_ItemGiveBombchuDropTwo 0x22BAE4 : {
		*(.patch_ItemGiveBombchuDropTwo)
	}

	.patch_BusinessScrubCheckFlags 0x22EE64 : {
		*(.patch_BusinessScrubCheckFlags)
	}

	.patch_SyatekiManReminder 0x2391D8 : {
		*(.patch_SyatekiManReminder)
	}

	.patch_EnExItemModelDraw 0x249C94 : {
		*(.patch_EnExItemModelDraw)
	}

	.patch_SpiritTempleItemGiveTwo 0x24CF4C : {
		*(.patch_SpiritTempleItemGiveTwo)
	}

	.patch_SkipDaruniaDanceThree 0x257f00 : {
		*(.patch_SkipDaruniaDanceThree)
	}

	.patch_LostWoodsShootingGame 0x259E4C : {
		*(.patch_LostWoodsShootingGame)
	}

	.patch_CanPlayBombchuBowlingOne 0x25A744 : {
		*(.patch_CanPlayBombchuBowlingOne)
	}

	.patch_SilenceNavi 0x26807C : {
		*(.patch_SilenceNavi)
	}

	.patch_CheckGerudoToken_269884 0x269884 : {
		*(.patch_CheckGerudoToken_269884)
	}

	.patch_SpiritTempleItemGiveThree 0x26B33C : {
		*(.patch_SpiritTempleItemGiveThree)
	}

	.patch_MinuetLocation 0x26C388 : {
		*(.patch_MinuetLocation)
	}

	.patch_BoleroLocation 0x26C448 : {
		*(.patch_BoleroLocation)
	}

	.patch_WaterTempleItemGiveTwo 0x26DCD4 : {
		*(.patch_WaterTempleItemGiveTwo)
	}

	.patch_SongOfTimeJingle 0x274B1C : {
		*(.patch_SongOfTimeJingle)
	}

	.patch_DoorOfTimeCheck 0x274B68 : {
		*(.patch_DoorOfTimeCheck)
	}

	.patch_FireTempleItemGiveThree 0x27D060 : {
		*(.patch_FireTempleItemGiveThree)
	}

	.patch_ShadowTempleItemGiveTwo 0x27DED0 : {
		*(.patch_ShadowTempleItemGiveTwo)
	}

	.patch_ImpaInCourtyardCheckForVisitedZelda 0x27DEF8 : {
		*(.patch_ImpaInCourtyardCheckForVisitedZelda)
	}

	.patch_ForestTempleItemGiveTwo 0x27E074 : {
		*(.patch_ForestTempleItemGiveTwo)
	}

	.patch_WaterTempleItemGiveThree 0x283CA8 : {
		*(.patch_WaterTempleItemGiveThree)
	}

	.patch_AnjuGiveCojiro 0x2884F4 : {
		*(.patch_AnjuGiveCojiro)
	}

	.patch_SunsSongLocation 0x2888C8 : {
		*(.patch_SunsSongLocation)
	}

	.patch_KakarikoGateCheck 0x28A678 : {
		*(.patch_KakarikoGateCheck)
	}

	.patch_FireTempleItemGiveFour 0x28E2AC : {
		*(.patch_FireTempleItemGiveFour)
	}

	.patch_ShadowTempleItemGiveThree 0x28F258 : {
		*(.patch_ShadowTempleItemGiveThree)
	}

	.patch_ForestTempleItemGiveThree 0x28FF44 : {
		*(.patch_ForestTempleItemGiveThree)
	}

	.patch_BombchuBowlingAlwaysFirstPrize 0x291924 : {
		*(.patch_BombchuBowlingAlwaysFirstPrize)
	}

	.patch_LostWoodsShootingGameTwo 0x2990E8 : {
		*(.patch_LostWoodsShootingGameTwo)
	}

	.patch_SerenadeCheckChestFlag 0x2B2544 : {
		*(.patch_SerenadeCheckChestFlag)
	}

	.patch_SerenadeLocation 0x2B2574 : {
		*(.patch_SerenadeLocation)
	}

	.patch_OverrideTextID 0x2BC1C4 : {
		*(.patch_OverrideTextID)
	}

	.patch_OverrideItemID 0x2BC1D0 : {
		*(.patch_OverrideItemID)
	}

	.patch_NoSilverGauntletsCutsceneWarp 0x2BC2A0 : {
		*(.patch_NoSilverGauntletsCutsceneWarp)
	}

	.patch_FishingIgnoreTempBOne 0x2C3A10 : {
		*(.patch_FishingIgnoreTempBOne)
	}

	.patch_DoorOfTimeOpenCutscene 0x2C6218 : {
		*(.patch_DoorOfTimeOpenCutscene)
	}

	.patch_NoHealFromHealthUpgrades 0x2CD07C : {
		*(.patch_NoHealFromHealthUpgrades)
	}

	.patch_GetCustomMessageEntryOne 0x2CD3A4 : {
		*(.patch_GetCustomMessageEntryOne)
	}

	.patch_GetCustomMessageTextOne 0x2CD3EC : {
		*(.patch_GetCustomMessageTextOne)
	}

	.patch_InstantTextFirstLine 0x2E049C : {
		*(.patch_InstantTextFirstLine)
	}

	.patch_InstantTextBoxBreak 0x2E0664 : {
		*(.patch_InstantTextBoxBreak)
	}

	.patch_InstantTextRemoveOff 0x2E06C8 : {
		*(.patch_InstantTextRemoveOff)
	}

	.patch_SkippableText 0x2E09BC : {
		*(.patch_SkippableText)
	}

	.patch_SceneInitAfterCopyScenes 0x2EAFDC : {
		*(.patch_SceneInitAfterCopyScenes)
	}

	.patch_CorrectCompassChests 0x2F161C : {
		*(.patch_CorrectCompassChests)
	}

	.patch_CorrectCompassChestsTwo 0x2F1770 : {
		*(.patch_CorrectCompassChestsTwo)
	}

	.patch_SaveGame 0x2FBFA8 : {
		*(.patch_SaveGame)
	}

	.patch_Gfx_Update 0x310254 : {
		*(.patch_Gfx_Update)
	}

	.patch_ISGPutaway 0x32B4AC : {
		*(.patch_ISGPutaway)
	}

	.patch_SetBGMEntrance 0x331048 : {
		*(.patch_SetBGMEntrance)
	}

	.patch_SceneExitOverride 0x3366EC : {
		*(.patch_SceneExitOverride)
	}

	.patch_SceneExitDynamicOverride 0x33676C : {
		*(.patch_SceneExitDynamicOverride)
	}

	.patch_EnteredLocation 0x338DB8 : {
		*(.patch_EnteredLocation)
	}

	.patch_LostWoodsBridgeMusic 0x338DD8 : {
		*(.patch_LostWoodsBridgeMusic)
	}

	.patch_ChestGetIceTrapObjectStatus 0x33AB24 : {
		*(.patch_ChestGetIceTrapObjectStatus)
	}

	.patch_BiggoronDayCheck 0x33DCC0 : {
		*(.patch_BiggoronDayCheck)
	}

	.patch_TurboTextSignalNPC 0x3469F4 : {
		*(.patch_TurboTextSignalNPC)
	}

	.patch_FairyReviveHealAmount 0x34AF48 : {
		*(.patch_FairyReviveHealAmount)
	}

	.patch_FishingIgnoreTempBTwo 0x34CFCC : {
		*(.patch_FishingIgnoreTempBTwo)
	}

	.patch_FWLoadSet 0x34D9E8 : {
		*(.patch_FWLoadSet)
	}

	.patch_FWGetSet 0x3519CC : {
		*(.patch_FWGetSet)
	}

	.patch_OverrideGraphicID_351B94 0x351B94 : {
		*(.patch_OverrideGraphicID_351B94)
	}

	.patch_ApplyDamageMultiplier 0x352DC0 : {
		*(.patch_ApplyDamageMultiplier)
	}

	.patch_OverrideGraphicID_35495C 0x35495C : {
		*(.patch_OverrideGraphicID_35495C)
	}

	.patch_OverrideGraphicID_354BB8 0x354BB8 : {
		*(.patch_OverrideGraphicID_354BB8)
	}

	.patch_FastChests 0x354CD4 : {
		*(.patch_FastChests)
	}

	.patch_LikeLikeNeverEatTunic 0x355C2C : {
		*(.patch_LikeLikeNeverEatTunic)
	}

	.patch_PlaySound 0x35C528 : {
		*(.patch_PlaySound)
	}

	.patch_ConvertBombDropOne 0x35E46C : {
		*(.patch_ConvertBombDropOne)
	}

	.patch_ISGCrouchStab 0x360690 : {
		*(.patch_ISGCrouchStab)
	}

	.patch_ModelSpawnGetObjectStatus 0x36A96C : {
		*(.patch_ModelSpawnGetObjectStatus)
	}

	.patch_SetBGMEvent 0x36EC40 : {
		*(.patch_SetBGMEvent)
	}

	.patch_DemoEffectMedallionDraw 0x37214C : {
		*(.patch_DemoEffectMedallionDraw)
	}

	.patch_IncomingGetItemID 0x3725AC : {
		*(.patch_IncomingGetItemID)
	}

	.patch_ConvertBombDropTwo 0x3747A4 : {
		*(.patch_ConvertBombDropTwo)
	}

	.patch_SetSFX 0x37547C : {
		*(.patch_SetSFX)
	}

	.patch_GKSetDurability 0x376BDC : {
		*(.patch_GKSetDurability)
	}

	.patch_GiantsKnifeWithoutKokiriSword 0x376BEC : {
		*(.patch_GiantsKnifeWithoutKokiriSword)
	}

	.patch_NoLensOfTruthNaviText 0x37798C : {
		*(.patch_NoLensOfTruthNaviText)
	}

	.patch_FrogReward 0x38992C : {
		*(.patch_FrogReward)
	}

	.patch_ChildShootingGallery 0x38AB70 : {
		*(.patch_ChildShootingGallery)
	}

	.patch_AdultShootingGallery 0x38ABA0 : {
		*(.patch_AdultShootingGallery)
	}

	.patch_SariasSongHintsOne 0x390620 : {
		*(.patch_SariasSongHintsOne)
	}

	.patch_SariasSongHintsTwo 0x39073C : {
		*(.patch_SariasSongHintsTwo)
	}

	.patch_OcarinaMinigameEndAfterWin 0x39DF38 : {
		*(.patch_OcarinaMinigameEndAfterWin)
	}

	.patch_LullabyLocation 0x3A0A7C : {
		*(.patch_LullabyLocation)
	}

	.patch_KokiriCheckOpenForest 0x3ACCFC : {
		*(.patch_KokiriCheckOpenForest)
	}

	.patch_TokenNoItemGive2 0x3AD270 : {
		*(.patch_TokenNoItemGive2)
	}

	.patch_GetToken2 0x3AD2F0 : {
		*(.patch_GetToken2)
	}

	.patch_TokenNoItemGive1 0x3ADD68 : {
		*(.patch_TokenNoItemGive1)
	}

	.patch_GetToken1 0x3ADDE4 : {
		*(.patch_GetToken1)
	}

	.patch_TalonGetCastleTextbox 0x3AE6E8 : {
		*(.patch_TalonGetCastleTextbox)
	}

	.patch_GerudoArcheryOne 0x3AFA34 : {
		*(.patch_GerudoArcheryOne)
	}

	.patch_MovableBlockCooldownTimer 0x3BD46C : {
		*(.patch_MovableBlockCooldownTimer)
	}

	.patch_MovableBlockSpeed 0x3BD508 : {
		*(.patch_MovableBlockSpeed)
	}

	.patch_MilkCrateCooldownTimer 0x3BD85C : {
		*(.patch_MilkCrateCooldownTimer)
	}

	.patch_MilkCrateSpeed 0x3BD88C : {
		*(.patch_MilkCrateSpeed)
	}

	.patch_ForestTempleBasementPuzzleDelay 0x3BFA8C : {
		*(.patch_ForestTempleBasementPuzzleDelay)
	}

	.patch_GerudoArcheryTwo 0x3C2D80 : {
		*(.patch_GerudoArcheryTwo)
	}

	.patch_DampeCheckCanDig1 0x3C3354 : {
		*(.patch_DampeCheckCanDig1)
	}

	.patch_DampeRollHigh 0x3C3418 : {
		*(.patch_DampeRollHigh)
	}

	.patch_DampeCheckRewardFlag 0x3C3598 : {
		*(.patch_DampeCheckRewardFlag)
	}

	.patch_DampeCheckCanDig2 0x3C35D0 : {
		*(.patch_DampeCheckCanDig2)
	}

	.patch_SongOfTimeLocation 0x3C375C : {
		*(.patch_SongOfTimeLocation)
	}

	.patch_EponasSongLocation 0x3C6194 : {
		*(.patch_EponasSongLocation)
	}

	.patch_MalonNextAction 0x3C6210 : {
		*(.patch_MalonNextAction)
	}

	.patch_MidoCheckDekuTreeClearFour 0x3D2C18 : {
		*(.patch_MidoCheckDekuTreeClearFour)
	}

	.patch_FireBlockCooldownTimer 0x3E0A2C : {
		*(.patch_FireBlockCooldownTimer)
	}

	.patch_FireBlockSpeed 0x3E0BA8 : {
		*(.patch_FireBlockSpeed)
	}

	.patch_BombPurchaseableCheck 0x3CE800 : {
		*(.patch_BombPurchaseableCheck)
	}

	.patch_ScrubStickUpgradeTwo 0x3CE990 : {
		*(.patch_ScrubStickUpgradeTwo)
	}

	.patch_ScrubNutUpgradeTwo 0x3CE9DC : {
		*(.patch_ScrubNutUpgradeTwo)
	}

	.patch_FreeScarecrow 0x3E55A8 : {
		*(.patch_FreeScarecrow)
	}

	.patch_MasterSwordAlwaysDrop 0x3E5E98 : {
		*(.patch_MasterSwordAlwaysDrop)
	}

	.patch_SkipMasterSwordFanfare 0x3E5F60 : {
		*(.patch_SkipMasterSwordFanfare)
	}

	.patch_FairyReward 0x3E7598 : {
		*(.patch_FairyReward)
	}

	.patch_RainbowBridge 0x3E7CAC : {
		*(.patch_RainbowBridge)
	}

	.patch_DekuTheaterSkullMask 0x3EAF38 : {
		*(.patch_DekuTheaterSkullMask)
	}

	.patch_CowItemOverride 0x3EE378 : {
		*(.patch_CowItemOverride)
	}

	.patch_CowBottleCheck 0x3F065C : {
		*(.patch_CowBottleCheck)
	}

	.patch_CarpetSalesmanCheckFlagOne 0x3F0A18 : {
		*(.patch_CarpetSalesmanCheckFlagOne)
	}

	.patch_CarpetSalesmanCheckFlagTwo 0x3F0A64 : {
		*(.patch_CarpetSalesmanCheckFlagTwo)
	}

	.patch_LabScientistIgnoreEyedropsInInventory 0x3F0B44 : {
		*(.patch_LabScientistIgnoreEyedropsInInventory)
	}

	.patch_HandleDoorDestroyCustomModels 0x3F1B88 : {
		*(.patch_HandleDoorDestroyCustomModels)
	}

	.patch_OverrideGrottoActorEntrance 0x3F2254 : {
		*(.patch_OverrideGrottoActorEntrance)
	}

	.patch_FireArrowRequirement 0x3F23AC : {
		*(.patch_FireArrowRequirement)
	}

	.patch_FireArrowCheckChestFlagOne 0x3F23FC : {
		*(.patch_FireArrowCheckChestFlagOne)
	}

	.patch_FireArrowCheckChestFlagTwo 0x3F2448 : {
		*(.patch_FireArrowCheckChestFlagTwo)
	}

	.patch_SlidingDoorDestroyCustomModels 0x3F4A70 : {
		*(.patch_SlidingDoorDestroyCustomModels)
	}

	.patch_DodongosCavernItemGive 0x3F57B0 : {
		*(.patch_DodongosCavernItemGive)
	}

	.patch_DodongosCavernCutsceneOverride 0x3F57C4 : {
		*(.patch_DodongosCavernCutsceneOverride)
	}

	.patch_DekuTreeItemGive 0x3F582C : {
		*(.patch_DekuTreeItemGive)
	}

	.patch_DekuTreeCutsceneOverride 0x3F5840 : {
		*(.patch_DekuTreeCutsceneOverride)
	}

	.patch_CarpetSalesmanSetFlag 0x3F9550 : {
		*(.patch_CarpetSalesmanSetFlag)
	}

	.patch_PreSwapBuffers 0x3FD384 : {
		*(.patch_PreSwapBuffers)
	}

	.patch_AwakeCallback 0x3FD43C : {
		*(.patch_AwakeCallback)
	}

	.patch_SleepQueryCallback 0x3FD6C4 : {
		*(.patch_SleepQueryCallback)
	}

	.patch_SaveMenuIgnoreOpen 0x42EC00 : {
		*(.patch_SaveMenuIgnoreOpen)
	}

	.patch_ItemsMenuDraw 0x434C08 : {
		*(.patch_ItemsMenuDraw)
	}

	.patch_LoadGame 0x447380 : {
		*(.patch_LoadGame)
	}

	.patch_DontSetMotionSetting 0x447410 : {
		*(.patch_DontSetMotionSetting)
	}

	.patch_OverrideFogDuringGameplayInit 0x4485B4 : {
		*(.patch_OverrideFogDuringGameplayInit)
	}

	.patch_CheckForPocketCuccoHatchGameplayInit 0x448A80 : {
		*(.patch_CheckForPocketCuccoHatchGameplayInit)
	}

	.patch_InitSceneClearExtendedObjects 0x449218 : {
		*(.patch_InitSceneClearExtendedObjects)
	}

	.patch_SaveFile_Init 0x449A04 : {
		*(.patch_SaveFile_Init)
	}

	.patch_GetCustomMessageEntryTwo 0x44D564 : {
		*(.patch_GetCustomMessageEntryTwo)
	}

	.patch_GetCustomMessageTextTwo 0x44D5A4 : {
		*(.patch_GetCustomMessageTextTwo)
	}

	.patch_GameplayDestroy 0x44E294 : {
		*(.patch_GameplayDestroy)
	}

	.patch_ExtendedObjectClear 0x44E754 : {
		*(.patch_ExtendedObjectClear)
	}

	.patch_PlayEntranceCutscene 0x44F068 : {
		*(.patch_PlayEntranceCutscene)
	}

	.patch_RequiemLocation 0x44F104 : {
		*(.patch_RequiemLocation)
	}

	.patch_NocturneLocation 0x44F12C : {
		*(.patch_NocturneLocation)
	}

	.patch_SariasGift 0x44F188 : {
		*(.patch_SariasGift)
	}

	.patch_LACSConditionOne 0x44F1D4 : {
		*(.patch_LACSConditionOne)
	}

	.patch_LACSConditionTwo 0x44F20C : {
		*(.patch_LACSConditionTwo)
	}

	.patch_SetSavewarpEntrance 0x44FBE4 : {
		*(.patch_SetSavewarpEntrance)
	}

	.patch_LullabyCheckFlag 0x44FD54 : {
		*(.patch_LullabyCheckFlag)
	}

	.patch_OpenSaveDontSpoilTradeItems 0x44FDF8 : {
		*(.patch_OpenSaveDontSpoilTradeItems)
	}

	.patch_before_GlobalContext_Update 0x452390 : {
		*(.patch_before_GlobalContext_Update)
	}

	.patch_after_GlobalContext_Update 0x452434 : {
		*(.patch_after_GlobalContext_Update)
	}

	.patch_FixItemsMenuSlotDuplication 0x456B90 : {
		*(.patch_FixItemsMenuSlotDuplication)
	}

	.patch_GameOverDontSpoilTradeItems 0x458BE0 : {
		*(.patch_GameOverDontSpoilTradeItems)
	}

	.patch_SetGameOverEntrance 0x458E3C : {
		*(.patch_SetGameOverEntrance)
	}

	.patch_SetGameOverRespawnFlag 0x458EF0 : {
		*(.patch_SetGameOverRespawnFlag)
	}

	.patch_InterfaceDrawDontSpoilTradeItems 0x45A17C : {
		*(.patch_InterfaceDrawDontSpoilTradeItems)
	}

	.patch_SunsSongEndCloseTextbox 0x45B514 : {
		*(.patch_SunsSongEndCloseTextbox)
	}

	.patch_SetSunsSongRespawnFlag 0x45B660 : {
		*(.patch_SetSunsSongRespawnFlag)
	}

	.patch_StoreChildBButtonEquip 0x45F20C : {
		*(.patch_StoreChildBButtonEquip)
	}

	.patch_AlwaysRestoreChildEquips 0x45F3B0 : {
		*(.patch_AlwaysRestoreChildEquips)
	}

	.patch_ChildDontEquipSwordSlotByDefault 0x45F49C : {
		*(.patch_ChildDontEquipSwordSlotByDefault)
	}

	.patch_TitleCardUpdate 0x4618B8 : {
		*(.patch_TitleCardUpdate)
	}

	.patch_ItemsMenuNumSprites 0x46B758 : {
		*(.patch_ItemsMenuNumSprites)
	}

	.patch_CheckForPocketCuccoHatchKankyo 0x470D1C : {
		*(.patch_CheckForPocketCuccoHatchKankyo)
	}

	.patch_EnableFW 0x476D1C : {
		*(.patch_EnableFW)
	}

	.patch_FWKeepWarpPoint 0x47C3C0 : {
		*(.patch_FWKeepWarpPoint)
	}

	.patch_TurboTextAdvance 0x480928 : {
		*(.patch_TurboTextAdvance)
	}

	.patch_TurboTextClose 0x488214 : {
		*(.patch_TurboTextClose)
	}

	.patch_SetBGMDayNight 0x483C88 : {
		*(.patch_SetBGMDayNight)
	}

	.patch_SwapFaroresWind 0x49186C : {
		*(.patch_SwapFaroresWind)
	}

	.patch_SkipTimeTravelCutsceneTwo 0x4918C8 : {
		*(.patch_SkipTimeTravelCutsceneTwo)
	}

	.patch_SwapAgeIgnoreSceneSetup 0x4918B0 : {
		*(.patch_SwapAgeIgnoreSceneSetup)
	}

	.patch_FireTempleItemGiveTwo 0x491B60 : {
		*(.patch_FireTempleItemGiveTwo)
	}

	.patch_FairyUseHealAmount 0x4968B4 : {
		*(.patch_FairyUseHealAmount)
	}

	.patch_ReturnFWSetupGrottoInfo 0x496B88 : {
		*(.patch_ReturnFWSetupGrottoInfo)
	}

	.patch_SetSpecialVoidOutRespawnFlag 0x496C70 : {
		*(.patch_SetSpecialVoidOutRespawnFlag)
	}

	.patch_GanonBattleDeathWarp 0x496C98 : {
		*(.patch_GanonBattleDeathWarp)
	}

	.patch_OverrideGraphicID_4BC604 0x4BC604 : {
		*(.patch_OverrideGraphicID_4BC604)
	}

	.patch_OverrideGraphicID_4BD5D0 0x4BD5D0 : {
		*(.patch_OverrideGraphicID_4BD5D0)
	}

	.patch_EditDrawGetItemBeforeModelSpawn 0x4C0FD0 : {
		*(.patch_EditDrawGetItemBeforeModelSpawn)
	}

	.patch_EditDrawGetItemAfterModelSpawn 0x4C61A4 : {
		*(.patch_EditDrawGetItemAfterModelSpawn)
	}

	. = 0x4C99A8;
	. = ALIGN(4);
	.loader : {
		*(.loader*)
	}

	.patch_DampeSetCollectibleFlag 0x4D9D50 : {
		*(.patch_DampeSetCollectibleFlag)
	}

	.patch_BombchuCheapestPriceOne 0x525348 : {
		*(.patch_BombchuCheapestPriceOne)
	}

	.patch_BombchuCheapestPriceTwo 0x5253D8 : {
		*(.patch_BombchuCheapestPriceTwo)
	}

	.patch_BombchuCheapestPriceThree 0x525408 : {
		*(.patch_BombchuCheapestPriceThree)
	}

	.patch_BombchuCheapestPriceFour 0x525498 : {
		*(.patch_BombchuCheapestPriceFour)
	}

	.patch_OcarinaMinigameRewardsOrder 0x52ED10 : {
		*(.patch_OcarinaMinigameRewardsOrder)
	}

	.patch_TycoonWalletSize 0x53CC08 : {
		*(.patch_TycoonWalletSize)
	}
	. = 0x005C7000;
    .text : {
        __text_start = . ;
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.data)
        *(.bss)
        *(COMMON)
		rCustomMessages = . ;
        __text_end  = . ;
    }
}
