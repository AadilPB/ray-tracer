# Raytracer

## Overview
A ray tracer based on the Ray Tracing in One Weekend(RTIOW) book series that renders images using parallel processing in a thread pool and displays the render progressively as each scanline is rendered.

## Results

## Roadmap

- Implement a *bounding volume hierarchy* data structure instead of the currently used *hittable list* through the second book of the RTIOW book series
- Implement the ability to wrap textures around objects through the second book of the RTIOW book series
- Implement a JSON scene format and a C++ reader to write scenes without the need to recompile
- Implement a python automation script to generate JSON scene files
- Implement a ray-triangle intersection
- Implement a .obj reader
- Complete the third book of the RTIOW book series
- Port to GPU compute library (OpenCL, Vulkan, TBD)
