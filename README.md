# LukkelEngine
> Graphics Engine written in C++<br>

I want to learn C++ and improve at it.  
This combined with my severe dissapointment in the gaming world (games running horribly bad on high-end hardware) made me think that a game engine would be great starting project.  
I'm very new to graphics programming in general so this has been an adventure to say the least.  
<br>
Coding C++ on Linux is not as smooth as it is on Windows. Visual Studio is a **great** tool to use for C++.
But I will make **LukkelEngine** run on Linux as well. I have yet to set up a good development environment on Linux.

---

## Implementation

- [ ] Settings menu (mouse sensitivity, camera speed etc..)
- [ ] Functionality to load object files
- [x] 3D Camera with mouse input (interactive first person camera)
- [ ] Camera interface to separate the camera system to 2D and 3D
- [ ] Physics
- [ ] Cleaner input management system

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

