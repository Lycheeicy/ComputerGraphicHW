#include "transform.h"
#include "ray.h"

// Scale about the origin by angle around axis.  Note that this scales the
// current transform; it does not just set rotate.  axis is a unit vector.
void Transform::Rotate(const vec3& axis, double angle)
{
    TODO;
}

// Scale about the origin by s.  Note that this scales the current
// transform; it does not just set scale=s.
void Transform::Scale(double s)
{
    TODO;
}

// Translate by shift.  Note that this translates the current transform; it
// does not just set translate.
void Transform::Translate(const vec3& shift)
{
    TODO;
}

// This is how rotate, scale, and translate are used to transform locations in
// space.  You can think of this as a definition.  The other transformation
// routines can be implemented based on this definition.
vec3 Transform::Transform_Point(const vec3& point) const
{
    return rotate*point*scale+translate;
}

// This should do the inverse of Transform_Point().  That is,
// x==Inverse_Transform_Point(Transform_Point(x)) for all x.  You can use this
// property to implement this function.
vec3 Transform::Inverse_Transform_Point(const vec3& point) const
{
    TODO;
    return {};
}

// This routine transforms directions (unit vectors).  The input is a unit
// vector, and the output should be as well.
vec3 Transform::Transform_Unit_Vector(const vec3& dir) const
{
    TODO;
    return {};
}

// This should do the inverse of Transform_Unit_Vector().  That is,
// x==Inverse_Transform_Unit_Vector(Transform_Unit_Vector(x)) for all x.  You
// can use this property to implement this function.
vec3 Transform::Inverse_Transform_Unit_Vector(const vec3& dir) const
{
    TODO;
    return {};
}

// Determine if the ray intersects with the transform of A and B.
void Transform::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    TODO;
}

// This should never be called.
vec3 Transform::Normal(const vec3& point) const
{
    assert(false);
    return vec3();
}

void Transform::Update_Bounding_Box()
{
    A->Update_Bounding_Box();
    infinite_box=A->infinite_box;
    if(infinite_box) return;
    Box b=A->bounding_box;
    bounding_box.Make_Empty();
    for(int i=0;i<8;i++)
    {
        vec3 p(i&1?b.lo[0]:b.hi[0],i&2?b.lo[1]:b.hi[1],i&4?b.lo[2]:b.hi[2]);
        bounding_box.Include_Point(Transform_Point(p));
    }
}
