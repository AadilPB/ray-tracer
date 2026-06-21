# Raytracer

## Overview
A CPU ray tracer engine based on the Ray Tracing in One Weekend(RTIOW) book series. The renderer uses multithreading for improved performance, scaling with the number of threads available on the user's CPU. An AMD Ryzen 5 3600 CPU was used for testing, using all 12 threads. Scenes are accepted in a JSON format, which can be generated using Python scripts provided in the ``scripts`` folder, with helper functions for writing the JSON found in ``scene_def.py``, alongside provided example scene scripts.


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

## Implementation


## Results

## Future Additions

- Implement Surface Area Heuristics to Bounded Volume Hierarchy
- Implement a .obj reader
- Complete the third book of the RTIOW book series
- Port to GPU compute library (OpenCL, Vulkan, TBD)

## References
