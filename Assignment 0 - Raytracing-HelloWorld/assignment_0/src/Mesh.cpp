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

#include "Mesh.h"
#include <fstream>
#include <string>
#include <stdexcept>
#include <limits>
#include "Plane.h"

//== IMPLEMENTATION ===========================================================


Mesh::Mesh(std::istream &is, const std::string &scenePath)
{
    std::string meshFile, mode;
    is >> meshFile;

    // load mesh from file
    read(scenePath.substr(0, scenePath.find_last_of("/\\") + 1) + meshFile); // Use both Unix and Windows path separators

    is >> mode;
    if      (mode ==  "FLAT") draw_mode_ = FLAT;
    else if (mode == "PHONG") draw_mode_ = PHONG;
    else throw std::runtime_error("Invalid draw mode " + mode);

    is >> material;
}


//-----------------------------------------------------------------------------


bool Mesh::read(const std::string &_filename)
{
    // read a mesh in OFF format


    // open file
    std::ifstream ifs(_filename);
    if (!ifs)
    {
        std::cerr << "Can't open " << _filename << "\n";
        return false;
    }


    // read OFF header
    std::string s;
    unsigned int nV, nF, dummy, i;
    ifs >> s;
    if (s != "OFF")
    {
        std::cerr << "No OFF file\n";
        return false;
    }
    ifs >> nV >> nF >> dummy;
    std::cout << "\n  read " << _filename << ": " << nV << " vertices, " << nF << " triangles";


    // read vertices
    Vertex v;
    vertices_.clear();
    vertices_.reserve(nV);
    for (i=0; i<nV; ++i)
    {
        ifs >> v.position;
        vertices_.push_back(v);
    }


    // read triangles
    Triangle t;
    triangles_.clear();
    triangles_.reserve(nF);
    for (i=0; i<nF; ++i)
    {
        ifs >> dummy >> t.i0 >> t.i1 >> t.i2;
        triangles_.push_back(t);
    }


    // close file
    ifs.close();


    // compute face and vertex normals
    compute_normals();

    // compute bounding box
    compute_bounding_box();


    return true;
}


//-----------------------------------------------------------------------------

// Determine the weights by which to scale triangle (p0, p1, p2)'s normal when
// accumulating the vertex normals for vertices 0, 1, and 2.
// (Recall, vertex normals are a weighted average of their incident triangles'
// normals, and in our raytracer we'll use the incident angles as weights.)
// \param[in] p0, p1, p2    triangle vertex positions
// \param[out] w0, w1, w2    weights to be used for vertices 0, 1, and 2
void angleWeights(const vec3 &p0, const vec3 &p1, const vec3 &p2,
                  double &w0, double &w1, double &w2) {
    // compute angle weights
    const vec3 e01 = normalize(p1-p0);
    const vec3 e12 = normalize(p2-p1);
    const vec3 e20 = normalize(p0-p2);
    w0 = acos( std::max(-1.0, std::min(1.0, dot(e01, -e20) )));
    w1 = acos( std::max(-1.0, std::min(1.0, dot(e12, -e01) )));
    w2 = acos( std::max(-1.0, std::min(1.0, dot(e20, -e12) )));
}


//-----------------------------------------------------------------------------

void Mesh::compute_normals()
{
    // compute triangle normals
    for (Triangle& t: triangles_)
    {
        const vec3& p0 = vertices_[t.i0].position;
        const vec3& p1 = vertices_[t.i1].position;
        const vec3& p2 = vertices_[t.i2].position;
        t.normal = normalize(cross(p1-p0, p2-p0));
    }

    // initialize vertex normals to zero
    for (Vertex& v: vertices_)
    {
        v.normal = vec3(0,0,0);
    }

    /** \todo
     * In some scenes (e.g the office scene) some objects should be flat
     * shaded (e.g. the desk) while other objects should be Phong shaded to appear
     * realistic (e.g. chairs). You have to implement the following:
     * - Compute vertex normals by averaging the normals of their incident triangles.
     * - Store the vertex normals in the Vertex::normal member variable.
     * - Weigh the normals by their triangles' angles.
     */

	// use for loop to visit each triangle only once
	for (Triangle& t : triangles_)
	{
		double w0, w1, w2;
		// use angleWeights to find the weights by which to scale each vertex of an incident triangle
		angleWeights(vertices_[t.i0].position, vertices_[t.i1].position, vertices_[t.i2].position, w0, w1, w2);

		// add contribution of each vertex of each triangle to vertex normals
		vertices_[t.i0].normal += t.normal * w0;
		vertices_[t.i1].normal += t.normal * w1;
		vertices_[t.i2].normal += t.normal * w2;
	}

	// now normalize all computed vertex normals
	for (Vertex &v : vertices_) {
		v.normal = normalize(v.normal);
	}
	
}


//-----------------------------------------------------------------------------


void Mesh::compute_bounding_box()
{
    bb_min_ = vec3(std::numeric_limits<double>::max());
    bb_max_ = vec3(std::numeric_limits<double>::lowest());

    for (Vertex v: vertices_)
    {
        bb_min_ = min(bb_min_, v.position);
        bb_max_ = max(bb_max_, v.position);
    }
}


//-----------------------------------------------------------------------------


bool Mesh::intersect_bounding_box(const Ray& _ray) const
{

    /** \todo
    * Intersect the ray `_ray` with the axis-aligned bounding box of the mesh.
    * Note that the minimum and maximum point of the bounding box are stored
    * in the member variables `bb_min_` and `bb_max_`. Return whether the ray
    * intersects the bounding box.
    * This function is ued in `Mesh::intersect()` to avoid the intersection test
    * with all triangles of every mesh in the scene. The bounding boxes are computed
    * in `Mesh::compute_bounding_box()`.
    */
    /*
    vec3 nx = vec3(1,0,0);
    vec3 ny = vec3(0,1,0);
    vec3 nz = vec3(0,0,1);
    vec3 n[3] = {nx, ny, nz};
    vec3 bb_points[2] = {bb_min_, bb_max_};
    vec3 intersectionpoint;
    vec3 intersectionnormal;
    double t;
    double tol = 1e-10;
    bool inters[6];
    
    //Intersection over all the 6 planes, fixing first the plane and then evaluating the intersection with both planes centered in each bb_point
    for(int k=0; k<3; k=k+1){
        int w, h; if(k==0){w=1; h=2;} else if(k==1){w=0; h=2;} else{w=0; h=1;}
        for(int j=0; j<2; j++){
            Plane(bb_points[j], n[k]).intersect(_ray, intersectionpoint, intersectionnormal, t);
            inters[k*2+j] = (intersectionpoint[w]+tol>=bb_points[0][w] && intersectionpoint[w]<=bb_points[1][w]+tol && intersectionpoint[h]+tol>=bb_points[0][h] && intersectionpoint[h]<=bb_points[1][h]+tol);
        }
    }
    //We have to check only 6-1 faces, since when a ray intersect in one face it has to go out through another (not the same)

    if(inters[0] || inters[1] || inters[2] || inters[3] || inters[4]){
        return (true);
    }
    else{
        return(false);
    }
    */
    //MORE EFFICIENT:
    bool exists_intersection = true; //We will change this value if there is no intersection ray-cube
	//Now loop over the coordinates (0->x), (1->y), (2->z)
	//Computing the bounders for t inside the corresponding infinite slabel 
	//E.g. {(x,y,z): x_min <= x <= x_max} is the infinite slabel corresponding to the x coordinate
	double min_t_possible;
	double max_t_possible;
	for (int i = 0; i < 3 && exists_intersection; i++) {
		double slabel_ray_min_t;
		double slabel_ray_max_t;
		//Deduct t_min and t_max from the inequations:
		if (_ray.direction[i] > 0) {
			slabel_ray_min_t = (bb_min_[i] - _ray.origin[i]) / _ray.direction[i];
			slabel_ray_max_t = (bb_max_[i] - _ray.origin[i]) / _ray.direction[i];
		}
		else if(_ray.direction[i] < 0){
			slabel_ray_max_t = (bb_min_[i] - _ray.origin[i]) / _ray.direction[i];
			slabel_ray_min_t = (bb_max_[i] - _ray.origin[i]) / _ray.direction[i];
		}
		else{
		    if(!(_ray.origin[i]<bb_max_[i] && _ray.origin[i]>bb_min_[i])){
			slabel_ray_min_t = 0;
			slabel_ray_max_t = 0;
		    }
		    else{
			slabel_ray_min_t = -INFINITY;
			slabel_ray_max_t = INFINITY;
		    }
		}
		if (i == 0) {
			min_t_possible = slabel_ray_min_t;
			max_t_possible = slabel_ray_max_t;
		}else {
			if (min_t_possible < slabel_ray_min_t) {
				min_t_possible = slabel_ray_min_t;
			}
			if (max_t_possible > slabel_ray_max_t) {
				max_t_possible = slabel_ray_max_t;
			}
			if (min_t_possible > max_t_possible) {
				exists_intersection = false;
			}
		}
	}
	return exists_intersection;
}

//-----------------------------------------------------------------------------

bool Mesh::intersect(const Ray& _ray,
                     vec3&      _intersection_point,
                     vec3&      _intersection_normal,
                     double&    _intersection_t ) const
{
    // check bounding box intersection
    if (!intersect_bounding_box(_ray))
    {
        return false;
    }

    vec3   p, n;
    double t;

    _intersection_t = NO_INTERSECTION;

    // for each triangle
    for (const Triangle& triangle : triangles_)
    {
        // does ray intersect triangle?
        if (intersect_triangle(triangle, _ray, p, n, t))
        {
            // is intersection closer than previous intersections?
            if (t < _intersection_t)
            {
                // store data of this intersection
                _intersection_t      = t;
                _intersection_point  = p;
                _intersection_normal = n;
            }
        }
    }

    return (_intersection_t != NO_INTERSECTION);
}


//-----------------------------------------------------------------------------


double CramerHelper(vec3 a, vec3  b, vec3 c){
    return(a[0]*b[1]*c[2]+a[1]*b[2]*c[0]+b[0]*c[1]*a[2]-c[0]*b[1]*a[2]-a[1]*b[0]*c[2]-b[2]*c[1]*a[0]);
}

bool
Mesh::
intersect_triangle(const Triangle&  _triangle,
                   const Ray&       _ray,
                   vec3&            _intersection_point,
                   vec3&            _intersection_normal,
                   double&          _intersection_t) const
{
    const vec3& p0 = vertices_[_triangle.i0].position;
    const vec3& p1 = vertices_[_triangle.i1].position;
    const vec3& p2 = vertices_[_triangle.i2].position;

    /** \todo
    * - intersect _ray with _triangle
    * - store intersection point in `_intersection_point`
    * - store ray parameter in `_intersection_t`
    * - store normal at intersection point in `_intersection_normal`.
    * - Depending on the member variable `draw_mode_`, use either the triangle
    *  normal (`Triangle::normal`) or interpolate the vertex normals (`Vertex::normal`).
    * - return `true` if there is an intersection with t > 0 (in front of the viewer)
    *
    * Hint: Rearrange `ray.origin + t*ray.dir = a*p0 + b*p1 + (1-a-b)*p2` to obtain a solvable
    * system for a, b and t.
    * Refer to [Cramer's Rule](https://en.wikipedia.org/wiki/Cramer%27s_rule) to easily solve it.
     */

 	vec3 a, b, c, d;
	double det, alpha, beta, gamma, t;

	// Have used ray.origin + t*ray.dir = alpha*p0 + beta*p1 + gamma*p2 where alpha = 1 - beta - gamma
	// Rearrangment explained in README

	a = p1 - p0;
	b = p2 - p0;
	c = -_ray.direction;
	d = _ray.origin - p0;

	// Use CramerHelper to find determinant of 3x3 matrix (a, b and c form the columns) 
	det = CramerHelper(a, b, c);
	// Check if ray is // to the triangle plane
	if (det != 0) {
		beta = CramerHelper(d, b, c) / det;
		gamma = CramerHelper(a, d, c) / det;
		t = CramerHelper(a, b, d) / det;
		alpha = 1 - beta - gamma;
		if (alpha >= 0 && beta >= 0 && gamma >= 0 && t > 0) { // conditions for barycentric coords and t 
			_intersection_point = _ray.origin + t * _ray.direction; // find intersection point
			_intersection_t = t; // store ray parameter
			// use draw mode to determine whether mesh object is flat or Phong shaded
			if (draw_mode_ == FLAT) { // if flat store normal as normal of intersected triangle
				_intersection_normal = _triangle.normal; 
			}
			else { // if Phong store normal as linearly interpolated vertex normals of intersected triangle (and normalize it)
				_intersection_normal = normalize(alpha*vertices_[_triangle.i0].normal + beta * vertices_[_triangle.i1].normal + gamma * vertices_[_triangle.i2].normal);
			}

			return(true);
		}
		else {
			return(false);
		}
	}
	else {

		return(false);
	}
}

//=============================================================================
