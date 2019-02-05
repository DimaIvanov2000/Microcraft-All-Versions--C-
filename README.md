# Microcraft All Versions (C)

A small-scale recreation of Markus Persson's Minecraft using a C console.

## How to Run

Download the file and / or run the code on your IDE of choice (Codeblocks or DevC++ should both work). Depending on the version, the programe may rely on a specific arrangement of files in directories to work. If downloaded and kept as is, it should be fine.

## How to Use

### Version 1 - 2016

A very basic version of Minecraft which is mainly able to generate a world and allow the player to move around. There is no collision between the player and blocks. The player can also break blocks which will appear in their inventory but the blocks cannot be placed.  
  
Controls:  
* WASD - Move character  
* IJKL - Change player orientation (mirrors WASD)  
* F - break block infront of player  
  
### Version 2 - 2017

This version is more fleshed out with features but remains largely incomplete when it comes to actual gameplay. The game features an elaborate title sequence, some other basic options, and most notably, the ability to create and store worlds in file format. A basic compression algorythm is used where block types are denoted with capital letters and if a block type repeats (when reading the world in English text reading fashion), the number of repeats is denoted by lower-case letters representing a number in base 26.  
Gameplay-wise, the program has more block types with a world that generates trees and is in colour. This time around, the player cannot alter the world and can merely move around.  
  
Controls:  
* WASD - Move character  
* IJKL - Change player orientation (mirrors WASD)  
