# OoT3D_Randomizer

This is an item randomizer for _The Legend of Zelda: Ocarina of Time 3D_ for the Nintendo 3DS. The first official release is coming soon!

* [Building](#building)
* [Installation](#installation)
* [General Description](#general-description)

## Building

Install the 3DS packages from [devkitPro](https://devkitpro.org/wiki/Getting_Started)

In the root folder, use ```make``` to build ```OoT3D_Randomizer.3dsx```. Use ```make debug=1``` for extra debugging features. In the case of problems, try using a ```make clean```.

## Installation

Please ensure that you are playing on the USA version of Ocarina of Time 3D, as it is the only version supported by the randomizer. You can use either the cartridge version or the installed digital version.

### On 3DS Console with Luma3DS
On your SD card, copy ```OoT3D_Randomizer.3dsx``` to ```/3ds/```.

Power on your 3DS while holding the SELECT key to launch the Luma3DS menu. Make sure that ```Enable game patching``` is turned on, then press START to save and launch the home menu. You only have to do this once.

To generate a playthrough, run Ocarina of Time 3D Randomizer from the homebrew launcher. Navigate the menus to choose the settings for your playthrough, and finish by selecting ```Generate Randomizer```. When prompted, make sure to select that you are playing on a 3DS console. After the app has finished, launch Ocarina of Time 3D from the home menu and enjoy your playthough!

### On Citra
Use Citra to launch ```OoT3D_Randomizer.3dsx```. Navigate the menus to choose the settings for your playthrough, and finish by selecting ```Generate Randomizer```. When prompted, make sure to select that you are playing on Citra emulator. After the app has finished, on the Citra window, click on ```File->Open Citra Folder```. From this folder, navigate to ```\sdmc\luma\titles\0004000000033500```, and you should find files called ```code.ips``` and ```exheader.bin```. In the Citra window, right-click on the installed copy Ocarina of Time 3D, and choose ```Open Mods Location```. Copy both ```code.ips``` and ```exheader.bin``` into this folder. Now, launch Ocarina of Time 3D and enjoy your playthrough!

## General Description

This program takes _The Legend of Zelda: Ocarina of Time 3D_ and randomizes the locations of the items for a new, more dynamic play experience.
Proper logic is used to ensure every seed is possible to complete without the use of glitches and will be safe from the possibility of softlocks with any possible usage of keys in dungeons.
