.arm
.text

.global hook_before_GlobalContext_Update
hook_before_GlobalContext_Update:
    push {r0-r12, lr}
    bl before_GlobalContext_Update
    pop {r0-r12, lr}
    cpy r7,r0
    bx lr

.global hook_after_GlobalContext_Update
hook_after_GlobalContext_Update:
    push {r0-r12, lr}
    bl after_GlobalContext_Update
    pop {r0-r12, lr}
    b 0x2E25F0

.global hook_Gfx_Update
hook_Gfx_Update:
    push {r0-r12, lr}
    bl Gfx_Update
    pop {r0-r12, lr}
    pop {r4-r8, pc}

.global hook_IncomingGetItemID
hook_IncomingGetItemID:
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r6
    cpy r2,r7
    bl ItemOverride_GetItem
    pop {r0-r12, lr}
    bx lr

.global hook_SaveFile_Init
hook_SaveFile_Init:
    push {r0-r12, lr}
    bl SaveFile_Init
    pop {r0-r12, lr}
    strb r1,[r0,#0x35]
    bx lr

.global rActiveItemRow
.rActiveItemRow_addr:
    .word rActiveItemRow

.global hook_OverrideTextID
hook_OverrideTextID:
    ldr r1,.rActiveItemRow_addr
    ldr r1,[r1]
    cmp r1,#0x0
    beq noOverrideTextID
    b 0x2BC1D0
noOverrideTextID:
    ldrb r1,[r6,#0x4]
    b 0x2BC1C8

.global hook_OverrideItemID
hook_OverrideItemID:
    ldr r1,.rActiveItemRow_addr
    ldr r1,[r1]
    cmp r1,#0x0
    beq noOverrideItemID
    push {r0-r12, lr}
    cpy r0,r2
    bl ItemOverride_GetItemTextAndItemID
    pop {r0-r12, lr}
    b 0x2BC1DC
noOverrideItemID:
    ldrb r1,[r6,#0x0]
    b 0x2BC1D4

# Puts override graphic ID into r0, no other effects
# If no active override, puts -0x1
# Need to wrap around this for individual cases because of differing register usage
.global hook_OverrideGraphicID
.global rActiveItemGraphicId_addr
.rActiveItemGraphicId_addr:
    .word rActiveItemGraphicId
hook_OverrideGraphicID:
    ldr r0,.rActiveItemRow_addr
    ldr r0,[r0]
    cmp r0,#0x0
    beq noOverrideGraphicID

    ldr r0,.rActiveItemGraphicId_addr
    ldr r0,[r0]
    b returnGraphicID
noOverrideGraphicID:
    mov r0,#-0x1
returnGraphicID:
    bx lr

.global hook_OverrideGraphicID_351B94
hook_OverrideGraphicID_351B94:
    push {r0,r1,lr}
    bl hook_OverrideGraphicID
    cpy r1,r0
    cmp r1,#-0x1
    pop {r0}
    bne returnGraphicID_351B94
    ldrsh r1,[r0,#-0x4]
returnGraphicID_351B94:
    cpy r0,r1
    pop {r1,lr}
    bx lr

.global hook_OverrideGraphicID_35495C
hook_OverrideGraphicID_35495C:
    push {lr}
    bl hook_OverrideGraphicID
    cmp r0,#-0x1
    bne returnGraphicID_35495C
    ldrsh r0,[r6,#0x2]
returnGraphicID_35495C:
    pop {lr}
    bx lr

.global hook_OverrideGraphicID_354BB8
hook_OverrideGraphicID_354BB8:
    push {lr}
    bl hook_OverrideGraphicID
    cmp r0,#-0x1
    bne returnGraphicID_354BB8
    ldrsh r0,[r6,#0x2]
returnGraphicID_354BB8:
    pop {lr}
    bx lr

.global hook_EditDrawGetItemBeforeModelSpawn
hook_EditDrawGetItemBeforeModelSpawn:
    push {r0-r12, lr}
    bl ItemOverride_EditDrawGetItemBeforeModelSpawn
    pop {r0-r12, lr}
    mov r7,#0x0
    bx lr

.global hook_EditDrawDetItemAfterModelSpawn
hook_EditDrawDetItemAfterModelSpawn:
    push {r0-r12, lr}
    bl ItemOverride_EditDrawGetItemAfterModelSpawn
    pop {r0-r12, lr}
    str r0,[r6,#0x78]
    bx lr

# TODO: Text ID in game gets messed up,
# Gives the "What's that?" text instead of
# the text about moving the statue
.global hook_AdultRollingGoronTwo
hook_AdultRollingGoronTwo:
    mov r0,#0x3000
    add r0,r0,#0x38
    b 0x1954B0

.global hook_DaruniaStrengthCheck
hook_DaruniaStrengthCheck:
    push {r0-r12, lr}
    bl EnDu_CheckRewardFlag
    cmp r0,#0x1
    pop {r0-r12, lr}
    b 0x1E48A0

.global hook_DampeCheckCollectibleFlag
hook_DampeCheckCollectibleFlag:
    push {r0-r12, lr}
    bl EnTk_CheckCollectFlag
    pop {r0-r12, lr}
    cpy r4,r0
    bx lr

.global hook_GetToken
hook_GetToken:
    push {r0-r12, lr}
    cpy r0,r4
    bl ItemOverride_GetSkulltulaToken
    pop {r0-r12, lr}
    bx lr

.global hook_ModelSpawnGetObjectStatus
hook_ModelSpawnGetObjectStatus:
    push {r1-r12, lr}
    cpy r0,r1
    bl ExtendedObject_GetStatus
    pop {r1-r12, lr}
    bx lr

.global hook_ChestGetIceTrapObjectStatus
hook_ChestGetIceTrapObjectStatus:
    push {r1-r12, lr}
    mov r0,#0x3
    bl ExtendedObject_GetStatus
    pop {r1-r12, lr}
    bx lr

.global hook_PoeCollectorCheckPoints
hook_PoeCollectorCheckPoints:
    push {r0-r12, lr}
    bl EnGb_CheckPoints
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_ItemEtceteraModelDraw
hook_ItemEtceteraModelDraw:
    push {r0-r12, lr}
    bl Model_DrawByActor
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x1170B4
    cpy r4,r0
    bx lr

.global hook_KokiriCheckOpenForest
hook_KokiriCheckOpenForest:
    push {r0-r12, lr}
    bl EnKo_CheckOpenForest
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_EnExItemModelDraw
hook_EnExItemModelDraw:
    push {r0-r12, lr}
    mov r0,r4
    bl Model_DrawByActor
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x249BC8
    add r1,r4,#0x148
    bx lr

.global hook_DemoEffectMedallionDraw
hook_DemoEffectMedallionDraw:
    push {r0-r12, lr}
    mov r0,r4
    bl Model_DrawByActor
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x372148
    ldr r0,[r4,#0x2A8]
    b 0x372150

.global hook_DemoEffectStoneDraw
hook_DemoEffectStoneDraw:
    push {r0-r12, lr}
    mov r0,r4
    bl Model_DrawByActor
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x1D20C0
    ldr r0,[r4,#0x2A8]
    b 0x1D20A0

.global hook_EnKoInitCheckForest
hook_EnKoInitCheckForest:
    push {r1-r12, lr}
    bl EnKo_CheckForestTempleBeat
    tst r0,#0x1
    pop {r1-r12, lr}
    bx lr

.global hook_FireArrowCheckChestFlag
hook_FireArrowCheckChestFlag:
    push {r0-r12, lr}
    bl ShotSun_CheckChestFlag
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_SerenadeCheckChestFlag
hook_SerenadeCheckChestFlag:
    push {r0-r12, lr}
    bl Cutscene_SerenadeCheckChestFlag
    cmp r0,#0x0
    pop {r0-r12, lr}
    cpy r0,r5
    bx lr

.global hook_ScarecrowCheckToBeActivated
hook_ScarecrowCheckToBeActivated:
    push {r0-r12, lr}
    bl Scarecrow_CheckToBeActivated
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_EponasSongCheckFlag
hook_EponasSongCheckFlag:
    push {r0-r12, lr}
    bl Cutscene_CheckEponasSongFlag
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_SariasSongCheckFlag
hook_SariasSongCheckFlag:
    push {r0-r12, lr}
    bl Cutscene_CheckSariasSongFlag
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_PoeCollectorGetFirstTextbox
hook_PoeCollectorGetFirstTextbox:
    push {r1-r12, lr}
    bl EnGb_GetFirstTextbox
    pop {r1-r12, lr}
    bx lr

.global hook_ApplyDamageMultiplier
hook_ApplyDamageMultiplier:
    push {r0-r3, r5-r12, lr}
    bl Settings_ApplyDamageMultiplier
    cpy r4,r0
    pop {r0-r3, r5-r12, lr}
    bx lr

.global hook_SceneInitAfterCopyScenes
hook_SceneInitAfterCopyScenes:
    push {r0-r12, lr}
    bl 0x371738
    bl Scene_Init
    pop {r0-r12, lr}
    bx lr

.global hook_StoreChildBButtonEquip
hook_StoreChildBButtonEquip:
    push {r0-r12, lr}
    bl SaveFile_SaveChildBButton
    pop {r0-r12, lr}
    b 0x45F210

.global hook_LullabyCheckFlag
hook_LullabyCheckFlag:
    push {r0-r12, lr}
    bl Cutscene_CheckLullabyFlag
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_FishingStoreTempB
hook_FishingStoreTempB:
    push {r0-r12, lr}
    bl Fishing_StoreTempB
    pop {r0-r12, lr}
    bx lr

.global hook_FishingRestoreTempB
hook_FishingRestoreTempB:
    push {r0-r12, lr}
    bl Fishing_RestoreTempB
    pop {r0-r12, lr}
    bx lr

.global hook_ConvertBombDropOne
hook_ConvertBombDropOne:
    push {r1-r12, lr}
    bl Item_ConvertBombDrop
    pop {r1-r12, lr}
    cpy r12,r0
    b 0x35E474

.global hook_ConvertBombDropTwo
hook_ConvertBombDropTwo:
    push {r1-r12, lr}
    cpy r0,r6
    bl Item_ConvertBombDrop
    pop {r1-r12, lr}
    cpy r6,r0
    b 0x3747B0

.global hook_BeanDaddyModifyBeansBought
hook_BeanDaddyModifyBeansBought:
    push {r1-r12, lr}
    bl EnMs_ModifyBeansBought
    pop {r1-r12, lr}
    cmp r0,#0xa
    bx lr

.global hook_BeanDaddyModifyPrice
hook_BeanDaddyModifyPrice:
    push {r0,r2-r12, lr}
    cpy r0,r1
    bl EnMs_ModifyPrice
    cpy r1,r0
    pop {r0,r2-r12, lr}
    cmp r0,r1
    bx lr

.global hook_CheckGerudoToken
hook_CheckGerudoToken:
    push {r1-r12, lr}
    bl SaveFile_CheckGerudoToken
    pop {r1-r12, lr}
    bx lr

.global hook_CowBottleCheck
hook_CowBottleCheck:
    push {r1-r12, lr}
    cpy r0,r4
    bl EnCow_BottleCheck
    pop {r1-r12, lr}
    bx lr

.global hook_CowItemOverride
hook_CowItemOverride:
    push {r0-r1, r3-r12, lr}
    bl EnCow_ItemOverride
    cpy r2,r0
    pop {r0-r1, r3-r12, lr}
    b 0x3EE37C

.global hook_AnjuCheckCuccoAmount
hook_AnjuCheckCuccoAmount:
    push {r1-r12, lr}
    bl EnNiwLady_CheckCuccoAmount
    pop {r1-r12, lr}
    cmp r0,#0x0
    b 0x179424

.global hook_KingZoraCheckMovedFlag
hook_KingZoraCheckMovedFlag:
    push {r1-r12, lr}
    bl EnKz_CheckMovedFlag
    pop {r1-r12, lr}
    cmp r0,#0x0
    bx lr

.global hook_FrogReward
hook_FrogReward:
    push {r0-r12, lr}
    bl EnFr_rSetReward
    pop {r0-r12, lr}
    b 0x389930

.global hook_CanPlayBombchuBowling
hook_CanPlayBombchuBowling:
    push {r0-r12, lr}
    bl EnBomBowlMan_CheckExplosives
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_SlidingDoorDestroyCustomModels
hook_SlidingDoorDestroyCustomModels:
    push {r0-r12, lr}
    cpy r0,r4
    bl Door_CheckToDeleteCustomModels
    pop {r0-r12, lr}
    mov r0,#0x0
    bx lr

.global hook_HandleDoorDestroyCustomModels
hook_HandleDoorDestroyCustomModels:
    push {r0-r12, lr}
    cpy r0,r4
    bl Door_CheckToDeleteCustomModels
    pop {r0-r12, lr}
    str r0,[r4,#0x3E4]
    bx lr

.global hook_TalonGetCastleTextbox
hook_TalonGetCastleTextbox:
    push {r0, r2-r12, lr}
    bl EnTa_GetCastleTextbox
    mov r1, r0
    pop {r0, r2-r12, lr}
    bx lr

.global hook_MidoCheckSpawn
hook_MidoCheckSpawn:
    push {r0-r12, lr}
    bl EnMd_ShouldSpawn
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_MidoForestDialog
hook_MidoForestDialog:
    push {r1-r12, lr}
    bl EnMd_GetTextKokiriForest
    pop {r1-r12, lr}
    bx lr

.global hook_CheckDekuTreeClear
hook_CheckDekuTreeClear:
    push {r0-r12, lr}
    bl Dungeon_CheckDekuTreeClear
    tst r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_CheckCurrentDungeonMode
hook_CheckCurrentDungeonMode:
    push {r0-r12, lr}
    bl Dungeon_GetCurrentDungeonMode
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_CanReadHints
hook_CanReadHints:
    push {r0-r12, lr}
    bl Hints_CanReadHints
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_FastChests
hook_FastChests:
    push {r0-r12, lr}
    bl Chest_OverrideAnimation
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_DecoratedChest
hook_DecoratedChest:
    push {r0-r12, lr}
    bl Chest_OverrideDecoration
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_FastOwlCutscenes
hook_FastOwlCutscenes:
    push {r0-r12, lr}
    bl EnOwl_FastCutscene
    pop {r0-r12, lr}
    mov r1,#0xa
    bx lr

.global hook_SetChildCustomTunic
hook_SetChildCustomTunic:
    push {r0-r12, lr}
    bl Player_SetChildCustomTunicCMAB
    pop {r0-r12, lr}
    b 0x191E60

.global hook_ShortenRainbowBridgeCS
hook_ShortenRainbowBridgeCS:
    push {r0-r12, lr}
    bl ShortenRainbowBridgeCS
    pop {r0-r12, lr}
    cpy r4,r0
    bx lr

.global hook_Chest_OverrideIceSmoke
hook_Chest_OverrideIceSmoke:
    push {r0-r12, lr}
    mov r0,r4
    bl Chest_OverrideIceSmoke
    cmp r0,#0x0
    pop {r0-r12, lr}
    cpy r0,r6
    bne 0x1D5E64
    b 0x1D5E60

.global hook_EnableFW
hook_EnableFW:
    push {r0-r12, lr}
    bl EnableFW
    pop {r0-r12, lr}
    add sp,sp,#0x14
    bx lr

.global hook_SetSavewarpEntrance
hook_SetSavewarpEntrance:
    push {r0-r12, lr}
    bl Entrance_SetSavewarpEntrance
    pop {r0-r12, lr}
    bx lr

.global hook_SetGameOverEntrance
hook_SetGameOverEntrance:
    push {r0-r12, lr}
    bl Entrance_SetGameOverEntrance
    pop {r0-r12, lr}
    bx lr

.global hook_GossipStoneAddSariaHint
hook_GossipStoneAddSariaHint:
    strh r1,[r5,#0x16]
    push {r0-r12, lr}
    add r0,r1,#0x600
    bl Hints_AddSariasSongHint
    pop {r0-r12, lr}
    bx lr

.global hook_NoHealFromHealthUpgrades
hook_NoHealFromHealthUpgrades:
    push {r1-r12, lr}
    bl NoHealFromHealthUpgrades
    pop {r1-r12, lr}
    bx lr

.global hook_NoHealFromBombchuBowlingPrize
hook_NoHealFromBombchuBowlingPrize:
    push {r1-r12, lr}
    bl NoHealFromBombchuBowlingPrize
    pop {r1-r12, lr}
    bx lr

.global hook_FairyPickupHealAmount
hook_FairyPickupHealAmount:
    push {r0-r12, lr}
    bl FairyPickupHealAmount
    pop {r0-r12, lr}
    bx lr

.global hook_FairyReviveHealAmount
hook_FairyReviveHealAmount:
    push {r1-r12, lr}
    bl FairyReviveHealAmount
    pop {r1-r12, lr}
    bx lr

.global hook_FairyUseHealAmount
hook_FairyUseHealAmount:
    push {r1-r12, lr}
    bl FairyUseHealAmount
    pop {r1-r12, lr}
    bx lr

.global hook_MedigoronCheckFlagOne
hook_MedigoronCheckFlagOne:
    push {r0-r12, lr}
    bl EnGm_CheckRewardFlag
    cmp r0,#1
    pop {r0-r12, lr}
    blt 0x130254
    beq 0x13026C
    tst r12,r3
    b 0x130250

.global hook_MedigoronCheckFlagTwo
hook_MedigoronCheckFlagTwo:
    bne childLink
    push {r0-r12, lr}
    bl EnGm_CheckRewardFlag
    cmp r0,#1
    pop {r0-r12, lr}
    blt 0x1302F8
    bne 0x1302C8
childLink:
    b 0x1302F0

.global hook_MedigoronSetRewardFlag
hook_MedigoronSetRewardFlag:
    mvn r0,#0xc7
    push {r0-r12, lr}
    bl EnGm_SetRewardFlag
    pop {r0-r12, lr}
    b 0x16C91C

.global hook_MedigoronItemOverrideOne
hook_MedigoronItemOverrideOne:
    push {r0-r1, r3-r12, lr}
    bl EnGm_ItemOverride
    cpy r2,r0
    pop {r0-r1, r3-r12, lr}
    b 0x14D960

.global hook_MedigoronItemOverrideTwo
hook_MedigoronItemOverrideTwo:
    push {r0-r1, r3-r12, lr}
    bl EnGm_ItemOverride
    cpy r2,r0
    pop {r0-r1, r3-r12, lr}
    b 0x16C9C0

.global hook_MedigoronGetCustomText
hook_MedigoronGetCustomText:
    push {r0-r12, lr}
    bl EnGm_UseCustomText
    cmp r0,#1
    pop {r0-r12, lr}
    moveq r2,#0x9100
    addeq r2,r2,#0x20
    movne r2,#0x3000
    addne r2,r2,#0x4F
    b 0x130260

.global hook_CarpetSalesmanCheckFlagOne
hook_CarpetSalesmanCheckFlagOne:
    push {r0-r12, lr}
    bl EnJs_CheckRewardFlag
    cmp r0,#1
    pop {r0-r12, lr}
    cmpne r0,#0
    bx lr

.global hook_CarpetSalesmanCheckFlagTwo
hook_CarpetSalesmanCheckFlagTwo:
    push {r0-r12, lr}
    bl EnJs_CheckRewardFlag
    cmp r0,#1
    pop {r0-r12, lr}
    addeq r1,r1,#1
    strh r1,[r0,r4]
    bx lr

.global hook_CarpetSalesmanSetFlag
hook_CarpetSalesmanSetFlag:
    push {r0-r12, lr}
    bl EnJs_SetRewardFlag
    pop {r0-r12, lr}
    mvn r0,#0xC7
    bx lr

.global hook_KakarikoGateCheck
hook_KakarikoGateCheck:
    push {r0-r12, lr}
    bl KakGate_CheckToFixBug
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_DoorOfTimeCheck
hook_DoorOfTimeCheck:
    cmp r0,#0x4
    bne 0x274B70
    push {r0-r12, lr}
    bl DoorOfTime_RequirementCheck
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_SongOfTimeJingle
hook_SongOfTimeJingle:
    mov r1,#0x0
    push {r0-r12, lr}
    bl DoorOfTime_RequirementCheck
    cmp r0,#0x1
    pop {r0-r12, lr}
    addne r0,r0,#0x4
    bx lr

.global hook_GKSetDurability
hook_GKSetDurability:
    push {r0-r12, lr}
    bl GK_SetDurability
    strh r0,[r8,#0x4a]
    pop {r0-r12, lr}
    b 0x376BE0

.global hook_SkippableText
hook_SkippableText:
    push {r0-r12, lr}
    bl Settings_GetQuickTextOption
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x2E0ED4
    ldr r0,[r5,#0x0]
    b 0x2E09C0

.global hook_InstantTextFirstLine
hook_InstantTextFirstLine:
    cmp r9,#0x0
    bgt NoInstantText
    push {r0-r12, lr}
    bl Settings_GetQuickTextOption
    cmp r0,#0x2
    pop {r0-r12, lr}
    blt NoInstantText
    push {r0-r12, lr}
    ldr r0,[r5,#0x0]
    ldr r1,[r0,#0x20]
    cpy r0,r5
    blx r1
    strb r11,[r4,#0x24]
    pop {r0-r12, lr}
NoInstantText:
    cmp r10,#0xFF
    bx lr

.global hook_InstantTextBoxBreak
hook_InstantTextBoxBreak:
    push {r0-r12, lr}
    bl Settings_GetQuickTextOption
    cmp r0,#0x2
    pop {r0-r12, lr}
    blt 0x2E0EE0
    push {r0-r12, lr}
    ldr r0,[r5,#0x0]
    ldr r1,[r0,#0x20]
    cpy r0,r5
    blx r1
    strb r11,[r4,#0x24]
    pop {r0-r12, lr}
    b 0x2E0EE0

.global hook_InstantTextRemoveOff
hook_InstantTextRemoveOff:
    push {r0-r12, lr}
    bl Settings_GetQuickTextOption
    cmp r0,#0x2
    pop {r0-r12, lr}
    bge 0x2E0ED4
    ldr r0,[r5,#0x0]
    b 0x2E06CC

.global hook_TurboTextAdvance
hook_TurboTextAdvance:
    push {r0-r12, lr}
    bl Settings_IsTurboText
    cmp r0,#0x0
    pop {r0-r12, lr}
    cmpeq r0,#0x0
    bx lr

.global hook_ItemsMenuDraw
hook_ItemsMenuDraw:
    push {r0-r12, lr}
    bl ItemsMenu_Draw
    pop {r0-r12, lr}
    b 0x2F8160

.global hook_PlaySound
hook_PlaySound:
    push {r1-r12, lr}
    bl SetBGM
    pop {r1-r12, lr}
    push {r3-r7, lr}
    b 0x35C52C

.global hook_SetBGMEntrance
hook_SetBGMEntrance:
    push {r1-r12, lr}
    bl SetBGM
    pop {r1-r12, lr}
    push {r4-r6, lr}
    b 0x33104C

.global hook_SetBGMDayNight
hook_SetBGMDayNight:
    push {r1-r12, lr}
    bl SetBGM
    pop {r1-r12, lr}
    push {r4-r6, lr}
    b 0x483C8C

.global hook_TurboTextClose
hook_TurboTextClose:
    push {r0-r12, lr}
    bl Settings_IsTurboText
    cmp r0,#0x0
    pop {r0-r12, lr}
    cmpeq r0,#0x0
    bx lr

.global hook_TurboTextSignalNPC
hook_TurboTextSignalNPC:
    movne r4,#0x1
    push {r0-r12, lr}
    bl Settings_IsTurboText
    cmp r0,#0x0
    pop {r0-r12, lr}
    movne r4,#0x1
    bx lr

.global hook_SkipSongReplayForTimeBlocksOne
hook_SkipSongReplayForTimeBlocksOne:
    add r1,r1,#0x2B00
    push {r0-r12, lr}
    bl Settings_GetSongReplaysOption
    cmp r0,#0x0
    pop {r0-r12, lr}
    beq 0x207FDC
    push {r0,r1}
    sub r1,r1,#0x70
    ldrb r0,[r1]
    cmp r0,#23
    pop {r0,r1}
    bne 0x208030
    b 0x207FDC

.global hook_SkipSongReplayForTimeBlocksTwo
hook_SkipSongReplayForTimeBlocksTwo:
    push {r0-r12, lr}
    bl Settings_GetSongReplaysOption
    cmp r0,#0x0
    pop {r0-r12, lr}
    bne 0x208028
    add r0,r0,#0x100
    b 0x207FFC

.global hook_CarpenterBossSetTradedSawFlag
hook_CarpenterBossSetTradedSawFlag:
    push {r0-r12, lr}
    bl EnToryo_SetTradedSawFlag
    pop {r0-r12, lr}
    str r0,[r4,#0xB10]
    bx lr

.global hook_KingZoraSetTradedPrescriptionFlag
hook_KingZoraSetTradedPrescriptionFlag:
    push {r0-r12, lr}
    bl EnKz_SetTradedPrescriptionFlag
    pop {r0-r12, lr}
    mov r2,#0x24
    b 0x1C52A4

.global hook_SkipSongReplayForTimeWarpBlocksOne
hook_SkipSongReplayForTimeWarpBlocksOne:
    add r1,r1,#0x2B00
    push {r0-r12, lr}
    bl Settings_GetSongReplaysOption
    cmp r0,#0x0
    pop {r0-r12, lr}
    beq 0x208040
    push {r0,r1}
    sub r1,r1,#0x70
    ldrb r0,[r1]
    cmp r0,#23
    pop {r0,r1}
    bne 0x208094
    b 0x208040

.global hook_SkipSongReplayForTimeWarpBlocksTwo
hook_SkipSongReplayForTimeWarpBlocksTwo:
    push {r0-r12, lr}
    bl Settings_GetSongReplaysOption
    cmp r0,#0x0
    pop {r0-r12, lr}
    bne 0x20808C
    add r0,r0,#0x100
    b 0x208060

.global hook_SyatekiManReminder
hook_SyatekiManReminder:
    push {r0-r12, lr}
    bl EnSyatekiMan_UseRemindText
    cmp r0,#1
    pop {r0-r12, lr}
    moveq r1,#0x9100
    addeq r1,r1,#0x40
    movne r1,#0x7100
    addne r1,r1,#0xAF
    b 0x23920C

.global hook_SkipTimeTravelCutscene
hook_SkipTimeTravelCutscene:
    push {r0-r12, lr}
    bl TimeTravelAdvanceCutsceneTimer
    pop {r0-r12, lr}
    ldmia sp!,{r4,r5,r6,pc}

.section .loader
.global hook_into_loader
hook_into_loader:
    push {r0-r12, lr}
    bl loader_main
    pop {r0-r12, lr}
    bl 0x100028
    b  0x100004
