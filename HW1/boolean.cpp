#include "boolean.h"

// Determine if the ray intersects with the boolean of A and B.
void Boolean::Intersection(const Ray& ray, std::vector<Hit>& hits) const
{
    TODO;
}

// This should never be called.
vec3 Boolean::Normal(const vec3& point) const
{
    assert(false);
    return vec3();
}

void Boolean::Update_Bounding_Box()
{
    A->Update_Bounding_Box();
    B->Update_Bounding_Box();
    // Compute bounding_box from A->bounding_box and B->bounding_box.
    // Note that this should depend on the type of boolean being performed.
    TODO;
}

