# This script adds a new symbol or patch address to the linker script, checking that the order is correct.
# When creating a patch, it also adds template asm instructions to the relevant files.
# Use by passing, in any order, `s` or `p` for Symbol or Patch, the hexadecimal address and a name (e.g. `p 0x4352F4 PlayInit`).
# Call with no arguments to just check the address order in the linker script.

import sys, re
from pathlib import Path

TYPE_PATCH = 'p'
TYPE_SYMBOL = 's'

newAddress = None
newName = None
type = None

if len(sys.argv) > 1:
    # interpret passed arguments
    for arg in sys.argv[1:]:
        if arg in [TYPE_PATCH, TYPE_SYMBOL]:
            type = arg
        else:
            try:
                newAddress = int(arg, 16)
            except ValueError:
                newName = arg

    # require values for missing parameters
    while type != TYPE_PATCH and type != TYPE_SYMBOL:
        type = input('Symbol or Patch? [s/p]: ')
    while not newName:
        newName = input('Insert name for the new %s' % ('patch: patch_' if type == TYPE_PATCH else 'symbol: '))
    while not newAddress:
        addressString = input('Insert address (hexadecimal): ')
        try:
            newAddress = int(addressString, 16)
        except ValueError:
            print('Invalid value')


LD_SYM_TEMPLATE='''\
	%s = 0x%X + _LD_OFF;\
'''

LD_PATCH_TEMPLATE='''\
	.patch_%s 0x%X + _LD_OFF : { *(.patch_%s) }\
'''

ASM_PATCH_TEMPLATE='''
PATCH %s
    bl hook_%s
'''

ASM_HOOK_TEMPLATE='''
HOOK %s
    push {r0-r12, lr}
    bl %s
    pop {r0-r12, lr}
    cpy r0,r0
    bx lr
'''

lastAddress = 0
insertIndex = 0

ldFile = Path('oot.ld')
ldLines = ldFile.read_text().splitlines()
for lineIndex, line in enumerate(ldLines):
    # Search lines with memory addresses
    result = re.search(r'0x[a-fA-F0-9]{6,}', line)
    if not result:
        continue
    addressString = result.group(0)
    address = int(addressString, 16)
    # Detect errors in the address order
    if lastAddress > address:
        sys.exit('Order error detected: line %d, address %s' % (lineIndex, addressString))
    lastAddress = address
    if not newAddress:
        continue
    # Check existing addresses for potential conflicts
    if (type == TYPE_PATCH if '.patch_' in line else type == TYPE_SYMBOL):
        typeString = 'patch' if type == TYPE_PATCH else 'symbol'
        if address == newAddress:
            sys.exit('ERROR: another %s is at the same address [0x%X]' % (typeString, address))
        if abs(address - newAddress) < 0x10:
            print('WARNING: another %s is at nearby address [0x%X]' % (typeString, address))
    # Select this line index for inserting new address, but continue loop to keep checking order
    if not insertIndex and address > newAddress:
        if '/*' in line and ldLines[lineIndex - 1] == '':
            insertIndex = lineIndex - 1
        else:
            insertIndex = lineIndex

# Add the new address
if newAddress:
    if type == TYPE_PATCH:
        newLine = LD_PATCH_TEMPLATE % (newName, newAddress, newName)
    else:
        newLine = LD_SYM_TEMPLATE % (newName, newAddress)
    ldLines.insert(insertIndex, newLine)
    ldFile.write_text('\n'.join(ldLines) + '\n', newline='')

if not newAddress:
    print('Order is correct')
elif type == TYPE_PATCH:
    # Add the template asm to `patches.s` and `hooks.s`
    with open('src/asm/patches.s', 'a', newline='') as file:
        file.write(ASM_PATCH_TEMPLATE % (newName, newName))
    with open('src/asm/hooks.s', 'a', newline='') as file:
        file.write(ASM_HOOK_TEMPLATE % (newName, newName))
    print('Patch added')
else:
    print('Symbol added')
