#include "plane.h"
#include "ray.h"
#include <cfloat>

// Intersect with the half space defined by the plane.  The plane's normal
// points outside.  If the ray starts on the "inside" side of the plane, be sure
// to record a hit with t=0 as the first entry in hits.
void Plane::
Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    TODO;
    vec3 oe = ray.endpoint - this->x1;
    vec3 eo = this->x1 - ray.endpoint;
    vec3 n = this->normal;
    double x;
    double d;
    double y;
    double l;
    double cos;
    vec3 startp;
    vec3 endp;
    Hit hit;
    Hit hit2;
    d = oe.magnitude();
    cos = dot(n, ray.direction) / n.magnitude() / ray.direction.magnitude();

    if (dot(oe, n) > 0) {
        if (dot(n, ray.direction) >= 0) {
            return;
        }
        else {
            if (dot(eo, ray.direction) > 0) {
                x = -dot(eo, n) / n.magnitude();
                l = x / (-(dot(ray.direction, n) / (ray.direction.magnitude() * n.magnitude()));
                startp = ray.endpoint + ray.direction * l;
                hit.location = startp;
                hit.object = this;
                hit.ray_exiting = false;
                mat3 rm;
                rm.make_id();
                hit.rotation = rm;    //not sure
                hit.t = l;
            }
            else if (dot(eo, ray.direction) == 0) {
                x = d;
                l=x / (-(dot(ray.direction, n) / (ray.direction.magnitude() * n.magnitude()));
                startp = ray.endpoint + ray.direction * l;
                hit.location = startp;
                hit.object = this;
                hit.ray_exiting = false;
                mat3 rm;
                rm.make_id();
                hit.rotation = rm;    //not sure
                hit.t = l;
            }
            else {
                x = d * (-dot(n, eo) / (n.magnitude() * eo.magnitude()));
                l = x / (-(dot(ray.direction, n) / (ray.direction.magnitude() * n.magnitude()));
                startp = ray.endpoint + ray.direction * l;
                hit.location = startp;
                hit.object = this;
                hit.ray_exiting = false;
                mat3 rm;
                rm.make_id();
                hit.rotation = rm;    //not sure
                hit.t = l;
            }
            hits[0] = hit;
            return;
        }
    }
    else if (dot(oe, n) == 0) {
        hit.location = ray.endpoint;
        hit.object = this;
        hit.ray_exiting = false;
        mat3 rm;
        rm.make_id();
        hit.rotation = rm;
        hit.t = 0;
        hits[0] = hit;
        return;
    }
    else {
        if (dot(n, ray.direction) <= 0) {
            hit.location = ray.endpoint;
            hit.object = this;
            hit.ray_exiting = false;
            mat3 rm;
            rm.make_id();
            hit.rotation = rm;
            hit.t = 0;
            hits[0] = hit;
            return;
        }
        else {
            if (dot(eo, ray.direction) > 0) {
                x = d * (dot(eo, n) / (eo.magnitude() * n.magnitude()));
                l = x / ((dot(ray.direction, n) / (ray.direction.magnitude() * n.magnitude()));
                startp = ray.endpoint;
                hit.location = startp;
                hit.object = this;
                hit.ray_exiting = false;
                mat3 rm;
                rm.make_id();
                hit.rotation = rm;
                hit.t = 0;
                endp = ray.endpoint + ray.direction * l;
                hit2.location = endp;
                hit2.object = this;
                hit2.ray_exiting = true;
                hit2.rotation = rm;    //not sure
                hit2.t = l;
            }
            else if (dot(eo, ray.direction) == 0) {
                x = d;
                l = x / ((dot(ray.direction, n) / (ray.direction.magnitude() * n.magnitude()));
                startp = ray.endpoint;
                hit.location = startp;
                hit.object = this;
                hit.ray_exiting = false;
                mat3 rm;
                rm.make_id();
                hit.rotation = rm;
                hit.t = 0;
                endp = ray.endpoint + ray.direction * l;
                hit2.location = endp;
                hit2.object = this;
                hit2.ray_exiting = true;
                hit2.rotation = rm;    //not sure
                hit2.t = l;
            }
            else {
                x = d * (dot(eo, n) / (eo.magnitude() * n.magnitude()));
                l = x / ((dot(ray.direction, n) / (ray.direction.magnitude() * n.magnitude()));
                startp = ray.endpoint;
                hit.location = startp;
                hit.object = this;
                hit.ray_exiting = false;
                mat3 rm;
                rm.make_id();
                hit.rotation = rm;
                hit.t = 0;
                endp = ray.endpoint + ray.direction * l;
                hit2.location = endp;
                hit2.object = this;
                hit2.ray_exiting = true;
                hit2.rotation = rm;    //not sure
                hit2.t = l;
            }
            hits[0] = hit;
            hits[1] = hit2;
            return;
        }
    }
}

vec3 Plane::
Normal(const vec3& point) const
{
    return normal;
}

void Plane::Update_Bounding_Box()
{
    bounding_box.Make_Full();
    infinite_box=true;
}

