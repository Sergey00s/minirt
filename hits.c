#include <Ray.h>



int hit_sph(t_sph sph, t_ray r, double min, double max, t_hit *rec)
{
    t_vec3d oc;
    double a;
    double hb;
    double c;
    double dis;

    oc = minus(sph.origin);
    oc = vec_plus(r.center, oc);
    a = lenght_squared(r.direction);
    hb = dot_product(oc, r.direction);
    c = lenght_squared(oc) - (sph.rad * sph.rad);
    dis = hb*hb - a*c;
    if (dis < 0.0)
        return 0;
    double sqrtd = sqrt(dis);
    double root;
    root = (-hb - sqrtd) / a;
    if (root < min || max < root)
    {
        root = (-hb + sqrtd) / a;
        if (root < min || max < root)
            return 0;
    }
    rec->t = root;
    rec->p = at(r, rec->t);
    rec->normal = vec_plus(rec->p, minus(sph.origin));
    rec->normal = vec_div(rec->normal, sph.rad);
    set_f_normal(rec, r, rec->normal);
    return 1;
}