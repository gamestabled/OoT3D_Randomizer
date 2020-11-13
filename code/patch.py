import os
import struct
import subprocess
import sys

elf = sys.argv[1]
result = subprocess.run([os.environ["DEVKITARM"] + r'/bin/arm-none-eabi-objdump', '--section-headers', elf], stdout=subprocess.PIPE)
lines = str(result.stdout).split('\\n')
sectionsInfo = [line.split()[1:6] for line in lines if line.split() and line.split()[0].isdigit()]
sections = ((sec[0], int(sec[2],16), int(sec[4],16), int(sec[1],16)) for sec in sectionsInfo if int(sec[2],16) != 0)


off = lambda vaddr: struct.pack(">I",vaddr - 0x100000)[1:]
sz = lambda size: struct.pack(">H", size)

ips = b'PATCH'
with open(elf, 'rb') as e:
    for name, vaddr, offset, size in sections:

        # if vaddr >= 0x4CA000 and vaddr < 0x5C7000: #this is not good lol just trying to avoid __GNU_EH_FRAME_HDR section
        #     continue

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
