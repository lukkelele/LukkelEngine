# LukkelEngine :palm_tree:
> Graphics Engine written in C++<br>

This is a project for me to improve at writing C++ code (or code in general).  
<br>
Combined with my severe dissapointment in the gaming world with games running horribly bad on high-end hardware
(I'm looking at you Battlefield 2042 :angry:)
made me think that a game engine would be fun starting project to begin working on.  
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
- *Realize that my implementation is **ABSOLUTE** garbage* :unamused:
- *Delete and start over again* :sunglasses:

I've promised myself to not spend too much time being stuck as that has been the main cause for me to quit projects in the past.
So if I see myself getting stuck for too long, I check out some real good implementations and try to see how I can change
my current one into something similar.<br><br>
Game architecture and graphics programming is **very difficult** and I have gained massive amounts of respect towards those who
pursue this professionally or have been in this field for a long time! :blush:<br>


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

## Todo
:black_square_button: Objects ready for spawning (e.g cubes, ground objects, spheres)<br>
:black_square_button: ImGui menues for individual objects<br>
:black_square_button: Settings menu (mouse sensitivity, camera speed etc..)<br>
### Upcoming implementations
:black_square_button: Component syncing for MeshComponents<br>
:black_square_button: Template objects ready for spawning (e.g cubes, ground objects, spheres)<br>
:black_square_button: ImGui menues for individual objects<br>
:black_square_button: Settings menu (mouse sensitivity, camera speed etc..)<br>

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
> VertexArray<br>
> VerteBuffer<br>
> VertexBufferLayout<br>
> Shader<br>
> Texture<br>

### Scene
Projected world. Holds entities (world objects).<br>
> Container of:
>> Entity
 


## Mathematics
<p align="center">The linear algebra used to create the projection and view matrices to create the 3D feel.</p>
<div align="center">
	<img align="center" src="/doc/img/matrix-transformations.png" width=600 height=600>
</div>

