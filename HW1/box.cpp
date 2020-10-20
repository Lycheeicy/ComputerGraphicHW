#include <limits>
#include "box.h"

// Return whether the ray intersects this box.
bool Box::Intersects(const Ray& ray) const
{
    vec3 v[2]={lo-ray.endpoint,hi-ray.endpoint},dir=ray.direction;
    double near=0;
    double far=std::numeric_limits<double>::infinity();
    for(int i=0; i<3; i++)
    {
        if(dir[i]<0)
        {
            v[0][i]=-v[0][i];
            v[1][i]=-v[1][i];
            std::swap(v[0][i],v[1][i]);
            dir[i]=-dir[i];
        }
        if(v[1][i]<0) return false;
        if(v[0][i]>0) near=std::max(near,v[0][i]/dir[i]);
        far=std::min(far,v[1][i]/dir[i]);
    }
    return near<=far;
}

// Compute the smallest box that contains both *this and bb.
Box Box::Union(const Box& bb) const
{
    Box box;
    box.lo=componentwise_min(lo,bb.lo);
    box.hi=componentwise_max(hi,bb.hi);
    return box;
}

// Compute the smallest box that is contained by both *this and bb.
Box Box::Intersection(const Box& bb) const
{
    Box box;
    box.lo=componentwise_max(lo,bb.lo);
    box.hi=componentwise_min(hi,bb.hi);
    return box;
}

// Enlarge this box (if necessary) so that pt also lies inside it.
void Box::Include_Point(const vec3& pt)
{
    lo=componentwise_min(lo,pt);
    hi=componentwise_max(hi,pt);
}

// Create a box to which points can be correctly added using Include_Point.
void Box::Make_Empty()
{
    lo.fill(std::numeric_limits<double>::infinity());
    hi=-lo;
}

// Create a box that contains everything.
void Box::Make_Full()
{
    hi.fill(std::numeric_limits<double>::infinity());
    lo=-hi;
}
