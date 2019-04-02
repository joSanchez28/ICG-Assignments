DESCRIPTION OF THE ASSIGNMENT SOLUTION
==========
In this assignment we have built the scene containing the Solar system with the Sun, some planets, the Moon and a spaceship.

The first part consisted in placing (computing its coordinates) the objects in the scene depending on the time. For doing that we implemented the `update_body_positions()` method. This method update the position of the planets based on their distance to their orbit's centre (the Sun for the planets and the Earth for the Moon). We have done that rotating the initial position of the planets (a position which is the orbit radius (`planet.distance_`) distant to the centre) using its parameter `angle_orbit_`, which already changes in time.

The second part was about placing the eye in the scene to look at a determined object (which we will able to choose with the keyboard controls). So, we implemented the `paint()` method. We distinguish two cases for calculate the eye position:

1. When we are looking to a celestial object (not thee spaceship), we rotate the vector `(0, 0, dist_factor_ * planet.radius_)` over two angles y_angle over the y'-axis and the x_angle over the x'-axis and then translate the position of the planet by this rotated vector.
2. When we look at the spaceship, the idea is the same, but we do not use the x_angle. Instead of that we rotate the y_anlge (as before) and then the ship angle (also over the y'-axis)

Knowing the eye position we compute the up vector (as a orthogonal of the eye vector) applying to it the same rotations as the ones applied to the vector `(0, 0, dist_factor_ * planet.radius_)` (when computing thee eye position) and finally obtain the view and the perspective by the GLSL functions and call the `draw_scene()` method.

In the third part we implemented the rendering of the objects in the method `draw_scene()`. For each object, first compute the model matrix by the scale (with the body radius_) then rotate by their self axis (with `planet.angle_self_`) and finally the translation to the currently computed position (computed in the first part of the assignment). Note that we avoid the rotation for the spaceship case (since it is make no sense). Then, following the given instructions, we obtain the model-view matrix (use already computed \_view) and the model-view-projection matrix (use already computed \_projection). Then we set up the shader and finally, we bound the texture (such that the sphere would be rendered with given  texture) and drew the sphere (for celestial bodies) or the spaceship.


WORKLOAD DISTRIBUTION
==================================
Carlos: 1/3  
Jorge: 1/3  
Natasha: 1/3
