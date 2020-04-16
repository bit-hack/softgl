# SoftGL

An opengl implementation using Software Rendering on the CPU.


## Q&A

> Why would I make this?
>
> Because its fun to learn OpenGL from the wrong end.

> What version of OpenGL does this support?
>
> Somewhere around OpenGL1.4

> Is it fast?
>
> While i'm trying to make it fast, its not even close to something like a Geforce256 graphics card.

> How do I use this?
>
> You dont, and you shouldnt. It really just an experiment.

> But really how do I use this?
>
> 1. Compile it.
> 2. Copy OpenGL32.dll, softgl_rast_reference.dll and softgl.cfg into your game folder.
> 3. Launch your game (which will most likely crash.)

> Whats your goal?
>
> When something like Doom3 is playable.

> Is it conformant?
>
> No.

## Features

- Per triangle Mip-Mapping
- Perspective correct texture mapping
- Simple backend architecture
- Experimental OpenCL backend
- Not much else at the moment


## Optimizations

- Affine mapping for small triangles
- Vectorizable edge based rendering
- 16x16 stamp rendering with fast culling
- Stamps coded in tight SSE


## The future

- Support more old OpenGL games
- Fixed point UV interpolation
- More blend modes
- Use AVX stamps
- Multuithread the rasterizer
- JIT the raster stamps
- Improve the OpenCL backend
- Z-buffer at the stamp level for fast culling
- More optimizations
- Support more features
  - Alpha Test
  - Scissor
  - Texenv
  - Stencil Test
  - ...


## Statistics

Stats from the quake 3 timedemo (default settings) invoked via `quake3.exe +timedemo 1 +demo four`.

> 1260 frames 51.0 seconds 24.7 fps 15.0/40.5/78.0/11.2 ms


## Screenshots

These screenshots show the current state of progress on 15/04/2020.

![](docs/screenshots/hl_of_demo.png?raw=true "Halflife opposing force demo")

![](docs/screenshots/quake3_demo.png?raw=true "Quake 3 demo")

![](docs/screenshots/ut99_goty.png?raw=true "Unreal Tournament GOTY")

![](docs/screenshots/quake2.png?raw=true "Quake 2")

![](docs/screenshots/doom3_1.png?raw=true "Doom 3")

![](docs/screenshots/doom3_2.png?raw=true "Doom 3")

![](docs/screenshots/ut2003.png?raw=true "Unreal Tournament 2003")
