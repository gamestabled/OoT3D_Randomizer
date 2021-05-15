import os
import struct
import subprocess
import sys
import json

elf = sys.argv[1]
result = subprocess.run([os.environ["DEVKITARM"] + r'/bin/arm-none-eabi-objdump', '--section-headers', elf], stdout=subprocess.PIPE)
lines = str(result.stdout).split('\\n')
sectionsInfo = [line.split()[1:6] for line in lines if line.split() and line.split()[0].isdigit()]
sections = ((sec[0], int(sec[2],16), int(sec[4],16), int(sec[1],16)) for sec in sectionsInfo if int(sec[2],16) != 0)

# Put here the symbols from the patch which are needed by the app
desiredSymbols = ("rItemOverrides", "gSettingsContext", "rScrubRandomItemPrices", "rDungeonRewardOverrides", "rCustomMessages", "numCustomMessageEntries", "ptrCustomMessageEntries", "rShopsanityPrices")

nmResult = subprocess.run([os.environ["DEVKITARM"] + r'/bin/arm-none-eabi-nm', elf], stdout=subprocess.PIPE)
nmLines = str(nmResult.stdout).split('\\n')
symbolsInfo = [line.split() for line in nmLines if len(line.split()) >= 2 and line.split()[2].replace("\\r", "") in desiredSymbols]
symbols = {sym[2].replace("\\r", ""):hex(int(sym[0],16)) for sym in symbolsInfo}
symbolsJson = json.dumps(symbols, indent=4)
with open("../source/patch_symbols.hpp", 'w') as syms:
    syms.write("#pragma once\n")
    for sym in symbolsInfo:
        syms.write("#define "+sym[2].replace("\\r", "").upper()+"_ADDR"+" 0x"+sym[0]+"\n")
print("wrote desired symbols to patch_symbols.json")

off = lambda vaddr: struct.pack(">I",vaddr - 0x100000)[1:]
sz = lambda size: struct.pack(">H", size)

ips = b'PATCH'
with open(elf, 'rb') as e:
    for name, vaddr, offset, size in sections:

        e.seek(offset, 0)
        while size > 65535:
            patch = e.read(65535)
            print('{:0X}'.format(vaddr))
            ips += off(vaddr)
            ips += sz(65535)
            ips += patch
            vaddr += 65535
            offset += 65535
            size -= 65535

        patch =  e.read(size)
        if len(patch) != 0:
            print('{:0X}'.format(vaddr), '{:0X}'.format(vaddr + size), name)
            ips += off(vaddr)
            ips += sz(size)
            ips += patch
ips += b'EOF'

with open("basecode.ips", 'wb') as patchFile:
    patchFile.write(ips)
print("created basecode.ips")
