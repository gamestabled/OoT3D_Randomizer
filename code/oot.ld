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

	.patch_ArmosCooldownTimer 0x10B41C : {
		*(.patch_ArmosCooldownTimer)
	}

	.patch_ArmosPushSpeed 0x10B5C4 : {
		*(.patch_ArmosPushSpeed)
	}

	.patch_ShortenRainbowBridgeCS 0x10B904 : {
		*(.patch_ShortenRainbowBridgeCS)
	}

	.patch_GrannyTextID 0x10DCD0 : {
		*(.patch_GrannyTextID)
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

	.patch_FlyingPotCollision 0x11DB34 : {
		*(.patch_FlyingPotCollision)
	}

	.patch_DodongoAfterSwallowBomb 0x11E4B8 : {
		*(.patch_DodongoAfterSwallowBomb)
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

	.patch_PlayerCheckVoidOut 0x132B64 : {
		*(.patch_PlayerCheckVoidOut)
	}

	.patch_BiggoronDontSetBGSFlag 0x133F7C : {
		*(.patch_BiggoronDontSetBGSFlag)
	}

	.patch_KingZoraDontStartTimer 0x134D7C : {
		*(.patch_KingZoraDontStartTimer)
	}

	.patch_StalchildDespawn_13DB68 0x13DB68 : {
		*(.patch_StalchildDespawn_13DB68)
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

	.patch_RandomGsLoc_SkipSoilJingle 0x15DBD8 : {
		*(.patch_RandomGsLoc_SkipSoilJingle)
	}

	.patch_GrannyBottleCheck 0x161044 : {
		*(.patch_GrannyBottleCheck)
	}

	.patch_GrannyItemOverrideOne 0x161094 : {
		*(.patch_GrannyItemOverrideOne)
	}

	.patch_ScrubStickUpgradeOne 0x161898 : {
		*(.patch_ScrubStickUpgradeOne)
	}

	.patch_ScrubNutUpgradeOne 0x1618EC : {
		*(.patch_ScrubNutUpgradeOne)
	}

	.patch_GrogCheckForShouldDespawn 0x16485C : {
		*(.patch_GrogCheckForShouldDespawn)
	}

	.patch_GetObjectEntry_164BC8 0x164BC8 : {
		*(.patch_GetObjectEntry_164BC8)
	}

	.patch_CheckFadoCanSpawnInLostWoods 0x1657EC : {
		*(.patch_CheckFadoCanSpawnInLostWoods)
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

	.patch_GetObjectEntry_EnRdInit_One 0x167DA4 : {
		*(.patch_GetObjectEntry_EnRdInit_One)
	}

	.patch_GetObjectEntry_EnRdInit_Two 0x167E38 : {
		*(.patch_GetObjectEntry_EnRdInit_Two)
	}

	.patch_SariasSongCheckFlag 0x1686A0 : {
		*(.patch_SariasSongCheckFlag)
	}

	.patch_GetObjectEntry_EnSiInit 0x168B20 : {
		*(.patch_GetObjectEntry_EnSiInit)
	}

	.patch_RandomGsLoc_BlockSpawn_Tree 0x16C43C : {
		*(.patch_RandomGsLoc_BlockSpawn_Tree)
	}

	.patch_MedigoronSetRewardFlag 0x16C918 : {
		*(.patch_MedigoronSetRewardFlag)
	}

	.patch_MedigoronItemOverrideTwo 0x16C9BC : {
		*(.patch_MedigoronItemOverrideTwo)
	}

	.patch_MaskSalesmanBorrowMask 0x16D148 : {
		*(.patch_MaskSalesmanBorrowMask)
	}

	.patch_KingZoraIgnoreSapphire 0x1736B8 : {
		*(.patch_KingZoraIgnoreSapphire)
	}

	.patch_MidoForestDialog 0x173944 : {
		*(.patch_MidoForestDialog)
	}

	.patch_LeeverSandCheck_Big 0x1743D0 : {
		*(.patch_LeeverSandCheck_Big)
	}

	.patch_SkipTimeTravelCutsceneOne 0x174DEC : {
		*(.patch_SkipTimeTravelCutsceneOne)
	}

	.patch_SkipTwinrovaQuarrelCutsceneTwo 0x176110 : {
		*(.patch_SkipTwinrovaQuarrelCutsceneTwo)
	}

	.patch_LostWoodsTargetCutscene 0x178058 : {
		*(.patch_LostWoodsTargetCutscene)
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

	.patch_BombchuShopInfinitePurchases 0x188D3C : {
		*(.patch_BombchuShopInfinitePurchases)
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

	.patch_GetObjectEntry_EnXcInit 0x18D7AC : {
		*(.patch_GetObjectEntry_EnXcInit)
	}

	.patch_PreludeLocation 0x18D9FC : {
		*(.patch_PreludeLocation)
	}

	.patch_SkullKidPoacherSawCheck 0x18ED80 : {
		*(.patch_SkullKidPoacherSawCheck)
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

	.patch_AdultItemsCMABsAsChild 0x191BB0 : {
		*(.patch_AdultItemsCMABsAsChild)
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

	.patch_GohmaLarvaDeathSignalParent 0x1968DC : {
		*(.patch_GohmaLarvaDeathSignalParent)
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

	.patch_PierreSoftlockFixOne 0x19C734 : {
		*(.patch_PierreSoftlockFixOne)
	}

	.patch_EnBlkobj_FindDarkLink 0x1A0BC8 : {
		*(.patch_EnBlkobj_FindDarkLink)
	}

	.patch_EnBlkobj_SpawnDarkLink 0x1A137C : {
		*(.patch_EnBlkobj_SpawnDarkLink)
	}

	.patch_RutoBlueWarpOverride 0x1A1900 : {
		*(.patch_RutoBlueWarpOverride)
	}

	.patch_KotakeDontPlayBattleMusic 0x1A8218 : {
		*(.patch_KotakeDontPlayBattleMusic)
	}

	.patch_GetObjectEntry_EnGomaInit_One 0x1B3130 : {
		*(.patch_GetObjectEntry_EnGomaInit_One)
	}

	.patch_GetObjectEntry_EnGomaInit_Two 0x1B3208 : {
		*(.patch_GetObjectEntry_EnGomaInit_Two)
	}

	.patch_GossipStoneAddSariaHint 0x1B3968 : {
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

	.patch_GetObjectEntry_EnTiteInit 0x1BBC9C : {
		*(.patch_GetObjectEntry_EnTiteInit)
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

	.patch_BabyDodongoAfterSwallowBomb 0x1C42DC : {
		*(.patch_BabyDodongoAfterSwallowBomb)
	}

	.patch_BiggoronAfterGiveItem 0x1C4E4C : {
		*(.patch_BiggoronAfterGiveItem)
	}

	.patch_KingZoraSetTradedPrescriptionFlag 0x1C52A0 : {
		*(.patch_KingZoraSetTradedPrescriptionFlag)
	}

	.patch_GerudoBattleMusic 0x1C6FD8 : {
		*(.patch_GerudoBattleMusic)
	}

	.patch_EnEncount1_SpawnLeever 0x1CC94C : {
		*(.patch_EnEncount1_SpawnLeever)
	}

	.patch_EnEncount1_SetLeeverAimType 0x1CC984 : {
		*(.patch_EnEncount1_SetLeeverAimType)
	}

	.patch_TruthSpinnerSpeed 0x1CD814 : {
		*(.patch_TruthSpinnerSpeed)
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

	.patch_LeeverDontChangeCategory 0x1DE010 : {
		*(.patch_LeeverDontChangeCategory)
	}

	.patch_LeeverSandCheck_Init 0x1DE078 : {
		*(.patch_LeeverSandCheck_Init)
	}

	.patch_AdultBlueWarpOverride 0x1E3F50 : {
		*(.patch_AdultBlueWarpOverride)
	}

	.patch_DaruniaCheckStrength 0x1E489C : {
		*(.patch_DaruniaCheckStrength)
	}

	.patch_CanPlayBombchuBowlingTwo 0x1EA1D4 : {
		*(.patch_CanPlayBombchuBowlingTwo)
	}

	.patch_BoomerangTrailEffect 0x1F4220 : {
		*(.patch_BoomerangTrailEffect)
	} /*EnBoom_Draw*/

	.patch_GohmaEggDeathSignalParent 0x1F5F48 : {
		*(.patch_GohmaEggDeathSignalParent)
	}

	.patch_Item00GiveAutomaticItemDrop 0x1F6E4C : {
		*(.patch_Item00GiveAutomaticItemDrop)
	}

	.patch_ItemGiveBombchuDropOne 0x1F6F70 : {
		*(.patch_ItemGiveBombchuDropOne)
	}

	.patch_GetObjectEntry_1F85B0 0x1F85B0 : {
		*(.patch_GetObjectEntry_1F85B0)
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

	.patch_ChestMinigame_DontOpenChestsOnInit 0x20EC8C : {
		*(.patch_ChestMinigame_DontOpenChestsOnInit)
	}

	.patch_ChestMinigame_KeyChestVisibility 0x20EDB8 : {
		*(.patch_ChestMinigame_KeyChestVisibility)
	}

	.patch_ChestMinigame_RewardChestVisibility 0x20EFE0 : {
		*(.patch_ChestMinigame_RewardChestVisibility)
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

	.patch_WaterSpoutMasterQuestCheck 0x212BDC : {
		*(.patch_WaterSpoutMasterQuestCheck)
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

	.patch_GetObjectEntry_ObjSwitchInit 0x215A60 : {
		*(.patch_GetObjectEntry_ObjSwitchInit)
	}

	.patch_EnEncount1_SpawnStalchildWolfos 0x21C020 : {
		*(.patch_EnEncount1_SpawnStalchildWolfos)
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

	.patch_HookshotDrawChain 0x2202A0 : {
		*(.patch_HookshotDrawChain)
	}

	.patch_GetObjectEntry_EnDekunutsInit 0x2293AC : {
		*(.patch_GetObjectEntry_EnDekunutsInit)
	}

	.patch_GetObjectEntry_EnHintnutsInit 0x22AB70 : {
		*(.patch_GetObjectEntry_EnHintnutsInit)
	}

	.patch_Item00GiveCollectedItemDrop 0x22B974 : {
		*(.patch_Item00GiveCollectedItemDrop)
	}

	.patch_patch_ItemGiveBombchuDropTwo 0x22BAE4 : {
		*(.patch_ItemGiveBombchuDropTwo)
	}

	.patch_GetObjectEntry_EnNutsballInit 0x22DEC4 : {
		*(.patch_GetObjectEntry_EnNutsballInit)
	}

	.patch_BusinessScrubCheckFlags 0x22EE64 : {
		*(.patch_BusinessScrubCheckFlags)
	}

	.patch_DarkLinkPlayerRecoil 0x22F838 : {
		*(.patch_DarkLinkPlayerRecoil)
	}

	.patch_GanonCSEquipMS 0x2359A4 : {
		*(.patch_GanonCSEquipMS)
	}

	.patch_AnubisFlameCircleCheck 0x246F64 : {
		*(.patch_AnubisFlameCircleCheck)
	}

	.patch_RainbowChuTrailOne 0x247FC0 : {
		*(.patch_RainbowChuTrailOne)
	} /*Bombchus use 2 EffectBlure instances*/

	.patch_RainbowChuTrailTwo 0x2480A4 : {
		*(.patch_RainbowChuTrailTwo)
	} /*Bombchus use 2 EffectBlure instances*/

	.patch_EnExItemModelDraw 0x249C94 : {
		*(.patch_EnExItemModelDraw)
	}

	.patch_RedeadCanFreezePlayer 0x24DC2C : {
		*(.patch_RedeadCanFreezePlayer)
	}

	.patch_SwordTrailDurationGrezzoFix 0x2507D0 : {
		*(.patch_SwordTrailDurationGrezzoFix)
	} /*duration is set to 6 due to framerate increase. NOP to allow custom duration*/

	.patch_MultiplyPlayerSpeed 0x251D34 : {
		*(.patch_MultiplyPlayerSpeed)
	}

	.patch_GameOverStart 0x252424 : {
		*(.patch_GameOverStart)
	}

	.patch_SkipDaruniaDanceThree 0x257F00 : {
		*(.patch_SkipDaruniaDanceThree)
	}

	.patch_LostWoodsTargetTimer 0x2592B8 : {
		*(.patch_LostWoodsTargetTimer)
	}

	.patch_LostWoodsShootingGame 0x259E4C : {
		*(.patch_LostWoodsShootingGame)
	}

	.patch_CanPlayBombchuBowlingOne 0x25A744 : {
		*(.patch_CanPlayBombchuBowlingOne)
	}

	.patch_GanonDrawMasterSword 0x26207C : {
		*(.patch_GanonDrawMasterSword)
	}

	.patch_NaviNotifications 0x267E04 : {
		*(.patch_NaviNotifications)
	}

	.patch_CheckGerudoToken_269884 0x269884 : {
		*(.patch_CheckGerudoToken_269884)
	}

	.patch_MinuetLocation 0x26C388 : {
		*(.patch_MinuetLocation)
	}

	.patch_BoleroLocation 0x26C448 : {
		*(.patch_BoleroLocation)
	}

	.patch_FlyingTileCollision 0x26E730 : {
		*(.patch_FlyingTileCollision)
	}

	.patch_DeadHandHandCanGrabPlayer 0x26EB58 : {
		*(.patch_DeadHandHandCanGrabPlayer)
	}

	.patch_RedBoulderExplode 0x26FE7C : {
		*(.patch_RedBoulderExplode)
	}

	.patch_MaskSalesmanGiveMaskOfTruth 0x271D48 : {
		*(.patch_MaskSalesmanGiveMaskOfTruth)
	}

	.patch_SongOfTimeJingle 0x274B1C : {
		*(.patch_SongOfTimeJingle)
	}

	.patch_DoorOfTimeCheck 0x274B68 : {
		*(.patch_DoorOfTimeCheck)
	}

	.patch_ImpaInCourtyardCheckForVisitedZelda 0x27DEF8 : {
		*(.patch_ImpaInCourtyardCheckForVisitedZelda)
	}

	.patch_GanonGiveMSMidFight 0x288030 : {
		*(.patch_GanonGiveMSMidFight)
	}

	.patch_AnjuGiveCojiro 0x2884F4 : {
		*(.patch_AnjuGiveCojiro)
	}

	.patch_SunsSongLocation 0x2888C8 : {
		*(.patch_SunsSongLocation)
	}

	.patch_PierreSoftlockFixTwo 0x288914 : {
		*(.patch_PierreSoftlockFixTwo)
	}

	.patch_PierreSoftlockFixThree 0x2889D4 : {
		*(.patch_PierreSoftlockFixThree)
	}

	.patch_KakarikoGateCheck 0x28A678 : {
		*(.patch_KakarikoGateCheck)
	}

	.patch_BombchuBowlingAlwaysFirstPrize 0x291924 : {
		*(.patch_BombchuBowlingAlwaysFirstPrize)
	}

	.patch_LostWoodsShootingGameTwo 0x2990E8 : {
		*(.patch_LostWoodsShootingGameTwo)
	}

	.patch_Sheik_GetTextID 0x2A4B44 : {
		*(.patch_Sheik_GetTextID)
	}

	.patch_SerenadeCheckChestFlag 0x2B2544 : {
		*(.patch_SerenadeCheckChestFlag)
	}

	.patch_SerenadeLocation 0x2B2574 : {
		*(.patch_SerenadeLocation)
	}

	.patch_RainbowSwordTrail 0x2B9AD0 : {
		*(.patch_RainbowSwordTrail)
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

	.patch_RunAnimationSpeed 0x2BE70C : {
		*(.patch_RunAnimationSpeed)
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

	.patch_ActorDraw 0x2D6310 : {
		*(.patch_ActorDraw)
	}

	.patch_CamUpdate 0x2D84C8 : {
		*(.patch_CamUpdate)
	}

	.patch_CamRoll 0x2D88E4 : {
		*(.patch_CamRoll)
	}

	.patch_CheckForTextControlCode 0x2E0490 : {
		*(.patch_CheckForTextControlCode)
	}

	.patch_HandleTextControlCode 0x2E057C : {
		*(.patch_HandleTextControlCode)
	}

	.patch_SceneInitAfterCopyScenes 0x2EAFDC : {
		*(.patch_SceneInitAfterCopyScenes)
	}

	.patch_ChildCanOpenBowSubMenu 0x2EB2D8 : {
		*(.patch_ChildCanOpenBowSubMenu)
	}

	.patch_FileSelect_CopyFile 0x2EDA04 : {
		*(.patch_FileSelect_CopyFile)
	}

	.patch_CorrectCompassChests 0x2F161C : {
		*(.patch_CorrectCompassChests)
	}

	.patch_CorrectCompassChestsTwo 0x2F1770 : {
		*(.patch_CorrectCompassChestsTwo)
	}

	.patch_OverrideDrawItemOne 0x2F7498 : {
		*(.patch_OverrideDrawItemOne)
	}

	.patch_OcarinaNoteButtonsDraw 0x2F9430 : {
		*(.patch_OcarinaNoteButtonsDraw)
	}

	.patch_SaveGame 0x2FBFA8 : {
		*(.patch_SaveGame)
	}

	.patch_SaveFileSwordless 0x2FDCE4 : {
		*(.patch_SaveFileSwordless)
	}

	.patch_Gfx_Update 0x310254 : {
		*(.patch_Gfx_Update)
	}

	.patch_OverrideDrawItemTwo 0x3148A8 : {
		*(.patch_OverrideDrawItemTwo)
	}

	.patch_OoBBombchuOne 0x315120 : {
		*(.patch_OoBBombchuOne)
	}

	.patch_OoBBombchuTwo 0x31513C : {
		*(.patch_OoBBombchuTwo)
	}

	.patch_OoBBombchuThree 0x315150 : {
		*(.patch_OoBBombchuThree)
	}

	.patch_CollisionATvsAC 0x3191B0 : {
		*(.patch_CollisionATvsAC)
	}

	.patch_ISGPutaway 0x32B4AC : {
		*(.patch_ISGPutaway)
	}

	.patch_SetBGMEntrance 0x331048 : {
		*(.patch_SetBGMEntrance)
	}

	.patch_NockArrow 0x33615C : {
		*(.patch_NockArrow)
	}

	.patch_DecreaseArrowCount 0x3362C4 : {
		*(.patch_DecreaseArrowCount)
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

	.patch_GetObjectEntry_339DFC 0x339DFC : {
		*(.patch_GetObjectEntry_339DFC)
	}

	.patch_GetObjectEntry_33A950 0x33A950 : {
		*(.patch_GetObjectEntry_33A950)
	}

	.patch_GetObjectEntry_33AB24 0x33AB24 : {
		*(.patch_GetObjectEntry_33AB24)
	} /* Used for: chest ice trap smoke effect */

	.patch_BiggoronDayCheck 0x33DCC0 : {
		*(.patch_BiggoronDayCheck)
	}

	.patch_FWandWarpSongTimerDepletion 0x33DE84 : {
		*(.patch_FWandWarpSongTimerDepletion)
	}

	.patch_RandomGsLoc_CustomTangibilityCheck 0x3415B0 : {
		*(.patch_RandomGsLoc_CustomTangibilityCheck)
	}

	.patch_MasterQuestGoldSkulltulaCheck 0x3415C8 : {
		*(.patch_MasterQuestGoldSkulltulaCheck)
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

	.patch_GetObjectEntry_34F270 0x34F270 : {
		*(.patch_GetObjectEntry_34F270)
	}

	.patch_GetObjectEntry_34FE68 0x34FE68 : {
		*(.patch_GetObjectEntry_34FE68)
	}

	.patch_FWGetSet 0x3519CC : {
		*(.patch_FWGetSet)
	}

	.patch_ApplyDamageMultiplier 0x352DC0 : {
		*(.patch_ApplyDamageMultiplier)
	}

	.patch_GetObjectEntry_352F28 0x352F28 : {
		*(.patch_GetObjectEntry_352F28)
	} /* Used for: Flare Dancer */

	.patch_GetObjectEntry_353CE4 0x353CE4 : {
		*(.patch_GetObjectEntry_353CE4)
	}

	.patch_FastChests 0x354CD4 : {
		*(.patch_FastChests)
	}

	.patch_AboutToPickUpActor 0x354DD8 : {
		*(.patch_AboutToPickUpActor)
	}

	.patch_MasterSwordTimerCheck 0x354DFC : {
		*(.patch_MasterSwordTimerCheck)
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

	.patch_SkullwalltulaAttack_35F328 0x35F328 : {
		*(.patch_SkullwalltulaAttack_35F328)
	}

	.patch_SkullwalltulaTargetRotation 0x35F828 : {
		*(.patch_SkullwalltulaTargetRotation)
	}

	.patch_SkullwalltulaAttack_35F834 0x35F834 : {
		*(.patch_SkullwalltulaAttack_35F834)
	}

	.patch_ISGCrouchStab 0x360690 : {
		*(.patch_ISGCrouchStab)
	}

	.patch_ForceTrailEffectUpdate 0x362108 : {
		*(.patch_ForceTrailEffectUpdate)
	} /*EffectBlure_AddVertex*/

	.patch_ExtendObjectGetSlot 0x363CB4 : {
		*(.patch_ExtendObjectGetSlot)
	}

	.patch_StalchildDespawn_366338 0x366338 : {
		*(.patch_StalchildDespawn_366338)
	}

	.patch_GetObjectEntry_36A96C 0x36A96C : {
		*(.patch_GetObjectEntry_36A96C)
	} /* Used for: freestanding item models */

	.patch_IgnoreMaskReaction 0x36BBC4 : {
		*(.patch_IgnoreMaskReaction)
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

	.patch_Model_EnableMeshGroupByIndex 0x372670 : {
		*(.patch_Model_EnableMeshGroupByIndex)
	}

	.patch_MaskSalesmanCheckNoMaskOne 0x372B64 : {
		*(.patch_MaskSalesmanCheckNoMaskOne)
	}

	.patch_MaskSalesmanCheckNoMaskTwo 0x372B70 : {
		*(.patch_MaskSalesmanCheckNoMaskTwo)
	}

	.patch_GetObjectEntry_372F7C 0x372F7C : {
	    *(.patch_GetObjectEntry_372F7C)
	}

	.patch_OverrideObjectIsLoaded 0x373074 : {
	    *(.patch_OverrideObjectIsLoaded)
	}

	.patch_ConvertBombDropTwo 0x3747A4 : {
		*(.patch_ConvertBombDropTwo)
	}

	.patch_SetSFX 0x37547C : {
		*(.patch_SetSFX)
	}

	.patch_CollisionCheck_SetAC_Once 0x376174 : {
		*(.patch_CollisionCheck_SetAC_Once)
	}

	.patch_CollisionCheck_SetAT_Once 0x3761FC : {
		*(.patch_CollisionCheck_SetAT_Once)
	}

	.patch_CollisionCheck_SetOC_Once 0x3762B0 : {
		*(.patch_CollisionCheck_SetOC_Once)
	}

	.patch_GKSetDurability 0x376BDC : {
		*(.patch_GKSetDurability)
	}

	.patch_GiantsKnifeWithoutKokiriSword 0x376BEC : {
		*(.patch_GiantsKnifeWithoutKokiriSword)
	}

	.patch_GiveItemMasterSword 0x376C18 : {
		*(.patch_GiveItemMasterSword)
	}

	.patch_NoLensOfTruthNaviText 0x37798C : {
		*(.patch_NoLensOfTruthNaviText)
	}

	.patch_AltHeadersCommand 0x379020 : {
		*(.patch_AltHeadersCommand)
	}

	.patch_FrogRewardPurple 0x3898F0 : {
		*(.patch_FrogRewardPurple)
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

	.patch_PeahatLarvaGroundCheck 0x391740 : {
		*(.patch_PeahatLarvaGroundCheck)
	}

	.patch_OcarinaMinigameEndAfterWin 0x39DF38 : {
		*(.patch_OcarinaMinigameEndAfterWin)
	}

	.patch_LullabyLocation 0x3A0A7C : {
		*(.patch_LullabyLocation)
	}

	.patch_OverrideDrawItemThree 0x3A0EA8 : {
		*(.patch_OverrideDrawItemThree)
	}

	.patch_AfterInvalidatingRoomObjects 0x3A7698 : {
		*(.patch_AfterInvalidatingRoomObjects)
	}

	.patch_AfterObjectListCommand 0x3A7708 : {
		*(.patch_AfterObjectListCommand)
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

	.patch_ShabomAfterDamagePlayer 0x3B5060 : {
		*(.patch_ShabomAfterDamagePlayer)
	}

	.patch_BabyDodongoWallCheck 0x3B833C : {
		*(.patch_BabyDodongoWallCheck)
	}

	.patch_RandomGsLoc_CustomTokenSpawnOffset 0x3B94C4 : {
		*(.patch_RandomGsLoc_CustomTokenSpawnOffset)
	}

	.patch_RandomGsLoc_BlockSpawn_Crate 0x3BCA68 : {
		*(.patch_RandomGsLoc_BlockSpawn_Crate)
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

	.patch_RandomGsLoc_BlockSpawn_Soil 0x3BF690 : {
		*(.patch_RandomGsLoc_BlockSpawn_Soil)
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

	.patch_BombPurchaseableCheck 0x3CE800 : {
		*(.patch_BombPurchaseableCheck)
	}

	.patch_ScrubStickUpgradeTwo 0x3CE990 : {
		*(.patch_ScrubStickUpgradeTwo)
	}

	.patch_ScrubNutUpgradeTwo 0x3CE9DC : {
		*(.patch_ScrubNutUpgradeTwo)
	}

	.patch_GrannySetRewardFlag 0x3D0E34 : {
		*(.patch_GrannySetRewardFlag)
	}

	.patch_GrannyItemOverrideTwo 0x3D0E60 : {
		*(.patch_GrannyItemOverrideTwo)
	}

	.patch_MidoCheckDekuTreeClearFour 0x3D2C18 : {
		*(.patch_MidoCheckDekuTreeClearFour)
	}

	.patch_LeeverAfterDie 0x3D4E10 : {
		*(.patch_LeeverAfterDie)
	}

	.patch_LeeverAfterSink 0x3D6188 : {
		*(.patch_LeeverAfterSink)
	}

	.patch_LeeverSandCheck_Small 0x3DE2A0 : {
		*(.patch_LeeverSandCheck_Small)
	}

	.patch_ShadowShip_Speed 0x3DFB30 : {
		*(.patch_ShadowShip_Speed)
	}

	.patch_FireBlockSpeed 0x3E0BB4 : {
		*(.patch_FireBlockSpeed)
	}

	.patch_FreeScarecrow 0x3E55A8 : {
		*(.patch_FreeScarecrow)
	}

	.patch_MasterSwordAlwaysDrop 0x3E5E98 : {
		*(.patch_MasterSwordAlwaysDrop)
	}

	.patch_PickUpMasterSword 0x3E5EC8 : {
		*(.patch_PickUpMasterSword)
	}

	.patch_SkipMasterSwordFanfare 0x3E5F60 : {
		*(.patch_SkipMasterSwordFanfare)
	}

	.patch_ShadowShip_CSTimer 0x3E6C50 : {
		*(.patch_ShadowShip_CSTimer)
	}

	.patch_FlyingPotDontChangeCategory 0x3E7008 : {
		*(.patch_FlyingPotDontChangeCategory)
	}

	.patch_FairyReward 0x3E7598 : {
		*(.patch_FairyReward)
	}

	.patch_RainbowBridge 0x3E7CAC : {
		*(.patch_RainbowBridge)
	}

	.patch_RemoveWaterfallCS 0x3E7F64 : {
		*(.patch_RemoveWaterfallCS)
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

	.patch_FastChestsTwo 0x3F1048 : {
		*(.patch_FastChestsTwo)
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

	.patch_LinkReflection 0x3F2F0C : {
		*(.patch_LinkReflection)
	}

	.patch_SlidingDoorDestroyCustomModels 0x3F4A70 : {
		*(.patch_SlidingDoorDestroyCustomModels)
	}

	.patch_ChildBlueWarpOverride 0x3F5774 : {
		*(.patch_ChildBlueWarpOverride)
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

	/* Start of regional differences: 0x41A144 */
	region_offset = DEFINED(_EUR_) ? 0x24 : 0;

	.patch_OcarinaNoteButtonsPress 0x41AAAC + region_offset : {
		*(.patch_OcarinaNoteButtonsPress)
	}

	.patch_CurseTrapDizzyStick 0x41AB24 + region_offset : {
		*(.patch_CurseTrapDizzyStick)
	}

	.patch_CurseTrapDizzyButtons 0x41ABDC + region_offset : {
		*(.patch_CurseTrapDizzyButtons)
	}

	.patch_PermadeathSkipMenu 0x41C980 + region_offset : {
		*(.patch_PermadeathSkipMenu)
	}

	.patch_SaveMenuIgnoreOpen 0x42EC00 + region_offset : {
		*(.patch_SaveMenuIgnoreOpen)
	}

	.patch_ItemsMenuDraw 0x434C08 + region_offset : {
		*(.patch_ItemsMenuDraw)
	}

	.patch_PlayInit 0x4352F4 + region_offset : {
		*(.patch_PlayInit)
	}

	/* Variation of regional differences: 0x436690 */
	region_offset = DEFINED(_EUR_) ? 0x20 : 0;

	.patch_GearMenuEmptySlot 0x438C00 + region_offset : {
		*(.patch_GearMenuEmptySlot)
	}

	.patch_DrawHeartIcon 0x444368 + region_offset : {
		*(.patch_DrawHeartIcon)
	}

	.patch_BeforeLoadGame 0x447380 + region_offset : {
		*(.patch_BeforeLoadGame)
	}

	.patch_DontSetMotionSetting 0x447410 + region_offset : {
		*(.patch_DontSetMotionSetting)
	}

	.patch_OverrideFogDuringGameplayInit 0x4485B4 + region_offset : {
		*(.patch_OverrideFogDuringGameplayInit)
	}

	.patch_CheckForWeirdEggHatchGameplayInit 0x448A64 + region_offset : {
		*(.patch_CheckForWeirdEggHatchGameplayInit)
	}

	.patch_CheckForPocketCuccoHatchGameplayInit 0x448A80 + region_offset : {
		*(.patch_CheckForPocketCuccoHatchGameplayInit)
	}

	.patch_InitSceneMirrorWorld 0x4490DC + region_offset : {
		*(.patch_InitSceneMirrorWorld)
	}

	.patch_InitSceneEntranceOverride 0x449190 + region_offset : {
		*(.patch_InitSceneEntranceOverride)
	}

	.patch_InitSceneClearExtendedObjects 0x449218 + region_offset : {
		*(.patch_InitSceneClearExtendedObjects)
	}

	.patch_SaveFile_Init 0x449A04 + region_offset : {
		*(.patch_SaveFile_Init)
	}

	.patch_SavewarpSetRespawnFlag 0x449E40 + region_offset : {
		*(.patch_SavewarpSetRespawnFlag)
	}

	.patch_Multiplayer_OnLoadFile 0x449EFC + region_offset : {
		*(.patch_Multiplayer_OnLoadFile)
	}

	.patch_AfterLoadGame 0x449F00 + region_offset : {
		*(.patch_AfterLoadGame)
	}

	.patch_GetCustomMessageEntryTwo 0x44D564 + region_offset : {
		*(.patch_GetCustomMessageEntryTwo)
	}

	.patch_GetCustomMessageTextTwo 0x44D5A4 + region_offset : {
		*(.patch_GetCustomMessageTextTwo)
	}

	.patch_GameplayDestroy 0x44E294 + region_offset : {
		*(.patch_GameplayDestroy)
	}

	.patch_ExtendedObjectClear 0x44E758 + region_offset : {
			*(.patch_ExtendedObjectClear)
	}

	.patch_Multiplayer_UpdatePrevActorFlags 0x44E878 + region_offset : {
		*(.patch_Multiplayer_UpdatePrevActorFlags)
	}

	.patch_PlayEntranceCutscene 0x44F068 + region_offset : {
		*(.patch_PlayEntranceCutscene)
	}

	.patch_RequiemLocation 0x44F104 + region_offset : {
		*(.patch_RequiemLocation)
	}

	.patch_NocturneLocation 0x44F12C + region_offset : {
		*(.patch_NocturneLocation)
	}

	.patch_SariasGift 0x44F188 + region_offset : {
		*(.patch_SariasGift)
	}

	.patch_LACSConditionOne 0x44F1D4 + region_offset : {
		*(.patch_LACSConditionOne)
	}

	.patch_LACSConditionTwo 0x44F20C + region_offset : {
		*(.patch_LACSConditionTwo)
	}

	.patch_BossChallenge_Enter 0x44F634 + region_offset : {
		*(.patch_BossChallenge_Enter)
	}

	.patch_SetSavewarpEntrance 0x44FBE4 + region_offset : {
		*(.patch_SetSavewarpEntrance)
	}

	.patch_LullabyCheckFlag 0x44FD54 + region_offset : {
		*(.patch_LullabyCheckFlag)
	}

	.patch_LoadFileSwordless 0x44FD98 + region_offset : {
		*(.patch_LoadFileSwordless)
	}

	.patch_OpenSaveDontSpoilTradeItems 0x44FDF8 + region_offset : {
		*(.patch_OpenSaveDontSpoilTradeItems)
	}

	.patch_OnActorSetup_SceneChange 0x452250 + region_offset : {
		*(.patch_OnActorSetup_SceneChange)
	}

	.patch_AfterActorSetup_SceneChange 0x4522B8 + region_offset : {
		*(.patch_AfterActorSetup_SceneChange)
	}

	.patch_before_GlobalContext_Update 0x452390 + region_offset : {
		*(.patch_before_GlobalContext_Update)
	}

	.patch_after_GlobalContext_Update 0x452434 + region_offset : {
		*(.patch_after_GlobalContext_Update)
	}

	.patch_FixItemsMenuSlotDuplication 0x456B90 + region_offset : {
		*(.patch_FixItemsMenuSlotDuplication)
	}

	.patch_GameOverDontSpoilTradeItems 0x458BE0 + region_offset : {
		*(.patch_GameOverDontSpoilTradeItems)
	}

	.patch_DeathHandleBButton 0x458CA8 + region_offset : {
		*(.patch_DeathHandleBButton)
	}

	.patch_PermadeathForceQuit 0x458E20 + region_offset : {
		*(.patch_PermadeathForceQuit)
	}

	.patch_SetGameOverEntrance 0x458E3C + region_offset : {
		*(.patch_SetGameOverEntrance)
	}

	.patch_SetGameOverRespawnFlag 0x458EF0 + region_offset : {
		*(.patch_SetGameOverRespawnFlag)
	}

	.patch_InterfaceDrawDontSpoilTradeItems 0x45A17C + region_offset : {
		*(.patch_InterfaceDrawDontSpoilTradeItems)
	}

	.patch_TimerExpiration 0x45A948 + region_offset : {
		*(.patch_TimerExpiration)
	}

	.patch_Timer2TickSound 0x45A9B4 + region_offset : {
		*(.patch_Timer2TickSound)
	}

	.patch_SunsSongEndCloseTextbox 0x45B514 + region_offset : {
		*(.patch_SunsSongEndCloseTextbox)
	}

	.patch_SetSunsSongRespawnFlag 0x45B660 + region_offset : {
		*(.patch_SetSunsSongRespawnFlag)
	}

	.patch_BossChallenge_ExitMenu 0x45CCA4 + region_offset : {
		*(.patch_BossChallenge_ExitMenu)
	}

	.patch_StoreChildBButtonEquip 0x45F20C + region_offset : {
		*(.patch_StoreChildBButtonEquip)
	}

	.patch_BecomeAdult 0x45F230 + region_offset : {
		*(.patch_BecomeAdult)
	}

	.patch_AlwaysRestoreChildEquips 0x45F3B0 + region_offset : {
		*(.patch_AlwaysRestoreChildEquips)
	}

	.patch_ChildDontEquipSwordSlotByDefault 0x45F49C + region_offset : {
		*(.patch_ChildDontEquipSwordSlotByDefault)
	}

	.patch_OnActorSetup_RoomChange 0x4613C4 + region_offset : {
		*(.patch_OnActorSetup_RoomChange)
	}

	.patch_AfterActorSetup_RoomChange 0x461434 + region_offset : {
		*(.patch_AfterActorSetup_RoomChange)
	}

	.patch_FixActorKillLoop 0x4615E0 + region_offset : {
		*(.patch_FixActorKillLoop)
	}

	.patch_ActorUpdate 0x461790 + region_offset : {
		*(.patch_ActorUpdate)
	}

	.patch_TitleCardUpdate 0x4618B8 + region_offset : {
		*(.patch_TitleCardUpdate)
	}

	.patch_ItemsMenuNumSprites 0x46B758 + region_offset : {
		*(.patch_ItemsMenuNumSprites)
	}

	.patch_CheckForWeirdEggHatchKankyo 0x470D00 + region_offset : {
		*(.patch_CheckForWeirdEggHatchKankyo)
	}

	.patch_CheckForPocketCuccoHatchKankyo 0x470D1C + region_offset : {
		*(.patch_CheckForPocketCuccoHatchKankyo)
	}

	.patch_CriticalHealthCheckOne 0x4715B8 + region_offset : {
		*(.patch_CriticalHealthCheckOne)
	}

	.patch_CriticalHealthCheckTwo 0x4716D4 + region_offset : {
		*(.patch_CriticalHealthCheckTwo)
	}

	.patch_EnableFW 0x476D1C + region_offset : {
		*(.patch_EnableFW)
	}

	.patch_StoreTargetActorType 0x479984 + region_offset : {
		*(.patch_StoreTargetActorType)
	}

	.patch_TargetReticleColor 0x47B284 + region_offset : {
		*(.patch_TargetReticleColor)
	}

	.patch_TargetPointerColor 0x47BAE8 + region_offset : {
		*(.patch_TargetPointerColor)
	}

	.patch_FWKeepWarpPoint 0x47C3C0 + region_offset : {
		*(.patch_FWKeepWarpPoint)
	}

	.patch_TurboTextAdvance 0x480928 + region_offset : {
		*(.patch_TurboTextAdvance)
	}

	.patch_SetBGMDayNight 0x483C88 + region_offset : {
		*(.patch_SetBGMDayNight)
	}

	.patch_Cutscene_CheckObjectLoaded 0x4849D8 + region_offset : {
		*(.patch_Cutscene_CheckObjectLoaded)
	}

	.patch_TurboTextClose 0x488214 + region_offset : {
		*(.patch_TurboTextClose)
	}

	.patch_WarpSongEntranceOverride 0x488850 + region_offset : {
		*(.patch_WarpSongEntranceOverride)
	}

	.patch_SetFWPlayerParams 0x4911B8 + region_offset : {
		*(.patch_SetFWPlayerParams)
	}

	.patch_SwapFaroresWind 0x49186C + region_offset : {
		*(.patch_SwapFaroresWind)
	}

	.patch_SwapAgeIgnoreSceneSetup 0x4918B0 + region_offset : {
		*(.patch_SwapAgeIgnoreSceneSetup)
	}

	.patch_SkipTimeTravelCutsceneTwo 0x4918C8 + region_offset : {
		*(.patch_SkipTimeTravelCutsceneTwo)
	}

	.patch_DMTOwlEntranceOverride 0x492064 + region_offset : {
		*(.patch_DMTOwlEntranceOverride)
	}

	.patch_LHOwlEntranceOverride 0x492080 + region_offset : {
		*(.patch_LHOwlEntranceOverride)
	}

	.patch_FairyUseHealAmount 0x4968B4 + region_offset : {
		*(.patch_FairyUseHealAmount)
	}

	.patch_SendDroppedBottleContents 0x496A1C + region_offset : {
		*(.patch_SendDroppedBottleContents)
	}

	.patch_ReturnFW 0x496B88 + region_offset : {
		*(.patch_ReturnFW)
	}

	.patch_SetSpecialVoidOutRespawnFlag 0x496C70 + region_offset : {
		*(.patch_SetSpecialVoidOutRespawnFlag)
	}

	.patch_GanonBattleDeathWarp 0x496C98 + region_offset : {
		*(.patch_GanonBattleDeathWarp)
	}

	.patch_GanonRestoreMSOnDeath 0x496CB4 + region_offset : {
		*(.patch_GanonRestoreMSOnDeath)
	}

	.patch_CriticalHealthCheckThree 0x49F294 + region_offset : {
		*(.patch_CriticalHealthCheckThree)
	}

	/* End of regional differences: 0x4A5AE0 */
	region_offset = 0;

	.patch_OverrideGiDrawIdPlusOne_Ground 0x4BC610 : {
		*(.patch_OverrideGiDrawIdPlusOne_Ground)
	}

	.patch_OverrideGiDrawIdPlusOne_Water 0x4BD5DC : {
		*(.patch_OverrideGiDrawIdPlusOne_Water)
	}

	.patch_EditDrawGetItemBeforeModelSpawn 0x4C0FD0 : {
		*(.patch_EditDrawGetItemBeforeModelSpawn)
	}

	.patch_HookshotRotation 0x4C2524 : {
		*(.patch_HookshotRotation)
	}

	.patch_EditDrawGetItemAfterMatrixUpdate 0x4C4D14 : {
		*(.patch_EditDrawGetItemAfterMatrixUpdate)
	}

	.patch_EditDrawGetItemAfterModelSpawn 0x4C61A4 : {
		*(.patch_EditDrawGetItemAfterModelSpawn)
	}

	.patch_CrouchStabHitbox 0x4C85D4 : {
		*(.patch_CrouchStabHitbox)
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

	.patch_TitleLinkObject 0x53CCF0 : {
		*(.patch_TitleLinkObject)
	}

	. = 0x005C7000;
	.text : {
		__text_start = . ;
		*(.text*)
		*(.rodata*)
		*(.data*)
		*(.bss*)
		*(.init*)
		*(.fini*)
		*(.eh_frame*)
		*(.init_array*)
		*(.fini_array*)
		*(COMMON)
		rCustomMessages = . ;
		__text_end = . ;
	}
}
