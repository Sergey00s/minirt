#include <Ray.h>


int	intersect_plane(t_plane plane, t_ray ray, double min, double max, t_hit *impact)
{
	double	denom;
	double	x;

	denom = dot_product(plane.normal, ray.direction);
	if (fabs(denom) > 0)
	{
		x = dot_product(vec_plus(plane.origin, minus(ray.center)), plane.normal) / denom;
		if (x > EPSILON && x < max)
		{
			impact->normal = normalize2(plane.normal);
			impact->p = vec_plus(ray.center, vec_multiply_by_value(ray.direction, x));
			impact->p = vec_plus(impact->p, vec_multiply_by_value(impact->normal, EPSILON));
			return (1);
		}
	}
	return (0);
}


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