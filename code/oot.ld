OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(loader_patch)
SECTIONS
{
	. = 0x100000;
	.patch_loader 0x100000 : {
		*(.patch_loader)
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

	.patch_BeanDaddyModifyBeansBought 0x130CEC : {
		*(.patch_BeanDaddyModifyBeansBought)
	}

	.patch_BiggoronSetGivenReward 0x133F7C :{
		*(.patch_BiggoronSetGivenReward)
	}

	.patch_SongOfStormsLocation 0x1427E0 : {
		*(.patch_SongOfStormsLocation)
	}

	.patch_BeanDaddyPurchase 0x14EDA8 : {
		*(.patch_BeanDaddyPurchase)
	}

	.patch_BeanDaddyModifyPrice 0x14EE98 : {
		*(.patch_BeanDaddyModifyPrice)
	}

	.patch_ScrubStickUpgradeOne 0x161898 : {
		*(.patch_ScrubStickUpgradeOne)
	}

	.patch_ScrubNutUpgradeOne 0x1618EC : {
		*(.patch_ScrubNutUpgradeOne)
	}

	.patch_EnKoInitBitMask 0x165760 : {
		*(.patch_EnKoInitBitMask)
	}

	.patch_DampeCheckCollectibleFlag 0x169F88 : {
		*(.patch_DampeCheckCollectibleFlag)
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

	.patch_ChildRollingGoron 0x194B18 : {
		*(.patch_ChildRollingGoron)
	}

	.patch_BiggoronCheckGivenRewardThree 0x194DA4 : {
		*(.patch_BiggoronCheckGivenRewardThree)
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

	.patch_BiggoronCheckGivenRewardTwo 0x1954EC : {
		*(.patch_BiggoronCheckGivenRewardTwo)
	}

	.patch_EponasSongCheckFlagTwo 0x195CFC : {
		*(.patch_EponasSongCheckFlagTwo)
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

	.patch_KingZoraSecondTunic 0x1B6A18 : {
		*(.patch_KingZoraSecondTunic)
	}

	.patch_KingZoraGiveTunic 0x1B6A64 : {
		*(.patch_KingZoraGiveTunic)
	}

	.patch_DemoEffectStoneDraw 0x1D209C : {
		*(.patch_DemoEffectStoneDraw)
	}

	.patch_CheckGerudoToken_1D7AD4 0x1D7AD4 : {
		*(.patch_CheckGerudoToken_1D7AD4)
	}

	.patch_BiggoronCheckGivenRewardOne 0x1D8A18 : {
		*(.patch_BiggoronCheckGivenRewardOne)
	}

	.patch_ForestTempleItemGive 0x1E3F84 : {
		*(.patch_ForestTempleItemGive)
	}

	.patch_FireTempleItemGive 0x1E4010 : {
		*(.patch_FireTempleItemGive)
	}

	.patch_WaterTempleItemGive 0x1E40D8 : {
		*(.patch_WaterTempleItemGive)
	}

	.patch_SpiritTempleBitMask 0x1E4154 : {
		*(.patch_SpiritTempleBitMask)
	}

	.patch_SpiritTempleItemGive 0x1E4168 : {
		*(.patch_SpiritTempleItemGive)
	}

	.patch_ShadowTempleBitMask 0x1E41DC : {
		*(.patch_ShadowTempleBitMask)
	}

	.patch_ShadowTempleItemGive 0x1E41F0 : {
		*(.patch_ShadowTempleItemGive)
	}

	.patch_DaruniaCheckStrength 0x1E489C : {
		*(.patch_DaruniaCheckStrength)
	}

	.patch_ItemGiveBombchuDropOne 0x1F6F70 : {
		*(.patch_ItemGiveBombchuDropOne)
	}

	.patch_BombchuBowlingStaticReward 0x206150 : {
		*(.patch_BombchuBowlingStaticReward)
	}

	.patch_DekuSproutBitMask 0x2153A8 : {
		*(.patch_DekuSproutBitMask)
	}

	.patch_DekuTheaterMaskOfTruth 0x21CA30 : {
		*(.patch_DekuTheaterMaskOfTruth)
	}

	.patch_patch_ItemGiveBombchuDropTwo 0x22BAE4 : {
		*(.patch_ItemGiveBombchuDropTwo)
	}

	.patch_BusinessScrubCheckFlags 0x22EE64 : {
		*(.patch_BusinessScrubCheckFlags)
	}

	.patch_EnExItemModelDraw 0x249C94 : {
		*(.patch_EnExItemModelDraw)
	}

	.patch_SpiritTempleItemGiveTwo 0x24CF4C : {
		*(.patch_SpiritTempleItemGiveTwo)
	}

	.patch_LostWoodsShootingGame 0x259E4C : {
		*(.patch_LostWoodsShootingGame)
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

	.patch_FireTempleItemGiveThree 0x27D060 : {
		*(.patch_FireTempleItemGiveThree)
	}

	.patch_ShadowTempleItemGiveTwo 0x27DED0 : {
		*(.patch_ShadowTempleItemGiveTwo)
	}

	.patch_ForestTempleItemGiveTwo 0x27E074 : {
		*(.patch_ForestTempleItemGiveTwo)
	}

	.patch_WaterTempleItemGiveThree 0x283CA8 : {
		*(.patch_WaterTempleItemGiveThree)
	}

	.patch_SunsSongLocation 0x2888C8 : {
		*(.patch_SunsSongLocation)
	}

	.patch_KakarikoGateCheck 0x28A67C : {
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

	.patch_GetCustomMessageEntryOne 0x2CD3A4 : {
		*(.patch_GetCustomMessageEntryOne)
	}

	.patch_GetCustomMessageTextOne 0x2CD3EC : {
		*(.patch_GetCustomMessageTextOne)
	}

	.patch_SceneInitAfterCopyScenes 0x2EAFDC : {
		*(.patch_SceneInitAfterCopyScenes)
	}

	.patch_Gfx_Update 0x310254 : {
		*(.patch_Gfx_Update)
	}

	.patch_ISGPutaway 0x32B4AC : {
		*(.patch_ISGPutaway)
	}

	.patch_ChestGetIceTrapObjectStatus 0x33AB24 : {
		*(.patch_ChestGetIceTrapObjectStatus)
	}

	/*.patch_MagicArrowsInInventory 0x33C350 : {
		*(.patch_MagicArrowsInInventory)
	}*/

	.patch_BiggoronDayCheck 0x33DCC0 : {
		*(.patch_BiggoronDayCheck)
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

	.patch_FastChests 0x354CD8 : {
		*(.patch_FastChests)
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

	.patch_DemoEffectMedallionDraw 0x37214C : {
		*(.patch_DemoEffectMedallionDraw)
	}

	.patch_IncomingGetItemID 0x3725AC : {
		*(.patch_IncomingGetItemID)
	}

	.patch_ConvertBombDropTwo 0x3747A4 : {
		*(.patch_ConvertBombDropTwo)
	}

	.patch_NoLensOfTruthNaviText 0x37798C : {
		*(.patch_NoLensOfTruthNaviText)
	}

	.patch_ChildShootingGallery 0x38AB70 : {
		*(.patch_ChildShootingGallery)
	}

	.patch_AdultShootingGallery 0x38AB9C : {
		*(.patch_AdultShootingGallery)
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

	.patch_FireBlockCooldownTimer 0x3E0A2C : {
		*(.patch_FireBlockCooldownTimer)
	}

	.patch_FireBlockSpeed 0x3E0BA8 : {
		*(.patch_FireBlockSpeed)
	}

	.patch_ScrubStickUpgradeTwo 0x3CE990 : {
		*(.patch_ScrubStickUpgradeTwo)
	}

	.patch_ScrubNutUpgradeTwo 0x3CE9DC : {
		*(.patch_ScrubNutUpgradeTwo)
	}

	.patch_MasterSwordAlwaysDrop 0x3E5E98 : {
		*(.patch_MasterSwordAlwaysDrop)
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

	.patch_FireArrowBitMask 0x3F23B0 : {
		*(.patch_FireArrowBitMask)
	}

	.patch_FireArrowCheckChestFlagOne 0x3F23FC : {
		*(.patch_FireArrowCheckChestFlagOne)
	}

	.patch_FireArrowCheckChestFlagTwo 0x3F2448 : {
		*(.patch_FireArrowCheckChestFlagTwo)
	}

	.patch_DodongosCavernItemGive 0x3F57B0 : {
		*(.patch_DodongosCavernItemGive)
	}

	.patch_DekuTreeItemGive 0x3F582C : {
		*(.patch_DekuTreeItemGive)
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

	.patch_ExtendedObjectClear 0x44E754 : {
		*(.patch_ExtendedObjectClear)
	}

	.patch_RequiemLocation 0x44F10C : {
		*(.patch_RequiemLocation)
	}

	.patch_NocturneLocation 0x44F12C : {
		*(.patch_NocturneLocation)
	}

	.patch_SariasGift 0x44F190 : {
		*(.patch_SariasGift)
	}

	.patch_LACSConditionOne 0x44F1D4 : {
		*(.patch_LACSConditionOne)
	}

	.patch_LACSConditionTwo 0x44F20C : {
		*(.patch_LACSConditionTwo)
	}

	.patch_LullabyCheckFlag 0x44FD54 : {
		*(.patch_LullabyCheckFlag)
	}

	.patch_before_GlobalContext_Update 0x452390 : {
		*(.patch_before_GlobalContext_Update)
	}

	.patch_after_GlobalContext_Update 0x452434 : {
		*(.patch_after_GlobalContext_Update)
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

	.patch_FishingStoreTempB 0x475F8C : {
		*(.patch_FishingStoreTempB)
	}

	.patch_FishingRestoreTempB 0x475FC0 : {
		*(.patch_FishingRestoreTempB)
	}

	.patch_FireTempleItemGiveTwo 0x491B60 : {
		*(.patch_FireTempleItemGiveTwo)
	}

	.patch_OverrideGraphicID_4BC604 0x4BC604 : {
		*(.patch_OverrideGraphicID_4BC604)
	}

	.patch_OverrideGraphicID_4BD5D0 0x4BD5D0 : {
		*(.patch_OverrideGraphicID_4BD5D0)
	}

	.patch_EditDrawGetItem 0x4C0FD0 : {
		*(.patch_EditDrawGetItem)
	}

	. = 0x4C99A8;
	. = ALIGN(4);
	.loader : {
		*(.loader*)
	}

	.patch_DampeSetCollectibleFlag 0x4D9D50 : {
		*(.patch_DampeSetCollectibleFlag)
	}

	.patch_OcarinaMinigameRewardsOrder 0x52ED10 : {
		*(.patch_OcarinaMinigameRewardsOrder)
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
        __text_end  = . ;
    }
}
