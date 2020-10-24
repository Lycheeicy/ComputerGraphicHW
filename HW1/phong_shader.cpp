#include "light.h"
#include "phong_shader.h"
#include "ray.h"
#include "render_world.h"
#include "object.h"

vec3 Phong_Shader::
Shade_Surface(const Ray& ray,const vec3& intersection_point,
    const vec3& normal,int recursion_depth) const
{
    vec3 color;
    //TODO; //determine the color
    //std::cout << "location is " << intersection_point << std::endl;
    //std::cout << "normal is " << normal << std::endl;
    //std::cout << "the size of the lights is " << this->world.lights.size() << std::endl;
    for (int i = 0; i < this->world.lights.size(); i++) {
        double brightness = this->world.lights[i]->brightness;
        vec3 colorl = this->world.lights[i]->color;
        vec3 el = this->world.lights[i]->Emitted_Light(this->world.lights[i]->position-intersection_point);
        //std::cout << "brightness " <<brightness << std::endl;
        //std::cout << "colorl is " << color << std::endl;
        double dmax;
        double smax;
        vec3 n = normal;
        vec3 l = this->world.lights[i]->position - intersection_point; //light color?
        l = l / l.magnitude();
        dmax = dot(n, l) >= 0 ? dot(n, l) : 0;
        double a = dot(n, l);
        vec3 r = n * (2 * a) - l;
        vec3 v = this->world.camera.position - intersection_point;
        v = v / v.magnitude();
        double th = dot(r, v) / r.magnitude();
        smax = cos(th) >= 0 ? cos(th) : 0;
        //std::cout << color + this->color_specular * pow(smax, this->specular_power)<< std::endl;
        color = color+this->color_diffuse*el*dmax + this->color_specular*el*pow(smax,this->specular_power);
        //std::cout << this->world.lights[i]->Emitted_Light(intersection_point)<< std::endl;
        //std::cout << "light is at "<<this->world.lights[i]->position << std::endl;
        //std::cout << "diffuse color is " << this->color_diffuse  << std::endl;
        //std::cout << "diffuse max is " << dmax << std::endl;
        //std::cout << "diffuse is " << color_diffuse *el* dmax << std::endl;
        //std::cout << "specular is " << this->color_specular * pow(smax, this->specular_power) << std::endl;
        //std::cout << "acos of answer is " << acos(0.336691)*180/pi << std::endl;
        //std::cout << "my acos is " << acos(dmax)*180/pi << std::endl;
        //std::cout << "the m of l and n is " << l.magnitude() << " " << n.magnitude() << std::endl;
    }
    color = this->color_ambient + color;
    //std::cout << "ambient is " << this->color_ambient << std::endl;
    return color;
}
