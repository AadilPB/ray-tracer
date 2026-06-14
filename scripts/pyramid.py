from scene_defs import *

scene = {}

scene["camera"] = camera([1.0, 1.0], 400, 250, 50, [0.5, 0.7, 1.0],
                         60, [4, 3, -1], [0, 0, -6], [0, 1, 0], 
                         0)

mat_front = lambertian([1, 0, 0])
mat_right = lambertian([0, 1, 0])
mat_back  = lambertian([0, 0, 1])
mat_left  = lambertian([1, 1, 0])
mat_base  = lambertian([1, 0, 1])

objects = []

objects.append(tri([-1, -1, -5], [ 1, -1, -5], [0, 1, -6], mat_front))
objects.append(tri([ 1, -1, -5], [ 1, -1, -7], [0, 1, -6], mat_right))
objects.append(tri([ 1, -1, -7], [-1, -1, -7], [0, 1, -6], mat_back))
objects.append(tri([-1, -1, -7], [-1, -1, -5], [0, 1, -6], mat_left))

objects.append(tri([-1, -1, -5], [1, -1, -5], [ 1, -1, -7], mat_base))
objects.append(tri([-1, -1, -5], [1, -1, -7], [-1, -1, -7], mat_base))

scene["objects"] = objects

save_scene(scene, "scenes/pyramid.json", indent = 4)
