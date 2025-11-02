.arm
.text
.syntax unified

.section .loader
.global hook_into_loader
hook_into_loader:
    push {r0-r12, lr}
    bl loader_main
    pop {r0-r12, lr}
    bl 0x100028
    b  0x100004

.section .text.randomizer_hooks

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

.global hook_Draw_PreSwapBuffers
hook_Draw_PreSwapBuffers:
    push {r0-r12, lr}
    bl Draw_PreSwapBuffers
    pop {r0-r12, lr}
    bx lr

.global hook_Gfx_SleepQueryCallback
hook_Gfx_SleepQueryCallback:
    push {r0-r12, lr}
    bl Gfx_SleepQueryCallback
    pop {r0-r12, lr}
    add r0,r0,#0x9C
    b 0x3FD6C8

.global hook_Gfx_AwakeCallback
hook_Gfx_AwakeCallback:
    push {r0-r12, lr}
    bl Gfx_AwakeCallback
    pop {r0-r12, lr}
    add r0,r0,#0x9C
    b 0x3FD440

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
    mov r0, r5
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

.global hook_OverrideDrawItemOne
hook_OverrideDrawItemOne:
    push {r1-r12, lr}
    bl ItemOverride_GetDrawItem
    pop {r1-r12, lr}
    ldrh r0,[r0]
    bx lr

.global hook_OverrideDrawItemTwo
hook_OverrideDrawItemTwo:
    add r0,r1,r0,lsl #0x1
    push {r1-r12, lr}
    bl ItemOverride_GetDrawItem
    pop {r1-r12, lr}
    bx lr

.global hook_OverrideDrawItemThree
hook_OverrideDrawItemThree:
    add r5,r0,r1,lsl #0x1
    push {r0-r4,r6-r12, lr}
    cpy r0,r5
    bl ItemOverride_GetDrawItem
    cpy r5,r0
    pop {r0-r4,r6-r12, lr}
    bx lr

.global hook_OverrideGiDrawIdPlusOne
hook_OverrideGiDrawIdPlusOne:
    push {r1-r12, lr}
    bl ItemOverride_OverrideGiDrawIdPlusOne
    pop {r1-r12, lr}
    strh r0,[r6,#0x4e]
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

.global hook_EditDrawGetItemAfterMatrixUpdate
hook_EditDrawGetItemAfterMatrixUpdate:
    push {r0-r12, lr}
    cpy r0,r1 @ SkeletonAnimationModel
    bl ItemOverride_EditDrawGetItemAfterMatrixUpdate
    pop {r0-r12, lr}
    b 0x330B98

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

.global hook_GetToken
hook_GetToken:
    push {r0-r12, lr}
    cpy r0,r4
    bl ItemOverride_GetSkulltulaToken
    pop {r0-r12, lr}
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

.global hook_ActorUpdate
hook_ActorUpdate:
    push {r0-r12, lr}
    bl Actor_rUpdate
    pop {r0-r12, lr}
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
.if _EUR_==1
    b 0x45F230
.else
    b 0x45F210
.endif

.global hook_LullabyCheckFlag
hook_LullabyCheckFlag:
    push {r0-r12, lr}
    bl Cutscene_CheckLullabyFlag
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_FishingIgnoreTempBOne
hook_FishingIgnoreTempBOne:
    bne 0x2C3A14
    push {r0-r12, lr}
    bl isFishing
    cmp r0,#0x1
    pop {r0-r12, lr}
    bne 0x2C3998
    moveq r0,#89
    b 0x2C3A14

.global hook_FishingIgnoreTempBTwo
hook_FishingIgnoreTempBTwo:
    blt 0x34CFD0
    push {r0-r12, lr}
    bl isFishing
    cmp r0,#0x1
    pop {r0-r12, lr}
    bne 0x34CFF0
    ldrb r1,[r4,#0x80]
    b 0x34CFD0

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
    cmp r0,#0x7
    cpylt r8,r0
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

.global hook_DungeonCheckJabuMQBox
hook_DungeonCheckJabuMQBox:
    push {r0-r12, lr}
    bl Dungeon_GetCurrentDungeonMode
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_JabuSwitchRutoCheck
hook_JabuSwitchRutoCheck:
    cmp r0,#0xA1
    bxeq lr
    cmp r0,#0x110
    bx lr

.global hook_JabuBoxCheckRuto
hook_JabuBoxCheckRuto:
    tst r0,#0x80
    push {r0-r12, lr}
    bleq ObjKibako_CheckRuto
    cmpeq r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_CanReadHints
hook_CanReadHints:
    push {r0-r12, lr}
    bl Hints_CanReadHints
    cmp r0,#0x1
    pop {r0-r12, lr}
    # Cannot read hints, show this text
    # "What do you suppose this stone is?"
    movne r0,#0x100
    addne r0,r0,#0xB1
    bxne lr
    push {r0-r12, lr}
    bl Hints_GetHintsSetting
    cmp r0,#0x0
    pop {r0-r12, lr}
    # Vanilla hints, can read them (wearing mask)
    # "Responding to your mask..."
    moveq r0,#0x2000
    addeq r0,r0,#0x54
    bxeq lr
    # Randomizer hints enabled, can read them
    # Hint message, skipping other text
    ldrh r0,[r4,#0x1C]
    and r0,r0,#0xFF
    add r0,r0,#0x400
    bx lr

.global hook_GossipStoneAddSariaHint
hook_GossipStoneAddSariaHint:
    ldrh r0,[r5,#0x16]
    push {r0-r12, lr}
    add r0,r0,#0x600
    bl Hints_AddSariasSongHint
    pop {r0-r12, lr}
    bx lr

.global hook_FastChests
hook_FastChests:
    push {r0-r12, lr}
    bl Chest_OverrideAnimation
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

.global hook_FWUnset
hook_FWUnset:
    push {r0-r12, lr}
    bl MagicWind_Unset
    mov r0,#-0x1
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_FWGetSet
hook_FWGetSet:
    push {r0-r12, lr}
    bl MagicWind_CheckSet
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x351A64
    b 0x3519D0

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

.global hook_SetGameOverRespawnFlag
hook_SetGameOverRespawnFlag:
    push {r0-r12, lr}
    bl Grotto_ForceGrottoReturn
    pop {r0-r12, lr}
    cmp r8,#0x3
    bx lr

.global hook_SetSunsSongRespawnFlag
hook_SetSunsSongRespawnFlag:
    push {r0-r12, lr}
    bl Grotto_ForceGrottoReturn
    pop {r0-r12, lr}
    cpy r0,r6
    bx lr

.global hook_SunsSongEndCloseTextbox
hook_SunsSongEndCloseTextbox:
    push {r0-r12, lr}
    bl Settings_SunsSongEndCloseTextbox
    pop {r0-r12, lr}
.if _EUR_==1
    b 0x45B538
.else
    b 0x45B518
.endif

.global hook_SetSpecialVoidOutRespawnFlag
hook_SetSpecialVoidOutRespawnFlag:
    push {r0-r12, lr}
    bl Grotto_ForceRegularVoidOut
    pop {r0-r12, lr}
    mov r1,#0x104
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

.global hook_GearMenuEmptySlot
hook_GearMenuEmptySlot:
    push {r0,r2-r12, lr}
    bl   GearMenu_GetRewardHint
    cpy  r1,r0
    pop  {r0,r2-r12, lr}
    cmp  r1,#0x0
    beq  0x2E9A1C @ clear tex box
    mov  r2,#0x1
    b    0x2E9A3C @ print reward hint

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
.if _EUR_==1
    b 0x483CAC
.else
    b 0x483C8C
.endif

.global hook_SetBGMEvent
hook_SetBGMEvent:
    push {r0, r2-r12, lr}
    cpy r0,r1
    bl SetBGM
    cpy r1,r0
    pop {r0, r2-r12, lr}
    push {r4-r11, lr}
    b 0x36EC44

.global hook_SetSFX
hook_SetSFX:
    push {r1-r12, lr}
    bl SetSFX
    pop {r1-r12, lr}
    push {r0-r11, lr}
    b 0x375480

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
    @ If about to warp to credits, signal NPC so that
    @ the collection flag is set before the game is saved
    bleq Triforce_IsWaitingForText
    cmp r0,#0x0
    pop {r0-r12, lr}
    movne r4,#0x1
    bx lr

.global hook_SkipSongReplays_TimeBlocksFix
hook_SkipSongReplays_TimeBlocksFix:
    bne 0x208008
    push  {r0-r12, lr}
    bl Settings_GetSongReplaysOption
    cmp r0,#0x0
    pop {r0-r12, lr}
    moveq r1,#0x6E
    movne r1,#0x10
    cmp r0,r0
    b 0x208008

.global hook_SkipSongReplays_WarpBlocksFix
hook_SkipSongReplays_WarpBlocksFix:
    bne 0x20806C
    push  {r0-r12, lr}
    bl Settings_GetSongReplaysOption
    cmp r0,#0x0
    pop {r0-r12, lr}
    moveq r1,#0x6E
    movne r1,#0x10
    cmp r0,r0
    b 0x20806C

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

.global hook_SkipTimeTravelCutsceneOne
hook_SkipTimeTravelCutsceneOne:
    push {r0-r12, lr}
    bl TimeTravelAdvanceCutsceneTimer
    pop {r0-r12, lr}
    ldmia sp!,{r4,r5,r6,pc}

.global hook_SkipTimeTravelCutsceneTwo
hook_SkipTimeTravelCutsceneTwo:
    push {r0-r12, lr}
    bl SetTimeTraveled
    pop {r0-r12, lr}
    mov r1,#0x324
    bx lr

.global hook_SkipMasterSwordFanfare
hook_SkipMasterSwordFanfare:
    push {r0-r12, lr}
    bl ShouldSkipMasterSwordCutscene
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x3E5F7C
    mov r1,#0x0
    bx lr

.global hook_EnteredLocation
hook_EnteredLocation:
    cpy r4,r0
    push {r0-r12, lr}
    bl Entrance_EnteredLocation
    pop {r0-r12, lr}
    bx lr

.global hook_LostWoodsBridgeMusic
hook_LostWoodsBridgeMusic:
    push {r0-r12, lr}
    bl Entrance_IsLostWoodsBridge
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_BeforeLoadGame
hook_BeforeLoadGame:
    add r0, r4, r5
    push {r0-r12, lr}
    bl SaveFile_BeforeLoadGame
    pop {r0-r12, lr}
.if _EUR_==1
    b 0x4473A4
.else
    b 0x447384
.endif

.global hook_AfterLoadGame
hook_AfterLoadGame:
    push {r0-r12, lr}
    bl SaveFile_AfterLoadGame
    pop {r0-r12, lr}
    pop {r4-r6, pc}

.global hook_FileSelect_CopyFile
hook_FileSelect_CopyFile:
    push {r0-r12, lr}
    bl SaveFile_BeforeCopy
    pop {r0-r12, lr}
    sub sp,sp,#0x240
    bx lr

.global hook_SaveGame
hook_SaveGame:
    cmp r5, #0
    beq .notSaving
    push {r0-r12, lr}
    ldrb r0, [r5, #42]
    adds r0, #-0x30
    bl SaveFile_SaveExtSaveData
    pop {r0-r12, lr}
.notSaving:
    push {r4-r9, lr}
    b 0x2fbfac

.global hook_SaveMenuIgnoreOpen
hook_SaveMenuIgnoreOpen:
    push {r0-r12, lr}
    bl SaveMenu_IgnoreOpen
    cmp r0,#0x1
    pop {r0-r12, lr}
.if _EUR_==1
    beq 0x42F294
.else
    beq 0x42F270
.endif
    bx lr

.global hook_GameOverStart
hook_GameOverStart:
    push {r0-r12, lr}
    bl SaveFile_OnGameOver
    pop {r0-r12, lr}
    bx lr

.global hook_PermadeathSkipMenu
hook_PermadeathSkipMenu:
    push {r0-r12, lr}
    bl Permadeath_GetOption
    cmp r0,#0x0
    pop {r0-r12, lr}
    movne r0,#0x10
    moveq r0,#0x2
    bx lr

.global hook_PermadeathForceQuit
hook_PermadeathForceQuit:
    ldrbeq r8,[r11,#0x9]
    bxne lr
    push {r0-r12, lr}
    bl Permadeath_GetOption
    cmp r0,#0x0
    pop {r0-r12, lr}
.if _EUR_==1
    bne 0x459014
.else
    bne 0x458FF4
.endif
    bxeq lr

.global hook_OverrideFogDuringGameplayInit
hook_OverrideFogDuringGameplayInit:
    push {r0-r12, lr}
    bl Fog_OverrideState
    pop {r0-r12, lr}
    bx lr

.global hook_SkipTwinrovaQuarrelCutscene
hook_SkipTwinrovaQuarrelCutscene:
    mov r0,#0x500
    add r0,r0,#0x9
    bx lr

.global hook_FixItemsMenuSlotDuplication
hook_FixItemsMenuSlotDuplication:
    mov r4,#0xFF
    mov lr,#0xFF
    add r10,r10,#0x1
.if _EUR_==1
    b 0x456BB4
.else
    b 0x456B94
.endif

.global hook_PlayEntranceCutscene
hook_PlayEntranceCutscene:
.if _EUR_==1
    bgt 0x44F0C4
.else
    bgt 0x44F0A4
.endif
    push {r0-r12, lr}
    ldrb r0,[r5,#0x3]
    bl EntranceCutscene_ShouldPlay
    cmp r0,#0x0
    pop {r0-r12, lr}
.if _EUR_==1
    beq 0x44F0C4
    b 0x44F08C
.else
    beq 0x44F0A4
    b 0x44F06C
.endif

.global hook_SkipJabuOpeningCutscene
hook_SkipJabuOpeningCutscene:
    ldrh r0,[r0,#0x0]
    push {r0-r12, lr}
    bl Jabu_SkipOpeningCutscene
    pop {r0-r12, lr}
    bx lr

.global hook_MultiplyPlayerSpeed
hook_MultiplyPlayerSpeed:
    vldr.32 s0,[r6,#0x21C]
    push {r0-r12, lr}
    bl Player_GetSpeedMultiplier
    vmov s1,r0
    pop {r0-r12, lr}
    vmul.f32 s0,s1
    bx lr

.global hook_RunAnimationSpeed
hook_RunAnimationSpeed:
    vldr.32 s17,[r5,#0x21C]
    push {r0-r12, lr}
    bl Player_GetSpeedMultiplier
    vmov s1,r0
    pop {r0-r12, lr}
    vmul.f32 s17,s1
    bx lr

.global hook_NaviNotifications
hook_NaviNotifications:
    push {r0-r12, lr}
    bl Navi_GetNotificationOption
    cmp r0,#0x1
    pop {r0-r12, lr}
    # Silenced
    blt 0x267E3C
    # Constant
    bgt 0x267E14
    # Normal
    ldr r0,[r0,#0x4C]
    bx lr

.global hook_ChestMinigame_KeyChestVisibility
hook_ChestMinigame_KeyChestVisibility:
    push {r0-r12, lr}
    bl Settings_GetChestMinigameOption
    cmp r0,#0x0
    pop {r0-r12, lr}
    orrne r10,r7,#0x0
    orreq r10,r7,#0x4000
    bx lr

.global hook_ChestMinigame_DontOpenChestsOnInit
hook_ChestMinigame_DontOpenChestsOnInit:
    cmp r0,#0x0
    bxeq lr
    push {r0-r12, lr}
    bl Settings_GetChestMinigameOption
    cmp r0,#0x1
    cmpgt r0,r0
    pop {r0-r12, lr}
    bx lr

.global hook_GameplayDestroy
hook_GameplayDestroy:
    cpy r4,r0
    push {r0-r12, lr}
    bl Entrance_CheckEpona
    pop {r0-r12, lr}
    bx lr

.global hook_SceneExitOverride
hook_SceneExitOverride:
    ldrsh r9, [r1,r0]
    push {r0-r8, r10-r12, lr}
    cpy r0, r9
    bl Entrance_OverrideNextIndex
    cpy r9, r0
    pop {r0-r8, r10-r12, lr}
    bx lr

.global hook_SceneExitDynamicOverride
hook_SceneExitDynamicOverride:
    push {r0-r12, lr}
    bl Entrance_OverrideDynamicExit
    pop {r0-r12, lr}
    bx lr

.global hook_OverrideGrottoActorEntrance
hook_OverrideGrottoActorEntrance:
    push {r0-r12, lr}
    cpy r0, r4
    bl Grotto_OverrideActorEntrance
    pop {r0-r12, lr}
    b 0x3F22C4

.global hook_ReturnFW
hook_ReturnFW:
    push {r0-r12, lr}
    bl Grotto_SetupReturnInfoOnFWReturn
    pop {r0-r12, lr}
    add sp,sp,#0x8
    bx lr

.global hook_WarpSongEntranceOverride
hook_WarpSongEntranceOverride:
    push {r0-r1, r3-r12, lr}
    cpy r0, r2
    bl Entrance_OverrideNextIndex
    cpy r2, r0
    pop {r0-r1, r3-r12, lr}
    strh r2,[r1,#0x1c]
    bx lr

.global hook_OwlEntranceOverride
hook_OwlEntranceOverride:
    push {r0, r2-r12, lr}
    cpy r0, r1
    bl Entrance_OverrideNextIndex
    cpy r1, r0
    pop {r0, r2-r12, lr}
    b 0x3716F0

.global hook_SavewarpSetRespawnFlag
hook_SavewarpSetRespawnFlag:
    push {r0-r12, lr}
    bl Grotto_ForceGrottoReturnOnSpecialEntrance
    pop {r0-r12, lr}
    mov r0,#0xFF
    bx lr

.global hook_AdultItemsCMABsAsChild
hook_AdultItemsCMABsAsChild:
    push {r0-r12, lr}
    bl Player_ShouldApplyAdultItemsCMABs
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_Model_EnableMeshGroupByIndex
hook_Model_EnableMeshGroupByIndex:
    push {r0,r2-r12,lr}
    bl Model_OverrideMesh
    cpy r1,r0
    pop {r0,r2-r12,lr}
    b 0x4C8B8C

.global hook_ArrowsOrSeeds
hook_ArrowsOrSeeds:
    push {r0-r12, lr}
    bl Player_ShouldUseSlingshot
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_HookshotDrawChain
hook_HookshotDrawChain:
    push {r0-r12, lr}
    bl Player_IsAdult
    cmp r0,#0x0
    pop {r0-r12, lr}
    beq 0x2202BC
    ldr r0,[r4,#0x290]
    b 0x2202A4

.global hook_HookshotRotation
hook_HookshotRotation:
    push {r0-r12, lr}
    bl Hookshot_GetZRotation
    vmov.f32 s0,r0
    pop {r0-r12, lr}
    bx lr

.global hook_LinkReflection
hook_LinkReflection:
    push {r0-r12, lr}
    bl Player_IsAdult
    cmp r0,#0x1
    pop {r0-r12, lr}
    streq r1,[r0,#0x714]
    bx lr

.global hook_ChildCanOpenBowSubMenu
hook_ChildCanOpenBowSubMenu:
    push {r0-r12, lr}
    bl Settings_BowAsChild
    cmp r0,#0x1
    pop {r0-r12, lr}
    beq 0x2EB2DC
    cmp r12,#0x0
    b 0x2EB2DC

.global hook_RedBoulderExplode
hook_RedBoulderExplode:
    ldrb r0,[r5,#0x1B5]
    push {r0-r12, lr}
    cpy r0,r5
    bl ObjHamishi_HitCount
    cmp r0,#0x2
    pop {r0-r12, lr}
    bge 0x26FE9C
    b 0x26FE80

.global hook_Multiplayer_UpdatePrevActorFlags
hook_Multiplayer_UpdatePrevActorFlags:
    str r0,[r5,#0x1b8]
    push {r0-r12, lr}
    bl Multiplayer_Sync_UpdatePrevActorFlags
    pop {r0-r12, pc}

.global hook_Multiplayer_OnLoadFile
hook_Multiplayer_OnLoadFile:
    strh r6,[r0,#0x4C]
    push {r0-r12, lr}
    bl Multiplayer_OnFileLoad
    pop {r0-r12, lr}
.if _EUR_==1
    b 0x449F20
.else
    b 0x449F00
.endif

.global hook_SendDroppedBottleContents
hook_SendDroppedBottleContents:
    add r0,r0,#0x8C
    push {r0-r12, lr}
    cpy r0,r2
    vmov r1,s0
    vmov r2,s1
    vmov r3,s2
    bl SendDroppedBottleContents
    pop {r0-r12, lr}
    bx lr

.global hook_IgnoreMaskReaction
hook_IgnoreMaskReaction:
    ldrh r0,[r0,#0x0]
    push {r0-r12, lr}
    cpy r0,r4
    bl SaveFile_GetIgnoreMaskReactionOption
    cmp r0,#0x1
    pop {r0-r12, lr}
    moveq r0,#0x0
    b 0x36BBC8

.global hook_MasterQuestGoldSkulltulaCheck
hook_MasterQuestGoldSkulltulaCheck:
    push {r0-r5,r7-r12, lr}
    bl Settings_IsMasterQuestDungeon
    cpy r6,r0
    pop {r0-r5,r7-r12, lr}
    b 0x3415CC

.global hook_WaterSpoutMasterQuestCheck
hook_WaterSpoutMasterQuestCheck:
    push {r1-r12, lr}
    bl Settings_IsMasterQuestDungeon
    pop {r1-r12, lr}
    bx lr

.global hook_PierreSoftlockFixTwo
hook_PierreSoftlockFixTwo:
    cpy r6,r1
    push {r0-r12, lr}
    mov r2,#0x1
    mov r1,#0x0
    cpy r0,r6
    bl 0x36E980
    pop {r0-r12, lr}
    bx lr

.global hook_StoreTargetActorType
hook_StoreTargetActorType:
    push {r0-r12, lr}
    cpy r0,r6
    bl Fairy_StoreTargetActorType
    pop {r0-r12, lr}
    cmp r5,#0x0
    bx lr

.global hook_ForceTrailEffectUpdate
hook_ForceTrailEffectUpdate:
    push {r1-r12, lr}
    cpy r0,r4
    bl forceTrailEffectUpdate
    pop {r1-r12, lr}
    cmp r0,#0x10
    bx lr

.global hook_RainbowSwordTrail
hook_RainbowSwordTrail:
    push {r0-r12, lr}
    bl updateSwordTrailColors
    pop {r0-r12, lr}
    add r8,r7,#0x100
    bx lr

.global hook_BoomerangTrailEffect
hook_BoomerangTrailEffect:
    push {r0-r12, lr}
    bl updateBoomerangTrailEffect
    cmp r0,#0x1
    pop {r0-r12, lr}
    bne 0x1F4228
    strb r4,[r0,#0x282]
    bx lr

.global hook_RainbowChuTrail
hook_RainbowChuTrail:
    push {r0-r12, lr}
    bl updateChuTrailColors
    cmp r0,#0x1
    pop {r0-r12, lr}
    addne pc,lr,#0x4
    strb r7,[r0,#0x282]
    bx lr

.global hook_TimerExpiration
hook_TimerExpiration:
    mov r0,#0x5
    push {r0-r12,lr}
    bl IceTrap_IsCurseActive
    cmp r0,#0x1
    pop {r0-r12,lr}
    bxne lr
    add lr,lr,#0x30
    mov r0,#0x0
    strh r0,[r4,#0x62]
    bx lr

.global hook_FWandWarpSongTimerDepletion
hook_FWandWarpSongTimerDepletion:
    moveq r1,#0x1
    movne r1,#0xEF
    push {r0-r12,lr}
    bl IceTrap_IsCurseActive
    cmp r0,#0x1
    pop {r0-r12,lr}
    bxeq lr
    strh r1,[r0,#0x64]
    bx lr

.global hook_Timer2TickSound
hook_Timer2TickSound:
    push {r0-r12,lr}
    bl IceTrap_IsCurseActive
    cmp r0,#0x1
    pop {r0-r12,lr}
    addeq lr,lr,#0x4
    cmp r0,#0x3C
    bx lr

.global hook_CurseTrapDizzyStick
hook_CurseTrapDizzyStick:
    push {r0-r12,lr}
    bl IceTrap_ReverseStick
    pop {r0-r12,lr}
    b 0x2FF258

.global hook_CurseTrapDizzyButtons
hook_CurseTrapDizzyButtons:
    push {r0,r3-r12,lr}
    # R1 and R2 contain button status fields
    # Apply the curse effect to both
    push {r2}
    cpy r0,r1
    bl IceTrap_RandomizeButtons
    pop {r2}
    push {r0}
    cpy r0,r2
    bl IceTrap_RandomizeButtons
    cpy r2,r0
    pop {r1}
    pop {r0,r3-r12,lr}
    stmia r0,{r1,r2,r3,r5,r6,r7,r8,r9,r10,r11,r12,lr}
.if _EUR_==1
    b 0x41AC04
.else
    b 0x41ABE0
.endif

.global hook_CrouchStabHitbox
hook_CrouchStabHitbox:
    push {r0-r12,lr}
    bl IceTrap_IsSlashHitboxDisabled
    cmp r0,#0x0
    pop {r0-r12,lr}
    movne r10,#0xFF
    strb r10,[r6,#0x227]
    bx lr

.global hook_BossChallenge_Enter
hook_BossChallenge_Enter:
    push {r0-r12,lr}
    bl BossChallenge_Enter
    pop {r0-r12,lr}
    cpy r4,r0
    bx lr

.global hook_BossChallenge_ExitMenu
hook_BossChallenge_ExitMenu:
    push {r0-r12,lr}
    cpy r0,r8
    bl BossChallenge_ExitMenu
    pop {r0-r12,lr}
    cmp r8,#0x0
    bx lr

.global hook_RestoreISG
hook_RestoreISG:
    push {lr}
    push {r0-r12}
    bl Settings_IsIsgEnabled
    cmp r0,#0x0
    pop {r0-r12}
    bleq 0x34BBFC @Function that cancels ISG
    pop {lr}
    bx lr

.global hook_GrannyTextID
hook_GrannyTextID:
    push {r1-r12,lr}
    bl EnDs_GetTextID
    pop {r1-r12,lr}
    bx lr

.global hook_GrannyBottleCheck
hook_GrannyBottleCheck:
    push {r0-r12,lr}
    bl EnDs_ShouldIgnoreBottle
    cmp r0,#0x0
    pop {r0-r12,lr}
    beq 0x377A04 @Check for bottle
    bx lr

.global hook_GrannyItemOverride
hook_GrannyItemOverride:
    push {r0,r1,r3-r12,lr}
    bl EnDs_ItemOverride
    cpy r2,r0
    pop {r0,r1,r3-r12,lr}
    b 0x3724DC @GiveItem

.global hook_GrannySetRewardFlag
hook_GrannySetRewardFlag:
    push {r0-r12,lr}
    bl EnDs_SetRewardFlag
    pop {r0-r12,lr}
    mov r0,#0x0
    bx lr

.global hook_BecomeAdult
hook_BecomeAdult:
    strh r3,[r2,#0x5e]
    push {r0-r12,lr}
    bl SaveFile_BecomeAdult
    cmp r0,#0x0
    pop {r0-r12,lr}
    ldrb r3,[r2,#0x60]
    bx lr

.global hook_SwordlessPatchCheck
hook_SwordlessPatchCheck:
    cmp r1,#0x0
    bxne lr
    push {r0-r12,lr}
    bl SaveFile_SwordlessPatchesEnabled
    cmp r0,#0x0
    pop {r0-r12,lr}
    bx lr

.global hook_HandleBButton
hook_HandleBButton:
    cmp r0,#0x3B
    cmpne r0,#0x3C
    cmpne r0,#0x3D
    cmpne r0,#0xFE
    bx lr

.global hook_LoadFileSwordless
hook_LoadFileSwordless:
    push {lr}
    push {r0-r12}
    bl SaveFile_LoadFileSwordless
    pop {r0-r12}
    bl hook_SwordlessPatchCheck
    pop {lr}
    bx lr

.global hook_GanonRestoreMSOnDeath
hook_GanonRestoreMSOnDeath:
    tst r0,r1
    bxne lr
    push {r0-r12,lr}
    bl SaveFile_SwordlessPatchesEnabled
    cmp r0,#0x0
    pop {r0-r12,lr}
    bx lr

.global hook_CriticalHealthCheck
hook_CriticalHealthCheck:
    cmp r0,#0x10
    movle r0,#0x00
    bxle lr
    cmp r0,#0x50
    movle r0,#0x10
    bxle lr
    cmp r0,#0xA0
    movle r0,#0x18
    bx lr

.global hook_InitSceneMirrorWorld
hook_InitSceneMirrorWorld:
    push {r0-r12,lr}
    bl Entrance_UpdateMQFlag
    pop {r0-r12,lr}
    cpy r4,r0
    bx lr

.global hook_InitSceneEntranceOverride
hook_InitSceneEntranceOverride:
    push {r0-r12,lr}
    bl Entrance_OverrideSpawnScene
    pop {r0-r12,lr}
    mov r0, #0x14
    bx lr

.global hook_CollisionATvsAC
hook_CollisionATvsAC:
    ldr r12,[sp,#0x18]
    push {r0-r12,lr}
    cpy r0,r1  @ AT collider
    cpy r1,r12 @ AC collider
    bl Actor_CollisionATvsAC
    cmp r0,#0x1
    pop {r0-r12,lr}
    bxeq lr
    b 0x3192E4

.global hook_CollisionCheck_SetAll_Once
hook_CollisionCheck_SetAll_Once:
    cpy r5,r2
    push {r0-r12,lr}
    bl HyperActors_GetExtraUpdate
    cmp r0,#0x1
    pop {r0-r12,lr}
    addeq lr,#0x8
    bx lr

.global hook_GanonDrawMasterSword
hook_GanonDrawMasterSword:
    ldrh r0,[r4,#0x2E]
    push {r0-r12,lr}
    bl SaveFile_SwordlessPatchesEnabled
    cmp r0,#0x0
    pop {r0-r12,lr}
    bxeq lr
    strb r10,[r4,#0x0] @ delete MS effect
    bx lr

.global hook_SetFWPlayerParams
hook_SetFWPlayerParams:
    push {r0-r9,r11-r12,lr}
    bl Grotto_ChooseFWPlayerParams
    mov r10,r0
    pop {r0-r9,r11-r12,lr}
    bx lr

.global hook_AboutToPickUpActor
hook_AboutToPickUpActor:
    ldrh r0,[r7]
    push {r0-r12,lr}
    mov r0,r7
    bl Player_CanPickUpThisActor
    cmp r0,#0x0
    pop {r0-r12,lr}
    subeq lr,lr,#0x8
    bx lr

.global hook_TargetReticleColor
hook_TargetReticleColor:
    mov r4,#0x0
    push {r0-r12,lr}
    cpy r0,r6 @ Target Context
    bl Fairy_SetTargetReticleColor
    cmp r0,#0x0
    pop {r0-r12,lr}
    bxeq lr    @ no custom Navi colors, return to original code
.if _EUR_==1   @ colors applied, skip original code
    b 0x47B308
.else
    b 0x47B2E8
.endif

.global hook_TargetPointerColor
hook_TargetPointerColor:
    ldr r0,[r6,#0x120]
    push {r0-r12,lr}
    cpy r0,r6 @ Target Context
    cpy r1,r4 @ Targeted actor
    bl Fairy_SetTargetPointerColor
    cmp r0,#0x0
    pop {r0-r12,lr}
    bxeq lr    @ no custom Navi colors, return to original code
.if _EUR_==1   @ colors applied, skip original code
    b 0x47BB50
.else
    b 0x47BB30
.endif

.global hook_ShadowShip_Speed
hook_ShadowShip_Speed:
    add r0,r4,#0x6C
    push {r0-r12,lr}
    vpush {s0-s1}
    bl ShadowShip_HasActiveStalfos
    vpop {s0-s1}
    cmp r0,#0x1
    mov r0,#0x5
    vmov s2,r0
    vcvt.f32.s32 s2,s2
    pop {r0-r12,lr}
    vmul.f32 s1,s2
    bxeq lr
    vmul.f32 s0,s2
    bx lr

.global hook_MaskSalesmanBorrowMask
hook_MaskSalesmanBorrowMask:
    ldrsh r1,[r6,#0x1C]
    push {r0-r12,lr}
    cpy r0,r1
    bl SaveFile_BorrowMask
    pop {r0-r12,lr}
    bx lr

.global hook_MaskSalesmanGiveMaskOfTruth
hook_MaskSalesmanGiveMaskOfTruth:
    orr r1,r1,#0x400
    push {r0-r12,lr}
    mov r0,#0x22 @ Mask of Truth SI id
    bl SaveFile_BorrowMask
    pop {r0-r12,lr}
    bx lr

.global hook_OoBBombchuOne
hook_OoBBombchuOne:
    cmp r5,#0x0
    bxeq lr
    ldrsh r0,[r5,#0xA]
    bx lr

.global hook_OoBBombchuTwo
hook_OoBBombchuTwo:
    cmp r5,#0x0
    bxeq lr
    ldrsh r0,[r5,#0xC]
    bx lr

.global hook_OoBBombchuThree
hook_OoBBombchuThree:
    cmp r5,#0x0
    bxeq lr
    ldrsh r0,[r5,#0xE]
    bx lr

.global hook_BombchuShopInfinitePurchases
hook_BombchuShopInfinitePurchases:
    ldrsh r3,[r1,#0x1C]
    push {r0-r12,lr}
    bl Settings_IsLogicVanilla
    cmp r0,#0x1
    pop {r0-r12,lr}
    movne r3,#0x0 @ Skip setting itemGetInf flag
    b 0x188D40

.global hook_CamRoll
hook_CamRoll:
    push {r0,lr}
    mov r0,#0x0
    strh r0,[r5,#0xA2]
    pop {r0}
    blx r1
    push {r0}
    ldrh r0,[r5,#0xA2]
    bl IceTrap_CamRoll
    strh r0,[r5,0xA2]
    pop {r0,lr}
    bx lr

.global hook_CamUpdate
hook_CamUpdate:
    push {r0-r12,lr}
    cpy r0,r1
    bl Camera_FreeCamEnabled
    cmp r0,#0x0
    pop {r0-r12,lr}
    cpyeq r6,r0
    bxeq lr
    bl Camera_FreeCamUpdate
    ldmia sp!,{r4-r11,pc}

.global hook_Sheik_GetTextID
hook_Sheik_GetTextID:
    push {r0, r2-r12, lr}
    cpy r0,r4
    bl Sheik_GetTextID
    cpy r1,r0
    pop {r0, r2-r12, lr}
    b 0x2A4B4C

.global hook_OnActorSetup_SceneChange
hook_OnActorSetup_SceneChange:
    cpy r4,r5
    push {r0-r12, lr}
    cpy r0,r5
    cpy r1,r6
    bl ActorSetup_OverrideEntry
    cmp r0,#0x1
    pop {r0-r12, lr}
    # Continue like normal
    bxne lr
    # Iterate actor entry pointer and skip
    add r5,#0x10
.if _EUR_==1
    b 0x4522C4
.else
    b 0x4522A4
.endif

.global hook_AfterActorSetup_SceneChange
hook_AfterActorSetup_SceneChange:
    strb r0,[r7,#0xC03]
    push {r0-r12, lr}
    bl ActorSetup_Extra
    pop {r0-r12, lr}
.if _EUR_==1
    b 0x4522DC
.else
    b 0x4522BC
.endif

.global hook_OnActorSetup_RoomChange
hook_OnActorSetup_RoomChange:
    cpy r4,r6
    push {r0-r12, lr}
    cpy r0,r6
    cpy r1,r7
    bl ActorSetup_OverrideEntry
    cmp r0,#0x1
    pop {r0-r12, lr}
    # Continue like normal
    bxne lr
    # Iterate actor entry pointer and skip
    add r6,#0x10
.if _EUR_==1
    b 0x461444
.else
    b 0x461424
.endif

.global hook_AfterActorSetup_RoomChange
hook_AfterActorSetup_RoomChange:
    strb r10,[r8,#0xC03]
    push {r0-r12, lr}
    bl ActorSetup_Extra
    pop {r0-r12, lr}
.if _EUR_==1
    b 0x461458
.else
    b 0x461438
.endif

.global hook_RandomGsLoc_CustomTangibilityCheck
hook_RandomGsLoc_CustomTangibilityCheck:
    sub sp,sp,#0x18
    push {r0-r12, lr}
    mov r1,#0x1
    mov r2,#0x0
    bl Gs_HasAltLoc
    cmp r0,#0x1
    pop {r0-r12, lr}
    # Has original location, run original function
    bne 0x3415B4
    push {r0-r12, lr}
    bl Gs_CustomTangibilityCheck
    cmp r0,#0x1
    pop {r0-r12, lr}
    # Return true
    beq 0x341BDC
    # Return false
    b 0x341BEC

.global hook_RandomGsLoc_CustomTokenSpawnOffset
hook_RandomGsLoc_CustomTokenSpawnOffset:
    vadd.f32 s0,s3,s0
    push {r0-r12, lr}
    cpy r0,r4
    mov r1,#0x1
    mov r2,#0x0
    bl Gs_HasAltLoc
    cmp r0,#0x1
    pop {r0-r12, lr}
    bxne lr
    push {r0-r12, lr}
    cpy r0,r4
    bl Gs_GetCustomTokenSpawnPos
    vldr s0,[r0,#0x0]
    vldr s1,[r0,#0x4]
    vldr s2,[r0,#0x8]
    pop {r0-r12, lr}
    bx lr

.global hook_RandomGsLoc_BlockSpawn_Crate
hook_RandomGsLoc_BlockSpawn_Crate:
    push {r0-r12, lr}
    cpy r0,r4
    mov r1,#0x2
    mov r2,#0x1
    bl Gs_HasAltLoc
    cmp r0,#0x1
    pop {r0-r12, lr}
    # If true
    beq 0x3BCAA4
    # If false
    orr r0,r2,#0x8000
    bx lr

.global hook_RandomGsLoc_BlockSpawn_Tree
hook_RandomGsLoc_BlockSpawn_Tree:
    push {r0-r12, lr}
    cpy r0,r4
    mov r1,#0x3
    mov r2,#0x1
    bl Gs_HasAltLoc
    cmp r0,#0x1
    pop {r0-r12, lr}
    # If true
    beq 0x16C47C
    # If false
    orr r0,r0,#0xE000
    bx lr

.global hook_RandomGsLoc_BlockSpawn_Soil
hook_RandomGsLoc_BlockSpawn_Soil:
    push {r0-r12, lr}
    cpy r0,r4
    mov r1,#0x4
    mov r2,#0x1
    bl Gs_HasAltLoc
    cmp r0,#0x1
    pop {r0-r12, lr}
    # If true
    beq 0x3BF6D0
    # If false
    ldrh r0,[r4,#0x1C]
    bx lr

.global hook_RandomGsLoc_SkipSoilJingle
hook_RandomGsLoc_SkipSoilJingle:
    push {r0-r12, lr}
    mov r1,#0x4
    mov r2,#0x1
    bl Gs_HasAltLoc
    cmp r0,#0x1
    pop {r0-r12, lr}
    # If true
    beq 0x15DC34
    # If false
    ldrsh r0,[r0,#0x1C]
    bx lr

.global hook_ActorDraw
hook_ActorDraw:
    push {r0-r12, lr}
    bl Actor_rDraw
    pop {r0-r12, lr}
    bx lr

.global hook_FlyingPotCollision
hook_FlyingPotCollision:
    strh r0,[r4,#0xBE]
    push {r0-r12, lr}
    cpy r0,r4 @ Actor
    bl FlyingTraps_Pot_OnImpact
    cmp r0,#0x1
    pop {r0-r12, lr}
    bne 0x11DEE4 @ Skip collision checks and return
    bx lr

.global hook_FlyingTileCollision
hook_FlyingTileCollision:
    cpy r0,r5
    push {r0-r12, lr}
    cpy r0,r4 @ Actor
    bl FlyingTraps_Tile_OnImpact
    cmp r0,#0x1
    pop {r0-r12, lr}
    addne lr,lr,#0x8 @ Skip setting actionFunc
    bx lr

.global hook_ShabomAfterDamagePlayer
hook_ShabomAfterDamagePlayer:
    push {r0-r12, lr}
    bl Shabom_CheckEnemySoul
    cmp r0,#0x0
    pop {r0-r12, lr}
    beq 0x3B511C @ Skip popping
    strh r10,[r5,#0x80]
    bx lr

.global hook_DodongoAfterSwallowBomb
hook_DodongoAfterSwallowBomb:
    mov r1,#0xA
    push {r0-r12, lr}
    cpy r0,r4 @ Actor
    bl Dodongos_AfterSwallowBomb_Normal
    cmp r0,#0x0
    pop {r0-r12, lr}
    bne 0x11E4F4
    bx lr

.global hook_BabyDodongoAfterSwallowBomb
hook_BabyDodongoAfterSwallowBomb:
    mov r3,#0x8
    push {r0-r12, lr}
    cpy r0,r4 @ Actor
    bl Dodongos_AfterSwallowBomb_Baby
    cmp r0,#0x0
    pop {r0-r12, lr}
    bne 0x1C4370
    bx lr

.global hook_OcarinaNoteButtonsDraw
hook_OcarinaNoteButtonsDraw:
    push {r0-r12, lr}
    bl OcarinaNotes_MoveButtons
    pop {r0-r12, lr}
    mov r2,r2,lsl #0x1 @ original code
    cmp r2,#0x0        @ original code
    mov r3,r3,lsl #0x1 @ original code
    bx lr

.global hook_OcarinaNoteButtonsPress
hook_OcarinaNoteButtonsPress:
    cpy r0,r6
    push {r1-r12, lr}
    bl OcarinaNotes_HandleInputs
    pop {r1-r12, lr}
    bx lr

.global hook_HandleTextControlCode
hook_HandleTextControlCode:
    ldrb r0,[r6,#0x4] @ Control Code identifier
    push {r0-r12, lr}
    cpy r1,r5 @ Text Object
    cpy r2,r3 @ Unk pointer
    bl Message_HandleTextControlCode
    cmp r0,#0x0
    pop {r0-r12, lr}
    bxeq lr    @ Not a custom control char, resume base game code
    b 0x2E0ED4 @ Handled custom control char, skip base game code

.global hook_CheckForTextControlCode
hook_CheckForTextControlCode:
    push {r1-r12, lr}
    cpy r2,r5 @ Text Object
    cpy r3,r9 @ Char Index (loop counter)
    bl Message_rCheckForControlCodes
    pop {r1-r12, lr}
    bx lr

.global hook_PlayInit
hook_PlayInit:
    push {r0-r12, lr}
    bl before_Play_Init
    pop {r0-r12, lr}
    cpy r5,r0
    bx lr

.global hook_GetObjectEntry_Generic
hook_GetObjectEntry_Generic:
    push {r1-r12, lr}
    @ r0 = slot
    bl Object_GetEntry
    pop {r1-r12, lr}
    bx lr

.global hook_GetObjectEntry_33AB24
hook_GetObjectEntry_33AB24:
    push {r1-r12, lr}
    ldr r0,[r4,#0x4]
    ldr r0,[r0,r5,lsl #0x3] @ objectId
    bl Object_FindEntryOrSpawn
    pop {r1-r12, lr}
    bx lr

.global hook_ExtendObjectGetSlot
hook_ExtendObjectGetSlot:
    push {r1-r12, lr}
    cpy r0,r1 @ objectId
    bl ExtendedObject_GetSlot
    pop {r1-r12, lr}
    bx lr

.global hook_OverrideObjectIsLoaded
hook_OverrideObjectIsLoaded:
    push {r1-r12, lr}
    @ r0,r1 = ObjectContext,slot
    bl Object_IsLoaded
    pop {r1-r12, lr}
    bx lr

.global hook_OverrideObjectIsLoadedForCutscenes
hook_OverrideObjectIsLoadedForCutscenes:
    push {r1-r12, lr}
    @ r0,r1 = ObjectContext,slot
    bl Object_IsLoaded_ForCutscenes
    pop {r1-r12, lr}
    bx lr

.global hook_AfterObjectListCommand
hook_AfterObjectListCommand:
    push {r0-r12, lr}
    bl ExtendedObject_AfterObjectListCommand
    pop {r0-r12, lr}
    mov r0,#0x1
    bx lr

.global hook_GetObjectEntry_34F270
hook_GetObjectEntry_34F270:
    push {r1-r12, lr}
    @ r0 = slot
    bl Object_GetEntry
    pop {r1-r12, lr}
    b 0x34F274

.global hook_AltHeadersCommand
hook_AltHeadersCommand:
    add r2,r7,r1
    push {r0-r12, lr}
    cpy r0,r2 @ alt headers pointers list
    bl Scene_GetLoadedLayer
    pop {r0-r12, lr}
    bx lr

.global hook_GohmaLarvaDeathSignalParent
hook_GohmaLarvaDeathSignalParent:
    ldr r1,[r4,#0x124]
    @ if parent pointer is null, skip
    @ setting childrenGohmaState
    cmp r1,#0x0
    addeq lr,lr,#0x10
    bx lr

.global hook_GohmaEggDeathSignalParent
hook_GohmaEggDeathSignalParent:
    ldr r0,[r4,#0x124]
    @ if parent pointer is null, skip
    @ setting childrenGohmaState
    cmp r0,#0x0
    addeq lr,lr,#0x10
    bx lr

.global hook_StalchildDespawn_13DB68
hook_StalchildDespawn_13DB68:
    push {r0-r12, lr}
    cpy r0,r4 @ actor
    bl Stalchild_CanDespawn
    cmp r0,#0x1
    pop {r0-r12, lr}
    addne lr,lr,#0x10 @ skip other checks, don't despawn
    bxne lr
    cmp r0,r1 @ base game code
    bx lr

.global hook_StalchildDespawn_366338
hook_StalchildDespawn_366338:
    cmp r0,#0x0
    bxne lr @ doesn't despawn
    push {r0-r12, lr}
    cpy r0,r4 @ actor
    bl Stalchild_CanDespawn
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_SkullwalltulaAttack_35F834
hook_SkullwalltulaAttack_35F834:
    cpy r5,r0
    b SkullwalltulaAttack

.global hook_SkullwalltulaAttack_35F328
hook_SkullwalltulaAttack_35F328:
    cpy r4,r0
SkullwalltulaAttack:
    push {r0-r12, lr}
    @ r0 = actor
    bl Skullwalltula_ShouldAttack
    cmp r0,#0x0
    pop {r0-r12, lr}
    bxlt lr @ proceed with vanilla checks
    movne r0,#0x1 @ attack
    moveq r0,#0x0 @ don't attack
    pop {r4-r7,pc} @ return and skip vanilla checks

.global hook_SkullwalltulaTargetRotation
hook_SkullwalltulaTargetRotation:
    sxth r0,r0
    push {r1-r12, lr}
    cpy r1,r4 @ actor
    bl Skullwalltula_GetTargetRotation
    pop {r1-r12, lr}
    bx lr

.global hook_SkullKidPoacherSawCheck
hook_SkullKidPoacherSawCheck:
    cmp r1,#0x32
    bxge lr @ higher than poacher's saw, resume vanilla code
    push {r0-r12, lr}
    @ less than poacher's saw, only kill actor if enemizer is off
    bl SkullKid_IsRandomized
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_LeeverSandCheck
hook_LeeverSandCheck:
    cmpne r0,#0x7
    bxeq lr
    push {r0-r12, lr}
    cpy r0,r4 @ actor
    bl Leever_ShouldSurviveOutsideSand
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_LeeverAfterSink
hook_LeeverAfterSink:
    push {r0-r12, lr}
    @ r0 = actor
    bl Leever_AfterSink
    pop {r0-r12, lr}
    bx lr

.global hook_LeeverAfterDie
hook_LeeverAfterDie:
    push {r0-r12, lr}
    cpy r0,r4 @ actor
    bl Leever_AfterDie
    pop {r0-r12, lr}
    cmp r0,#0x0
    bx lr

.global hook_PlayerCheckVoidOut
hook_PlayerCheckVoidOut:
    ldrb r0,[r4,#0x2]  @ actor->type
    cmp r0,#0x2        @ ACTORTYPE_PLAYER
    addne lr,lr,#0x17C @ Dark Link, skip void out (USA: 0x132CE4)
    cmpeq r8,#0x0      @ Normal Player, continue as normal
    bx lr

.global hook_EnBlkobj_SpawnDarkLink
hook_EnBlkobj_SpawnDarkLink:
    push {r1-r12, lr}
    cpy r0,r4 @ EnBlkobj actor
    bl DarkLink_Spawn
    pop {r1-r12, lr}
    bx lr

.global hook_EnBlkobj_FindDarkLink
hook_EnBlkobj_FindDarkLink:
    push {r1-r12, lr}
    bl DarkLink_IsAlive
    pop {r1-r12, lr}
    bx lr

.global hook_EnEncount1_SpawnStalchildWolfos
hook_EnEncount1_SpawnStalchildWolfos:
    cpy r1,r9
    push {r0-r12, lr}
    cpy r0,r9       @ this EnEncount1
    add r1,sp,#0xC  @ actorId (r3)
    add r2,sp,#0x44 @ params (Stack[0xc])
    bl EnemySpawner_OverrideSpawnedActor
    pop {r0-r12, lr}
    bx lr

.global hook_EnEncount1_SpawnLeever
hook_EnEncount1_SpawnLeever:
    push {r0-r12, lr}
    cpy r0,r5       @ this EnEncount1
    add r1,sp,#0xC  @ actorId (r3)
    add r2,sp,#0x20 @ params (r8)
    bl EnemySpawner_OverrideSpawnedActor
    pop {r0-r12, lr}
    str r8,[sp,#0xC]
    bx lr

.global hook_EnEncount1_SetLeeverAimType
hook_EnEncount1_SetLeeverAimType:
    push {r0}
    ldrh r0,[r7] @ actor->id
    cmp r0,#0x1C @ Leever actor id
    pop {r0}
    strheq r0,[r1,r7] @ Set aimType only if actor is Leever
    bx lr

.global hook_DarkLinkPlayerRecoil
hook_DarkLinkPlayerRecoil:
    cmp r1,r6
    bxne lr @ not recoiling
    push {r0-r12, lr}
    bl DarkLink_ShouldOverridePlayerRecoilSpeed
    cmp r0,#0x1
    pop {r0-r12, lr}
    bx lr

.global hook_BabyDodongoWallCheck
hook_BabyDodongoWallCheck:
    tst r0,#0x8
    bxeq lr @ no wall detected, return
    push {r0-r12, lr}
    @ Prevent burrowing for soulless baby dodongos.
    cpy r0,r4
    bl EnemySouls_CheckSoulForActor
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_PeahatLarvaGroundCheck
hook_PeahatLarvaGroundCheck:
    tsteq r1,#0x1
    bxeq lr @ did not hit ground
    push {r0-r12, lr}
    cpy r0,r4 @ actor
    bl EnemySouls_CheckSoulForActor
    cmp r0,#0x0
    pop {r0-r12, lr}
    @ Prevent death when hitting ground without soul.
    bx lr

.global hook_RedeadCanFreezePlayer
hook_RedeadCanFreezePlayer:
    cmp r1,r0
    bxgt lr @ far away, resume vanilla checks
    ldr r0,const_RedeadMaxYDist
    vldr s0,[r4,#0x9C] @ actor->yDistToPlayer
    vabs.f32 s0,s0
    vmov r1,s0
    cmp r1,r0 @ add check on Y distance
    bx lr
const_RedeadMaxYDist:
    .float 200.0

.global hook_DeadHandHandCanGrabPlayer
hook_DeadHandHandCanGrabPlayer:
    cmp r0,r1
    bxgt lr @ far away, resume vanilla checks
    vpush {s0}
    ldr r0,const_DeadHandHandMaxYDist
    vldr s0,[r4,#0x9C] @ actor->yDistToPlayer
    vabs.f32 s0,s0
    vmov r1,s0
    cmp r1,r0 @ add check on Y distance
    vpop {s0}
    bx lr
const_DeadHandHandMaxYDist:
    .float 100.0

.global hook_GerudoBattleMusic
hook_GerudoBattleMusic:
    push {r0-r12, lr}
    bl GerudoFighter_IsRandomized
    cmp r0,#0x0
    pop {r0-r12, lr}
    beq 0x34F724 @ start battle music
    bx lr

@ This fixes a base game bug where, after going through a room transition, actors under
@ certain conditions will get killed on every frame and never deleted.
@ Fig's explanation from OoT Discord: https://discord.com/channels/82938430371139584/82991320754294784/1002187734946947113
@ With Enemy Randomizer, these "zombie" enemy actors can prevent a room from being cleared.
.global hook_FixActorKillLoop
hook_FixActorKillLoop:
    bxne lr @ object is loaded, continue without killing actor
    push {r0-r12, lr}
    @ check if actor is already killed so that it doesn't get
    @ killed again and it gets properly deleted instead
    cpy r0,r4 @ actor
    bl Actor_IsKilled
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr

.global hook_AfterInvalidatingRoomObjects
hook_AfterInvalidatingRoomObjects:
    push {r0-r12, lr}
    bl ExtendedObject_InvalidateRoomObjects
    pop {r0-r12, lr}
    ldr r0,[sp,#0x18]
    bx lr

.global hook_DrawHeartIcon
hook_DrawHeartIcon:
    push {r0-r12, lr}
    cpy r0,r1 @ heart icon index
    bl Gloom_ShouldDrawHeartBorder
    cmp r0,#0x0
    pop {r0-r12, lr}
    bx lr
    
.global hook_Item00GiveAutomaticItemDrop
hook_Item00GiveAutomaticItemDrop:
    ldrsh r0,[r4,#0x1c]
    push {r0-r12, lr}
    cpy r0,r4 @ actor
    bl ItemOverride_GetItemDrop
    cmp r0,#0x0
    pop {r0-r12, lr}
    addne lr,lr,#0x8 @ Item overridden, skip Item_Give
    bx lr

.global hook_Item00GiveCollectedItemDrop
hook_Item00GiveCollectedItemDrop:
    ldrsh r0,[r5,#0x1c]
    push {r0-r12, lr}
    cpy r0,r5 @ actor
    bl ItemOverride_GetItemDrop
    cmp r0,#0x0
    pop {r0-r12, lr}
    addne lr,lr,#0x8 @ Item overridden, skip Item_Give
    bx lr
