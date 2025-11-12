This is the repo for the randomizer for The Legend of Zelda: Ocarina of Time 3D.

The randomizer places the items of the game in random locations with optional logic so the game is still beatable.

This is done by a homebrew 3DS application built in C++ which creates a patch using code written in C alongside some hooks and other patches written in ARM assembly.
The homebrew application's source code lives in ./source/ and the code for the patch is located in ./code/. You don't have to immediately open those directories. It's here for some extra context so you know where to look for stuff when needed. 