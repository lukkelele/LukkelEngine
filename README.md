# LukkelEngine :vertical_traffic_light:
> Graphics Engine written in C++<br>

This is a project for me to improve at writing C++ code (or code in general).  
<br>
Combined with my severe dissapointment in the gaming world with games running horribly bad on high-end hardware
(I'm looking at you, **Battlefield 2042**)
made me think that a game engine would be a fun starting project to begin working on.  
I'm very new to graphics programming in general so this has been an adventure to say the least.  
<br>
I'm by no means that great of a programmer to solve all the problems and implement all the features
a game engine requires. 
I've promised myself to not spend too much time being stuck as that has been the main cause for me to quit projects in the past.
So if I see myself getting stuck for too long, I check out some real good implementations and try to see how I can change
my current one into something similar.<br>
The ECS system is one great example. My initial implementation made me realize quite 
quickly that I was in dire need of something else than the code I implemented as it got really hard to follow.<br>


As I am doing this project I'm reading game architecture and other graphics programming books to learn as much as possible.<br>
The base layout of the engine is bound to change because the more I learn the more I will want to change things. Also because I have performance in mind 
and let me tell you, the current implementation surely does **NOT** care about performance. I'll do it in this order:<br>
1. Make it work
2. Make it better

---

## Implementation
<!-- Checklist -->
:black_square_button: Functionality to load object files<br>
:black_square_button: Ortographic camera for 2D <br>
:white_check_mark: 3D Camera with mouse input (interactive first person camera)<br>
:white_check_mark: Physics (not fully)<br>
:white_check_mark: Manipulation of in world objects (rigid bodies)<br>
:white_check_mark: Raycasting <br>
:black_square_button: Hot reloading of shaders/textures and manipulation of them during runtime<br>
:white_check_mark: Collision system<br>
:white_check_mark: Rigidbody constraints <br>
:black_square_button: Rigidbody skeleton <br>
:black_square_button: Base models for interacting with world (player models, projectiles) <br>
:black_square_button: Objects ready for spawning (e.g cubes, ground objects, spheres)<br>
:black_square_button: Change name of namespace (not sure yet :custom_arrow_right: LK, LE, LKE, LKEN, etc...)<br>

---
## Engine design
### Application
Main application.<br>

### LukkeLallish
Inherits from **Application** and is the current runtime of the engine. It is technically not the 'Sandbox'
but I do use it as such for now.<br>
The word *'Lallish'* is a swedish slang for not being serious or playing around. I named it this because I use **LukkeLallish** for 
testing and playing around with newly added tools and engine implementations.

---

## Screenshots

### March 19, 2023
Improved the UI, added constraints and updated the event handling. I was in dire need to use an event system as the 
world physics cant really function without it. 

<div align="center">
	<img align="center" src="/doc/img/lukkelengine-03-19-3.png" width=740 height=440>
<p align="center">The cyan cube has a pivot constraint that can be added and removed with the UI (constraints menu to the left)</p>
</div>

<div align="center">
	<img align="center" src="/doc/img/lukkelengine-03-19-2.png" width=740 height=440>
<p align="center"></p>
</div>

<div align="center">
	<img align="center" src="/doc/img/lukkelengine-03-19-1.png" width=740 height=440>
<p align="center">Colliding objects are set to the color black whenever a valid detection takes place</p>
</div>

### March 12, 2023

<div align="center">
	<img align="center" src="/doc/img/lukkelengine-03-12-1.png" width=740 height=440>
<p align="center"></p>
</div>

<div align="center">
	<img align="center" src="/doc/img/lukkelengine-03-12-2bodyPicked.png" width=740 height=440>
<p align="center">Selected object with raycasting after clicking left mouse button</p>
</div>

<div align="center">
	<img align="center" src="/doc/img/lukkelengine-03-12-3-changecolors.png" width=740 height=440>
<p align="center">Changed color of selected object</p>
</div>

<div align="center">
	<img align="center" src="/doc/img/lukkelengine-03-12-4.png" width=740 height=440>
<p align="center">View of the platform</p>
</div>

---

### February 26, 2023

<div align="center">
	<img align="center" src="/doc/img/engine-26-2-2023-pic1.png" width=740 height=440>
</div>
<p align="center">Scene overview with a cube</p>

<br>
<div align="center">
	<img align="center" src="/doc/img/engine-26-2-2023-pic2.png" width=740 height=440>
<p align="center">The same cube but from a closer distance</p>
</div>

<br>


--- 


