//=============================================================================
//
//   Exercise code for "Introduction to Computer Graphics"
//     by Julian Panetta, EPFL
//
//=============================================================================
#version 140

// Eye-space fragment position and normals from vertex shader.
in vec3 v2f_normal;
in vec3 v2f_ec_vertex;

uniform vec3 light_position; // Eye-space light position
uniform vec3 light_color;

// Material parameters
uniform vec3  diffuse_color;
uniform vec3 specular_color;
uniform float shininess;

uniform samplerCube shadow_map; // Distances in the shadow map can be accessed with texture(shadow_map, direction).r

out vec4 f_light_contribution;

void main()
{
    // Normalize the interpolated normal
    vec3 N = -sign(dot(v2f_normal, v2f_ec_vertex)) *  // Orient the normal so it always points opposite the camera rays
             normalize(v2f_normal);

    /** \todo
    * Compute this light's diffuse and specular contributions.
    * You should be able to copy your phong lighting code from assignment 6 mostly as-is,
    * though notice that the light and view vectors need to be computed from scratch
    * here; this time, they are not passed from the vertex shader.
    *
    * The light should only contribute to this fragment if the fragment is not occluded
    * by another object in the scene. You need to check this by comparing the distance
    * from the fragment to the light against the distance recorded for this
    * light ray in the shadow map.
    *
    * To prevent "shadow acne" and minimize aliasing issues, we need a rather large
    * tolerance on the distance comparison. It's recommended to use a *multiplicative*
    * instead of additive tolerance: compare the fragment's distance to 1.01x the
    * distance from the shadow map.
    ***/
    
    vec3 color = vec3(0.0f);
	 
	// compare distance from frag to light (v2f_ec_vertex; but maybe change from eye space) 
	// against distance recorded for light ray in shadow map (texture(shadow_map, direction).r; or texture(shadow_map, light_ray).r)

	vec3 frag_light = v2f_ec_vertex - light_position;
	float dist1 = sqrt(frag_light[0]*frag_light[0]+frag_light[1]*frag_light[1]+frag_light[2]*frag_light[2]);
	float dist2 = 1.01 * texture(shadow_map, light_position).r;

	if (dist1 < dist2){
	// compute diffuse term and add to color
	vec3 light = normalize(vec3(light_position) - v2f_ec_vertex); // compute light vector
	// only illumination when n_l > 0 therefore only compute those
	float n_l = dot(N, light);
	if (n_l > 0){
	color += light_color * diffuse_color * n_l;
	}

	// compute specular term and add to color
	vec3 view = normalize(-v2f_ec_vertex);
	// only illumination when r_v > 0 therefore only compute those
	vec3 r = 2 * N * n_l - light; // define r vector
	float r_v = dot(r, view);
	if (r_v > 0){
	color += light_color * specular_color * pow(r_v, shininess);
	}

	} 

    // append the required alpha value
    f_light_contribution = vec4(color, 1.0);
}
