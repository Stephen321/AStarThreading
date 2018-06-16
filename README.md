# AStarThreading
*Using SDL_Threads to better improve the performance of many A\* pathfinding characters in large maps.*

A level is a grid with walls which block movement. The green square is a target for all the yellow squares. The green square randomly selects a target to pathfind towards. Yellow squares target the green square. Once all yellow squares have reached the green square, the next level begins.  

Threads can be seen to improve the speed at which the yellow squares can begin moving for the larger level. FPS is better with multiple threads for the larger levels.

## Issues:
[Known issues and to do list](https://github.com/Stephen321/AStarThreading/issues/1)

## Video:
https://youtu.be/KTlbpNSpPlE

## Controls:
- F to toggle fps display.
- L to toggle path lines.
- T to toggle threads.
- Arrow keys to move camera.
- Scroll wheel to zoom in/out camera.

