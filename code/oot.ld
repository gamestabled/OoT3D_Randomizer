OUTPUT_FORMAT("elf32-littlearm", "elf32-littlearm", "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(loader_patch)
SECTIONS
{
	. = 0x100000;
	.patch_loader 0x100000 : {
		*(.patch_loader)
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

	.patch_DampeCheckCollectibleFlag 0x169F88 : {
		*(.patch_DampeCheckCollectibleFlag)
	}

	.patch_ChildRollingGoron 0x194B18 : {
		*(.patch_ChildRollingGoron)
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

	.patch_KingZoraSecondTunic 0x1B6A18 : {
		*(.patch_KingZoraSecondTunic)
	}

	.patch_KingZoraGiveTunic 0x1B6A64 : {
		*(.patch_KingZoraGiveTunic)
	}
	
	.patch_DaruniaCheckStrength 0x1E489C : {
		*(.patch_DaruniaCheckStrength)
	}

	.patch_LostWoodsShootingGame 0x259E4C : {
		*(.patch_LostWoodsShootingGame)
	}

	.patch_OverrideOcarinaSongs 0x26C478 : {
		*(.patch_OverrideOcarinaSongs)
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

	.patch_OverrideGraphicID_351B94 0x351B94 : {
		*(.patch_OverrideGraphicID_351B94)
	}

	.patch_OverrideGraphicID_35495C 0x35495C : {
		*(.patch_OverrideGraphicID_35495C)
	}

	.patch_OverrideGraphicID_354BB8 0x354BB8 : {
		*(.patch_OverrideGraphicID_354BB8)
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

	.patch_FastChests 0x354CD8 : {
		*(.patch_FastChests)
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

	.patch_before_GlobalContext_Update 0x452390 : {
		*(.patch_before_GlobalContext_Update)
	}

	.patch_after_GlobalContext_Update 0x452434 : {
		*(.patch_after_GlobalContext_Update)
	}

	.patch_OverrideGraphicID_495CD0 0x495CD0 : {
		*(.patch_OverrideGraphicID_495CD0)
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
