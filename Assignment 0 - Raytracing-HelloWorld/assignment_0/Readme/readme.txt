DESCRIPTION OF THE ASSIGNMENT SOLUTION
==========
In this assignment, we have implemented ray intersections with planes and cylinders and compute surface normals at the intersection points.

For the ray **intersection with the plane**, we have made use of the equations in the slides (which we have seen during the lectures), 
deducting the *intersection_t* parameter (parameter of the ray equation) and then the intersection point. The implementation (as you can see in `Plane.cpp`) 
was quite easy having done this deduction.

For the ray **intersection with the cylinder**, first we have derivated the implicit equation of the cylinder, using scalar products and the Pitagora's theorem 
(as showed in the theory exercise pdf), plugin in the ray equation. The implementation is inspired by the implementation of the sphere intersection with the ray 
(in `Sphere.cpp`). First we intersected the ray with an infinite height cylinder solving the deducted quadratic equation (using the provided `solveQuadratic()` 
method); then we checked that the intersection point is within the finite cylinder and which of the intersections (if there are two) is the nearest to the viewer. 
Finally, we dealed with the sign of the normal intersection vector (by checking the distances from the ray origin to the intersection point and to the projection 
of the intersection point into the cylinder axis line).

WORKLOAD DISTRIBUTION
==========
Carlos: 1/3  
Jorge: 1/3  
Natasha: 1/3  