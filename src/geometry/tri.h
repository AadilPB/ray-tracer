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
            auto denom = dot(normal, r.direction());

            if(std::fabs(denom) < 1e-8)
                return false;

            auto t = (D - dot(normal, r.origin())) / denom;

            if(!ray_t.contains(t))
                return false;

            auto intersection = r.at(t);
           
            double area = normal.length();

            vec3 edge_cross; // Vector perpendicular to the plane of the triangle

            // Find u for the triangle 
            vec3 v1p = intersection - v1;
            vec3 v1v2 = v2 - v1;
            edge_cross = cross(v1v2, v1p);
            auto u = dot(normal, edge_cross);
            if (u < 0) return false;

            // Find v for the triangle 
            vec3 v2p = intersection - v2;
            vec3 v2v0 = v0 - v2;
            edge_cross = cross(v2v0, v2p);
            auto v = dot(normal, edge_cross);
            if (v < 0) return false;

            
            vec3 v0p = intersection - v0;
            edge_cross = cross(edge0, v0p);
            if (dot(normal, edge_cross) < 0) return false;

            u /= denom;
            v /= denom;

            rec.u = u;
            rec.v = v;
            rec.t = t;
            rec.p = intersection;
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
