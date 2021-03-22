#!/bin/bash

gather_required_files() {
  echo "Our python version: "
  python3 -V
  sudo apt update && sudo apt install automake build-essential wget unzip zip -y
  wget https://github.com/3DSGuy/Project_CTR/releases/download/makerom-v0.17/makerom-v0.17-ubuntu_x86_64.zip
  unzip makerom-v0.17-ubuntu_x86_64.zip
  git clone https://github.com/Steveice10/bannertool.git
  cd bannertool
  git submodule update --init
  make
  unzip ./output/bannertool.zip
  mv linux-x86_64/bannertool ../bannertoolexec
  cd ..
  wget https://github.com/dnasdw/3dstool/releases/download/v1.2.6/3dstool_linux_x86_64.tar.gz
  tar -zxvf 3dstool_linux_x86_64.tar.gz
  chmod +x bannertoolexec
  chmod +x makerom
  chmod + 3dstool
}

compile() {
  # If building manually just replace SHA with your own text.
  export commitHashShort=$(echo ${GITHUB_SHA::6})
  sed -i "s/COMMITNUM/$commitHashShort/" ./source/menu.cpp
  make
  ./bannertoolexec makebanner -i ./banner.png -a ./audio.wav -o ./banner.bnr
  ./bannertoolexec makesmdh -s "Ocarina of Time 3D Randomizer" -l "A different Ocarina of Time experience" -p "Gamestabled & Gymnast86" -i icon.png -o ./icon.icn
  ./3dstool -cvtf romfs ./romfs.bin --romfs-dir ./romfs
  ./makerom -f cia -o OoT3D_Randomizer.cia -DAPP_ENCRYPTED=false -target t -exefslogo -elf ./OoT3D_Randomizer.elf -icon ./icon.icn -banner ./banner.bnr -rsf ./ootrando.rsf -romfs ./romfs.bin -major 1 -minor 0 -micro 1
}

clean_up() {
  rm -rf bannertool* makerom* 3dstool* icon.icn ext_key.txt ignore_3dstool.txt banner.bnr romfs.bin
}

gather_required_files
compile
clean_up
