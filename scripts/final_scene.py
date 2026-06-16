from scene_defs import *
import math
import random

scene = {}

scene["camera"] = camera([1.0, 1.0], 400, 250, 4, [0, 0, 0],
                         40, [478, 278, -600], [278, 278, 0], [0, 1, 0],
                          0)

objects = []
boxes1 = []
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
        boxes1.append(box([x0, y0, z0], [x1, y1, z1], ground))

boxes1 = bvh_node(boxes1)
objects.append(boxes1)
light = diffuse_light([7, 7, 7])
objects.append(quad([123, 553, 147], [300, 0, 0], [0, 0, 265], light))

center1 = [400, 400, 200]
center2 = [center1[0] + 30, center1[1] + 0, center1[2] + 0]
sphere_material = lambertian([0.7, 0.3, 0.1])
objects.append(sphere(center1, 50, sphere_material, center2))

objects.append(sphere([260, 150, 45], 50, dielectric(1.5)))
objects.append(sphere([0, 150, 145], 50, metal([0.8, 0.8, 0.9], 1.0)))

boundary = sphere([360, 150, 145], 70, dielectric(1.5))
objects.append(boundary)
objects.append(constant_medium(boundary, 0.2, texture = None, albedo = [0.2, 0.4, 0.9]))
boundary = sphere([0, 0, 0], 5000, dielectric(1.5))
objects.append(constant_medium(boundary, .0001, texture = None, albedo = [1, 1, 1]))

emat = lambertian(color = None, texture = image_texture("textures/earthmap.jpg"))
objects.append(sphere([400, 200, 400], 100, emat))
pertext = noise_texture(0.2)
objects.append(sphere([220, 280, 300], 80, lambertian(color = None, texture = pertext)))

boxes2 = []
white = lambertian([0.73, 0.73, 0.73])
ns = 1000
for j in range(ns):
    boxes2.append(sphere([random.uniform(0, 165), random.uniform(0, 165), random.uniform(0, 165)], 10, white))

objects.append(translate(rotate_y(bvh_node(boxes2), 15), [-100, 270, 395]))


scene["objects"] = objects

save_scene(scene, "scenes/final_scene.json", indent = 4)

