#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "raytracer.h"

#include <vector>



class hittable_list : public hittable
{
    public:
        std::vector<shared_ptr<hittable>> objects;

        hittable_list() {}
        hittable_list(shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }

        void add(shared_ptr<hittable> object) 
        {
            objects.push_back(object);
        }

        bool hit(const ray& r, interval ray_t, hit_record& rec) const override 
        {
            // Declare a temporary record, a hit check, and a double to hold the closest ray hit
            hit_record temp_rec;
            bool hit_anything = false;
            auto closest_so_far = ray_t.max;

            
            for (const auto& object : objects)
            {
                // For each object, check if the ray intersects it within the valid range.
                // if hit, record it and shrink t_max to the intersection points, so any
                // objects further away are automatically excluded from registering a hit.
                if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec))
                {
                    hit_anything = true;
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_anything;
        }
};


#endif
