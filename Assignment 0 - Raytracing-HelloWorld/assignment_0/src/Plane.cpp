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

#include "Plane.h"
#include <limits>


//== CLASS DEFINITION =========================================================



Plane::Plane(const vec3& _center, const vec3& _normal)
: center(_center), normal(_normal)
{
}


//-----------------------------------------------------------------------------

bool
Plane::
intersect(const Ray& _ray,
          vec3&      _intersection_point,
          vec3&      _intersection_normal,
          double&    _intersection_t ) const
{
    /** \todo
     * - compute the intersection of the plane with `_ray`
     * - if ray and plane are parallel there is no intersection
     * - otherwise compute intersection data and store it in `_intersection_point`, `_intersection_normal`, and `_intersection_t`.
     * - return whether there is an intersection in front of the viewer (t > 0)
    */

    // We have to define a method for the plane, which intersects it with the ray.
    
    const vec3 &dir = _ray.direction;
    const vec3   co = center-_ray.origin;

    double t=-1.0;
    _intersection_t = NO_INTERSECTION;

    if(dot(normal, dir)!=0){ // ray // plane (cos(90º) = 0) no intersection (denominator equals to 0)
        t = dot(normal, co)/dot(normal, dir);
        _intersection_t = t;
        _intersection_point = _ray.origin+t*dir;
        _intersection_normal = normal;
    }
    
    if(t>0){
        return true;
    }
    else{
        return false;
    }

}
//=============================================================================
