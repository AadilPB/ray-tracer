from scene_defs import *

scene = {}

scene["camera"] = camera([16, 9], 640, 100, 50, [0.70, 0.80, 1.00],
                            20, [13, 2, 3], [0, 0, 0], [0, 1, 0], 0)

objects = []

pertext = noise_texture(4)
objects.append(sphere([0, -1000, 0], 1000, lambertian(color = None, texture = pertext)))
objects.append(sphere([0, 2, 0], 2, lambertian(color = None, texture = pertext)))
scene["objects"] = objects

save_scene(scene, "scenes/perlin_spheres.json", indent = 4)
