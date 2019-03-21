DESCRIPTION OF THE ASSIGNMENT SOLUTION
==========
In this three-part assignment, we first computed the vertex normals then computed the ray-triangle intersection and finally the ray-bounding box intersection. 

For the first part, we computed the vertex normals by averaging each vertex's incident triangles' normals weighted by their opening angle as explained in the lecture. 
To make the implementation more efficient we used a for loop so that each triangle in the mesh would only be visited once. Within the for loop each triangle was looked at where the opening angle for its three vertices were calculated using the angleWeights() function
and then each vertex's contribution to a vertex normal was added. This contribution is just the incident triangle normal multipled by the vertex opening angle. 

For the second part, we had to implement the ray-triangle intersection where we represented the triangle explicitly with barycentric coordinates; i.e. 
ray.origin + t * ray.dir = alpha * p0 + beta * p1 + gamma * p2,
where alpha, beta, gamma are the barycentric coordinates; p0, p1, p2 are the triangle's three vertex positions and t is the ray parameter (as explained in lectures). The problem with this system is that it has only 3 equations but 4 unknowns therefore we used the condition that the barycentric
coordinates must sum to 1 to reduce the number of unknowns to 3; i.e.
ray.origin + t * ray.dir = (1 - beta - gamma) * p0 + beta * p1 + gamma * p2. 
We were able to solve this by first rearranging the system like so
(p1 - p0) * beta + (p2 - p0) * gamma - dt = o - p
with the 3 unknowns being the beta, gamma and t. Then using Cramer's rule to find these unknowns. 
Using the draw_mode variable, we could determine if an object should be flat or Phong shaded. If it was Phong shaded we computed the ray-triangle intersection normal using the normal interpolation formula below which used the barycentric coordinates that we calculated
alpha * n0 + beta * n1 + gamma * n2,
where n0, n1 and n2 are the triangle's three vertex normals. If it was flat shaded we could just store the normal as the ray-triangle intersection normal. 

For the last part, we had to check whether a ray intersects with the current mesh's bounding box by filling in the function intersect_bounding_box (). The best best approach we have found is to consider the three infinite "slabs" x_min <= x <= x_max, y_min <= y <= y_max, and z_min <= z <= z_max. So we calculate the t possible interval for the segment of the ray o + t d that falls within a single one of these slabs. Then we combine these intervals to find the possible t values (if any) for which the ray is simultaneously within all three of these slabs. The implementation is described below:

We first assume that there is an intersection and then computing when there would not be one. We could do this by going through 
each direction (x, y, z) and computing the ray parameter for intersection by equating the ray equation to the bounding box coordinates, i.e.
_ray.origin[i] + t * _ray.direction[i] = bb_[i],
where the integer i will be either of the 3 coordinates and bb_ could be either box coordinates (bb_max or min). This is equivalent of the ray intersecting with an infinite plane that has boundaries (1d) of the bounding box. 
Once the first coordinate's (i=0) t_max and min has been calculated it will be stored in the max_t_possible and min_t_possible variables and then the for loop will cycle to the next coordinate (i=1). We store new max_t_possible and min_t_possible variables if the new t values calculated make the boundaries smaller.
There will be no intersection if min_t_possible > max_t_possible. To help with this explanation see bounding_box_intersection_examples.pdf. 


WORKLOAD DISTRIBUTION
==========
Carlos: 1/3  
Jorge: 1/3  
Natasha: 1/3  
