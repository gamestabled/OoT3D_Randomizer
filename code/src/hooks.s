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
.global rActiveItemTextId
.rActiveItemTextId_addr:
    .word rActiveItemTextId
hook_OverrideTextID:
    ldr r1,.rActiveItemRow_addr
    ldr r1,[r1]
    cmp r1,#0x0
    beq noOverrideTextID

    ldr r1,.rActiveItemTextId_addr
    ldr r1,[r1]
    b returnTextID
noOverrideTextID:
    ldrb r1,[r6,#0x4]
returnTextID:
    bx lr

.global hook_OverrideItemID
.global rActiveItemActionId
.rActiveItemActionId_addr:
    .word rActiveItemActionId
hook_OverrideItemID:
    push {r0, lr}
    ldr r1,.rActiveItemRow_addr
    ldr r1,[r1]
    cmp r1,#0x0
    beq noOverrideItemID

    ldr r0,.rActiveItemRow_addr
    ldr r0,[r0]
    bl ItemTable_CallEffect
    
    ldr r1,.rActiveItemActionId_addr
    ldr r1,[r1]
    b returnItemID
noOverrideItemID:    
    ldrb r1,[r6,#0x0]
returnItemID:
    push {r0-r4}
    bl ItemOverride_AfterItemReceived
    pop {r0-r4}
    pop {r0, lr}
    bx lr

# Puts override graphic ID into r0, no other effects
# If no active override, puts -0x1
# Need to wrap around this for individual cases because of differing register usage
.global hook_OverrideGraphicID
.global rActiveItemGraphicId_addr
.rActiveItemGraphicId_addr:
    .word rActiveItemGraphicId
hook_OverrideGraphicID:
    ldr r0,.rActiveItemActionId_addr
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

.section .loader
.global hook_into_loader
hook_into_loader:
    push {r0-r12, lr}
    bl loader_main
    pop {r0-r12, lr}
    bl 0x100028
    b  0x100004
