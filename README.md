# OoT3D_Randomizer

This is an item randomizer for _The Legend of Zelda: Ocarina of Time 3D_ for the Nintendo 3DS.

* [Building](#building)
* [Installation](#installation)
* [General Description](#general-description)
  * [Getting Stuck](#getting-stuck)
  * [Known Issues](#known-issues)

## Building

(If you are looking to play the randomizer, jump to [Installation](#installation), this section is for people interested in contributing or messing with the code)!

Install the 3DS packages from [devkitPro](https://devkitpro.org/wiki/Getting_Started)

In the root folder, use ```make``` to build ```OoT3D_Randomizer.3dsx```. Use ```make debug=1``` for extra debugging features, including extra items when starting a new file. In the case of problems, try using a ```make clean```.

## Installation

Please ensure that you are playing on the USA version of Ocarina of Time 3D, as it is the only version supported by the randomizer. You can use either the cartridge version or the installed digital version. In all instructions below, if a directory doesn't exist, just create it.

### On 3DS Console with Luma3DS
On your SD card, copy ```OoT3D_Randomizer.3dsx``` to ```SD:/3ds/```.

Power on your 3DS while holding the SELECT key to launch the Luma3DS menu. Make sure that ```Enable game patching``` is turned on, then press START to save and launch the home menu. You only have to do this once.

To generate a playthrough, run Ocarina of Time 3D Randomizer from the homebrew launcher. Navigate the menus to choose the settings for your playthrough, and finish by selecting ```Generate Randomizer```. When prompted, make sure to select that you are playing on a 3DS console. After the app has finished, launch Ocarina of Time 3D from the home menu and enjoy your playthough!

If the 3DS crashes when you launch the game, you probably need to update Luma3DS.

### On Citra
Use Citra to launch ```OoT3D_Randomizer.3dsx```. Navigate the menus to choose the settings for your playthrough, and finish by selecting ```Generate Randomizer```. When prompted, make sure to select that you are playing on Citra emulator. After the app has finished, on the Citra window, click on ```File->Open Citra Folder```. From this folder, navigate to ```\sdmc\luma\titles\0004000000033500```, and you should find files called ```code.ips``` and ```exheader.bin```. In the Citra window, right-click on the installed copy Ocarina of Time 3D, and choose ```Open Mods Location```. (If you haven't installed OoT3D, you can go to ```File->Open Citra Folder``` and then open up ```\load\mods\0004000000033500```.) Copy both ```code.ips``` and ```exheader.bin``` into this folder. Now, launch Ocarina of Time 3D and enjoy your playthrough!

### On Citra for recent Nightly Pre-releases:
The same as above, but in ```\sdmc\luma\titles\0004000000033500``` you should also find a folder called ```romfs```. Make sure to also copy this entire folder into ```\load\mods\0004000000033500```. This will become standard for future releases.

### Savefiles
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
Before reporting an issue, please make sure to check out the [the Logic wiki for the original OoTRandomizer](https://wiki.ootrandomizer.com/index.php?title=Logic), the information there will apply to OoT3D in nearly every situation.

### Reporting bugs

Let us know if you believe you have discovered a bug by posting in our Discord server, or by opening an issue. In the [Discord](https://discord.gg/wumv4wWWeB), we have a list of currently known issues and fixes which are pending release, which we try to keep fairly up to date.
