from scene_defs import *
import math
import random

scene = {}

scene["camera"] = camera([1.0, 1.0], 400, 250, 4, [0, 0, 0],
                         40, [478, 278, -600], [278, 278, 0], [0, 1, 0],
                          0)

objects = []

boxes_per_side = 20;
ground = lambertian([0.48, 0.83, 0.53])

for i in range(boxes_per_side):
    for j in range(boxes_per_side):
        w = 100.0
        x0 = -1000.0 + i*w
        z0 = -1000.0 + j*w
        y0 = 0.0
        x1 = x0 + w
        y1 = random.uniform(1, 101)
        z1 = z0 + w
        objects.append(box([x0, y0, z0], [x1, y1, z1], ground))

light = diffuse_light([7, 7, 7])
objects.append(quad([123, 553, 147], [300, 0, 0], [0, 0, 265], light))

scene["objects"] = objects

save_scene(scene, "scenes/final_scene.json", indent = 4)

