# an-opengl-game
A game and game engine built from scratch using OpenGL in C++. This is an ongoing project.

## Building

Necessary dependencies: GLFW 3.3, GLAD, stb_image.h, glm, assimp 5.2.5

`glad.c` and `stb_image.h` should be placed in the `/src` directory (they are not included as part of this repository and should be downloaded independently).

Uses OpenGL version 330 core

## Game Story

* Voxel based survival game
* Third person perspective

A player begins in an auto-generated world. They have nothing - they are naked. Immediately they feel the wrath of the world and their personal metrics start depleting. The world is harsh as anything can kill them - hunger, thirst, exposure, animals, etc. They need to explore the world to gather resources before they succumb to the elements. A player does not win, but tries to survive for as long as possible. The single metric of winning the game is game time. This should be something that a player cannot cheat (i.e. they must remain an active player consistently in order to survive for as long as possible). 