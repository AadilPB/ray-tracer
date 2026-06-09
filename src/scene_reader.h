#ifndef SCENE_READER_H
#define SCENE_READER_H

#include <fstream>
#include <vector>

#include "json.hpp"
#include "camera.h"
#include "hittable.h"
#include "sphere.h"
#include "hittable_list.h"
#include "material.h"
#include "texture.h"


using json = nlohmann::json;

namespace scene_reader 
{

    void camera_setup(const json& data, camera& cam);
    void load_objects(const json& data, hittable_list& world);
    shared_ptr<hittable> read_object(const json& data);
    shared_ptr<material> load_material(const json& data);
    shared_ptr<texture> load_texture(const json& data);

    void load_scene(const std::string& path, camera& cam, hittable_list& world)
    {
        std::ifstream f(path);

        if(!f.is_open())
        {
            std::cerr << "Failed to open scene file: " << path << std::endl;
            return;
        }


        json data = json::parse(f);
    
        camera_setup(data["camera"], cam);
        load_objects(data["objects"], world);

    }

    void camera_setup(const json& data, camera& cam)
    {
        auto ar = data.at("aspect_ratio").get<std::vector<double>>();
        cam.aspect_ratio      = ar[0] / ar[1];
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
            world.add(read_object(obj));
        }
    }

    shared_ptr<hittable> read_object(const json& obj)
    {
        if(obj.at("type") == "sphere")
            {
                auto center = obj.at("center").get<std::vector<double>>();
                auto radius = obj.at("radius").get<double>();
                json mat_data = obj.at("material");
                auto mat = load_material(mat_data);
                return make_shared<sphere>(point3(center[0], center[1], center[2]), radius, mat);

            }

            if(obj.at("type") == "quad")
            {
                auto Q = obj.at("q").get<std::vector<double>>();
                auto u = obj.at("u").get<std::vector<double>>();
                auto v = obj.at("v").get<std::vector<double>>();

                json mat_data = obj.at("material");
                auto mat = load_material(mat_data);
                return make_shared<quad>(point3(Q[0], Q[1], Q[2]), vec3(u[0], u[1], u[2]), vec3(v[0], v[1], v[2]), mat);
            }

            if(obj.at("type") == "tri")
            {
                auto v0 = obj.at("v0").get<std::vector<double>>();
                auto v1 = obj.at("v1").get<std::vector<double>>();
                auto v2 = obj.at("v2").get<std::vector<double>>();

                json mat_data = obj.at("material");
                auto mat = load_material(mat_data);
                return make_shared<tri>(point3(v0[0], v0[1], v0[2]), 
                point3(v1[0], v1[1], v1[2]), point3(v2[0], v2[1], v2[2]), mat);
            }

            if(obj.at("type") == "box")
            {
                auto a = obj.at("a").get<std::vector<double>>();
                auto b = obj.at("b").get<std::vector<double>>();
                json mat_data = obj.at("material");
                auto mat = load_material(mat_data);
                return box(point3(a[0], a[1], a[2]), point3(b[0], b[1], b[2]), mat);
            }

            if(obj.at("type") == "rotate_y")
            {
                auto angle = obj.at("angle").get<double>();
                json subject = obj.at("object");
                return make_shared<rotate_y>(read_object(subject), angle);
            }

            if(obj.at("type") == "translate")
            {
                auto offset = obj.at("offset").get<std::vector<double>>();
                json subject = obj.at("object");
                return make_shared<translate>(read_object(subject), vec3(offset[0], offset[1], offset[2]));
            }

            if(obj.at("type") == "constant_medium")
            {
                auto density = obj.at("density").get<double>();
                auto boundary = read_object(obj.at("object"));
                if(obj.contains("texture")) 
                {
                    auto tex = load_texture(obj.at("texture"));
                    return make_shared<constant_medium>(boundary, density, tex);
                }
                else
                {
                    auto medium_color = obj.at("color").get<std::vector<double>>();
                    return make_shared<constant_medium>(boundary, density, color(medium_color[0], medium_color[1], medium_color[2]));
                } 
            }

            return nullptr;
    }

    shared_ptr<material> load_material(const json& mat)
    {
        if(mat.at("type") == "lambertian")
        {
            if(mat.contains("texture"))
            {
                auto tex = load_texture(mat["texture"]);
                return make_shared<lambertian>(tex);
            }
            else{
                auto obj_color = mat.at("color").get<std::vector<double>>();
                return make_shared<lambertian>(color(obj_color[0], obj_color[1], obj_color[2])); 
            }
                return nullptr;
        }
            
        if(mat.at("type") == "metal")
        {
            auto albedo = mat.at("albedo").get<std::vector<double>>();
            auto fuzz   = mat.at("fuzz").get<double>();
            return make_shared<metal>(color(albedo[0], albedo[1], albedo[2]), fuzz);
        }

        if(mat.at("type") == "dielectric")
        {
            auto refraction_index = mat.at("refraction_index").get<double>();
            return make_shared<dielectric>(refraction_index);
        }

        if(mat.at("type") == "diffuse_light")
        {
            auto obj_emit = mat.at("emit").get<std::vector<double>>();
            return make_shared<diffuse_light>(color(obj_emit[0], obj_emit[1], obj_emit[2]));
        }

        return nullptr;
    }

    shared_ptr<texture> load_texture(const json& tex)
    {
         if(tex.at("type") == "solid_color")
        {
            if(tex.contains("albedo"))
            {
              auto albedo = tex.at("albedo").get<std::vector<double>>();
              return make_shared<solid_color>(color(albedo[0], albedo[1], albedo[2]));  
            }
            if(tex.contains("color"))
            {
                auto RGB = tex.at("color").get<std::vector<double>>();
                return make_shared<solid_color>(RGB[0], RGB[1], RGB[2]); 
            }
            return nullptr;
        }
         if(tex.at("type") == "checker_texture")
        {
            auto scale = tex.at("scale").get<double>();
            auto c1 = tex.at("c1").get<std::vector<double>>();
            auto c2 = tex.at("c2").get<std::vector<double>>();
            return make_shared<checker_texture>(scale, color(c1[0], c1[1], c1[2]), color(c2[0], c2[1], c2[2]));
        }
        if(tex.at("type") == "noise_texture")
        {
            auto scale = tex.at("scale");
            return make_shared<noise_texture>(scale);
        }
        if(tex.at("type") == "image_texture")
        {
            auto filename = tex.at("filename").get<std::string>();
            return make_shared<image_texture>(filename.c_str());
        }
        
        return nullptr;
    }
}


#endif
