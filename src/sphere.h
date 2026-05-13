#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "raytracer.h"

class sphere : public hittable
{
    public:
       
        // Stationary Sphere
        sphere(const point3& static_center, double radius, shared_ptr<material> mat) 
        : center(static_center, vec3(0, 0, 0)), radius(std::fmax(0, radius)), mat(mat) 
        {
            auto rvec = vec3(radius, radius, radius);
            bbox = aabb(static_center - rvec, static_center + rvec);
        }

        // Moving Sphere
        sphere(const point3& center1, const point3& center2, double radius,
                shared_ptr<material> mat)
                : center(center1, center2 - center1), radius(std::fmax(0, radius)), mat(mat)
                {
                    auto rvec = vec3(radius, radius, radius);
                    aabb box1(center.at(0) - rvec, center.at(0) + rvec);
                    aabb box2(center.at(1) - rvec, center.at(1) + rvec);
                    bbox = aabb(box1, box2);
                }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override
        {
            // Here the equation of the circle is used to see if a ray has hit the sphere
            // The equation of a sphere vectorized is C - P where C is the center of the sphere 
            // and P is a point on the sphere.
            // Using this formula with the formula of a ray, rearranging to the quadratic formula
            // allows us to see when a ray has hit the sphere, where if it has hit the sphere a 
            // solution exists, rendering the sphere. 
            point3 current_center = center.at(r.time());
            vec3 oc = current_center - r.origin();
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
            vec3 outward_normal = (rec.p - current_center) / radius;
            rec.set_face_normal(r, outward_normal);
            rec.mat = mat;

            return true;
        }

        aabb bounding_box() const override { return bbox;}

        private:
            ray center;
            double radius;
            shared_ptr<material> mat;
            aabb bbox;
};


#endif
