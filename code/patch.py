import os
import struct
import subprocess
import sys

# If symbols required by the app haven't changed with the latest build,
# the HPP files won't be rewritten so that the app will build faster
def are_existing_symbols_valid(hppFilePath, newSymbolsInfo):
    try:
        with open(hppFilePath, 'r') as hppFile:
            hppFileLines = hppFile.readlines()[1:] # Skip first line ("#pragma once")
            if len(hppFileLines) != len(newSymbolsInfo):
                return False # Symbols amount changed
            for line, newSym in zip(hppFileLines, newSymbolsInfo):
                oldAddressString = line.split()[-1]
                oldAddressInt = int(oldAddressString, 16)
                newAddressInt = int(newSym[0], 16)
                if (oldAddressInt != newAddressInt):
                    return False # Some symbol changed
    except:
        return False # The HPP file doesn't exist (or some other problem occurred)
    return True

elf = sys.argv[1]
region = sys.argv[2]
debug = int(sys.argv[3])
result = subprocess.run([os.environ["DEVKITARM"] + r'/bin/arm-none-eabi-objdump', '--section-headers', elf], stdout=subprocess.PIPE)
lines = str(result.stdout).split('\\n')
sectionsInfo = [line.split()[1:6] for line in lines if line.split() and line.split()[0].isdigit()]
sections = ((sec[0], int(sec[2],16), int(sec[4],16), int(sec[1],16)) for sec in sectionsInfo if int(sec[2],16) != 0)

# Put here the symbols from the patch which are needed by the app
desiredSymbols = ("rItemOverrides", "gSettingsContext", "gSpoilerData", "gSpoilerDataLocs", "rScrubRandomItemPrices", "rDungeonRewardOverrides", "rCustomMessages",
"numCustomMessageEntries", "ptrCustomMessageEntries", "rShopsanityPrices", "rEntranceOverrides", "rBGMOverrides", "rSfxData", "rDungeonInfoData", "rGsLocOverrides",
"rEnemyOverrides")

nmResult = subprocess.run([os.environ["DEVKITARM"] + r'/bin/arm-none-eabi-nm', elf], stdout=subprocess.PIPE)
nmLines = str(nmResult.stdout).split('\\n')
symbolsInfo = [line.split() for line in nmLines if len(line.split()) >= 3 and line.split()[2].replace("\\r", "") in desiredSymbols]
hppFileName = "patch_symbols_" + region + ".hpp"
hppFilePath = "../source/" + hppFileName
if are_existing_symbols_valid(hppFilePath, symbolsInfo):
    print(hppFileName + " unchanged. Run `make clean` to delete it.")
else:
    with open(hppFilePath, 'w') as syms:
        syms.write("#pragma once\n")
        for sym in symbolsInfo:
            syms.write("#define "+sym[2].replace("\\r", "").upper()+"_" + region + "_ADDR 0x"+sym[0]+"\n")
    print("wrote desired symbols to " + hppFileName)

off = lambda vaddr: struct.pack(">I",vaddr - 0x100000)[1:]
sz = lambda size: struct.pack(">H", size)

ips = b'PATCH'
with open(elf, 'rb') as e:
    for name, vaddr, offset, size in sections:

        e.seek(offset, 0)
        while size > 65535:
            patch = e.read(65535)
            if (debug):
                print('{:0X}'.format(vaddr))
            ips += off(vaddr)
            ips += sz(65535)
            ips += patch
            vaddr += 65535
            offset += 65535
            size -= 65535

        patch =  e.read(size)
        if len(patch) != 0:
            if (debug):
                print('{:0X}'.format(vaddr), '{:0X}'.format(vaddr + size), name)
            ips += off(vaddr)
            ips += sz(size)
            ips += patch
ips += b'EOF'

basecodeFile = "basecode_" + region + ".ips"
with open(basecodeFile, 'wb') as patchFile:
    patchFile.write(ips)
    print("created " + basecodeFile + "\n")
