# LukkelEngine
> Graphics Engine written in C++<br>

As I've grown impatient with Python and Java I figured it was time for me to step in to a new realm.
One language I always have had a special love towards is **C** and **C++**. Especially **C++**, something about 
the entire structure of the language is just something I appreciate. It is so clean in away.<br><br>
My preferred way of learning is to just do something, be horrible at it and try again.<br>
A project is a very good way of learning as it *requires* things to work.<br>
My restlessness combined with my severe dissapointment in the gaming world made me think that a game engine
would be great starting project. Games are no longer optimized and they all run bad.
A thought popped up: *"**how hard could it be?**"*<br>
And just like that **LukkelEngine** was born.

---
## Components

### Application
Main application.<br>
All components are used inside **Application**.
> - Layers
> - Logging
> - Error handling

### Scene
Projected world.
> - Entity (entities)

### Renderer
Holds mostly abstracted OpenGL to create an API that is way more clean than raw OpenGL calls.
> - Camera
> - VertexArray
> - VertexBuffer
> - IndexBuffer
> - Shader
> - Texture
 
<br>

**LukkelEngine** 

## Mathematics
<p align="center">The linear algebra used to create the projection and view matrices to create the 3D *feel*.</p>
<div align="center">
	<img align="center" src="/res/img/matrix-transformations.png" width=460 height=440>
</div>

---

# LukkeLallish -> Sandbox

The sandbox is simply a child of *Application* and implements custom layers that are inserted on to the engine.
This is done to simulate a real life example of actually using the engine. Not that anyone besides me ever will do that,
still I think it is appropriate to code *as if* that is the case.


