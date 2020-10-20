#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "object.h"
#include "mat.h"
class Transform : public Object
{
public:
    Object* A;

    mat3 rotate;
    double scale=1;
    vec3 translate;

    Transform(Object* o)
        :A(o)
    {
        rotate.make_id();
    }

    void Rotate(const vec3& axis, double angle);
    void Scale(double s);
    void Translate(const vec3& shift);

    vec3 Transform_Point(const vec3& point) const;
    vec3 Inverse_Transform_Point(const vec3& point) const;
    vec3 Transform_Unit_Vector(const vec3& dir) const;
    vec3 Inverse_Transform_Unit_Vector(const vec3& dir) const;

    virtual void Intersection(const Ray& ray, std::vector<Hit>& hits) const override;
    virtual vec3 Normal(const vec3& point) const override;
    virtual void Update_Bounding_Box() override;
};
#endif
