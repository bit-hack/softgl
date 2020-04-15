# SoftGL

A opengl implementation using Software Rendering on the CPU.


## Q&A

Why would I make this?
Because its fun to learn OpenGL from the wrong end.

What version of OpenGL does this support?
Somewhere around OpenGL1.4

Is it fast?
While i'm trying to make it fast, its not even close to something like a Geforce graphics card.

How do I use this?
You dont, and you shouldnt. It really just an experiment.

But really how do I use this?
1. Compile it.
2. Copy OpenGL32.dll, softgl_rast_reference.dll and softgl.cfg into your game folder.
3. Your game will most likely crash.

Whats your goal?
When something like Doom3 is playable.


## Features

- Mip-Mapping
- Perspective correct texture mapping
- Simple backend architecture
- Experimental OpenCL backend
- Not much else at the moment


## Optimizations

- Affine mapping for small triangles
- Vectorizable edge based rendering
- 16x16 stamp rendering with fast culling
- Stamps coded in tight SSE


## Screenshots

These screenshots show the current state of progress on 15/04/2020.

![](/docs/screenshots/hl_of_demo.png?raw=true "Halflife opposing force demo")

![](/docs/screenshots/quake3_demo.png?raw=true "Quake 3 demo")

![](/docs/screenshots/ut99_goty.png?raw=true "Unreal Tournament GOTY")

![](/docs/screenshots/quake2.png?raw=true "Quake 2")
