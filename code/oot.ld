OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(loader_patch)
SECTIONS
{
	. = 0x100000;
	.patch_loader 0x100000 : {
		*(.patch_loader)
	}
	
	.patch_ItemEtceteraModelDraw 0x117080 : {
		*(.patch_ItemEtceteraModelDraw)
	}

	.patch_SkulltulaRewardOne 0x12CC68 : {
		*(.patch_SkulltulaRewardOne)
	}

	.patch_SkulltulaRewardTwo 0x12CD38 : {
		*(.patch_SkulltulaRewardTwo)
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

	.patch_PreludeLocation 0x18D9FC : {
		*(.patch_PreludeLocation)
	}

	.patch_PoeCollectorCheckPoints 0x19091C : {
		*(.patch_PoeCollectorCheckPoints)
	}

	.patch_ChildRollingGoron 0x194B18 : {
		*(.patch_ChildRollingGoron)
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

	.patch_BombchuBowlingStaticReward 0x206150 : {
		*(.patch_BombchuBowlingStaticReward)
	}

	.patch_DekuSproutBitMask 0x2153A8 : {
		*(.patch_DekuSproutBitMask)
	}

	.patch_DekuTheaterMaskOfTruth 0x21CA30 : {
		*(.patch_DekuTheaterMaskOfTruth)
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

	.patch_Gfx_Update 0x310254 : {
		*(.patch_Gfx_Update)
	}

	.patch_BiggoronDayCheck 0x33DCC0 : {
		*(.patch_BiggoronDayCheck)
	}

	.patch_OverrideGraphicID_351B94 0x351B94 : {
		*(.patch_OverrideGraphicID_351B94)
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

	.patch_ModelSpawnGetObjectStatus 0x36A96C : {
		*(.patch_ModelSpawnGetObjectStatus)
	}

	.patch_DemoEffectMedallionDraw 0x37214C : {
		*(.patch_DemoEffectMedallionDraw)
	}

	.patch_IncomingGetItemID 0x3725AC : {
		*(.patch_IncomingGetItemID)
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

	.patch_ScrubStickUpgradeTwo 0x3CE990 : {
		*(.patch_ScrubStickUpgradeTwo)
	}

	.patch_ScrubNutUpgradeTwo 0x3CE9DC : {
		*(.patch_ScrubNutUpgradeTwo)
	}

	.patch_MasterSwordAlwaysDrop 0x3E5E98 : {
		*(.patch_MasterSwordAlwaysDrop)
	}

	.patch_RainbowBridge 0x3E7CAC : {
		*(.patch_RainbowBridge)
	}

	.patch_DekuTheaterSkullMask 0x3EAF38 : {
		*(.patch_DekuTheaterSkullMask)
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

	.patch_before_GlobalContext_Update 0x452390 : {
		*(.patch_before_GlobalContext_Update)
	}

	.patch_after_GlobalContext_Update 0x452434 : {
		*(.patch_after_GlobalContext_Update)
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
	
	. = 0x4C99A8;
	. = ALIGN(4);
	.loader : {
		*(.loader*)
	}

	.patch_DampeSetCollectibleFlag 0x4D9D50 : {
		*(.patch_DampeSetCollectibleFlag)
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
