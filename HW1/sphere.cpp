#include "sphere.h"
#include "ray.h"

// Determine if the ray intersects with the sphere
void Sphere::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    TODO;
    double x;
    double y;
    double cos;
    double d;
    double l;
    double r = this->radius;
    vec3 startp;
    vec3 endp;
    vec3 eo = this->center - ray.endpoint;
    vec3 oe = ray.endpoint - this->center;
    Hit hit;
    Hit hit2;
    if ((ray.endpoint - this->center).magnitude() <= this->radius) {
        hit.location = ray.endpoint;
        hit.object = this;
        hit.ray_exiting = false;
        hit.t = 0;
        mat3 rm;
        rm.make_id();
        hit.rotation = rm;    //not sure
        if (dot(eo, ray.direction) > 0) {
            cos = dot(eo, ray.direction) / eo.magnitude() / ray.direction.magnitude();
            d = eo.magnitude();
            x = cos * d;
            y = sqrt(d * d - x * x);
            l = sqrt(this->radius * this->radius - y * y);
            endp = ray.endpoint + ray.direction * (x + l);
            hit2.t = x + l;
        }
        else if (dot(eo, ray.direction) < 0) {
            cos = dot(oe, ray.direction) / oe.magnitude() / ray.direction.magnitude();
            d = oe.magnitude();
            x = d * cos;
            y = sqrt(d*d-x*x);
            l = sqrt(r * r - y * y) - x;
            endp = ray.endpoint + ray.direction * l;
            hit2.t = l;
        }
        else if (dot(eo, ray.direction) == 0) {
            d = eo.magnitude();
            l = sqrt(r * r - d * d);
            endp = ray.endpoint + ray.direction * l;
            hit2.t = l;
        }
        hit2.location = endp;
        hit2.object = this;
        hit2.ray_exiting = true;
        //mat3 rm;
        rm.make_id();
        hit2.rotation = rm;   //not sure
        hits[0] = hit;
        hits[1] = hit2;
        return;
    }
    else {
        if (dot(eo, ray.direction) > 0) {
            d = eo.magnitude();
            cos = dot(eo, ray.direction) / eo.magnitude() / ray.direction.magnitude();
            x = d * cos;
            y = sqrt(d * d - x * x);
            l = sqrt(this->radius * this->radius - y * y);
            if (y > this->radius)  return;
            else if (y == this->radius) {
                endp = ray.endpoint + ray.direction * x;
                hit.location = endp;
                hit.object = this;
                hit.ray_exiting = false;
                mat3 rm;
                rm.make_id();
                hit.rotation =rm;
                hit.t = x;
                hit2.location = endp;
                hit2.object = this;
                hit2.ray_exiting = true;
                rm.make_id();
                hit2.rotation = rm;
                hit2.t = x;
                hits[0] = hit;
                hits[1] = hit2;
                return;
            }
            else if (y < this->radius) {
                startp = ray.endpoint + ray.direction * (x - l);
                endp = ray.endpoint + ray.direction * (x + l);
                hit.location = startp;
                hit.object = this;
                hit.ray_exiting = false;
                mat3 rm;
                rm.make_id();
                hit.rotation = rm;
                hit.t = x-l;
                hit2.location = endp;
                hit2.object = this;
                hit2.ray_exiting = true;
                hit2.rotation = rm;
                hit2.t = x+l;
                hits[0] = hit;
                hits[1] = hit2;
            }
        }
        else {
            return;
        }
    }
}

vec3 Sphere::Normal(const vec3& point) const
{
    vec3 normal;
    TODO; // compute the normal direction
    return normal;
}

// set this->bounding_box so that it contains the sphere as tightly as possible.
void Sphere::Update_Bounding_Box()
{
    TODO;
    infinite_box=false;
}

