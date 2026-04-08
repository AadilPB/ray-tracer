#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "raytracer.h"

class sphere : public hittable
{
    public:
       

        sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override
        {
            // Here the equation of the circle is used to see if a ray has hit the sphere
            // The equation of a sphere vectorized is C - P where C is the center of the sphere 
            // and P is a point on the sphere.
            // Using this formula with the formula of a ray, rearranging to the quadratic formula
            // allows us to see when a ray has hit the sphere, where if it has hit the sphere a 
            // solution exists, rendering the sphere. 
            vec3 oc = center - r.origin();
            auto a = r.direction().length_squared();
            auto h = dot(r.direction(), oc);
            auto c = oc.length_squared() - radius * radius;
            auto discriminant = h*h - (a * c);

            if (discriminant < 0)
            {
                return false;
            }
            auto sqrtd = std::sqrt(discriminant);
            auto root = (h - sqrtd) / a;

            if (root <= ray_t.min || ray_t.max <= root)
            {
                root = (h + sqrtd) / a;
                if (root <= ray_t.min || ray_t.max <= root)
                    return false;
            }

            rec.t = root;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;
            vec3 outward_normal = (rec.p - center) / radius;
            rec.set_face_normal(r, outward_normal);

            return true;
        }

        private:
            point3 center;
            double radius;
};


#endif
