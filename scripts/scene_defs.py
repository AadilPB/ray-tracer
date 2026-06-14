import json

def camera(aspect_ratio, image_width, samples_per_pixel, max_depth, 
           background, vfov, lookfrom, lookat, vup, 
           defocus_angle=None, focus_dist=None):
    cam_def = {
        "aspect_ratio"      : aspect_ratio,
        "image_width"       : image_width,
        "samples_per_pixel" : samples_per_pixel,
        "max_depth"         : max_depth,
        "background"        : background,
        "vfov"              : vfov,
        "lookfrom"          : lookfrom,
        "lookat"            : lookat,
        "vup"               : vup
    }

    if defocus_angle is not None:
        cam_def["defocus_angle"] = defocus_angle

    if focus_dist is not None: 
        cam_def["focus_dist"] = focus_dist

    return cam_def;

# Objects
def sphere(center, radius, material, center2=None):
    
    if center2 is None:
        result = {
            "type"     : "sphere",
            "center"   : center,
            "radius"   : radius,
            "material" : material
        }
        
    if center2 is not None:
        result = {
            "type"      : "sphere",
            "center1"   : center,
            "center2"   : center2,
            "radius"    : radius,
            "material"  : material
        }

    return result

def quad(Q, u, v, material):
    result = {
        "type"     : "quad",
        "q"        : Q,
        "u"        : u,
        "v"        : v,
        "material" : material
    }
    return result

def tri(v0, v1, v2, material):
    result = {
        "type"     : "tri",
        "v0"       : v0,
        "v1"       : v1,
        "v2"       : v2,
        "material" : material
    }
    return result

def box(a, b, material):
    result = {
        "type"     : "box",
        "a"        : a,
        "b"        : b,
        "material" : material
    }
    return result

def rotate_y(angle, subject):
    result = {
        "type"   : "rotate_y",
        "angle"  : angle,
        "object" : subject
    }
    return result

def translate(offset, subject):
    result = {
        "type"   : "translate",
        "offset" : offset,
        "object" : subject
    }
    return result

def constant_medium(density, boundary, texture = None, albedo = None):
    if texture is not None:
        result = {
            "type"     : "constant_medium",
            "density"  : density,
            "boundary" : boundary,
            "texture"  : texture
        }
    else:
        result = {
            "type"     : "constant_medium",
            "density"  : density,
            "boundary" : boundary,
            "albedo"  : albedo
        }
    return result

# Materials
def lambertian(color = None, texture = None):
    if color is None and texture is None:
        raise ValueError("lambertian material needs either a color or texture input")
    
    if color is not None:
        lambertian_def = {
            "type"   : "lambertian",
            "albedo" : color
        }
    
    else:
        lambertian_def = {
            "type"    : "lambertian",
            "texture" : texture
        }

    return lambertian_def

def metal(albedo, fuzz):
    metal_def = {
        "type"   : "metal",
        "albedo" : albedo,
        "fuzz"   : fuzz
    }
    return metal_def

def dielectric(refraction_index):
    dielectric_def = {
        "type"             : "dielectric",
        "refraction_index" : refraction_index
    }
    return dielectric_def


#Textures

def solid_color(albedo = None, color = None):
    if albedo is not None:
        solid_color_def = {
            "type" : "solid_color",
            "albedo" : albedo
        }
    else:
        solid_color_def = {
            "type" : "solid_color",
            "color" : color
        }

    return solid_color_def

def checker_texture(scale, c1, c2):
    result = {
        "type"  : "checker_texture",
        "scale" : scale,
        "c1"    : c1,
        "c2"    : c2
    }
    return result

def noise_texture(scale):
    result = {
        "type" : "noise_texture",
        "scale" : scale
    }
    return result

def image_texture(filename):
    result = {
        "type"     : image_texture,
        "filename" : filename
    }
    return result

def save_scene(scene, path, indent = None):
    with open (path, "w") as f:
        json.dump(scene, f, indent = indent)
