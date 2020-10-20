#ifndef __HIT_H__
#define __HIT_H__

#include "mat.h"

class Object;

// Records information about an intersection, which may be needed later for
// Boolean operations or for a subsequent call to Normal.
struct Hit
{
    // The primitive geometry whose surface was intersected.  This should
    // not point at a Union, Difference, or Intersection object.  Instead it
    // should point at the particular component.
    const Object* object;

    // Distance along the ray at which this occurred
    double t;

    // Location of the intersection on the original primitive.  Note that
    // because of transform objects, this location might not be the same as what
    // you would evaluate from the ray.
    vec3 location;

    // If we have transform nodes, then the normal direction may need to be
    // rotated.  When calling Normal on object, the normal direction should be
    // rotated with this matrix.
    mat3 rotation;

    // Was the ray entering or exiting the primitive geometry stored in
    // "object"?  This will tell you whether you will need to reverse the
    // normal that you compute.
    bool ray_exiting;

    // This routine calculates the normal direction corresponding to this
    // intersection.  This routine should account for ray_exiting and
    // transformations.  Note that all of the information required to implement
    // this is available to this routine.  Anything that needs normal directions
    // for an intersection should call this routine rather than calling the
    // Normal routine on objects directly.
    vec3 Normal() const;
};

#endif
