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
a game engine requires. As this is a project for me to learn more about C++, there are parts which
are not *'mine'*.<br>
The ECS system is one great example. My initial implementation made me realize quite 
quickly that I was in dire need of something else than the code I implemented as it got really hard to follow.<br>

**My workflow has been like this:**
- *Implement a core feature*
- *Try it out*
- *Realize that my implementation is **ABSOLUTE** garbage*
- *Delete and start over again* :sunglasses:

I've promised myself to not spend too much time being stuck as that has been the main cause for me to quit projects in the past.
So if I see myself getting stuck for too long, I check out some real good implementations and try to see how I can change
my current one into something similar.
<br><br>

As I am doing this project I'm reading game architecture and rendering books to learn as much as possible.<br>
The base layout of the engine is bound to change because the more I learn :custom_arrow_right: the more able I get to
tweak and customize the entire engine without making everything explode. Also because I have performance in mind 
and let me tell you, the current implementation surely does **NOT** care about performance. I'll do it in this order:<br>
1. Make it work
2. Make it better


---

## Implementation
<!-- Checklist -->
:black_square_button: Functionality to load object files<br>
:white_check_mark: 3D Camera with mouse input (interactive first person camera)<br>
:black_square_button: Camera interface to separate the camera system to 2D and 3D<br>
:white_check_mark: Physics (not fully)<br>
:black_square_button: Cleaner input management system<br>
:black_square_button: Manipulation of in world objects (rigid bodies)<br>
:black_square_button: Realtime changes of shaders/textures and manipulation of them<br>
:black_square_button: Collision system<br>
:black_square_button: Vector and matrix classes<br>

## Todo
:black_square_button: Objects ready for spawning (e.g cubes, ground objects, spheres)<br>
:black_square_button: ImGui menues for individual objects<br>
:black_square_button: Settings menu (mouse sensitivity, camera speed etc..)<br>
### Upcoming implementations
:white_check_mark: Template objects ready for spawning (e.g cubes, ground objects, spheres)<br>
:black_square_button: Settings menu (mouse sensitivity, camera speed etc..)<br>
:black_square_button: Change name of namespace (not sure yet :custom_arrow_right: LK, LE, LKE, LKEN, etc...)<br>
:black_square_button: Raycasting<br>

### Needs fixing
:black_square_button: Memory leak at entity resets from inspector menu<br>
:black_square_button: Translation at the model transformation. Need to fix the position vector there

---
## Engine design
### Application
Main application.<br>

### Sandbox
Inherits from **Application** and is the main implementation of the engine.

### Renderer
Abstracted OpenGL to create an API that is way more clean than raw OpenGL calls.<br>
To be honest, the way that OpenGL works with its context and states is kind of hard to get a grasp on.
My goal is to have a solid API that takes care of the raw OpenGL without me being forced to use it *directly*.

### Scene
Projected world. Holds entities (world objects).<br>

---

## Notes for myself
Need to set up a roadmap and daily goals. I also need to refine the current implementation before I begin implementing new things.
I also need to separate the 3D 'FpsCamera' to a new 3D camera and then create a ortographic camera without projections. 
Before I start reading more about raycasting and further interaction functionality, I need to tidy up the current code. 
I'm not happy with the current state of the code. I need to step back for a second and make sure I am creating
an abstract API that is simple to use. Therefore I also need to fix the btVector3 :custom_arrow_left_right: glm::vec3 issues.

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


## Mathematics
<p align="center">Some of the linear algebra used to create the projection and view matrices to create the 3D feel.</p>
<div align="center">
	<img align="center" src="/doc/img/matrix-transformations.png" width=440 height=400>
</div>

