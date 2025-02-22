# This script adds a new patch to `oot.ld`, checking that the address order is correct.
# It also adds template asm instructions to `patches.s` and `hooks.s`.
# Use by passing the hexadecimal address and the patch name (e.g. `0x4352F4 PlayInit`),
# or no arguments to just check the address order in `oot.ld`.

import sys, re

newPatchAddress = int(sys.argv[1], 16) if len(sys.argv) > 1 else None
newPatchName = sys.argv[2] if len(sys.argv) > 2 else None

LD_PATCH_TEMPLATE='''\
	.patch_%s 0x%X %s: {
		*(.patch_%s)
	}

'''

ASM_PATCH_TEMPLATE='''
.section .patch_%s
.global %s_patch
%s_patch:
    bl hook_%s
'''

ASM_HOOK_TEMPLATE='''
.global hook_%s
hook_%s:
    push {r0-r12, lr}
    bl %s
    pop {r0-r12, lr}
    cpy r0,r0
    bx lr
'''

lastAddress = 0
isOrderCorrect = True
insertIndex = 0

with open('oot.ld', 'r+', newline='') as file:
    lines = file.readlines()
    for lineIndex, line in enumerate(lines):
        # Search lines with memory addresses
        result = re.search("0x[a-f-A-F0-9]{6,}", line)
        if result:
            addressString = result.group(0)
            address = int(addressString, 16)
            # Detect errors in the patches order
            if lastAddress > address:
                print('Order error detected: line %d, address %s' % (lineIndex, addressString))
                isOrderCorrect=False
            lastAddress = address
            # Choose where the new patch will be added
            if newPatchAddress:
                if abs(address - newPatchAddress) < 0x10:
                    print('WARNING: another patch is at address 0x%X' % address)
                if not insertIndex and address > newPatchAddress:
                    insertIndex = lineIndex
    # Add the new patch if no errors have been detected
    if newPatchAddress and isOrderCorrect:
        if not newPatchName:
            newPatchName = input('Insert name for the new patch: patch_')
        regionOffsetString = '+ region_offset ' if newPatchAddress >= 0x41A144 and newPatchAddress < 0x4A5AE0 else ''
        lines.insert(insertIndex, LD_PATCH_TEMPLATE % (newPatchName, newPatchAddress, regionOffsetString, newPatchName))
        file.seek(0)
        file.writelines(lines)

if isOrderCorrect:
    if not newPatchAddress:
        print('Order is correct')
    else:
        # Add the template asm to `patches.s` and `hooks.s`
        with open('src/patches.s', 'a', newline='') as file:
            file.write(ASM_PATCH_TEMPLATE % (newPatchName, newPatchName, newPatchName, newPatchName))
        with open('src/hooks.s', 'a', newline='') as file:
            file.write(ASM_HOOK_TEMPLATE % (newPatchName, newPatchName, newPatchName))
        print('Patch added')
