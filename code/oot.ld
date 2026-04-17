OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(loader_patch)
SECTIONS
{
	_LD_OFF = 0;

	. = 0x100000 + _LD_OFF;
	.patch_loader 0x100000 + _LD_OFF : { *(.patch_loader) }
	nninitRegion = 0x100028 + _LD_OFF;
	EnDns_SetupBurrow = 0x100434 + _LD_OFF;
	EnBb_Update = 0x1005EC + _LD_OFF;
	EnIk_UpdateEnemy = 0x1008B4 + _LD_OFF;
	EnZf_Update = 0x101C48 + _LD_OFF;
	.patch_GrogSetTradedCojiroFlag 0x104C50 + _LD_OFF : { *(.patch_GrogSetTradedCojiroFlag) }
	.patch_MidoCheckDekuTreeClearTwo 0x105CD4 + _LD_OFF : { *(.patch_MidoCheckDekuTreeClearTwo) }
	.patch_ArmosCooldownTimer 0x10B41C + _LD_OFF : { *(.patch_ArmosCooldownTimer) }
	.patch_ArmosPushSpeed 0x10B5C4 + _LD_OFF : { *(.patch_ArmosPushSpeed) }
	EnMb_ClubWaitPlayerNear = 0x10B5D0 + _LD_OFF;
	.patch_ShortenRainbowBridgeCS 0x10B904 + _LD_OFF : { *(.patch_ShortenRainbowBridgeCS) }
	.patch_GrannyTextID 0x10DCD0 + _LD_OFF : { *(.patch_GrannyTextID) }
	OceffSpot_End = 0x10FBD0 + _LD_OFF;
	ObjLift_Shake = 0x110E98 + _LD_OFF;
	.patch_LabScientistDontStartTimerAndSetFlag 0x112440 + _LD_OFF : { *(.patch_LabScientistDontStartTimerAndSetFlag) }
	.patch_BombchuPurchaseableCheck 0x112ED0 + _LD_OFF : { *(.patch_BombchuPurchaseableCheck) }
	EnDha_Update = 0x113050 + _LD_OFF;
	.patch_PoeCollectorGetFirstTextbox 0x113844 + _LD_OFF : { *(.patch_PoeCollectorGetFirstTextbox) }
	ItemEtcetera_Draw = 0x11707C + _LD_OFF;
	.patch_ItemEtceteraModelDraw 0x117080 + _LD_OFF : { *(.patch_ItemEtceteraModelDraw) }
	EnFd_Reappear = 0x117D98 + _LD_OFF;
	.patch_FlyingPotCollision 0x11DB34 + _LD_OFF : { *(.patch_FlyingPotCollision) }
	.patch_DodongoAfterSwallowBomb 0x11E4B8 + _LD_OFF : { *(.patch_DodongoAfterSwallowBomb) }
	EnGe1_TalkAfterGame_Archery = 0x12A5C8 + _LD_OFF;
	.patch_SariasSongItemGive 0x12C84C + _LD_OFF : { *(.patch_SariasSongItemGive) }
	.patch_SariasSongLocation 0x12C8F8 + _LD_OFF : { *(.patch_SariasSongLocation) }
	.patch_SkulltulaRewardOne 0x12CC68 + _LD_OFF : { *(.patch_SkulltulaRewardOne) }
	.patch_SkulltulaRewardTwo 0x12CD38 + _LD_OFF : { *(.patch_SkulltulaRewardTwo) }
	DemoGt_Update = 0x12E1C4 + _LD_OFF;
	EnTest_Update = 0x12E2D0 + _LD_OFF;
	.patch_MedigoronCheckFlagOne 0x13024C + _LD_OFF : { *(.patch_MedigoronCheckFlagOne) }
	.patch_MedigoronGetCustomText 0x130258 + _LD_OFF : { *(.patch_MedigoronGetCustomText) }
	.patch_MedigoronCheckFlagTwo 0x1302C4 + _LD_OFF : { *(.patch_MedigoronCheckFlagTwo) }
	.patch_BeanDaddyModifyBeansBought 0x130CEC + _LD_OFF : { *(.patch_BeanDaddyModifyBeansBought) }
	EnBubble_Pop = 0x1321A8 + _LD_OFF;
	.patch_PlayerCheckVoidOut 0x132B64 + _LD_OFF : { *(.patch_PlayerCheckVoidOut) }
	EnGo2_SetGetItem = 0x133EBC + _LD_OFF;
	.patch_BiggoronDontSetBGSFlag 0x133F7C + _LD_OFF : { *(.patch_BiggoronDontSetBGSFlag) }
	.patch_KingZoraDontStartTimer 0x134D7C + _LD_OFF : { *(.patch_KingZoraDontStartTimer) }
	EnMb_ClubAttack = 0x136C68 + _LD_OFF;
	.patch_GanonFinalBlow 0x13B684 + _LD_OFF : { *(.patch_GanonFinalBlow) }
	.patch_StalchildDespawn_13DB68 0x13DB68 + _LD_OFF : { *(.patch_StalchildDespawn_13DB68) }
	.patch_SongOfStormsLocation 0x1427E0 + _LD_OFF : { *(.patch_SongOfStormsLocation) }
	ObjBean_StallGrowth = 0x143684 + _LD_OFF;
	ObjBean_GrowSprout = 0x1436C4 + _LD_OFF;
	.patch_JabuSwitchRutoCheck 0x143AC8 + _LD_OFF : { *(.patch_JabuSwitchRutoCheck) }
	.patch_OwlMagicCheck 0x144B44 + _LD_OFF : { *(.patch_OwlMagicCheck) }
	EnGeldB_Update = 0x14A04C + _LD_OFF;
	EnGirlA_InitializeItemAction = 0x14D5C8 + _LD_OFF;
	.patch_MedigoronItemOverrideOne 0x14D95C + _LD_OFF : { *(.patch_MedigoronItemOverrideOne) }
	.patch_BeanDaddyPurchase 0x14EDA8 + _LD_OFF : { *(.patch_BeanDaddyPurchase) }
	.patch_BeanDaddyModifyPrice 0x14EE98 + _LD_OFF : { *(.patch_BeanDaddyModifyPrice) }
	.patch_SkipTwinrovaQuarrelCutsceneOne 0x15273C + _LD_OFF : { *(.patch_SkipTwinrovaQuarrelCutsceneOne) }
	EnCrow_Respawn = 0x158648 + _LD_OFF;
	.patch_FairyPickupHealAmount 0x15CA4C + _LD_OFF : { *(.patch_FairyPickupHealAmount) }
	.patch_RandomGsLoc_SkipSoilJingle 0x15DBD8 + _LD_OFF : { *(.patch_RandomGsLoc_SkipSoilJingle) }
	ObjBean_UnplantedWait = 0x15E154 + _LD_OFF;
	.patch_GrannyBottleCheck 0x161044 + _LD_OFF : { *(.patch_GrannyBottleCheck) }
	.patch_GrannyItemOverrideOne 0x161094 + _LD_OFF : { *(.patch_GrannyItemOverrideOne) }
	EnDns_SetupSale = 0x161828 + _LD_OFF;
	.patch_ScrubStickUpgradeOne 0x161898 + _LD_OFF : { *(.patch_ScrubStickUpgradeOne) }
	.patch_ScrubNutUpgradeOne 0x1618EC + _LD_OFF : { *(.patch_ScrubNutUpgradeOne) }
	EnDns_Talk = 0x161960 + _LD_OFF;
	EnBb_Init = 0x162328 + _LD_OFF;
	EnBb_Destroy = 0x162C28 + _LD_OFF;
	EnGs_Init = 0x16461C + _LD_OFF;
	.patch_GrogCheckForShouldDespawn 0x16485C + _LD_OFF : { *(.patch_GrogCheckForShouldDespawn) }
	EnIk_Init = 0x164B0C + _LD_OFF;
	.patch_GetObjectEntry_164BC8 0x164BC8 + _LD_OFF : { *(.patch_GetObjectEntry_164BC8) }
	.patch_CheckFadoCanSpawnInLostWoods 0x1657EC + _LD_OFF : { *(.patch_CheckFadoCanSpawnInLostWoods) }
	.patch_EnKoInitCheckForest_165834 0x165834 + _LD_OFF : { *(.patch_EnKoInitCheckForest_165834) }
	.patch_EnKoInitCheckForest_165878 0x165878 + _LD_OFF : { *(.patch_EnKoInitCheckForest_165878) }
	.patch_EnKoInitCheckForest_1658C0 0x1658C0 + _LD_OFF : { *(.patch_EnKoInitCheckForest_1658C0) }
	.patch_EnKoInitCheckForest_1658F0 0x1658F0 + _LD_OFF : { *(.patch_EnKoInitCheckForest_1658F0) }
	.patch_KingZoraCheckMovedFlag 0x165A60 + _LD_OFF : { *(.patch_KingZoraCheckMovedFlag) }
	EnMb_Init = 0x165BA4 + _LD_OFF;
	.patch_MidoCheckSpawn 0x166154 + _LD_OFF : { *(.patch_MidoCheckSpawn) }
	.patch_MidoCheckDekuTreeClearOne 0x16623C + _LD_OFF : { *(.patch_MidoCheckDekuTreeClearOne) }
	EnPeehat_Update = 0x167644 + _LD_OFF;
	.patch_GetObjectEntry_EnRdInit_One 0x167DA4 + _LD_OFF : { *(.patch_GetObjectEntry_EnRdInit_One) }
	.patch_GetObjectEntry_EnRdInit_Two 0x167E38 + _LD_OFF : { *(.patch_GetObjectEntry_EnRdInit_Two) }
	.patch_SariasSongCheckFlag 0x1686A0 + _LD_OFF : { *(.patch_SariasSongCheckFlag) }
	EnSi_Init = 0x168A90 + _LD_OFF;
	.patch_GetObjectEntry_EnSiInit 0x168B20 + _LD_OFF : { *(.patch_GetObjectEntry_EnSiInit) }
	EnSi_Destroy = 0x168C3C + _LD_OFF;
	EnSw_Init = 0x1691C8 + _LD_OFF;
	.patch_RandomGsLoc_BlockSpawn_Tree 0x16C43C + _LD_OFF : { *(.patch_RandomGsLoc_BlockSpawn_Tree) }
	.patch_MedigoronSetRewardFlag 0x16C918 + _LD_OFF : { *(.patch_MedigoronSetRewardFlag) }
	.patch_MedigoronItemOverrideTwo 0x16C9BC + _LD_OFF : { *(.patch_MedigoronItemOverrideTwo) }
	.patch_MaskSalesmanBorrowMask 0x16D148 + _LD_OFF : { *(.patch_MaskSalesmanBorrowMask) }
	.patch_KingZoraIgnoreSapphire 0x1736B8 + _LD_OFF : { *(.patch_KingZoraIgnoreSapphire) }
	.patch_MidoForestDialog 0x173944 + _LD_OFF : { *(.patch_MidoForestDialog) }
	EnGoma_SetupHatch = 0x1741C8 + _LD_OFF;
	.patch_LeeverSandCheck_Big 0x1743D0 + _LD_OFF : { *(.patch_LeeverSandCheck_Big) }
	.patch_SkipTimeTravelCutsceneOne 0x174DEC + _LD_OFF : { *(.patch_SkipTimeTravelCutsceneOne) }
	.patch_SkipTwinrovaQuarrelCutsceneTwo 0x176110 + _LD_OFF : { *(.patch_SkipTwinrovaQuarrelCutsceneTwo) }
	.patch_LostWoodsTargetCutscene 0x178058 + _LD_OFF : { *(.patch_LostWoodsTargetCutscene) }
	.patch_CarpenterBossDontNullExchangeItem 0x178BE4 + _LD_OFF : { *(.patch_CarpenterBossDontNullExchangeItem) }
	.patch_CarpenterBossSetTradedSawFlag 0x178D58 + _LD_OFF : { *(.patch_CarpenterBossSetTradedSawFlag) }
	.patch_AnjuCheckCuccoAmount 0x179420 + _LD_OFF : { *(.patch_AnjuCheckCuccoAmount) }
	EnReeba_SetupSurface = 0x181394 + _LD_OFF;
	BgYdanSp_BurnWallWeb = 0x181878 + _LD_OFF;
	BgYdanSp_WallWebIdle = 0x181C88 + _LD_OFF;
	EnDaiku_WaitFreedom = 0x182FF0 + _LD_OFF;
	.patch_FastOwlCutscenes 0x188584 + _LD_OFF : { *(.patch_FastOwlCutscenes) }
	.patch_BombchuShopInfinitePurchases 0x188D3C + _LD_OFF : { *(.patch_BombchuShopInfinitePurchases) }
	EnBox_Init = 0x1899EC + _LD_OFF;
	EnCow_Init = 0x189FD4 + _LD_OFF;
	EnCow_Destroy = 0x18A3E4 + _LD_OFF;
	.patch_BusinessScrubTable 0x18A634 + _LD_OFF : { *(.patch_BusinessScrubTable) }
	EnGe1_Init = 0x18B218 + _LD_OFF;
	.patch_CheckGerudoToken_18B368 0x18B368 + _LD_OFF : { *(.patch_CheckGerudoToken_18B368) }
	.patch_CheckGerudoToken_18B3A0 0x18B3A0 + _LD_OFF : { *(.patch_CheckGerudoToken_18B3A0) }
	.patch_CheckGerudoToken_18B3C0 0x18B3C0 + _LD_OFF : { *(.patch_CheckGerudoToken_18B3C0) }
	.patch_CheckGerudoToken_18B448 0x18B448 + _LD_OFF : { *(.patch_CheckGerudoToken_18B448) }
	.patch_CheckGerudoToken_18B6F4 0x18B6F4 + _LD_OFF : { *(.patch_CheckGerudoToken_18B6F4) }
	.patch_CheckGerudoToken_18B710 0x18B710 + _LD_OFF : { *(.patch_CheckGerudoToken_18B710) }
	EnMa1_Init = 0x18C334 + _LD_OFF;
	.patch_EponasSongCheckFlag 0x18C56C + _LD_OFF : { *(.patch_EponasSongCheckFlag) }
	EnMag_Init = 0x18CBB8 + _LD_OFF;
	.patch_GetObjectEntry_EnXcInit 0x18D7AC + _LD_OFF : { *(.patch_GetObjectEntry_EnXcInit) }
	.patch_PreludeLocation 0x18D9FC + _LD_OFF : { *(.patch_PreludeLocation) }
	EnOwl_Init = 0x18DB28 + _LD_OFF;
	EnPoh_Init = 0x18DF00 + _LD_OFF;
	.patch_SkullKidPoacherSawCheck 0x18ED80 + _LD_OFF : { *(.patch_SkullKidPoacherSawCheck) }
	.patch_PoeCollectorCheckPoints 0x19091C + _LD_OFF : { *(.patch_PoeCollectorCheckPoints) }
	.patch_GoronShopPurchaseableCheck 0x19120C + _LD_OFF : { *(.patch_GoronShopPurchaseableCheck) }
	PlayerActor_Init = 0x191844 + _LD_OFF;
	.patch_PlayerEditAndRetrieveCMB 0x191970 + _LD_OFF : { *(.patch_PlayerEditAndRetrieveCMB) }
	.patch_AdultItemsCMABsAsChild 0x191BB0 + _LD_OFF : { *(.patch_AdultItemsCMABsAsChild) }
	.patch_SetChildCustomTunic 0x191DB0 + _LD_OFF : { *(.patch_SetChildCustomTunic) }
	.patch_PlayerGetCustomTunicCMAB 0x191DD4 + _LD_OFF : { *(.patch_PlayerGetCustomTunicCMAB) }
	PlayerActor_Destroy = 0x19262C + _LD_OFF;
	.patch_SkipDaruniaDanceOne 0x19493C + _LD_OFF : { *(.patch_SkipDaruniaDanceOne) }
	.patch_SkipDaruniaDanceTwo 0x194944 + _LD_OFF : { *(.patch_SkipDaruniaDanceTwo) }
	.patch_ChildRollingGoron 0x194B18 + _LD_OFF : { *(.patch_ChildRollingGoron) }
	.patch_BiggoronCheckBGSFlag 0x194DA0 + _LD_OFF : { *(.patch_BiggoronCheckBGSFlag) }
	.patch_ChildRollingGoronDontCheckBombBag 0x195414 + _LD_OFF : { *(.patch_ChildRollingGoronDontCheckBombBag) }
	.patch_AdultRollingGoronIgnoreMedallion 0x195450 + _LD_OFF : { *(.patch_AdultRollingGoronIgnoreMedallion) }
	.patch_AdultRollingGoronOne 0x195480 + _LD_OFF : { *(.patch_AdultRollingGoronOne) }
	.patch_AdultRollingGoronTwo 0x1954AC + _LD_OFF : { *(.patch_AdultRollingGoronTwo) }
	.patch_BiggoronGetTextId 0x1954F8 + _LD_OFF : { *(.patch_BiggoronGetTextId) }
	.patch_EponasSongCheckFlagTwo 0x195CFC + _LD_OFF : { *(.patch_EponasSongCheckFlagTwo) }
	.patch_GohmaLarvaDeathSignalParent 0x1968DC + _LD_OFF : { *(.patch_GohmaLarvaDeathSignalParent) }
	.patch_AmyBlockCooldownTimer 0x196ECC + _LD_OFF : { *(.patch_AmyBlockCooldownTimer) }
	.patch_AmyBlockSpeed 0x196F3C + _LD_OFF : { *(.patch_AmyBlockSpeed) }
	.patch_DampeChest 0x19A420 + _LD_OFF : { *(.patch_DampeChest) }
	BgYdanSp_BurnFloorWeb = 0x19A52C + _LD_OFF;
	BgYdanSp_FloorWebIdle = 0x19A8EC + _LD_OFF;
	.patch_PierreSoftlockFixOne 0x19C734 + _LD_OFF : { *(.patch_PierreSoftlockFixOne) }
	.patch_EnBlkobj_FindDarkLink 0x1A0BC8 + _LD_OFF : { *(.patch_EnBlkobj_FindDarkLink) }
	.patch_EnBlkobj_SpawnDarkLink 0x1A137C + _LD_OFF : { *(.patch_EnBlkobj_SpawnDarkLink) }
	.patch_RutoBlueWarpOverride 0x1A1900 + _LD_OFF : { *(.patch_RutoBlueWarpOverride) }
	Boss_Tw_Init = 0x1A7E18 + _LD_OFF;
	.patch_KotakeDontPlayBattleMusic 0x1A8218 + _LD_OFF : { *(.patch_KotakeDontPlayBattleMusic) }
	Boss_Tw_Destroy = 0x1A88E8 + _LD_OFF;
	EnFd_Update = 0x1B004C + _LD_OFF;
	EnFu_Update = 0x1B1328 + _LD_OFF;
	EnGeldB_Draw = 0x1B2B00 + _LD_OFF;
	.patch_GetObjectEntry_EnGomaInit_One 0x1B3130 + _LD_OFF : { *(.patch_GetObjectEntry_EnGomaInit_One) }
	.patch_GetObjectEntry_EnGomaInit_Two 0x1B3208 + _LD_OFF : { *(.patch_GetObjectEntry_EnGomaInit_Two) }
	.patch_GossipStoneAddSariaHint 0x1B3968 + _LD_OFF : { *(.patch_GossipStoneAddSariaHint) }
	.patch_ReadGossipStoneHints 0x1B3A44 + _LD_OFF : { *(.patch_ReadGossipStoneHints) }
	EnIshi_Init = 0x1B5460 + _LD_OFF;
	.patch_SkipJabuOpeningCutscene 0x1B583C + _LD_OFF : { *(.patch_SkipJabuOpeningCutscene) }
	EnKz_Update = 0x1B66F8 + _LD_OFF;
	.patch_KingZoraSecondTunic 0x1B6A18 + _LD_OFF : { *(.patch_KingZoraSecondTunic) }
	.patch_KingZoraGiveTunic 0x1B6A64 + _LD_OFF : { *(.patch_KingZoraGiveTunic) }
	EnMb_Update = 0x1B6D80 + _LD_OFF;
	.patch_MidoCheckDekuTreeClearThree 0x1B7414 + _LD_OFF : { *(.patch_MidoCheckDekuTreeClearThree) }
	EnNb_Draw = 0x1B7FBC + _LD_OFF;
	EnSi_Draw = 0x1BA050 + _LD_OFF;
	EnSi_Update = 0x1BA0C8 + _LD_OFF;
	EnSw_Update = 0x1BB110 + _LD_OFF;
	.patch_GetObjectEntry_EnTiteInit 0x1BBC9C + _LD_OFF : { *(.patch_GetObjectEntry_EnTiteInit) }
	EnTk_Update = 0x1BC088 + _LD_OFF;
	Fishing_Init = 0x1C0AD8 + _LD_OFF;
	.patch_FishingNewRecord 0x1C3AA4 + _LD_OFF : { *(.patch_FishingNewRecord) }
	.patch_FishingSizeIgnoreChild 0x1C3DFC + _LD_OFF : { *(.patch_FishingSizeIgnoreChild) }
	.patch_FishingSizeIgnoreAdult 0x1C3E40 + _LD_OFF : { *(.patch_FishingSizeIgnoreAdult) }
	.patch_BabyDodongoAfterSwallowBomb 0x1C42DC + _LD_OFF : { *(.patch_BabyDodongoAfterSwallowBomb) }
	.patch_BiggoronAfterGiveItem 0x1C4E4C + _LD_OFF : { *(.patch_BiggoronAfterGiveItem) }
	.patch_KingZoraSetTradedPrescriptionFlag 0x1C52A0 + _LD_OFF : { *(.patch_KingZoraSetTradedPrescriptionFlag) }
	.patch_GerudoBattleMusic 0x1C6FD8 + _LD_OFF : { *(.patch_GerudoBattleMusic) }
	.patch_EnEncount1_SpawnLeever 0x1CC94C + _LD_OFF : { *(.patch_EnEncount1_SpawnLeever) }
	.patch_EnEncount1_SetLeeverAimType 0x1CC984 + _LD_OFF : { *(.patch_EnEncount1_SetLeeverAimType) }
	EnEiyer_WanderUnderground = 0x1CD1D4 + _LD_OFF;
	.patch_TruthSpinnerSpeed 0x1CD814 + _LD_OFF : { *(.patch_TruthSpinnerSpeed) }
	ActorShadow_DrawFeet = 0x1D04F4 + _LD_OFF;
	.patch_DemoEffectStoneDraw 0x1D209C + _LD_OFF : { *(.patch_DemoEffectStoneDraw) }
	EnBox_Update = 0x1D5B70 + _LD_OFF;
	.patch_ChestIceSmoke 0x1D5E5C + _LD_OFF : { *(.patch_ChestIceSmoke) }
	EnDns_Update = 0x1D67CC + _LD_OFF;
	EnGe1_Update = 0x1D742C + _LD_OFF;
	.patch_CheckGerudoToken_1D7AD4 0x1D7AD4 + _LD_OFF : { *(.patch_CheckGerudoToken_1D7AD4) }
	EnGeldB_Init = 0x1D7BD8 + _LD_OFF;
	EnGirlA_Init = 0x1D7F20 + _LD_OFF;
	.patch_BiggoronSetTextId 0x1D8A10 + _LD_OFF : { *(.patch_BiggoronSetTextId) }
	.patch_BombchuShopAlwaysOpen 0x1DC6B0 + _LD_OFF : { *(.patch_BombchuShopAlwaysOpen) }
	EnOwl_Update = 0x1DCB60 + _LD_OFF;
	EnPoh_UpdateLiving = 0x1DD974 + _LD_OFF;
	.patch_LeeverDontChangeCategory 0x1DE010 + _LD_OFF : { *(.patch_LeeverDontChangeCategory) }
	.patch_LeeverSandCheck_Init 0x1DE078 + _LD_OFF : { *(.patch_LeeverSandCheck_Init) }
	EnSkb_Update = 0x1DE320 + _LD_OFF;
	EnSkj_Update = 0x1DE890 + _LD_OFF;
	EnSsh_Update = 0x1DF0A4 + _LD_OFF;
	ObjBean_Init = 0x1E12B0 + _LD_OFF;
	PlayerActor_Update = 0x1E1B54 + _LD_OFF;
	.patch_AdultBlueWarpOverride 0x1E3F50 + _LD_OFF : { *(.patch_AdultBlueWarpOverride) }
	.patch_DaruniaCheckStrength 0x1E489C + _LD_OFF : { *(.patch_DaruniaCheckStrength) }
	BgYdanSp_FloorWebBreaking = 0x1E8438 + _LD_OFF;
	.patch_CanPlayBombchuBowlingTwo 0x1EA1D4 + _LD_OFF : { *(.patch_CanPlayBombchuBowlingTwo) }
	ArmsHook_Init = 0x1EBF84 + _LD_OFF;
	Boss_Tw_Draw = 0x1EEDF0 + _LD_OFF;
	Boss_Tw_Update = 0x1EF880 + _LD_OFF;
	.patch_BoomerangTrailEffect 0x1F4220 + _LD_OFF : { *(.patch_BoomerangTrailEffect) } /*EnBoom_Draw*/
	EnCrow_Update = 0x1F4D40 + _LD_OFF;
	EnDodojr_Init = 0x1F51E8 + _LD_OFF;
	EnDoor_Update = 0x1F53C8 + _LD_OFF;
	.patch_GohmaEggDeathSignalParent 0x1F5F48 + _LD_OFF : { *(.patch_GohmaEggDeathSignalParent) }
	EnIshi_Update = 0x1F69AC + _LD_OFF;
	EnItem00_Init = 0x1F69B4 + _LD_OFF;
	.patch_Item00GiveAutomaticItemDrop 0x1F6E4C + _LD_OFF : { *(.patch_Item00GiveAutomaticItemDrop) }
	.patch_ItemGiveBombchuDropOne 0x1F6F70 + _LD_OFF : { *(.patch_ItemGiveBombchuDropOne) }
	EnItem00_Destroy = 0x1F706C + _LD_OFF;
	EnTorch2_Init = 0x1F853C + _LD_OFF;
	.patch_GetObjectEntry_1F85B0 0x1F85B0 + _LD_OFF : { *(.patch_GetObjectEntry_1F85B0) }
	Fishing_DrawFish = 0x1F98B4 + _LD_OFF;
	Fishing_UpdateFish = 0x1F9ACC + _LD_OFF;
	BgSpot02Objects_Explode = 0x205EDC + _LD_OFF;
	.patch_BombchuBowlingStaticReward 0x206150 + _LD_OFF : { *(.patch_BombchuBowlingStaticReward) }
	EnWonderTalk_Action_2065E0 = 0x2065E0 + _LD_OFF;
	.patch_SkipSongReplays_TimeBlocksFix 0x208004 + _LD_OFF : { *(.patch_SkipSongReplays_TimeBlocksFix) }
	.patch_SkipSongReplays_WarpBlocksFix 0x208068 + _LD_OFF : { *(.patch_SkipSongReplays_WarpBlocksFix) }
	EnChanger_Init = 0x20EC50 + _LD_OFF;
	.patch_ChestMinigame_DontOpenChestsOnInit 0x20EC8C + _LD_OFF : { *(.patch_ChestMinigame_DontOpenChestsOnInit) }
	.patch_ChestMinigame_KeyChestVisibility 0x20EDB8 + _LD_OFF : { *(.patch_ChestMinigame_KeyChestVisibility) }
	.patch_ChestMinigame_RewardChestVisibility 0x20EFE0 + _LD_OFF : { *(.patch_ChestMinigame_RewardChestVisibility) }
	EnDaiku_Update = 0x20F1A8 + _LD_OFF;
	EnEiyer_Update = 0x20F700 + _LD_OFF;
	EnExItem_Init = 0x20FC50 + _LD_OFF;
	EnExItem_Destroy = 0x20FDE0 + _LD_OFF;
	EnGirlA_Draw = 0x210188 + _LD_OFF;
	.patch_ShopItemDontSetAnimSpeedOne 0x2101BC + _LD_OFF : { *(.patch_ShopItemDontSetAnimSpeedOne) }
	.patch_ShopItemDontSetAnimSpeedTwo 0x2101CC + _LD_OFF : { *(.patch_ShopItemDontSetAnimSpeedTwo) }
	.patch_CourtyardCheckForVisitedZeldaOne 0x210C4C + _LD_OFF : { *(.patch_CourtyardCheckForVisitedZeldaOne) }
	.patch_CourtyardCheckForVisitedZeldaTwo 0x210C78 + _LD_OFF : { *(.patch_CourtyardCheckForVisitedZeldaTwo) }
	.patch_BugsRecatchable 0x212090 + _LD_OFF : { *(.patch_BugsRecatchable) }
	.patch_WaterSpoutMasterQuestCheck 0x212BDC + _LD_OFF : { *(.patch_WaterSpoutMasterQuestCheck) }
	ObjBean_Update = 0x214BEC + _LD_OFF;
	.patch_DekuSproutCheckForest 0x2153A4 + _LD_OFF : { *(.patch_DekuSproutCheckForest) }
	.patch_DungeonCheckJabuMQBox 0x21590C + _LD_OFF : { *(.patch_DungeonCheckJabuMQBox) }
	.patch_JabuBoxCheckRuto 0x215934 + _LD_OFF : { *(.patch_JabuBoxCheckRuto) }
	ObjLift_Update = 0x2159DC + _LD_OFF;
	ObjSwitch_Init = 0x215A14 + _LD_OFF;
	.patch_GetObjectEntry_ObjSwitchInit 0x215A60 + _LD_OFF : { *(.patch_GetObjectEntry_ObjSwitchInit) }
	.patch_EnEncount1_SpawnStalchildWolfos 0x21C020 + _LD_OFF : { *(.patch_EnEncount1_SpawnStalchildWolfos) }
	.patch_DekuTheaterMaskOfTruth 0x21CA30 + _LD_OFF : { *(.patch_DekuTheaterMaskOfTruth) }
	.patch_BombchuBowlingPrizeOrder 0x21CAD4 + _LD_OFF : { *(.patch_BombchuBowlingPrizeOrder) }
	EnDntNomal_SetupTargetUnburrow = 0x21CCFC + _LD_OFF;
	EnDntNomal_SetupTargetWalk = 0x21CED4 + _LD_OFF;
	.patch_NoHealFromBombchuBowlingPrize 0x21D170 + _LD_OFF : { *(.patch_NoHealFromBombchuBowlingPrize) }
	.patch_HookshotDrawChain 0x2202A0 + _LD_OFF : { *(.patch_HookshotDrawChain) }
	DemoEffect_Init = 0x22345C + _LD_OFF;
	DemoEffect_Destroy = 0x2245B8 + _LD_OFF;
	EffectBlure_Update = 0x227000 + _LD_OFF;
	EnBubble_Draw = 0x228CB4 + _LD_OFF;
	EnBubble_Update = 0x228F24 + _LD_OFF;
	.patch_GetObjectEntry_EnDekunutsInit 0x2293AC + _LD_OFF : { *(.patch_GetObjectEntry_EnDekunutsInit) }
	EnEncount1_Init = 0x229994 + _LD_OFF;
	EnHintnuts_Init = 0x22AB2C + _LD_OFF;
	.patch_GetObjectEntry_EnHintnutsInit 0x22AB70 + _LD_OFF : { *(.patch_GetObjectEntry_EnHintnutsInit) }
	EnItem00_Draw = 0x22B6C0 + _LD_OFF;
	EnItem00_Update = 0x22B71C + _LD_OFF;
	.patch_Item00GiveCollectedItemDrop 0x22B974 + _LD_OFF : { *(.patch_Item00GiveCollectedItemDrop) }
	.patch_patch_ItemGiveBombchuDropTwo 0x22BAE4 + _LD_OFF : { *(.patch_ItemGiveBombchuDropTwo) }
	.patch_GetObjectEntry_EnNutsballInit 0x22DEC4 + _LD_OFF : { *(.patch_GetObjectEntry_EnNutsballInit) }
	EnShopnuts_Init = 0x22ED2C + _LD_OFF;
	.patch_BusinessScrubCheckFlags 0x22EE64 + _LD_OFF : { *(.patch_BusinessScrubCheckFlags) }
	EnTorch2_Update = 0x22F0C8 + _LD_OFF;
	.patch_DarkLinkPlayerRecoil 0x22F838 + _LD_OFF : { *(.patch_DarkLinkPlayerRecoil) }
	ObjMure3_Update = 0x2318AC + _LD_OFF;
	.patch_GanonCSEquipMS 0x2359A4 + _LD_OFF : { *(.patch_GanonCSEquipMS) }
	EnNiwLady_Action_2389EC = 0x2389EC + _LD_OFF;
	EnDntNomal_SetupTargetGivePrize = 0x2394CC + _LD_OFF;
	BgTreemouth_Init = 0x2412B4 + _LD_OFF;
	BgYdanSp_Update = 0x241EF8 + _LD_OFF;
	BossGanon_Update = 0x242A94 + _LD_OFF;
	DoorShutter_Init = 0x2453E0 + _LD_OFF;
	EnAnubice_Update = 0x246E58 + _LD_OFF;
	.patch_AnubisFlameCircleCheck 0x246F64 + _LD_OFF : { *(.patch_AnubisFlameCircleCheck) }
	.patch_RainbowChuTrailOne 0x247FC0 + _LD_OFF : { *(.patch_RainbowChuTrailOne) } /*Bombchus use 2 EffectBlure instances*/
	.patch_RainbowChuTrailTwo 0x2480A4 + _LD_OFF : { *(.patch_RainbowChuTrailTwo) } /*Bombchus use 2 EffectBlure instances*/
	.patch_EnExItemModelDraw 0x249C94 + _LD_OFF : { *(.patch_EnExItemModelDraw) }
	EnMThunder_Init = 0x24C910 + _LD_OFF;
	EnPoh_Update = 0x24D368 + _LD_OFF;
	.patch_RedeadCanFreezePlayer 0x24DC2C + _LD_OFF : { *(.patch_RedeadCanFreezePlayer) }
	.patch_SwordTrailDurationGrezzoFix 0x2507D0 + _LD_OFF : { *(.patch_SwordTrailDurationGrezzoFix) } /*duration is set to 6 due to framerate increase. NOP to allow custom duration*/
	.patch_MultiplyPlayerSpeed 0x251D34 + _LD_OFF : { *(.patch_MultiplyPlayerSpeed) }
	.patch_GameOverStart 0x252424 + _LD_OFF : { *(.patch_GameOverStart) }
	ItemBHeart_Init = 0x25375C + _LD_OFF;
	ItemBHeart_Destroy = 0x2537D4 + _LD_OFF;
	ItemOcarina_Init = 0x253818 + _LD_OFF;
	ItemOcarina_Destroy = 0x253A1C + _LD_OFF;
	OceffSpot_Update = 0x255BDC + _LD_OFF;
	OceffWipe_Update = 0x256158 + _LD_OFF;
	BgCheck_RaycastDown1 = 0x257054 + _LD_OFF;
	.patch_SkipDaruniaDanceThree 0x257F00 + _LD_OFF : { *(.patch_SkipDaruniaDanceThree) }
	.patch_LostWoodsTargetTimer 0x2592B8 + _LD_OFF : { *(.patch_LostWoodsTargetTimer) }
	.patch_LostWoodsShootingGame 0x259E4C + _LD_OFF : { *(.patch_LostWoodsShootingGame) }
	.patch_CanPlayBombchuBowlingOne 0x25A744 + _LD_OFF : { *(.patch_CanPlayBombchuBowlingOne) }
	EnDaiku_InitEscape = 0x25A8E4 + _LD_OFF;
	.patch_GanonDrawMasterSword 0x26207C + _LD_OFF : { *(.patch_GanonDrawMasterSword) }
	DemoEffect_Update = 0x262C58 + _LD_OFF;
	DemoKankyo_Update = 0x262EA4 + _LD_OFF;
	DoorGerudo_Update = 0x263118 + _LD_OFF;
	.patch_NaviNotifications 0x267E04 + _LD_OFF : { *(.patch_NaviNotifications) }
	EnEncount1_Update = 0x2682D0 + _LD_OFF;
	EnExRuppy_Update = 0x2689B8 + _LD_OFF;
	.patch_CheckGerudoToken_269884 0x269884 + _LD_OFF : { *(.patch_CheckGerudoToken_269884) }
	EnNutsball_Update = 0x26BD8C + _LD_OFF;
	.patch_MinuetLocation 0x26C388 + _LD_OFF : { *(.patch_MinuetLocation) }
	.patch_BoleroLocation 0x26C448 + _LD_OFF : { *(.patch_BoleroLocation) }
	EnTakaraMan_Init = 0x26DEB8 + _LD_OFF;
	EnYukabyun_Update = 0x26E628 + _LD_OFF;
	.patch_FlyingTileCollision 0x26E730 + _LD_OFF : { *(.patch_FlyingTileCollision) }
	.patch_DeadHandHandCanGrabPlayer 0x26EB58 + _LD_OFF : { *(.patch_DeadHandHandCanGrabPlayer) }
	ObjHamishi_Update = 0x26FD24 + _LD_OFF;
	.patch_RedBoulderExplode 0x26FE7C + _LD_OFF : { *(.patch_RedBoulderExplode) }
	OceffStorm_Update = 0x27112C + _LD_OFF;
	OceffWipe2_Update = 0x2714B8 + _LD_OFF;
	OceffWipe3_Update = 0x27181C + _LD_OFF;
	OceffWipe4_Update = 0x271C10 + _LD_OFF;
	.patch_MaskSalesmanGiveMaskOfTruth 0x271D48 + _LD_OFF : { *(.patch_MaskSalesmanGiveMaskOfTruth) }
	ItemEtcetera_Init = 0x273F28 + _LD_OFF;
	ItemEtcetera_Destroy = 0x2740BC + _LD_OFF;
	.patch_SongOfTimeJingle 0x274B1C + _LD_OFF : { *(.patch_SongOfTimeJingle) }
	.patch_DoorOfTimeCheck 0x274B68 + _LD_OFF : { *(.patch_DoorOfTimeCheck) }
	EnDaiku_EscapeRotate = 0x2754E4 + _LD_OFF;
	BgBdanSwitch_Init = 0x276508 + _LD_OFF;
	BgSpot12Saku_Init = 0x27AD6C + _LD_OFF;
	BossDodongo_Update = 0x27BE30 + _LD_OFF;
	.patch_ImpaInCourtyardCheckForVisitedZelda 0x27DEF8 + _LD_OFF : { *(.patch_ImpaInCourtyardCheckForVisitedZelda) }
	DoorShutter_Update = 0x27E6E0 + _LD_OFF;
	EnDntNomal_Update = 0x280510 + _LD_OFF;
	EnGanonOrgan_Init = 0x280E0C + _LD_OFF;
	EnPoh_UpdateDead = 0x282E88 + _LD_OFF;
	EnSyatekiMan_Init = 0x283F94 + _LD_OFF;
	ItemBHeart_Draw = 0x285BEC + _LD_OFF;
	ItemBHeart_Update = 0x285C18 + _LD_OFF;
	ItemOcarina_Draw = 0x285D48 + _LD_OFF;
	ObjOshihiki_Update = 0x286520 + _LD_OFF;
	.patch_GanonGiveMSMidFight 0x288030 + _LD_OFF : { *(.patch_GanonGiveMSMidFight) }
	.patch_AnjuGiveCojiro 0x2884F4 + _LD_OFF : { *(.patch_AnjuGiveCojiro) }
	.patch_SunsSongLocation 0x2888C8 + _LD_OFF : { *(.patch_SunsSongLocation) }
	.patch_PierreSoftlockFixTwo 0x288914 + _LD_OFF : { *(.patch_PierreSoftlockFixTwo) }
	.patch_PierreSoftlockFixThree 0x2889D4 + _LD_OFF : { *(.patch_PierreSoftlockFixThree) }
	.patch_KakarikoGateCheck 0x28A678 + _LD_OFF : { *(.patch_KakarikoGateCheck) }
	.patch_BombchuBowlingAlwaysFirstPrize 0x291924 + _LD_OFF : { *(.patch_BombchuBowlingAlwaysFirstPrize) }
	ItemEtcetera_Update = 0x298D88 + _LD_OFF;
	.patch_LostWoodsShootingGameTwo 0x2990E8 + _LD_OFF : { *(.patch_LostWoodsShootingGameTwo) }
	BgSpot12Saku_Update = 0x29E030 + _LD_OFF;
	.patch_Sheik_GetTextID 0x2A4B44 + _LD_OFF : { *(.patch_Sheik_GetTextID) }
	EnSyatekiMan_Update = 0x2A60BC + _LD_OFF;
	BgSpot01Idomizu_Init = 0x2AC704 + _LD_OFF;
	BgSpot01Idosoko_Init = 0x2AC7C8 + _LD_OFF;
	BgSpot06Objects_Destroy = 0x2AD1E4 + _LD_OFF;
	BgSpot15Rrbox_Update = 0x2AD484 + _LD_OFF;
	EnItem00_Collected = 0x2B175C + _LD_OFF;
	.patch_SerenadeCheckChestFlag 0x2B2544 + _LD_OFF : { *(.patch_SerenadeCheckChestFlag) }
	.patch_SerenadeLocation 0x2B2574 + _LD_OFF : { *(.patch_SerenadeLocation) }
	EnPeehat_StateAttackRecoil = 0x2B2CC0 + _LD_OFF;
	.patch_RainbowSwordTrail 0x2B9AD0 + _LD_OFF : { *(.patch_RainbowSwordTrail) }
	Model_GetMeshGroupCount = 0x2BB71C + _LD_OFF;
	.patch_OverrideTextID 0x2BC1C4 + _LD_OFF : { *(.patch_OverrideTextID) }
	.patch_OverrideItemID 0x2BC1D0 + _LD_OFF : { *(.patch_OverrideItemID) }
	.patch_NoSilverGauntletsCutsceneWarp 0x2BC2A0 + _LD_OFF : { *(.patch_NoSilverGauntletsCutsceneWarp) }
	.patch_RunAnimationSpeed 0x2BE70C + _LD_OFF : { *(.patch_RunAnimationSpeed) }
	.patch_FishingIgnoreTempBOne 0x2C3A10 + _LD_OFF : { *(.patch_FishingIgnoreTempBOne) }
	.patch_DoorOfTimeOpenCutscene 0x2C6218 + _LD_OFF : { *(.patch_DoorOfTimeOpenCutscene) }
	.patch_NoHealFromHealthUpgrades 0x2CD07C + _LD_OFF : { *(.patch_NoHealFromHealthUpgrades) }
	.patch_GetCustomMessageEntryOne 0x2CD3A4 + _LD_OFF : { *(.patch_GetCustomMessageEntryOne) }
	.patch_GetCustomMessageTextOne 0x2CD3EC + _LD_OFF : { *(.patch_GetCustomMessageTextOne) }
	Math_SinS = 0x2CFCA0 + _LD_OFF;
	Camera_CheckWater = 0x2D06A0 + _LD_OFF;
	.patch_ActorDraw 0x2D6310 + _LD_OFF : { *(.patch_ActorDraw) }
	.patch_OcarinaNoteSound_Player 0x2D6A04 + _LD_OFF : { *(.patch_OcarinaNoteSound_Player) }
	EffectSs_Delete = 0x2D6A50 + _LD_OFF;
	.patch_CamUpdate 0x2D84C8 + _LD_OFF : { *(.patch_CamUpdate) }
	.patch_CamRoll 0x2D88E4 + _LD_OFF : { *(.patch_CamRoll) }
	Message_GetText = 0x2DF4B0 + _LD_OFF;
	Message_GetEntry = 0x2DF4C4 + _LD_OFF;
	.patch_CheckForTextControlCode 0x2E0490 + _LD_OFF : { *(.patch_CheckForTextControlCode) }
	.patch_HandleTextControlCode 0x2E057C + _LD_OFF : { *(.patch_HandleTextControlCode) }
	Object_UpdateEntries = 0x2E4EA0 + _LD_OFF;
	.patch_SceneInitAfterCopyScenes 0x2EAFDC + _LD_OFF : { *(.patch_SceneInitAfterCopyScenes) }
	.patch_ChildCanOpenBowSubMenu 0x2EB2D8 + _LD_OFF : { *(.patch_ChildCanOpenBowSubMenu) }
	MenuSpritesManager_OffsetSpriteAt = 0x2EB3D8 + _LD_OFF;
	.patch_FileSelect_CopyFile 0x2EDA04 + _LD_OFF : { *(.patch_FileSelect_CopyFile) }
	.patch_CorrectCompassChests 0x2F161C + _LD_OFF : { *(.patch_CorrectCompassChests) }
	.patch_CorrectCompassChestsTwo 0x2F1770 + _LD_OFF : { *(.patch_CorrectCompassChestsTwo) }
	ZAR_Destroy = 0x2F70C4 + _LD_OFF;
	.patch_OverrideDrawItemOne 0x2F7498 + _LD_OFF : { *(.patch_OverrideDrawItemOne) }
	MenuSpritesManager_SetSpriteAt = 0x2F8D40 + _LD_OFF;
	MenuSpritesManager_RegisterItemSprite = 0x2F8D74 + _LD_OFF;
	.patch_OcarinaNoteButtonsDraw 0x2F9430 + _LD_OFF : { *(.patch_OcarinaNoteButtonsDraw) }
	.patch_SaveGame 0x2FBFA8 + _LD_OFF : { *(.patch_SaveGame) }
	SaveGame = 0x2FDAC8 + _LD_OFF;
	.patch_SaveFileSwordless 0x2FDCE4 + _LD_OFF : { *(.patch_SaveFileSwordless) }
	Message_UnkControlCodeHandler = 0x306318 + _LD_OFF;
	.patch_Gfx_Update 0x310254 + _LD_OFF : { *(.patch_Gfx_Update) }
	.patch_OverrideDrawItemTwo 0x3148A8 + _LD_OFF : { *(.patch_OverrideDrawItemTwo) }
	.patch_OoBBombchuOne 0x315120 + _LD_OFF : { *(.patch_OoBBombchuOne) }
	.patch_OoBBombchuTwo 0x31513C + _LD_OFF : { *(.patch_OoBBombchuTwo) }
	.patch_OoBBombchuThree 0x315150 + _LD_OFF : { *(.patch_OoBBombchuThree) }
	Inventory_ReplaceItem = 0x316CEC + _LD_OFF;
	.patch_CollisionATvsAC 0x3191B0 + _LD_OFF : { *(.patch_CollisionATvsAC) }
	ElfMessage_GetSariaText = 0x31C698 + _LD_OFF;
	.patch_ISGPutaway 0x32B4AC + _LD_OFF : { *(.patch_ISGPutaway) }
	Object_Spawn = 0x32E21C + _LD_OFF;
	Actor_WorldDistXYZToActor = 0x3306C4 + _LD_OFF;
	Camera_UpdateInterface = 0x330D84 + _LD_OFF;
	.patch_SetBGMEntrance 0x331048 + _LD_OFF : { *(.patch_SetBGMEntrance) }
	Flags_SetCollectible = 0x3329D8 + _LD_OFF;
	NockArrow = 0x33603C + _LD_OFF;
	.patch_NockArrow 0x33615C + _LD_OFF : { *(.patch_NockArrow) }
	.patch_DecreaseArrowCount 0x3362C4 + _LD_OFF : { *(.patch_DecreaseArrowCount) }
	.patch_SceneExitOverride 0x3366EC + _LD_OFF : { *(.patch_SceneExitOverride) }
	.patch_SceneExitDynamicOverride 0x33676C + _LD_OFF : { *(.patch_SceneExitDynamicOverride) }
	.patch_EnteredLocation 0x338DB8 + _LD_OFF : { *(.patch_EnteredLocation) }
	.patch_LostWoodsBridgeMusic 0x338DD8 + _LD_OFF : { *(.patch_LostWoodsBridgeMusic) }
	Math_CosS = 0x338F60 + _LD_OFF;
	.patch_GetObjectEntry_339DFC 0x339DFC + _LD_OFF : { *(.patch_GetObjectEntry_339DFC) }
	.patch_GetObjectEntry_33A950 0x33A950 + _LD_OFF : { *(.patch_GetObjectEntry_33A950) }
	.patch_GetObjectEntry_33AB24 0x33AB24 + _LD_OFF : { *(.patch_GetObjectEntry_33AB24) } /* Used for: chest ice trap smoke effect */
	Inventory_ChangeUpgrade = 0x33C730 + _LD_OFF;
	.patch_BiggoronDayCheck 0x33DCC0 + _LD_OFF : { *(.patch_BiggoronDayCheck) }
	.patch_FWandWarpSongTimerDepletion 0x33DE84 + _LD_OFF : { *(.patch_FWandWarpSongTimerDepletion) }
	SkelAnime_InitLink = 0x3413EC + _LD_OFF;
	.patch_RandomGsLoc_CustomTangibilityCheck 0x3415B0 + _LD_OFF : { *(.patch_RandomGsLoc_CustomTangibilityCheck) }
	.patch_MasterQuestGoldSkulltulaCheck 0x3415C8 + _LD_OFF : { *(.patch_MasterQuestGoldSkulltulaCheck) }
	.patch_TurboTextSignalNPC 0x3469F4 + _LD_OFF : { *(.patch_TurboTextSignalNPC) }
	Magic_Reset = 0x34708C + _LD_OFF;
	Player_SetEquipmentData = 0x34913C + _LD_OFF;
	.patch_FairyReviveHealAmount 0x34AF48 + _LD_OFF : { *(.patch_FairyReviveHealAmount) }
	Actor_SetFeetPos = 0x34CBB4 + _LD_OFF;
	EventSet = 0x34CBF8 + _LD_OFF;
	.patch_FishingIgnoreTempBTwo 0x34CFCC + _LD_OFF : { *(.patch_FishingIgnoreTempBTwo) }
	.patch_FWLoadSet 0x34D9E8 + _LD_OFF : { *(.patch_FWLoadSet) }
	Audio_RestoreBGM = 0x34EC14 + _LD_OFF;
	Effect_Delete = 0x34F0F4 + _LD_OFF;
	.patch_GetObjectEntry_34F270 0x34F270 + _LD_OFF : { *(.patch_GetObjectEntry_34F270) }
	SystemArena_Free = 0x34FC6C + _LD_OFF;
	.patch_GetObjectEntry_34FE68 0x34FE68 + _LD_OFF : { *(.patch_GetObjectEntry_34FE68) }
	SystemArena_Malloc = 0x35010C + _LD_OFF;
	SkelAnime_Free2 = 0x350BE0 + _LD_OFF;
	EventCheck = 0x350CF4 + _LD_OFF;
	.patch_FWGetSet 0x3519CC + _LD_OFF : { *(.patch_FWGetSet) }
	Health_ChangeBy = 0x352DBC + _LD_OFF;
	.patch_ApplyDamageMultiplier 0x352DC0 + _LD_OFF : { *(.patch_ApplyDamageMultiplier) }
	.patch_GetObjectEntry_352F28 0x352F28 + _LD_OFF : { *(.patch_GetObjectEntry_352F28) } /* Used for: Flare Dancer */
	.patch_GetObjectEntry_353CE4 0x353CE4 + _LD_OFF : { *(.patch_GetObjectEntry_353CE4) }
	Collider_SetCylinder = 0x353D24 + _LD_OFF;
	Collider_InitCylinder = 0x353DD0 + _LD_OFF;
	SetupItemInWater = 0x354894 + _LD_OFF;
	.patch_FastChests 0x354CD4 + _LD_OFF : { *(.patch_FastChests) }
	.patch_AboutToPickUpActor 0x354DD8 + _LD_OFF : { *(.patch_AboutToPickUpActor) }
	.patch_MasterSwordTimerCheck 0x354DFC + _LD_OFF : { *(.patch_MasterSwordTimerCheck) }
	Camera_BGCheckInfo = 0x3553FC + _LD_OFF;
	.patch_LikeLikeNeverEatTunic 0x355C2C + _LD_OFF : { *(.patch_LikeLikeNeverEatTunic) }
	DeleteModel_At = 0x357248 + _LD_OFF;
	ZAR_GetCMBByIndex = 0x358EF8 + _LD_OFF;
	BossChallenge_IsActive = 0x35B164 + _LD_OFF;
	.patch_Audio_PlayFanfare 0x35C528 + _LD_OFF : { *(.patch_Audio_PlayFanfare) }
	Audio_PlayFanfare = 0x35C528 + _LD_OFF;
	LinkDamage = 0x35D304 + _LD_OFF;
	FireDamage = 0x35D8D8 + _LD_OFF;
	Player_InBlockingCsMode = 0x35DB20 + _LD_OFF;
	SkelAnime_DrawOpa = 0x35E240 + _LD_OFF;
	.patch_ConvertBombDropOne 0x35E46C + _LD_OFF : { *(.patch_ConvertBombDropOne) }
	WaterBox_GetSurfaceImpl = 0x35E8A0 + _LD_OFF;
	.patch_SkullwalltulaAttack_35F328 0x35F328 + _LD_OFF : { *(.patch_SkullwalltulaAttack_35F328) }
	.patch_SkullwalltulaTargetRotation 0x35F828 + _LD_OFF : { *(.patch_SkullwalltulaTargetRotation) }
	.patch_SkullwalltulaAttack_35F834 0x35F834 + _LD_OFF : { *(.patch_SkullwalltulaAttack_35F834) }
	LinkAnimation_PlayOnce = 0x3604F0 + _LD_OFF;
	.patch_ISGCrouchStab 0x360690 + _LD_OFF : { *(.patch_ISGCrouchStab) }
	.patch_ForceTrailEffectUpdate 0x362108 + _LD_OFF : { *(.patch_ForceTrailEffectUpdate) } /*EffectBlure_AddVertex*/
	Actor_GetScreenPos = 0x363A20 + _LD_OFF;
	Object_GetSlot = 0x363C10 + _LD_OFF;
	.patch_ExtendObjectGetSlot 0x363CB4 + _LD_OFF : { *(.patch_ExtendObjectGetSlot) }
	Flags_GetCollectible = 0x36405C + _LD_OFF;
	EffectSsDeadDb_Spawn = 0x3642F4 + _LD_OFF;
	Audio_SetBGM = 0x3655D0 + _LD_OFF;
	.patch_StalchildDespawn_366338 0x366338 + _LD_OFF : { *(.patch_StalchildDespawn_366338) }
	Audio_GetActiveSeqId = 0x366684 + _LD_OFF;
	Flags_SetEnv = 0x366704 + _LD_OFF;
	Actor_SetModelMatrix = 0x3679D0 + _LD_OFF;
	DisplayTextbox = 0x367C7C + _LD_OFF;
	SkeletonAnimationModel_SetMesh = 0x369178 + _LD_OFF;
	Model_DisableMeshGroupByIndex = 0x36932C + _LD_OFF;
	Actor_FindNearby = 0x369334 + _LD_OFF;
	PauseContext_GetState = 0x3695F8 + _LD_OFF;
	BgCheck_EntityLineTest1 = 0x369F9C + _LD_OFF;
	Player_InCsMode = 0x36A7A0 + _LD_OFF;
	SkeletonAnimationModel_Spawn = 0x36A924 + _LD_OFF;
	.patch_GetObjectEntry_36A96C 0x36A96C + _LD_OFF : { *(.patch_GetObjectEntry_36A96C) } /* Used for: freestanding item models */
	Animation_GetLastFrame = 0x36AE14 + _LD_OFF;
	.patch_IgnoreMaskReaction 0x36BBC4 + _LD_OFF : { *(.patch_IgnoreMaskReaction) }
	Flags_UnsetSwitch = 0x36BEAC + _LD_OFF;
	Matrix_Multiply = 0x36C174 + _LD_OFF;
	Flags_GetClear = 0x36CF6C + _LD_OFF;
	Math_Vec3f_DistXZ = 0x36D260 + _LD_OFF;
	Math_SmoothStepToF = 0x36E168 + _LD_OFF;
	Flags_GetSwitch = 0x36E864 + _LD_OFF;
	Flags_SetClear = 0x36EC14 + _LD_OFF;
	.patch_SetBGMEvent 0x36EC40 + _LD_OFF : { *(.patch_SetBGMEvent) }
	SetEventBGM = 0x36EC40 + _LD_OFF;
	Player_GetMask = 0x36EF98 + _LD_OFF;
	SetNextEntrance = 0x3716F0 + _LD_OFF;
	Actor_HasParent = 0x371E40 + _LD_OFF;
	Matrix_UpdatePosition = 0x372070 + _LD_OFF;
	.patch_DemoEffectMedallionDraw 0x37214C + _LD_OFF : { *(.patch_DemoEffectMedallionDraw) }
	SkeletonAnimationModel_Draw = 0x372170 + _LD_OFF;
	SkeletonAnimationModel_MatrixCopy = 0x3721E0 + _LD_OFF;
	Actor_OfferGetItem = 0x3724DC + _LD_OFF;
	.patch_IncomingGetItemID 0x3725AC + _LD_OFF : { *(.patch_IncomingGetItemID) }
	Message_CloseTextbox = 0x3725E0 + _LD_OFF;
	Model_EnableMeshGroupByIndex = 0x37266C + _LD_OFF;
	.patch_Model_EnableMeshGroupByIndex 0x372670 + _LD_OFF : { *(.patch_Model_EnableMeshGroupByIndex) }
	.patch_MaskSalesmanCheckNoMaskOne 0x372B64 + _LD_OFF : { *(.patch_MaskSalesmanCheckNoMaskOne) }
	.patch_MaskSalesmanCheckNoMaskTwo 0x372B70 + _LD_OFF : { *(.patch_MaskSalesmanCheckNoMaskTwo) }
	ActorShape_Init = 0x372D4C + _LD_OFF;
	Actor_Find = 0x372D64 + _LD_OFF;
	TexAnim_Spawn = 0x372D94 + _LD_OFF;
	ZAR_GetCMABByIndex = 0x372F0C + _LD_OFF;
	SkeletonAnimationModel_SpawnAt = 0x372F38 + _LD_OFF;
	.patch_GetObjectEntry_372F7C 0x372F7C + _LD_OFF : { *(.patch_GetObjectEntry_372F7C) }
	.patch_OverrideObjectIsLoaded 0x373074 + _LD_OFF : { *(.patch_OverrideObjectIsLoaded) }
	EnWonderTalk_Update = 0x3731F4 + _LD_OFF;
	Actor_Spawn = 0x3738D0 + _LD_OFF;
	.patch_ConvertBombDropTwo 0x3747A4 + _LD_OFF : { *(.patch_ConvertBombDropTwo) }
	.patch_SetSFX 0x37547C + _LD_OFF : { *(.patch_SetSFX) }
	Audio_PlaySfxGeneral = 0x37547C + _LD_OFF;
	Math_SmoothStepToS = 0x375A18 + _LD_OFF;
	Enemy_StartFinishingBlow = 0x375B70 + _LD_OFF;
	Audio_PlayActorSfx2 = 0x375BCC + _LD_OFF;
	Animation_Change = 0x375C08 + _LD_OFF;
	Flags_SetSwitch = 0x375C10 + _LD_OFF;
	CollisionCheck_SetAC = 0x376168 + _LD_OFF;
	.patch_CollisionCheck_SetAC_Once 0x376174 + _LD_OFF : { *(.patch_CollisionCheck_SetAC_Once) }
	.patch_CollisionCheck_SetAT_Once 0x3761FC + _LD_OFF : { *(.patch_CollisionCheck_SetAT_Once) }
	CollisionCheck_SetOC = 0x3762A4 + _LD_OFF;
	.patch_CollisionCheck_SetOC_Once 0x3762B0 + _LD_OFF : { *(.patch_CollisionCheck_SetOC_Once) }
	Collider_UpdateCylinder = 0x37632C + _LD_OFF;
	Actor_UpdateBgCheckInfo = 0x376340 + _LD_OFF;
	EnDns_ChangeAnim = 0x37693C + _LD_OFF;
	Message_GetState = 0x3769D8 + _LD_OFF;
	Rupees_ChangeBy = 0x376A60 + _LD_OFF;
	Item_Give = 0x376A78 + _LD_OFF;
	.patch_GKSetDurability 0x376BDC + _LD_OFF : { *(.patch_GKSetDurability) }
	.patch_GiantsKnifeWithoutKokiriSword 0x376BEC + _LD_OFF : { *(.patch_GiantsKnifeWithoutKokiriSword) }
	.patch_GiveItemMasterSword 0x376C18 + _LD_OFF : { *(.patch_GiveItemMasterSword) }
	.patch_NoLensOfTruthNaviText 0x37798C + _LD_OFF : { *(.patch_NoLensOfTruthNaviText) }
	Inventory_HasEmptyBottle = 0x377A04 + _LD_OFF;
	.patch_AltHeadersCommand 0x379020 + _LD_OFF : { *(.patch_AltHeadersCommand) }
	EnWonderTalk2_Update = 0x3794EC + _LD_OFF;
	Actor_KillAllWithMissingObject = 0x379C3C + _LD_OFF;
	BgSpot02Objects_Update = 0x3831AC + _LD_OFF;
	BgSpot06Objects_Update = 0x3833F8 + _LD_OFF;
	.patch_FrogRewardPurple 0x3898F0 + _LD_OFF : { *(.patch_FrogRewardPurple) }
	.patch_FrogReward 0x38992C + _LD_OFF : { *(.patch_FrogReward) }
	.patch_ChildShootingGallery 0x38AB70 + _LD_OFF : { *(.patch_ChildShootingGallery) }
	.patch_AdultShootingGallery 0x38ABA0 + _LD_OFF : { *(.patch_AdultShootingGallery) }
	BgSpot00Hanebasi_Update = 0x38B390 + _LD_OFF;
	.patch_SariasSongHintsOne 0x390620 + _LD_OFF : { *(.patch_SariasSongHintsOne) }
	.patch_SariasSongHintsTwo 0x39073C + _LD_OFF : { *(.patch_SariasSongHintsTwo) }
	EnPeehat_Larva_StateSeekPlayer = 0x391588 + _LD_OFF;
	.patch_PeahatLarvaGroundCheck 0x391740 + _LD_OFF : { *(.patch_PeahatLarvaGroundCheck) }
	EnTest_Wait = 0x39D8CC + _LD_OFF;
	.patch_OcarinaMinigameEndAfterWin 0x39DF38 + _LD_OFF : { *(.patch_OcarinaMinigameEndAfterWin) }
	.patch_LullabyLocation 0x3A0A7C + _LD_OFF : { *(.patch_LullabyLocation) }
	.patch_OverrideDrawItemThree 0x3A0EA8 + _LD_OFF : { *(.patch_OverrideDrawItemThree) }
	.patch_AfterInvalidatingRoomObjects 0x3A7698 + _LD_OFF : { *(.patch_AfterInvalidatingRoomObjects) }
	.patch_AfterObjectListCommand 0x3A7708 + _LD_OFF : { *(.patch_AfterObjectListCommand) }
	EnFdFire_Disappear = 0x3ABFB8 + _LD_OFF;
	.patch_KokiriCheckOpenForest 0x3ACCFC + _LD_OFF : { *(.patch_KokiriCheckOpenForest) }
	EnFd_JumpToGround = 0x3ACD84 + _LD_OFF;
	.patch_TokenNoItemGive2 0x3AD270 + _LD_OFF : { *(.patch_TokenNoItemGive2) }
	.patch_GetToken2 0x3AD2F0 + _LD_OFF : { *(.patch_GetToken2) }
	.patch_TokenNoItemGive1 0x3ADD68 + _LD_OFF : { *(.patch_TokenNoItemGive1) }
	.patch_GetToken1 0x3ADDE4 + _LD_OFF : { *(.patch_GetToken1) }
	.patch_TalonGetCastleTextbox 0x3AE6E8 + _LD_OFF : { *(.patch_TalonGetCastleTextbox) }
	.patch_GerudoArcheryOne 0x3AFA34 + _LD_OFF : { *(.patch_GerudoArcheryOne) }
	EnHs_ActionAfterTradeCojiro = 0x3B02C0 + _LD_OFF;
	.patch_ShabomAfterDamagePlayer 0x3B5060 + _LD_OFF : { *(.patch_ShabomAfterDamagePlayer) }
	EnBubble_Disappear = 0x3B5190 + _LD_OFF;
	EnDodojr_DropItem = 0x3B7C64 + _LD_OFF;
	.patch_BabyDodongoWallCheck 0x3B833C + _LD_OFF : { *(.patch_BabyDodongoWallCheck) }
	EnSw_GoldSkulltulaDeath = 0x3B91BC + _LD_OFF;
	.patch_RandomGsLoc_CustomTokenSpawnOffset 0x3B94C4 + _LD_OFF : { *(.patch_RandomGsLoc_CustomTokenSpawnOffset) }
	EnYukabyun_Levitate = 0x3B9E3C + _LD_OFF;
	ObjLift_Fall = 0x3BB7BC + _LD_OFF;
	.patch_RandomGsLoc_BlockSpawn_Crate 0x3BCA68 + _LD_OFF : { *(.patch_RandomGsLoc_BlockSpawn_Crate) }
	.patch_MovableBlockCooldownTimer 0x3BD46C + _LD_OFF : { *(.patch_MovableBlockCooldownTimer) }
	.patch_MovableBlockSpeed 0x3BD508 + _LD_OFF : { *(.patch_MovableBlockSpeed) }
	.patch_MilkCrateCooldownTimer 0x3BD85C + _LD_OFF : { *(.patch_MilkCrateCooldownTimer) }
	.patch_MilkCrateSpeed 0x3BD88C + _LD_OFF : { *(.patch_MilkCrateSpeed) }
	.patch_RandomGsLoc_BlockSpawn_Soil 0x3BF690 + _LD_OFF : { *(.patch_RandomGsLoc_BlockSpawn_Soil) }
	.patch_ForestTempleBasementPuzzleDelay 0x3BFA8C + _LD_OFF : { *(.patch_ForestTempleBasementPuzzleDelay) }
	ObjLift_Wait = 0x3C05B0 + _LD_OFF;
	EnSw_SetupGoingHome = 0x3C2A50 + _LD_OFF;
	.patch_GerudoArcheryTwo 0x3C2D80 + _LD_OFF : { *(.patch_GerudoArcheryTwo) }
	.patch_DampeCheckCanDig1 0x3C3354 + _LD_OFF : { *(.patch_DampeCheckCanDig1) }
	.patch_DampeRollHigh 0x3C3418 + _LD_OFF : { *(.patch_DampeRollHigh) }
	.patch_DampeCheckRewardFlag 0x3C3598 + _LD_OFF : { *(.patch_DampeCheckRewardFlag) }
	.patch_DampeCheckCanDig2 0x3C35D0 + _LD_OFF : { *(.patch_DampeCheckCanDig2) }
	.patch_SongOfTimeLocation 0x3C375C + _LD_OFF : { *(.patch_SongOfTimeLocation) }
	EnDns_Burrow = 0x3C3C04 + _LD_OFF;
	.patch_EponasSongLocation 0x3C6194 + _LD_OFF : { *(.patch_EponasSongLocation) }
	.patch_MalonNextAction 0x3C6210 + _LD_OFF : { *(.patch_MalonNextAction) }
	EnIshi_LiftedUp = 0x3CBAC4 + _LD_OFF;
	EnSw_WalltulaIdle = 0x3CDAAC + _LD_OFF;
	.patch_BombPurchaseableCheck 0x3CE800 + _LD_OFF : { *(.patch_BombPurchaseableCheck) }
	EnDns_Sale = 0x3CE92C + _LD_OFF;
	.patch_ScrubStickUpgradeTwo 0x3CE990 + _LD_OFF : { *(.patch_ScrubStickUpgradeTwo) }
	.patch_ScrubNutUpgradeTwo 0x3CE9DC + _LD_OFF : { *(.patch_ScrubNutUpgradeTwo) }
	EnDns_PostBurrow = 0x3CEA64 + _LD_OFF;
	EnSi_DestroyAfterText = 0x3D0544 + _LD_OFF;
	EnDodojr_JumpAttackBounce = 0x3D069C + _LD_OFF;
	.patch_GrannySetRewardFlag 0x3D0E34 + _LD_OFF : { *(.patch_GrannySetRewardFlag) }
	.patch_GrannyItemOverrideTwo 0x3D0E60 + _LD_OFF : { *(.patch_GrannyItemOverrideTwo) }
	.patch_MidoCheckDekuTreeClearFour 0x3D2C18 + _LD_OFF : { *(.patch_MidoCheckDekuTreeClearFour) }
	EnReeba_Die = 0x3D4CB0 + _LD_OFF;
	.patch_LeeverAfterDie 0x3D4E10 + _LD_OFF : { *(.patch_LeeverAfterDie) }
	.patch_LeeverAfterSink 0x3D6188 + _LD_OFF : { *(.patch_LeeverAfterSink) }
	BossDodongo_DeathCutscene = 0x3DA7AC + _LD_OFF;
	.patch_LeeverSandCheck_Small 0x3DE2A0 + _LD_OFF : { *(.patch_LeeverSandCheck_Small) }
	.patch_ShadowShip_Speed 0x3DFB30 + _LD_OFF : { *(.patch_ShadowShip_Speed) }
	.patch_FireBlockSpeed 0x3E0BB4 + _LD_OFF : { *(.patch_FireBlockSpeed) }
	EnDodongo_Idle = 0x3E4FE8 + _LD_OFF;
	.patch_FreeScarecrow 0x3E55A8 + _LD_OFF : { *(.patch_FreeScarecrow) }
	.patch_MasterSwordAlwaysDrop 0x3E5E98 + _LD_OFF : { *(.patch_MasterSwordAlwaysDrop) }
	.patch_PickUpMasterSword 0x3E5EC8 + _LD_OFF : { *(.patch_PickUpMasterSword) }
	.patch_SkipMasterSwordFanfare 0x3E5F60 + _LD_OFF : { *(.patch_SkipMasterSwordFanfare) }
	EnYukabyun_Wait = 0x3E6880 + _LD_OFF;
	.patch_ShadowShip_CSTimer 0x3E6C50 + _LD_OFF : { *(.patch_ShadowShip_CSTimer) }
	EnTuboTrap_WaitForProximity = 0x3E6F88 + _LD_OFF;
	.patch_FlyingPotDontChangeCategory 0x3E7008 + _LD_OFF : { *(.patch_FlyingPotDontChangeCategory) }
	.patch_FairyReward 0x3E7598 + _LD_OFF : { *(.patch_FairyReward) }
	.patch_RainbowBridge 0x3E7CAC + _LD_OFF : { *(.patch_RainbowBridge) }
	.patch_RemoveWaterfallCS 0x3E7F64 + _LD_OFF : { *(.patch_RemoveWaterfallCS) }
	.patch_DekuTheaterSkullMask 0x3EAF38 + _LD_OFF : { *(.patch_DekuTheaterSkullMask) }
	EnDoor_Open = 0x3EC04C + _LD_OFF;
	.patch_CowItemOverride 0x3EE378 + _LD_OFF : { *(.patch_CowItemOverride) }
	DoorGerudo_Unlocking = 0x3EEE38 + _LD_OFF;
	DoorShutter_SlidingDoor_Open = 0x3EEE7C + _LD_OFF;
	.patch_CowBottleCheck 0x3F065C + _LD_OFF : { *(.patch_CowBottleCheck) }
	.patch_CarpetSalesmanCheckFlagOne 0x3F0A18 + _LD_OFF : { *(.patch_CarpetSalesmanCheckFlagOne) }
	.patch_CarpetSalesmanCheckFlagTwo 0x3F0A64 + _LD_OFF : { *(.patch_CarpetSalesmanCheckFlagTwo) }
	.patch_LabScientistIgnoreEyedropsInInventory 0x3F0B44 + _LD_OFF : { *(.patch_LabScientistIgnoreEyedropsInInventory) }
	.patch_FastChestsTwo 0x3F1048 + _LD_OFF : { *(.patch_FastChestsTwo) }
	EnDoor_Idle = 0x3F1B28 + _LD_OFF;
	.patch_HandleDoorDestroyCustomModels 0x3F1B88 + _LD_OFF : { *(.patch_HandleDoorDestroyCustomModels) }
	.patch_OverrideGrottoActorEntrance 0x3F2254 + _LD_OFF : { *(.patch_OverrideGrottoActorEntrance) }
	.patch_FireArrowRequirement 0x3F23AC + _LD_OFF : { *(.patch_FireArrowRequirement) }
	.patch_FireArrowCheckChestFlagOne 0x3F23FC + _LD_OFF : { *(.patch_FireArrowCheckChestFlagOne) }
	.patch_FireArrowCheckChestFlagTwo 0x3F2448 + _LD_OFF : { *(.patch_FireArrowCheckChestFlagTwo) }
	.patch_LinkReflection 0x3F2F0C + _LD_OFF : { *(.patch_LinkReflection) }
	DoorGerudo_Idle = 0x3F3FA0 + _LD_OFF;
	DoorShutter_SlidingDoor_Idle = 0x3F4A3C + _LD_OFF;
	.patch_SlidingDoorDestroyCustomModels 0x3F4A70 + _LD_OFF : { *(.patch_SlidingDoorDestroyCustomModels) }
	.patch_ChildBlueWarpOverride 0x3F5774 + _LD_OFF : { *(.patch_ChildBlueWarpOverride) }
	BgIceShelter_Melt = 0x3F5F00 + _LD_OFF;
	.patch_CarpetSalesmanSetFlag 0x3F9550 + _LD_OFF : { *(.patch_CarpetSalesmanSetFlag) }
	.patch_PreSwapBuffers 0x3FD384 + _LD_OFF : { *(.patch_PreSwapBuffers) }
	.patch_AwakeCallback 0x3FD43C + _LD_OFF : { *(.patch_AwakeCallback) }
	.patch_SleepQueryCallback 0x3FD6C4 + _LD_OFF : { *(.patch_SleepQueryCallback) }
	Message_SetInstantText = 0x40B608 + _LD_OFF;

	/* 0x419E18 - 0x41A143 : Language related function, don't place anything in this range */
	/* 0x41A144 */ _LD_OFF = _LD_EUR ? 0x24 : _LD_OFF;

	.patch_OcarinaNoteButtonsPress 0x41AAAC + _LD_OFF : { *(.patch_OcarinaNoteButtonsPress) }
	.patch_CurseTrapDizzyStick 0x41AB24 + _LD_OFF : { *(.patch_CurseTrapDizzyStick) }
	.patch_CurseTrapDizzyButtons 0x41ABD0 + _LD_OFF : { *(.patch_CurseTrapDizzyButtons) }
	.patch_PermadeathSkipMenu 0x41C980 + _LD_OFF : { *(.patch_PermadeathSkipMenu) }
	.patch_SaveMenuIgnoreOpen 0x42EC00 + _LD_OFF : { *(.patch_SaveMenuIgnoreOpen) }
	.patch_ItemsMenuDraw 0x434C08 + _LD_OFF : { *(.patch_ItemsMenuDraw) }
	.patch_PlayInit 0x4352F4 + _LD_OFF : { *(.patch_PlayInit) }

	/* 0x436690 */ _LD_OFF = _LD_EUR ? 0x20 : _LD_OFF;

	.patch_GearMenuEmptySlot 0x438C00 + _LD_OFF : { *(.patch_GearMenuEmptySlot) }
	.patch_DrawHeartIcon 0x444368 + _LD_OFF : { *(.patch_DrawHeartIcon) }
	SaveFile_Delete = 0x446FC4 + _LD_OFF;
	.patch_BeforeLoadGame 0x447380 + _LD_OFF : { *(.patch_BeforeLoadGame) }
	ret_BeforeLoadGame = 0x447384 + _LD_OFF;
	.patch_DontSetMotionSetting 0x447410 + _LD_OFF : { *(.patch_DontSetMotionSetting) }
	.patch_OverrideFogDuringGameplayInit 0x4485B4 + _LD_OFF : { *(.patch_OverrideFogDuringGameplayInit) }
	.patch_CheckForWeirdEggHatchGameplayInit 0x448A64 + _LD_OFF : { *(.patch_CheckForWeirdEggHatchGameplayInit) }
	.patch_CheckForPocketCuccoHatchGameplayInit 0x448A80 + _LD_OFF : { *(.patch_CheckForPocketCuccoHatchGameplayInit) }
	.patch_InitSceneMirrorWorld 0x4490DC + _LD_OFF : { *(.patch_InitSceneMirrorWorld) }
	.patch_InitSceneEntranceOverride 0x449190 + _LD_OFF : { *(.patch_InitSceneEntranceOverride) }
	.patch_InitSceneClearExtendedObjects 0x449218 + _LD_OFF : { *(.patch_InitSceneClearExtendedObjects) }
	.patch_SaveFile_Init 0x449A04 + _LD_OFF : { *(.patch_SaveFile_Init) }
	.patch_SavewarpSetRespawnFlag 0x449E40 + _LD_OFF : { *(.patch_SavewarpSetRespawnFlag) }
	.patch_Multiplayer_OnLoadFile 0x449EFC + _LD_OFF : { *(.patch_Multiplayer_OnLoadFile) }
	.patch_AfterLoadGame 0x449F00 + _LD_OFF : { *(.patch_AfterLoadGame) }
	.patch_GetCustomMessageEntryTwo 0x44D564 + _LD_OFF : { *(.patch_GetCustomMessageEntryTwo) }
	.patch_GetCustomMessageTextTwo 0x44D5A4 + _LD_OFF : { *(.patch_GetCustomMessageTextTwo) }
	.patch_GameplayDestroy 0x44E294 + _LD_OFF : { *(.patch_GameplayDestroy) }
	.patch_ExtendedObjectClear 0x44E758 + _LD_OFF : { 	*(.patch_ExtendedObjectClear) }
	.patch_Multiplayer_UpdatePrevActorFlags 0x44E878 + _LD_OFF : { *(.patch_Multiplayer_UpdatePrevActorFlags) }
	.patch_PlayEntranceCutscene 0x44F030 + _LD_OFF : { *(.patch_PlayEntranceCutscene) }
	.patch_RequiemLocation 0x44F104 + _LD_OFF : { *(.patch_RequiemLocation) }
	.patch_NocturneLocation 0x44F12C + _LD_OFF : { *(.patch_NocturneLocation) }
	ret_NocturneLocation = 0x44F180 + _LD_OFF;
	.patch_SariasGift 0x44F188 + _LD_OFF : { *(.patch_SariasGift) }
	.patch_LACSConditionOne 0x44F1D4 + _LD_OFF : { *(.patch_LACSConditionOne) }
	.patch_LACSConditionTwo 0x44F20C + _LD_OFF : { *(.patch_LACSConditionTwo) }
	.patch_BossChallenge_Enter 0x44F634 + _LD_OFF : { *(.patch_BossChallenge_Enter) }
	.patch_SetSavewarpEntrance 0x44FBE4 + _LD_OFF : { *(.patch_SetSavewarpEntrance) }
	ret_SetSavewarpEntrance = 0x44FCE0 + _LD_OFF;
	.patch_LullabyCheckFlag 0x44FD54 + _LD_OFF : { *(.patch_LullabyCheckFlag) }
	.patch_LoadFileSwordless 0x44FD98 + _LD_OFF : { *(.patch_LoadFileSwordless) }
	.patch_OpenSaveDontSpoilTradeItems 0x44FDF8 + _LD_OFF : { *(.patch_OpenSaveDontSpoilTradeItems) }
	ret_OpenSaveDontSpoilTradeItems = 0x44FEB8 + _LD_OFF;
	.patch_OnActorSetup_SceneChange 0x452250 + _LD_OFF : { *(.patch_OnActorSetup_SceneChange) }
	ret_OnActorSetup_SceneChange = 0x4522A4 + _LD_OFF;
	.patch_AfterActorSetup_SceneChange 0x4522B8 + _LD_OFF : { *(.patch_AfterActorSetup_SceneChange) }
	.patch_before_GlobalContext_Update 0x452390 + _LD_OFF : { *(.patch_before_GlobalContext_Update) }
	.patch_after_GlobalContext_Update 0x452434 + _LD_OFF : { *(.patch_after_GlobalContext_Update) }
	.patch_FixItemsMenuSlotDuplication 0x456B90 + _LD_OFF : { *(.patch_FixItemsMenuSlotDuplication) }
	ret_FixItemsMenuSlotDuplication = 0x456B94 + _LD_OFF;
	.patch_GameOverDontSpoilTradeItems 0x458BE0 + _LD_OFF : { *(.patch_GameOverDontSpoilTradeItems) }
	ret_GameOverDontSpoilTradeItems = 0x458CA0 + _LD_OFF;
	.patch_DeathHandleBButton 0x458CA8 + _LD_OFF : { *(.patch_DeathHandleBButton) }
	.patch_PermadeathForceQuit 0x458E20 + _LD_OFF : { *(.patch_PermadeathForceQuit) }
	.patch_SetGameOverEntrance 0x458E3C + _LD_OFF : { *(.patch_SetGameOverEntrance) }
	ret_SetGameOverEntrance = 0x458EC8 + _LD_OFF;
	.patch_SetGameOverRespawnFlag 0x458EF0 + _LD_OFF : { *(.patch_SetGameOverRespawnFlag) }
	ret_PermadeathForceQuit = 0x458FF4 + _LD_OFF;
	.patch_InterfaceDrawDontSpoilTradeItems 0x45A17C + _LD_OFF : { *(.patch_InterfaceDrawDontSpoilTradeItems) }
	ret_InterfaceDrawDontSpoilTradeItems = 0x45A210 + _LD_OFF;
	.patch_TimerExpiration 0x45A948 + _LD_OFF : { *(.patch_TimerExpiration) }
	.patch_Timer2TickSound 0x45A9B4 + _LD_OFF : { *(.patch_Timer2TickSound) }
	.patch_SunsSongEndCloseTextbox 0x45B514 + _LD_OFF : { *(.patch_SunsSongEndCloseTextbox) }
	ret_SunsSongEndCloseTextbox = 0x45B518 + _LD_OFF;
	.patch_SetSunsSongRespawnFlag 0x45B660 + _LD_OFF : { *(.patch_SetSunsSongRespawnFlag) }
	.patch_BossChallenge_ExitMenu 0x45CCA4 + _LD_OFF : { *(.patch_BossChallenge_ExitMenu) }
	.patch_StoreChildBButtonEquip 0x45F20C + _LD_OFF : { *(.patch_StoreChildBButtonEquip) }
	ret_StoreChildBButtonEquip = 0x45F210 + _LD_OFF;
	.patch_BecomeAdult 0x45F230 + _LD_OFF : { *(.patch_BecomeAdult) }
	.patch_AlwaysRestoreChildEquips 0x45F3B0 + _LD_OFF : { *(.patch_AlwaysRestoreChildEquips) }
	.patch_ChildDontEquipSwordSlotByDefault 0x45F49C + _LD_OFF : { *(.patch_ChildDontEquipSwordSlotByDefault) }
	Object_Clear = 0x45FDA0 + _LD_OFF;
	.patch_OnActorSetup_RoomChange 0x4613C4 + _LD_OFF : { *(.patch_OnActorSetup_RoomChange) }
	ret_OnActorSetup_RoomChange = 0x461424 + _LD_OFF;
	.patch_AfterActorSetup_RoomChange 0x461434 + _LD_OFF : { *(.patch_AfterActorSetup_RoomChange) }
	.patch_FixActorKillLoop 0x4615E0 + _LD_OFF : { *(.patch_FixActorKillLoop) }
	.patch_ActorUpdate 0x461790 + _LD_OFF : { *(.patch_ActorUpdate) }
	.patch_TitleCardUpdate 0x4618B8 + _LD_OFF : { *(.patch_TitleCardUpdate) }
	.patch_ItemsMenuNumSprites 0x46B758 + _LD_OFF : { *(.patch_ItemsMenuNumSprites) }
	.patch_CheckForWeirdEggHatchKankyo 0x470D00 + _LD_OFF : { *(.patch_CheckForWeirdEggHatchKankyo) }
	.patch_CheckForPocketCuccoHatchKankyo 0x470D1C + _LD_OFF : { *(.patch_CheckForPocketCuccoHatchKankyo) }
	.patch_CriticalHealthCheckOne 0x4715B8 + _LD_OFF : { *(.patch_CriticalHealthCheckOne) }
	.patch_CriticalHealthCheckTwo 0x4716D4 + _LD_OFF : { *(.patch_CriticalHealthCheckTwo) }
	.patch_EnableFW 0x476D1C + _LD_OFF : { *(.patch_EnableFW) }
	.patch_OcarinaNoteSound_Npc 0x477C08 + _LD_OFF : { *(.patch_OcarinaNoteSound_Npc) }
	Quake_Update = 0x4787C8 + _LD_OFF;
	TitleCard_Update = 0x47953C + _LD_OFF;
	.patch_StoreTargetActorType 0x479984 + _LD_OFF : { *(.patch_StoreTargetActorType) }
	.patch_TargetReticleColor 0x47B284 + _LD_OFF : { *(.patch_TargetReticleColor) }
	ret_TargetReticleColor = 0x47B2E8 + _LD_OFF;
	.patch_TargetPointerColor 0x47BAE8 + _LD_OFF : { *(.patch_TargetPointerColor) }
	ret_TargetPointerColor = 0x47BB30 + _LD_OFF;
	Camera_GetCamDataId = 0x47BFD8 + _LD_OFF;
	.patch_FWKeepWarpPoint 0x47C3C0 + _LD_OFF : { *(.patch_FWKeepWarpPoint) }
	.patch_TurboTextAdvance 0x480928 + _LD_OFF : { *(.patch_TurboTextAdvance) }
	.patch_SetBGMDayNight 0x483C88 + _LD_OFF : { *(.patch_SetBGMDayNight) }
	ret_SetBGMDayNight = 0x483C8C + _LD_OFF;
	.patch_Cutscene_CheckObjectLoaded 0x4849D8 + _LD_OFF : { *(.patch_Cutscene_CheckObjectLoaded) }
	.patch_TurboTextClose 0x488214 + _LD_OFF : { *(.patch_TurboTextClose) }
	.patch_WarpSongEntranceOverride 0x488850 + _LD_OFF : { *(.patch_WarpSongEntranceOverride) }
	.patch_SetFWPlayerParams 0x4911B8 + _LD_OFF : { *(.patch_SetFWPlayerParams) }
	.patch_SwapFaroresWind 0x49186C + _LD_OFF : { *(.patch_SwapFaroresWind) }
	.patch_SwapAgeIgnoreSceneSetup 0x4918B0 + _LD_OFF : { *(.patch_SwapAgeIgnoreSceneSetup) }
	.patch_SkipTimeTravelCutsceneTwo 0x4918C8 + _LD_OFF : { *(.patch_SkipTimeTravelCutsceneTwo) }
	.patch_DMTOwlEntranceOverride 0x492064 + _LD_OFF : { *(.patch_DMTOwlEntranceOverride) }
	.patch_LHOwlEntranceOverride 0x492080 + _LD_OFF : { *(.patch_LHOwlEntranceOverride) }
	.patch_PlayerBonk 0x492CD0 + _LD_OFF : { *(.patch_PlayerBonk) }
	.patch_FairyUseHealAmount 0x4968B4 + _LD_OFF : { *(.patch_FairyUseHealAmount) }
	.patch_SendDroppedBottleContents 0x496A1C + _LD_OFF : { *(.patch_SendDroppedBottleContents) }
	.patch_ReturnFW 0x496B88 + _LD_OFF : { *(.patch_ReturnFW) }
	.patch_SetSpecialVoidOutRespawnFlag 0x496C70 + _LD_OFF : { *(.patch_SetSpecialVoidOutRespawnFlag) }
	.patch_GanonBattleDeathWarp 0x496C98 + _LD_OFF : { *(.patch_GanonBattleDeathWarp) }
	.patch_GanonRestoreMSOnDeath 0x496CB4 + _LD_OFF : { *(.patch_GanonRestoreMSOnDeath) }
	.patch_CriticalHealthCheckThree 0x49F294 + _LD_OFF : { *(.patch_CriticalHealthCheckThree) }

	/* 0x4A5B00 */ _LD_OFF = _LD_EUR ? 0x0 : _LD_OFF;

	Player_Action_Running = 0x4BA378 + _LD_OFF;
	.patch_OverrideGiDrawIdPlusOne_Ground 0x4BC610 + _LD_OFF : { *(.patch_OverrideGiDrawIdPlusOne_Ground) }
	.patch_OverrideGiDrawIdPlusOne_Water 0x4BD5DC + _LD_OFF : { *(.patch_OverrideGiDrawIdPlusOne_Water) }
	PlayerActor_Draw = 0x4BF618 + _LD_OFF;
	Message_CheckForControlCodes = 0x4C08C0 + _LD_OFF;
	.patch_EditDrawGetItemBeforeModelSpawn 0x4C0FD0 + _LD_OFF : { *(.patch_EditDrawGetItemBeforeModelSpawn) }
	.patch_HookshotRotation 0x4C2524 + _LD_OFF : { *(.patch_HookshotRotation) }
	HookshotRotation = 0x4C257C + _LD_OFF;
	.patch_EditDrawGetItemAfterMatrixUpdate 0x4C4D14 + _LD_OFF : { *(.patch_EditDrawGetItemAfterMatrixUpdate) }
	.patch_EditDrawGetItemAfterModelSpawn 0x4C61A4 + _LD_OFF : { *(.patch_EditDrawGetItemAfterModelSpawn) }
	Model_IsMeshGroupUsed = 0x4C6880 + _LD_OFF;
	.patch_CrouchStabHitbox 0x4C85D4 + _LD_OFF : { *(.patch_CrouchStabHitbox) }

	/* 0x4C99A7: End of vanilla code in .text section */
	. = 0x4C99A8 + _LD_OFF;
	. = ALIGN(4);
	.loader : {
		*(.loader*)
	}

	gGearUsabilityTable = 0x4D47C8 + _LD_OFF;
	gOcarinaMenuSongLengths = 0x4D53C8 + _LD_OFF;
	gOcarinaMenuSongNoteSequences = 0x4D541C + _LD_OFF;
	gDrawItemTable = 0x4D88C8 + _LD_OFF;
	.patch_DampeSetCollectibleFlag 0x4D9D50 + _LD_OFF : { *(.patch_DampeSetCollectibleFlag) }
	gDungeonSceneTable = 0x4DC400 + _LD_OFF;
	gMQDungeonSceneTable = 0x4DCBA8 + _LD_OFF;
	GyroDrawHUDIcon = 0x4FC648 + _LD_OFF;
	gIsBottomScreenDimmed = 0x5043EC + _LD_OFF;
	gGearMenuSpritesManager = 0x50447C + _LD_OFF;
	gGearMenuSelectedSlot = 0x50448C + _LD_OFF;
	gItemsMenuSpritesManager = 0x506734 + _LD_OFF;
	gBowMenuSpritesManager = 0x506738 + _LD_OFF;
	gItemsMenuGlowSpritesManager = 0x50673C + _LD_OFF;
	gMenuSpritesManager_506740 = 0x506740 + _LD_OFF;
	gItemsMenuSelectedSlot = 0x506748 + _LD_OFF;
	gItemUsabilityTable = 0x506C58 + _LD_OFF;
	gDungeonMapMenuSpritesManager = 0x506CD0 + _LD_OFF;
	OcarinaUIStruct = 0x5093EC + _LD_OFF;
	gRandInt = 0x50C0C4 + _LD_OFF;
	gRandFloat = 0x50C0C8 + _LD_OFF;
	NaviColorsArray = 0x50C998 + _LD_OFF;
	gActorOverlayTable = 0x50CD84 + _LD_OFF;
	gGanondorfBlood = 0x514F78 + _LD_OFF;
	gGanonBlood = 0x515194 + _LD_OFF;
	EnChanger_LoserGetItemIds = 0x521774 + _LD_OFF;
	VanillaScrubTable = 0x522384 + _LD_OFF;
	EnGirlA_ShopItemEntries = 0x524F50 + _LD_OFF;
	.patch_BombchuCheapestPriceOne 0x525348 + _LD_OFF : { *(.patch_BombchuCheapestPriceOne) }
	.patch_BombchuCheapestPriceTwo 0x5253D8 + _LD_OFF : { *(.patch_BombchuCheapestPriceTwo) }
	.patch_BombchuCheapestPriceThree 0x525408 + _LD_OFF : { *(.patch_BombchuCheapestPriceThree) }
	.patch_BombchuCheapestPriceFour 0x525498 + _LD_OFF : { *(.patch_BombchuCheapestPriceFour) }
	.patch_OcarinaMinigameRewardsOrder 0x52ED10 + _LD_OFF : { *(.patch_OcarinaMinigameRewardsOrder) }
	z3D_Fog_State = 0x531EB4 + _LD_OFF;
	TimerFrameCounter = 0x539D8A + _LD_OFF;
	gRestrictionFlags = 0x539DC4 + _LD_OFF;
	sFloorType = 0x53A0A4 + _LD_OFF;
	dynamicExitList = 0x53C094 + _LD_OFF;
	PlayerDListGroup_EmptySheathAdult = 0x53C4D8 + _LD_OFF;
	PlayerDListGroup_EmptySheathChildWithHylianShield = 0x53C4DC + _LD_OFF;
	Vec3f_PlayerFeet_unk = 0x53CACC + _LD_OFF;
	.patch_TycoonWalletSize 0x53CC08 + _LD_OFF : { *(.patch_TycoonWalletSize) }
	.patch_TitleLinkObject 0x53CCF0 + _LD_OFF : { *(.patch_TitleLinkObject) }
	gObjectTable = 0x53CCF4 + _LD_OFF;
	gEntranceTable = 0x543BB8 + _LD_OFF;
	gSceneTable = 0x545484 + _LD_OFF;
	gSfxDefaultFreqAndVolScale = 0x54AC20 + _LD_OFF;
	gSfxDefaultReverb = 0x54AC24 + _LD_OFF;
	sPrevMainBgmSeqId = 0x54ACB8 + _LD_OFF;
	gOcarinaSongNotes = 0x54B5F2 + _LD_OFF;
	gOcarinaSongButtons = 0x54C222 + _LD_OFF;
	ControlStick_X = 0x5655C0 + _LD_OFF;
	ControlStick_Y = 0x5655C4 + _LD_OFF;
	gSaveContext = 0x587958 + _LD_OFF;
	gEffectContext = 0x58B2E0 + _LD_OFF;
	gEffectSsInfo = 0x598530 + _LD_OFF;
	gMainClass = 0x5BE5B8 + _LD_OFF;

	/* 0x005C6607: End of vanilla .bss section */
	. = 0x005C7000 + _LD_OFF;
	_LD_TEXT_START = . ;
	.text : {
		__text_start = . ;
		*(.text*)
		__text_end = . ;
		*(.rodata*)
		*(.data*)
		*(.bss*)
		*(COMMON)
		rCustomMessages = . ;
	}
	_LD_TEXT_SIZE = __text_end - __text_start;

	/* Section not included in patch. */
	.other_executable : {
		*(.init)
		*(.fini)
	}

	/*
	 * Section not included in patch. Use high address to force placement
	 * in separate segment to avoid linker warning.
	 */
	.other_allocatable 0x01000000 : {
		*(.eh_frame)
		*(.init_array)
		*(.fini_array)
	}

	gStaticContext = 0x8080010 + _LD_OFF;
	real_hid = 0x10002000 + _LD_OFF;
	Z3D_TOP_SCREEN_LEFT_1 = 0x14313890 + _LD_OFF;
	Z3D_TOP_SCREEN_LEFT_2 = 0x14359DA0 + _LD_OFF;
	Z3D_BOTTOM_SCREEN_1 = 0x143A02B0 + _LD_OFF;
	Z3D_BOTTOM_SCREEN_2 = 0x143D86C0 + _LD_OFF;
	Z3D_TOP_SCREEN_RIGHT_1 = 0x14410AD0 + _LD_OFF;
	Z3D_TOP_SCREEN_RIGHT_2 = 0x14456FE0 + _LD_OFF;

	/* 0xFFFFFFFF */
}
