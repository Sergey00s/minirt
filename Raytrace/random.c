#include <Ray.h>


double random_double_mm(double min, double max) 
{
    // Returns a random real in [min,max).
    return min + (max-min)*random_double();
}

double random_double() 
{
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

t_vec3d rand_unit_mm(double min, double max)
{
    return (vec3d(random_double_mm(min, max), random_double_mm(min, max), random_double_mm(min, max)));
}

t_vec3d rand_unit()
{
    return (vec3d(random_double(), random_double(), random_double()));
}

t_vec3d rand_in_unit_sphere()
{
    t_vec3d p;

    p = vec3d(0, 0, 0);   
    while (1)
    {
        p = rand_unit_mm(-1,1);
        if (lenght_squared(p) >= 1.0)
            continue;
        return p;
    }
    return p;
}

t_vec3d rand_unit_vec()
{
    return unit_vector(rand_in_unit_sphere());
}



t_vec3d random_in_hemisphere(t_vec3d normal)
{
    t_vec3d in_unit_sphere;
    
    in_unit_sphere = rand_in_unit_sphere();
    if (dot_product(in_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
        return in_unit_sphere;
    else
        return minus(in_unit_sphere);
}