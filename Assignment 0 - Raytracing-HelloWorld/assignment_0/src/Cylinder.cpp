//=============================================================================
//
//   Exercise code for the lecture
//   "Introduction to Computer Graphics"
//   by Prof. Dr. Mario Botsch, Bielefeld University
//
//   Copyright (C) Computer Graphics Group, Bielefeld University.
//
//=============================================================================

//== INCLUDES =================================================================

#include "Cylinder.h"
#include "SolveQuadratic.h"

#include <array>
#include <cmath>

//== IMPLEMENTATION =========================================================

bool
Cylinder::
intersect(const Ray&  _ray,
          vec3&       _intersection_point,
          vec3&       _intersection_normal,
          double&     _intersection_t) const
{
    /** \todo
     * - compute the first valid intersection `_ray` with the cylinder
     *   (valid means in front of the viewer: t > 0)
     * - store intersection point in `_intersection_point`
     * - store ray parameter in `_intersection_t`
     * - store normal at _intersection_point in `_intersection_normal`.
     * - return whether there is an intersection sfkjgbkj\nwith t > 0
    */

    const vec3 &dir = _ray.direction;
    const vec3   oc = _ray.origin - center;

    double n1 = dot(oc, axis);
    double n2 = dot(dir, axis);

    double dec = 0;
    double findec = 0;

    std::array<double, 2> t;
          
    // Solving for an infinite height cylinder
    size_t nsol = solveQuadratic(dot(dir, dir) - n2*n2,
                                 2 * (dot(dir, oc) - n1*n2),
                                 dot(oc, oc) - n1*n1 - radius * radius, t);
    
    _intersection_t = NO_INTERSECTION;
    // Get closest and front intersection point with the finite cylinder. Save the amount in the axis direction (findec) for later usage.
    for (size_t i = 0; i < 2; ++i) {
        dec = dot(_ray.origin+t[i]*dir-center, axis);
        //t>0 and accomplish height of the cylinder
        if (t[i] > 0 && ((dec<height/2 && dec>=0) || (-dec<=height/2 && dec<=0))){
            _intersection_t = std::min(_intersection_t, t[i]);
            if(_intersection_t==t[i]){
                findec = dec;
            }
        }
    }


    if(_intersection_t != NO_INTERSECTION){
        //_intersection_point = _ray.origin+_intersection_t*dir;
        _intersection_point  = _ray(_intersection_t);
        // Normal vector pointing towards the viewer (normal and view ray direction pointing in opposite directions)
        if(distance(_ray.origin, center+axis*findec) > distance(_ray.origin, _intersection_point)){
            _intersection_normal = (_intersection_point - (center+axis*findec)) / radius;
        }
        else{
            _intersection_normal = -(_intersection_point - (center+axis*findec)) / radius;       
        }

        return true;
    }
    else{
        return false;
    }
}
