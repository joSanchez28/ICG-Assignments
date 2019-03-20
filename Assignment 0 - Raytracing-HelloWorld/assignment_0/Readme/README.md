DESCRIPTION OF THE ASSIGNMENT SOLUTION
==========
In this three-part assignment, we first computed the vertex normals then computed the ray-triangle intersection and finally the ray-bounding box intersection. 

For the first part, we computed the vertex normals by averaging each vertex's incident triangles' normals weighted by their opening angle as explained in the lecture. 
To make the implementation more efficient we used a for loop so that each triangle in the mesh would only be visited once. Within the for loop each triangle was looked at where the opening angle for its three vertices were calculated using the angleWeights() function
and then each vertex's contribution to a vertex normal was added. This contribution is just the incident triangle normal multipled by the vertex opening angle. 


WORKLOAD DISTRIBUTION
==========
Carlos: 1/3  
Jorge: 1/3  
Natasha: 1/3  
