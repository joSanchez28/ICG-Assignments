DESCRIPTION OF THE ASSIGNMENT SOLUTION
==========
In this two-part assignment, we first implemented the Phong lighting model (including shadows) then we added reflections to the scenes.cpp.   

For the first part, our implementation is based on the expression as follows: 
*Color = I_ambience * M_ambient + sum(i, I_light[i] * (M_diffuse * (n·l[i]) + M_specular * (r[i]·v)^s )*
where M refers to the material of the object and I to the intensity components . This is the Phong lighting model which was dervied in the lecture and heavily approximates the physical behaviour of light.
In our code we compute each lighting component (ambient, diffuse, specular) and add each contribution to color. We implemented the restrictions n·l[i] > 0 for the diffuse component and (r·v) < 0 for the specular component as physically there would be no illumination since the ray would be intersecting behind the object. 
To create shadows we first generate a shadow ray and then determine if there are any objects intersecting the ray which would mean the light is blocked. If so, we do not include these components for when we determine and add the lighting contributions to color. As expected, we encountered the shadow acne error and therefore solved this by displacing the ray origin very slightly in the ray direction.
We summed the multiple light sources by using a for loop which added each light contributions to color. 

For the second part of the assignment we used the `trace()` function to trace the child rays recursively and computed the color from this (called reflected_color). Then we computed the final returned color which weighted the components (Phong lighting color and reflected color) using how reflective the material is (found from material.mirror). This was computed with the following expression given to use:
*color = (1 − α) · color + α · reflected_color*. 
We calculate recursively the different reflections that are produced from the initial one. This recursivity is limited by the max_depth parameter (which in our case is read as 5).

WORKLOAD DISTRIBUTION
==========
Carlos: 1/3  
Jorge: 1/3  
Natasha: 1/3  
