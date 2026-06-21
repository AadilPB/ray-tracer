# Raytracer

## Overview
A CPU ray tracer engine based on the Ray Tracing in One Weekend(RTIOW) book series. The renderer uses multithreading for improved performance, scaling with the number of threads available on the user's CPU. An AMD Ryzen 5 3600 CPU was used for testing, using all 12 threads. Scenes are accepted in a JSON format, which can be generated using Python scripts provided in the ``scripts`` folder, with helper functions for writing the JSON found in ``scene_def.py``, alongside provided example scene scripts.

<img width="1200" height="1200" alt="image" src="https://github.com/user-attachments/assets/b4cbe323-2f49-4432-8a11-edad3a057397" />

*A high-quality scene featuring a diffuse light with a moon texture, a plane made using a quad with a noise texture, and a lambertian pyramid.*

<img width="1200" height="675" alt="image" src="https://github.com/user-attachments/assets/0127977a-cf57-42e0-87b9-faf14e206148" />

*A low-quality scene with a multiple lambertian, metal and dielectric spheres*

## Building and Running the Program
### Prerequisites
1. To run this program a Windows 10/11 computer is required
2. Install MSYS2 from https://www.msys2.org/
3. Open the UCRT64 terminal
4. Run ``pacman -Syu`` to ensure all packages are up to date
5. Install the following packages:
```
pacman -S mingw-w64-ucrt-x86_64-gcc
pacman -S mingw-w64-ucrt-x86_64-cmake
pacman -S mingw-w64-ucrt-x86_64-SDL2
```
### Building
To build the program, run the following commands in the project directory:
```
mkdir build
cd build
cmake ..
cmake --build .
cd ..
```
### Running
To run the program, there are two options:
1. If `.json` scene description files are placed in the ``scenes`` folder, the program can be run as:
```
raytrace filename
```
2. If the .json is located elsewhere, provide the full path: 
```
raytrace filepath
```
   
## How it Works

## Scene Definition
Scenes are defined in `.json` files. Python functions are provided in `scene_defs.py` to help construct these files so that they can be build using scripts. 

To import the scene building functions:
```
from scene_defs import *
```
Then, define the following:
```
scene = {}
objects = []
```
`scene` is a dictionary that holds the `"camera"` and `"objects"` keys, which define the scene's camera and the objects that populate it.

After appending all required objects to the `"objects"` list, assign it to the `"objects"` key in the scene dictionary:
```
scene["objects"] = objects
```

To save the scripted scene as a .json file:
```
save_scene(scene, path, indent = 4)
```
This function takes the scene dictionary, the intended path for the `.json` scene file, and an indent value, which determines the indentation level in the `.json` scene file.

### The Camera

### Objects
#### Sphere
#### Quad
#### Tri
#### Box

### Object Wrappers
#### Rotate Y
#### Translate
#### Constant Medium
#### BVH Node

### Materials
#### Lambertian
#### Metal
#### Dielectric
#### Diffuse Light

### Textures
#### Solid Color
#### Checker 
#### Noise
#### Image Texture

## Results

## Future Additions

- Implement Surface Area Heuristics to Bounded Volume Hierarchy
- Implement a .obj reader
- Complete the third book of the RTIOW book series
- Port to GPU compute library (OpenCL, Vulkan, TBD)

## References
