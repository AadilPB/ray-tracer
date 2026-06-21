from scene_defs import *

scene = {}

scene["camera"] = camera([1.0, 1.0], 1200, 250, 50, [0, 0, 0],
                         60, [4, 3, -1], [0, 0, -6], [0, 1, 0], 
                         0)


marble_tex = noise_texture(4)
pyramid_colour = lambertian([0.98, 0.68, 0.05])
light = diffuse_light(emit = None, texture = image_texture("textures/moon.png"))
objects = []

objects.append(tri([-1, -1, -5], [ 1, -1, -5], [0, 1, -6], pyramid_colour))
objects.append(tri([ 1, -1, -5], [ 1, -1, -7], [0, 1, -6], pyramid_colour))
objects.append(tri([ 1, -1, -7], [-1, -1, -7], [0, 1, -6], pyramid_colour))
objects.append(tri([-1, -1, -7], [-1, -1, -5], [0, 1, -6], pyramid_colour))

objects.append(tri([-1, -1, -5], [1, -1, -5], [ 1, -1, -7], pyramid_colour))
objects.append(tri([-1, -1, -5], [1, -1, -7], [-1, -1, -7], pyramid_colour))
objects.append(quad([-500, -1, 5], [1000, 0, 0], [0, 0, -1000], lambertian(color = None, texture = marble_tex)))
objects.append(sphere([-5, 3, -6], 3, light))

scene["objects"] = objects

save_scene(scene, "scenes/pyramid.json", indent = 4)
