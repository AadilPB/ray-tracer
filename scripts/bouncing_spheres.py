import scene_defs as sc
import json
import random
import math

scene = {}

scene["camera"] = sc.camera([16.0, 9.0], 800, 10, 50, [0.70, 0.80, 1.00],
                            20, [13, 2, 3], [0, 0, 0], [0, 1, 0], 0.6, 10.0)

objects = []

checker = sc.checker_texture(0.32, [0.2, 0.3, 0.1], [0.9, 0.9, 0.9])

for a in range(-11, 11):
    for b in range(-11, 11):
        choose_mat = random.random()
        center = [a + 0.9*random.random(), 0.2, b+0.9*random.random()];
        condition = [center[0] - 4, center[1] - 0.2, center[2] - 0]
        condition_length = math.sqrt(condition[0]**2 + condition[1]**2 + condition[2]**2)
        if condition_length > 0.9:
            if choose_mat < 0.8:
                #diffuse
                albedo = [random.random() * random.random(), 
                          random.random() * random.random(), 
                          random.random() * random.random()]
                sphere_material = sc.lambertian(albedo)
                center2 = [center[0], center[1] + random.uniform(0, 0.5), center[2]]
                objects.append(sc.sphere(center, 0.2, sphere_material, center2))
            elif choose_mat < 0.95:
                #metal
                albedo = [random.uniform(0.5, 1), random.uniform(0.5, 1), random.uniform(0.5, 1)]
                fuzz = random.uniform(0, 0.5)
                sphere_material = sc.metal(albedo, fuzz)
                objects.append(sc.sphere(center, 0.2, sphere_material))
            else:
                #glass
                sphere_material = sc.dielectric(1.5)
                objects.append(sc.sphere(center, 0.2, sphere_material))

        

material1 = sc.dielectric(1.5)
material2 = sc.lambertian([0.4, 0.2, 0.1], None)
material3 = sc.metal([0.7, 0.6, 0.5], 0.0)

objects.append(sc.sphere([0, -1000, 0], 1000, sc.lambertian(None, checker)))
objects.append(sc.sphere([0, 1, 0], 1.0, material1))
objects.append(sc.sphere([-4, 1, 0], 1.0, material2))
objects.append(sc.sphere([4, 1, 0], 1.0, material3))


scene["objects"] = objects

sc.save_scene(scene, "scenes/bouncing_spheres.json", 4)
