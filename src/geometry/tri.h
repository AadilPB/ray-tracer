#ifndef TRI_H
#define TRI_H

#include "hittable.h"
#include "raytracer.h"

class tri : public hittable
{
    public:

        tri(const point3& v0, const point3& v1, const point3& v2, shared_ptr<material> mat)
            : v0(v0), v1(v1), v2(v2), mat(mat)
            {
                edge0 = v1 - v0; //From A to B
                edge1 = v2 - v0; // From A to C
                auto n = cross(edge0, edge1);
                normal = unit_vector(n);
                D = dot(normal, v0);
            }

        aabb bounding_box() const override { return bbox; }

        bool hit( const ray& r, interval ray_t, hit_record& rec ) const override
        {
            
            vec3 pvec = cross(r.direction(), edge1);
            double det = dot(edge0, pvec);

            // Include both faces
            if (std::fabs(det) < 1e-8) return false;

            double inv_det = 1.0 / det;
           
            // Find u coordinate in barycentric coordinate system
            vec3 tvec = r.origin() - v0;
            auto u = dot(tvec, pvec) * inv_det;
            if(u < 0 || u > 1) return false;
            
            // Find v coordinate in barycentric coordinate system
            vec3 qvec = cross(tvec, edge0);
            auto v = dot(r.direction(), qvec) * inv_det;
            if(v < 0 || u + v > 1) return false;

            // Ray parameter t
            auto t = dot(edge1, qvec) * inv_det;
            if(!ray_t.contains(t)) return false;

            rec.t = t;
            rec.u = u;
            rec.v = v;
            rec.mat = mat;
            rec.set_face_normal(r, normal);
            return true;
        }

    private:
        aabb bbox;
        shared_ptr<material> mat;
        point3 v0, v1, v2; 
        vec3 normal;
        double D;
        vec3 edge0, edge1;
    
};


#endif
