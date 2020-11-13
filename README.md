# OoT3D_Randomizer

This is a WIP item randomizer for _The Legend of Zelda: Ocarina of Time 3D_ for the Nintendo 3DS.

* [Building](#building)
* [Installation](#installation)
* [General Description](#general-description)

## Building

Install the 3DS packages from [devkitPro](https://devkitpro.org/wiki/Getting_Started)

In the code folder, use ```make```. This should generate a ```code.ips``` which serves as the template for the generated patch.

In the root folder, use ```make``` to build ```OoT3D_Randomizer.3dsx```.

## Installation

On your SD card, copy the built ```code.ips``` to ```/luma/titles/0004000000033500/``` and rename ```code.ips``` to ```basecode.ips```. Also copy ```OoT3D_Randomizer.3dsx``` to ```/3ds/```.

TODO: the app should generate ```exheader.bin```, but it doesn't yet. For now, either construct ```exheader.bin``` yourself or get it from a different source.

To use, run OoT3D_Randomizer from the homebrew launcher.

## General Description

This program takes _The Legend of Zelda: Ocarina of Time 3D_ and randomizes the locations of the items for a new, more dynamic play experience.
Once completed, proper logic will be used to ensure every seed is possible to complete without the use of glitches and will be safe from the possibility of softlocks with any possible usage of keys in dungeons.
