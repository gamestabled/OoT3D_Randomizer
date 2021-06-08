#!/bin/bash

compile() {
  # If building manually just replace SHA with your own text.
  export commitHashShort=$(echo ${GITHUB_SHA::6})
  sed -i "s/develop/${commitHashShort:-develop}/" ./source/randomizer.hpp
  make
  bannertoolexec makebanner -i ./banner.png -a ./audio.wav -o ./banner.bnr
  bannertoolexec makesmdh -s "Ocarina of Time 3D Randomizer" -l "A different Ocarina of Time experience" -p "Gamestabled & Gymnast86" -i icon.png -o ./icon.icn
  3dstool -cvtf romfs ./romfs.bin --romfs-dir ./romfs
  makerom -f cia -o OoT3D_Randomizer.cia -DAPP_ENCRYPTED=false -target t -exefslogo -elf ./OoT3D_Randomizer.elf -icon ./icon.icn -banner ./banner.bnr -rsf ./ootrando.rsf -romfs ./romfs.bin -major 1 -minor 1 -micro 1
  qrencode -ocia.png https://github.com/$GITHUB_REPOSITORY/releases/download/Nightly-$GITHUB_SHA/OoT3D_Randomizer.cia
  qrencode -o3dsx.png https://github.com/$GITHUB_REPOSITORY/releases/download/Nightly-$GITHUB_SHA/OoT3D_Randomizer.3dsx
  ls -la
}

clean_up() {
  rm -rf bannertool* makerom* 3dstool* icon.icn ext_key.txt ignore_3dstool.txt banner.bnr romfs.bin
}

compile
clean_up