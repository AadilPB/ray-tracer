from scene_defs import *

scene = {}

scene["camera"] = camera([1.0, 1.0], 400, 250, 50, [0, 0, 0],
                         60, [4, 3, -1], [0, 0, -6], [0, 1, 0], 
                         0)


marble_tex = noise_texture(4)
light = diffuse_light([10, 10, 10])
objects = []

objects.append(tri([-1, -1, -5], [ 1, -1, -5], [0, 1, -6], lambertian(color = None, texture = marble_tex)))
objects.append(tri([ 1, -1, -5], [ 1, -1, -7], [0, 1, -6], lambertian(color = None, texture = marble_tex)))
objects.append(tri([ 1, -1, -7], [-1, -1, -7], [0, 1, -6], lambertian(color = None, texture = marble_tex)))
objects.append(tri([-1, -1, -7], [-1, -1, -5], [0, 1, -6], lambertian(color = None, texture = marble_tex)))

objects.append(tri([-1, -1, -5], [1, -1, -5], [ 1, -1, -7], lambertian(color = None, texture = marble_tex)))
objects.append(tri([-1, -1, -5], [1, -1, -7], [-1, -1, -7], lambertian(color = None, texture = marble_tex)))
objects.append(quad([-500, -1, 5], [1000, 0, 0], [0, 0, -1000], lambertian(color = None, texture = marble_tex)))
objects.append(sphere([-5, 3, -6], 3, light))

scene["objects"] = objects

save_scene(scene, "scenes/pyramid.json", indent = 4)
