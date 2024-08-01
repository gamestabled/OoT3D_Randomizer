# OoT3D_Randomizer

This is an item randomizer for _The Legend of Zelda: Ocarina of Time 3D_ for the Nintendo 3DS.

* [Installation](#installation)
  * [On 3DS Console with Luma3DS](#On-3DS-Console-with-Luma3DS)
  * [On Citra](#On-Citra)
  * [Save Files](#Save-Files)
* [General Description](#general-description)
  * [Getting Stuck](#getting-stuck)
* [Building](#building)
* [Reporting Bugs](#reporting-bugs)

## Installation

You can download the latest stable version of the randomizer [here](https://github.com/gamestabled/OoT3D_Randomizer/releases/latest). You can use either the ```OoT3D_Randomizer.3dsx``` or ```OoT3D_Randomizer.cia``` files provided to generate randomizer patches.

You can use either the cartridge version or the installed digital version. In all instructions below, if a directory doesn't exist, just create it.

### On 3DS Console with Luma3DS
On your SD card, copy ```OoT3D_Randomizer.3dsx``` to ```SD:/3ds/``` or copy ```OoT3D_Randomizer.cia``` to ```SD:/cias/```. When using the ```.3dsx``` file, you will need to launch the randomzier app through the homebrew menu every time you wish to launch it. When using the ```.cia``` file, you will need to install the file using the FBI app, so that the randomizer app appears directly on the 3DS home menu. Alternatively, if your 3DS is connected to the internet, you can use FBI to scan the QR code for either the ```.3dsx``` file or the ```.cia``` file, and the randomizer will be downloaded and installed automatically.

Power on your 3DS while holding the SELECT key to launch the Luma3DS menu. Make sure that ```Enable game patching``` is turned on, then press START to save and launch the home menu. You only have to do this once.

To generate a playthrough, run Ocarina of Time 3D Randomizer from the homebrew launcher. Navigate the menus to choose the settings for your playthrough, and finish by selecting ```Generate Randomizer```. When prompted, make sure to select that you are playing on a 3DS console. After the app has finished, launch Ocarina of Time 3D from the home menu and enjoy your playthough!

If the 3DS crashes when you launch the game, you probably need to update Luma3DS.

### On Citra
Use Citra to launch ```OoT3D_Randomizer.3dsx```. Navigate the menus to choose the settings for your playthrough, and finish by selecting ```Generate Randomizer```. When prompted, make sure to select that you are playing on Citra emulator. After the app has finished, on the Citra window, click on ```File->Open Citra Folder```. From this folder, navigate to ```\sdmc\luma\titles\0004000000033500```, and you should find files called ```code.ips```, ```exheader.bin```, and a folder called ```romfs```. In the Citra window, right-click on the installed copy of Ocarina of Time 3D, and choose ```Open Mods Location```. (If you haven't installed OoT3D, you can go to ```File->Open Citra Folder``` and then open up ```\load\mods\0004000000033500```.) Copy ```code.ips```, ```exheader.bin```, and ```romfs``` into this folder. Now, launch Ocarina of Time 3D and enjoy your playthrough!

### Save Files
Right now, save files are shared between any playthroughs you create and the base game. This means that you are responsible for managing your own save files. If you are playing on a 3DS, check out [Checkpoint](https://github.com/FlagBrew/Checkpoint/releases), an easy-to-use homebrew save manager.

## General Description

This program takes _The Legend of Zelda: Ocarina of Time 3D_ and randomizes the locations of the items for a new, more dynamic play experience.
Proper logic is used to ensure every seed is possible to complete without the use of glitches and will be safe from the possibility of softlocks with any possible usage of keys in dungeons.

The randomizer will ensure a glitchless path through the seed will exist, but the randomizer will not prevent the use of glitches for those players who enjoy that sort of thing, though we offer no guarantees that all glitches will have identical behavior to the original game. Glitchless can still mean that clever or unintuitive strategies may be required involving the use of things like Hover Boots, the Hookshot, or other items that may not have been as important in the original game.

Each major dungeon will earn you a random Spiritual Stone or Medallion once completed. The particular dungeons where these can be found, as well as other relevant dungeon information and the current seed hash can be viewed by pressing SELECT, and using the L or R button to move between pages.

As a service to the player in this very long game, various tedious elements of the game have been removed or sped up, and more convenience tweaks are planned for the future. Some of these changes can be customized when creating your seed.

Please be sure to explore the many customizable settings which are available when using the app! There are many options which can alter the length or difficulty of each playthrough.

Want to discuss the randomizer with others? Join our [Discord server](https://discord.gg/wumv4wWWeB)!

### Getting Stuck

With a game the size of _Ocarina of Time 3D_, it's quite easy for players to get stuck in certain situations with no apparent path to progressing.
Before reporting an issue, please make sure to check out the [the Logic wiki for the original OoT Randomizer](https://wiki.ootrandomizer.com/index.php?title=Logic), the information there will apply to OoT3D in nearly every situation. 

You may also find a map tracker helpful, as these allow you to see all checks which are available with your current items, and check which ones you've gotten already. Some recommended trackers are [track-oot](https://track-oot.net/) and Hamsda's pack for EmoTracker, although keep in mind these were designed for the original OoT Randomizer so there may be some slight discrepancies.

## Building

(If you are looking to play the randomizer, jump to [Installation](#installation), this section is for people interested in contributing or messing with the code)!

Install the 3DS packages from [devkitPro](https://devkitpro.org/wiki/Getting_Started)

A small portion of this project is done in python. If you decide to use the Msys2 console from devkitpro, you can install python using the command `pacman -S python` within Msys2.


In the root folder, use ```make``` to build ```OoT3D_Randomizer.3dsx```. Use ```make debug=1``` for extra debugging features, including extra items when starting a new file. In the case of problems, try using a ```make clean```.
For faster compilation using multiple threads, you can use `make -j4` (in this example, the `4` is the number of threads being used).

## Reporting Bugs

Let us know if you believe you have discovered a bug by posting in our Discord server, or by opening an issue. In the [Discord](https://discord.gg/wumv4wWWeB), we have a list of currently known issues and fixes which are pending release, which we try to keep fairly up to date.
