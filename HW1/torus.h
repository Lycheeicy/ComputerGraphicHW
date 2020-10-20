#ifndef __TORUS_H__
#define __TORUS_H__

#include "object.h"
#include <gsl/gsl_poly.h>

class Torus : public Object
{
    vec3 center;
    vec3 axis;
    double inner_radius;
    double outer_radius;
    gsl_poly_complex_workspace * w;

public:
    Torus(const vec3& center,const vec3& axis,
        double inner_radius,double outer_radius);
    ~Torus();

    virtual void Intersection(const Ray& ray, std::vector<Hit>& hits) const override;
    virtual vec3 Normal(const vec3& point) const override;
    virtual void Update_Bounding_Box() override;
};
#endif
