#include "render_world.h"
#include "flat_shader.h"
#include "object.h"
#include "light.h"
#include "ray.h"


Render_World::Render_World()
    :background_shader(0),ambient_intensity(0),enable_shadows(true),
    recursion_depth_limit(3)
{}

Render_World::~Render_World()
{
    delete background_shader;
    for(size_t i=0;i<objects.size();i++) delete objects[i];
    for(size_t i=0;i<lights.size();i++) delete lights[i];
}

// Find the closest object of intersection and return the object that was
// intersected.  Record the Hit structure in hit.  If no intersection occurred,
// return NULL.  Note that in the case of a Boolean, the object returned will be
// the Boolean, but the object stored in hit will be the underlying primitive.
// Any intersection with t<=small_t should be ignored.
Object* Render_World::Closest_Intersection(const Ray& ray, Hit& hit)
{
    //TODO;
    Object* result=NULL;
    //return result;
    double min_t = std::numeric_limits<double>::max();
    //std::cout << objects.size()<< std::endl;
    for (int i = 0; i < objects.size(); i++) {       
        Object* var = objects[i];
        std::vector<Hit> vec;
        var->Intersection(ray, vec);
        //std::cout << vec.size() << std::endl;
        //std::cout <<"hit1 t "<< vec[0].t<< std::endl;
        //std::cout << "hit1 exiting "<<vec[0].ray_exiting<< std::endl;
        //std::cout << "hit2 t " << vec[1].t << std::endl;
        //std::cout << "hit2 exiting " << vec[1].ray_exiting << std::endl;
        if (vec.size() == 0)  continue;
        if(vec[0].t<=min_t&&vec[0].t>small_t){
            hit = vec[0];
            min_t = vec[0].t;
            result =(Object *) hit.object;
            //std::cout <<min_t<< std::endl;
        }
        //return result;

    }
    //std::cout << (*result). << std::endl;
    return result;
}

// set up the initial view ray and call
void Render_World::Render_Pixel(const ivec2& pixel_index)
{
    //TODO; // set up the initial view ray here
    Ray ray;
    ray.endpoint = this->camera.position;
    ray.direction = (this->camera.World_Position(pixel_index) - ray.endpoint).normalized();
    vec3 color=Cast_Ray(ray,1);
    camera.Set_Pixel(pixel_index,Pixel_Color(color));
}

void Render_World::Render()
{
    for(int j=0;j<camera.number_pixels[1];j++)
        for(int i=0;i<camera.number_pixels[0];i++)
            Render_Pixel(ivec2(i,j));
}

// cast ray and return the color of the closest intersected surface point,
// or the background color if there is no object intersection
vec3 Render_World::Cast_Ray(const Ray& ray,int recursion_depth)
{
    vec3 color;
    //return color;
    //TODO; // determine the color here
    Hit hit;
    Object* object;
    object=Closest_Intersection(ray, hit);
    if (object == NULL) {
        vec3 vec(0, 0, 0);
        return background_shader->Shade_Surface(ray,vec,vec,recursion_depth);
    }
    color=object->material_shader->Shade_Surface(ray, hit.location, hit.object->Normal(hit.location), recursion_depth);
    //std::cout << hit.location << std::endl;
    //std::cout << hit.object->Normal(hit.location) << std::endl;
    return color;
}
