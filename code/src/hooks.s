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

#The magic number here is SPIRIT_MEDALLION from dungeon_rewards.h
.global hook_SpiritTempleBitMask
hook_SpiritTempleBitMask:
    push {r1-r12, lr}
    mov r0,#0x06
    bl DungeonReward_GetBitMask
    pop {r1-r12, lr}
    bx lr

#The magic number here is SHADOW_MEDALLION from dungeon_rewards.h
.global hook_ShadowTempleBitMask
hook_ShadowTempleBitMask:
    push {r1-r12, lr}
    mov r0,#0x07
    bl DungeonReward_GetBitMask
    pop {r1-r12, lr}
    bx lr

#The magic number here is FOREST_MEDALLION from dungeon_rewards.h
.global hook_DekuSproutBitMask
hook_DekuSproutBitMask:
    push {r0, r2-r12, lr}
    mov r0,#0x03
    bl DungeonReward_GetBitMask
    cpy r1,r0
    pop {r0, r2-r12, lr}
    bx lr

.global hook_EnKoInitBitMask
hook_EnKoInitBitMask:
    push {r0, r2-r12, lr}
    mov r0,#0x03
    bl DungeonReward_GetBitMaskAddr
    cpy r1,r0
    pop {r0, r2-r12, lr}
    bx lr

#The magic number here is WATER_MEDALLION from dungeon_rewards.h
.global hook_FireArrowBitMask
hook_FireArrowBitMask:
    push {r0-r2, r4-r12, lr}
    mov r0,#0x05
    bl DungeonReward_GetBitMask
    cpy r3,r0
    pop {r0-r2, r4-r12, lr}
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

.section .loader
.global hook_into_loader
hook_into_loader:
    push {r0-r12, lr}
    bl loader_main
    pop {r0-r12, lr}
    bl 0x100028
    b  0x100004
