#ifndef SCENE_READER_H
#define SCENE_READER_H

#include <fstream>
#include <vector>

#include "json.hpp"
#include "camera.h"
#include "hittable.h"
#include "sphere.h"
#include "hittable_list.h"



using json = nlohmann::json;

namespace scene_reader 
{

    void camera_setup(const json& data, camera& cam)
    {
        cam.aspect_ratio      = data.at("image_width").get<double>() / data.at("image_height").get<double>();
        cam.image_width       = data.at("image_width");
        cam.samples_per_pixel = data.at("samples_per_pixel");
        cam.max_depth         = data.at("max_depth");
        
        auto background       = data.at("background").get<std::vector<double>>(); 
        auto lookfrom         = data.at("lookfrom").get<std::vector<double>>(); 
        auto lookat           = data.at("lookat").get<std::vector<double>>(); 
        auto vup              = data.at("vup").get<std::vector<double>>(); 
        
        cam.background        = color(background[0], background[1], background[2]);
        cam.vfov              = data.at("vfov");
        cam.lookfrom          = point3(lookfrom[0], lookfrom[1], lookfrom[2]);
        cam.lookat            = point3(lookat[0], lookat[1], lookat[2]);
        cam.vup               = vec3(vup[0], vup[1], vup[2]);

        cam.defocus_angle =  data.at("defocus_angle");
    }

    void load_objects(const json& data, hittable_list& world)
    {
        for (const auto& obj : data)
        {
            if(obj.at("type") == "sphere")
            {
                auto center = obj.at("center").get<std::vector<double>>();
                auto obj_color = obj.at("color").get<std::vector<double>>();
                auto radius = obj.at("radius").get<double>();
                if(obj.at("material") == "lambertian")
                    world.add(make_shared<sphere>(point3(center[0], center[1], center[2]), 
                    radius, make_shared<lambertian>(color(obj_color[0], obj_color[1], obj_color[2]))));
            }
        }
    }

    void load_scene(const std::string& path, camera& cam, hittable_list& world)
    {
        std::ifstream f(path);
        json data = json::parse(f);

        camera_setup(data["camera"], cam);
        load_objects(data["objects"], world);

    }


}


#endif
