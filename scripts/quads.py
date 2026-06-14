from scene_defs import *

scene = {}

scene["camera"] = camera([1.0, 1.0], 400, 100, 50, [0.70, 0.80, 1.00],
                         80, [0, 0, 9], [0, 0, 0], [0, 1, 0],
                         0)

objects = []

left_red = lambertian([1.0, 0.2, 0.2])
back_green = lambertian([0.2, 1.0, 0.2])
right_blue = lambertian([0.2, 0.2, 1.0])
upper_orange = lambertian([1.0, 0.5, 0.0])
lower_teal = lambertian([0.2, 0.8, 0.8])

objects.append(quad([-3, -2, 5], [0, 0, -4], [0, 4, 0], left_red))
objects.append(quad([-2, -2, 0], [4, 0, 0], [0, 4, 0], back_green))
objects.append(quad([3, -2, 1], [0, 0, 4], [0, 4, 0], right_blue))
objects.append(quad([-2, 3, 1], [4, 0, 0], [0, 0, 4], upper_orange))
objects.append(quad([-2, -3, 5], [4, 0, 0], [0, 0, -4], lower_teal))

scene["objects"] = objects


save_scene(scene, "scenes/quads.json", indent = 4)
