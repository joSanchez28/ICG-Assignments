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
	bool intersection = false;

	//Are ray and  plane parallel? If yes; then there is no intersection by indications.
	if (dot(normal, _ray.direction) != 0) {
		//Compute the intersection data and store it:
		_intersection_t = (-dot(normal, _ray.origin) + norm(center)) / dot(normal, _ray.direction); //Note: norm(center) = distance(center, (0,0,0))
		_intersection_point = _ray.origin + _intersection_t * _ray.direction;
		_intersection_normal = (_intersection_point - center) + normal;

		if (_intersection_t > 0) {
			intersection = true;
		}
	}

    return intersection;
}


//=============================================================================
