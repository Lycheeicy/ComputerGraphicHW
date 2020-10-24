#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <vector>
#include "vec.h"
#include "hit.h"
#include "box.h"

// t has to be bigger than small_t to register an intersection with a ray.  You
// may need to tweak this value.
// http://stackoverflow.com/questions/17688360/ray-tracing-shadow-bug
static const double small_t = 1e-4;
extern bool debug_pixel;

class Ray;
class Shader;
class Object;

class Object
{
public:
    Shader* material_shader;
    Box bounding_box;
    bool infinite_box=false;

    Object() :material_shader(0) {}
    virtual ~Object() {}

    // Check for an intersection in the range [0,inf).  Record all intersections
    // in order they are encountered, whether entering or leaving, in hits.  If
    // the ray begins inside the object, record that the ray enters the object
    // at time 0. In this way even entries indicate the ray entering, and odd
    // entries indicate that the ray is leaving.  Note that this differs from
    // the ray_exiting entry of the Hits structure in the case of Booleans,
    // which refers to the underlying primitive rather than the aggregate
    // object.
    virtual void Intersection(const Ray& ray, std::vector<Hit>& hits) const=0;

    // Return the normal.  This routine should never be called for intersections
    // recorded at time 0, since these hits indicate that the ray started inside
    // the object, not that it actually intersects its surface.  Note that this
    // routine should not be called directly, since it will not properly take
    // into account transforms.
    virtual vec3 Normal(const vec3& point) const=0;

    virtual void Update_Bounding_Box()=0;
};
#endif
