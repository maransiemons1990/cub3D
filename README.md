# Cub3D
<a href><img src="images/screenshot_bonus.png" title="Screenshot_bonus" alt="Screenshot_bonus"></a>

"This project is inspired by the world-famous eponymous 90's game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you'll have to find your way."

This project is part of the Codam curriculum. It's a project out of the 2nd circle of the curriculum:</br>
</br>
<a href><img src="images/curriculum_cub3d.png" width="300" title="cub3d" alt="cub3d"></a>

For more information check the subject documentation.

## Bonus

Extra:
* Floor and ceiling texture
* Multiple sprites (2, 3 and 4 in the map)

## Getting Started

- Clone the repository to your computer
- Run make or make bonus
```
$ make bonus
```
- Execute program
```
./cub3D <scene_file.cub>
```

For example:
```
./cub3D maps/bonus_map.cub
```

> ! Bonus needs a different <scene_file.cub>

## Scene_file.cub

The program takes as a first argument a scene description file with the .cub extension.

The map:
- N, S, E, W: player's start position and spawning orientation
- 1: wall
- 2, 3, 4 : sprites

Identifiers:
- R: resolution
- NO: path to the north side of the wall texture
- SO: path to the south side of the wall texture
- EA: path to the east side of the wall texture
- WE: path to the west side of the wall texture
- S: path to the sprite texure
- F: floor color/floor texture
- C: ceiling color/ceiling texture

## Game

Keys:
- WASD to move
- Left and right arrow key to rotate
- ESC to exit the game

Game option:
- "--save" as a second argument to save the first rendered image in bmp format

## Acknowledgments and sources

* https://lodev.org/cgtutor/raycasting.html
* https://itnext.io/bits-to-bitmaps-a-simple-walkthrough-of-bmp-image-format-765dc6857393
