import os, sys, subprocess
from pathlib import Path

USA_ELF_PATH = 'code/basecode_USA.elf'
EUR_ELF_PATH = 'code/basecode_EUR.elf'
CPP_FILE_PATH = 'source/patch_symbols.cpp'
LD_TEXT_START = '_LD_TEXT_START'

# Put here the symbols from the patch which are needed by the app
desiredSymbols = ['rItemOverrides', 'gSettingsContext', 'gSpoilerData', 'gSpoilerDataLocs', 'rScrubRandomItemPrices',
                  'rDungeonRewardOverrides', 'rCustomMessages', 'numCustomMessageEntries', 'ptrCustomMessageEntries',
                  'rShopsanityPrices', 'rEntranceOverrides', 'rBGMOverrides', 'rSfxData', 'rDungeonInfoData',
                  'rGsLocOverrides', 'rEnemyOverrides']

def getSymbolsTable(elfFilePath):
    nmResult = subprocess.run([os.environ['DEVKITARM'] + r'/bin/arm-none-eabi-nm', elfFilePath], text=True, capture_output=True)
    nmLines = nmResult.stdout.replace('\r', '').split('\n')
    symbolsDict = dict()
    for line in nmLines:
        words = line.split()
        if len(words) != 3:
            continue
        [addr, type, name] = words
        symbolsDict[name] = addr
    return symbolsDict

symTableUSA = getSymbolsTable(USA_ELF_PATH)
symTableEUR = getSymbolsTable(EUR_ELF_PATH)

if symTableUSA[LD_TEXT_START] != symTableEUR[LD_TEXT_START]:
    sys.exit('ERROR: USA and EUR regions should use the same base address for custom code!')

newContent = '#include "patch.hpp"\n\nconst PatchSymbols gPatchSymbols = {\n'
for name in desiredSymbols:
    newContent += f'    .{name} = 0x{symTableUSA[name]},\n'
newContent += '};\n'

cppFile = Path(CPP_FILE_PATH)
oldContent = cppFile.read_text() if cppFile.exists() else ''

# If the CPP content doesn't change, don't rewrite the file so it won't be recompiled
if newContent != oldContent:
    cppFile.write_text(newContent, newline='\n')
    print(f'Wrote desired symbols to {CPP_FILE_PATH}')
else:
    print(f'Patch symbols unchanged')
