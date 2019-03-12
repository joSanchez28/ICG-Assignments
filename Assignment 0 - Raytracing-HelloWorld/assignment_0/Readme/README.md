DESCRIPTION OF THE ASSIGNMENT SOLUTION
==========
In this assignment, we have implemented the Phong lighting model and add reflections to your scenes.

First we have done the `lightning` method. Our implementation is based on the expression which we have seen in the lectures and the practical sessions. This expresion is:   
*Color = I_ambience * M_ambient + sum(i, I_light[i] * (M_diffuse * (n·l[i]) + M_specular * (r[i]·v)^s )*.  
where M refers to the material of the object and I to the intensity components. Basically, we compute the ambience component and then we loop over all the lights adding their diffuse and specular contributions to the color.

It was important before adding these components to make sure that the ray of the  light is impacting in the visible surface of the object (not at the back of the object). We did this with the restriction n·l[i] > 0 so that the cosine between both vectors is between 90º and -90º. For the specular component we have also the restriction (r·v) < 0, which means the same for these vectors.

Then, to implement the shadows we made use of the shadows rays (also explained during the lectures). We check if there is any object between the lights position and the specific object; if this is happening we just avoid the sum of both components (diffuse and specular). As we expected we obtained the acned images and we solved this issue displacing the point along the l[i] vector (along the ray which go from the specific point to the light).

Finally, for dealing with the reflections components we implemented the `trace()` method. We generate the reflection of the ray direction to the normal of the object at the point and then use the expression *color = (1 − α) · color + α · reflected_color*. So we calculate recursively the different reflections that are produces from the initial one and so on. This recursivity is limited by the max_depth parameter (which in our case is read as 5).

WORKLOAD DISTRIBUTION
==========
Carlos: 1/3  
Jorge: 1/3  
Natasha: 1/3  
