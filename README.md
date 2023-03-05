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
:white_check_mark: 3D Camera with mouse input (interactive first person camera)<br>
:white_check_mark: Physics (not fully)<br>
:black_square_button: Manipulation of in world objects (rigid bodies)<br>
:white_check_mark: Raycasting (I've achieved hit detection)<br>
:black_square_button: Realtime changes of shaders/textures and manipulation of them<br>
:black_square_button: Collision system<br>

## Todo
:black_square_button: Objects ready for spawning (e.g cubes, ground objects, spheres)<br>
:white_check_mark: ImGui menues for individual objects<br>
:black_square_button: Mesh and body factories<br>
:black_square_button: Separate files for collision detection/raycasting and other form of in-world interactions<br>
:black_square_button: Settings menu (mouse sensitivity, camera speed etc..)<br>
### Upcoming implementations
:white_check_mark: Template objects ready for spawning (e.g cubes, ground objects, spheres)<br>
:white_check_mark: Settings menu (mouse sensitivity, camera speed etc..) :custom_arrow_right: more incoming<br>
:black_square_button: Change name of namespace (not sure yet :custom_arrow_right: LK, LE, LKE, LKEN, etc...)<br>
:black_square_button: Camera interface to separate the camera system to 2D and 3D<br>

### Needs fixing
:black_square_button: Memory leak at entity resets from inspector menu<br>

### Might/might not do
:black_square_button: Vector and matrix classes to abstract **Bullet3** from **GLM**<br>

---
## Engine design
### Application
Main application.<br>

### LukkeLallish (Sandbox)
Inherits from **Application** and is the current runtime of the engine.

### Renderer
Abstracted OpenGL to create an API that is way more clean than raw OpenGL calls.<br>
To be honest, the way that OpenGL works with its context and states is kind of hard to get a grasp on.
My goal is to have a solid API that takes care of the raw OpenGL without me being forced to use it *directly*.  
As I'm also reading books about **OpenGL** alongside this project, I've come to the conclusion that relying on
the use of the states is not something I will pursue (*for now, at least*). There are early benchmarks in **Quake 3**
that show a quite significant increase in performance for just skipping the state checks. Modern OpenGL is better of course but 
I'm currently running **OpenGL 3.3** so I'll reduce my use of them just as a precaution.

---

## Screenshots

### 26 February 2023

<div align="center">
	<img align="center" src="/doc/img/engine-26-2-2023-pic1.png" width=740 height=440>
</div>
<p align="center">Scene overview with a cube</p>

<br>
<div align="center">
	<img align="center" src="/doc/img/engine-26-2-2023-pic2.png" width=740 height=440>
<p align="center">The same cube but from a closer distance</p>
</div>


--- 


