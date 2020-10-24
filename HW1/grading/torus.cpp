#include "torus.h"
#include "ray.h"
#include <algorithm>

Torus::Torus(const vec3& center,const vec3& axis,
    double inner_radius,double outer_radius)
    :center(center),axis(axis),inner_radius(inner_radius),
    outer_radius(outer_radius)
{
    w = gsl_poly_complex_workspace_alloc(5);
}

Torus::~Torus()
{
    gsl_poly_complex_workspace_free(w);
}

// Determine if the ray intersects with the torus
void Torus::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    TODO;
}

vec3 Torus::Normal(const vec3& point) const
{
    vec3 normal;
    TODO; // compute the normal direction
    return normal;
}

void Torus::Update_Bounding_Box()
{
    double x=axis[0]*axis[0],y=axis[1]*axis[1],z=axis[2]*axis[2];
    vec3 u(sqrt(y+z),sqrt(x+z),sqrt(x+y));
    vec3 v(u*outer_radius+inner_radius);
    bounding_box.lo=center-v;
    bounding_box.hi=center+v;
    infinite_box=false;
}

