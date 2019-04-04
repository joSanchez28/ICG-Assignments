DESCRIPTION OF THE ASSIGNMENT SOLUTION
==========
Ihis assignment builds a scene containing the Solar system with the Sun, some planets, the Moon and a spaceship.

The first part consisted of placing the objects in the scene by filling in the missing code in the update_body_positions() function. This was achieved by rotating the initial position of the planets (given by distance_) by the angle angle_orbit_ which changes with simulation time; mat4::rotate_y was used to implement this tranformation. 
It should be noted that the moon orbits around the earth and therefore we had to add its coordinates that were computed in the same way as above to the earth's position so that the moon's position would be correct in the world coordinate frame. 

The second part placed the eye/camera in the scene so as to look at a choosen object (selected using the keyboard controls) therefore the appropriate view matrix had to be computed within the function paint(). There are two cases to be distinguised, firstly the calculation of eye position for a celestial body where we placed the eye in the z-axis (0, 0, dist_factor_ * planet.radius_) and then rotated this vector over the two given x and y angles. Secondly, where we looked at the spaceship which was calculated in the same way however the x angle was ignored and also the variable Ship::angle_ was used in order to fix the view with respect to the ship as it moves.
Finally, after the up vector was calculated, the function mat4::look_at was used to obtain the view matrix. 

In the third part we implemented the rendering of the objects in the method `draw_scene()`. For each object, first compute the model matrix by the scale (with the body radius_) then rotate by their self axis (with `planet.angle_self_`) and finally the translation to the currently computed position (computed in the first part of the assignment). Note that we avoid the rotation for the spaceship case (since it is make no sense). Then, following the given instructions, we obtain the model-view matrix (use already computed \_view) and the model-view-projection matrix (use already computed \_projection). Then we set up the shader and finally, we bound the texture (such that the sphere would be rendered with given  texture) and drew the sphere (for celestial bodies) or the spaceship.


WORKLOAD DISTRIBUTION
==================================
Carlos: 1/3  
Jorge: 1/3  
Natasha: 1/3
