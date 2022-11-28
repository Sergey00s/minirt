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





int intersect_triangle3(double orig[3], double dir[3],
			double vert0[3], double vert1[3], double vert2[3],
			double *t, double *u, double *v)
{
   double edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
   double det,inv_det;

   /* find vectors for two edges sharing vert0 */
   SUB(edge1, vert1, vert0);
   SUB(edge2, vert2, vert0);

   /* begin calculating determinant - also used to calculate U parameter */
   CROSS(pvec, dir, edge2);

   /* if determinant is near zero, ray lies in plane of triangle */
   det = DOT(edge1, pvec);

   /* calculate distance from vert0 to ray origin */
   SUB(tvec, orig, vert0);
   inv_det = 1.0 / det;
   
   CROSS(qvec, tvec, edge1);
      
   if (det > EPSILON)
   {
      *u = DOT(tvec, pvec);
      if (*u < 0.0 || *u > det)
	 return 0;
            
      /* calculate V parameter and test bounds */
      *v = DOT(dir, qvec);
      if (*v < 0.0 || *u + *v > det)
	 return 0;
      
   }
   else if(det < -EPSILON)
   {
      /* calculate U parameter and test bounds */
      *u = DOT(tvec, pvec);
      if (*u > 0.0 || *u < det)
	 return 0;
      
      /* calculate V parameter and test bounds */
      *v = DOT(dir, qvec) ;
      if (*v > 0.0 || *u + *v < det)
	 return 0;
   }
   else return 0;  /* ray is parallell to the plane of the triangle */

   *t = DOT(edge2, qvec) * inv_det;
   (*u) *= inv_det;
   (*v) *= inv_det;
}


t_vec3d vector3_lerp(t_vec3d a, t_vec3d b, double value)
{
    t_vec3d dif;

    dif = vec_plus(b, minus(a));
    dif = vec_multiply_by_value(dif, value);
    return (vec_plus(dif, a));
}

t_vec3d calculate_pos(t_tris tris, double u, double v)
{
    t_vec3d b_c;
    t_vec3d a_b;

    a_b = vector3_lerp(tris.a, tris.b, u);
    b_c = vector3_lerp(tris.b, tris.c, v);
    return vec_plus(a_b, vec_plus(b_c, minus(tris.b)));
}

int tocall(t_ray ray, t_tris tris, double *value, t_vec3d *pos)
{
    int result;
    double u;
    double v;

    tris.a.x -= wn.cam.origin.x;
    tris.a.y -= wn.cam.origin.y;
    tris.a.z -= wn.cam.origin.z;
    tris.b.x -= wn.cam.origin.x;
    tris.b.y -= wn.cam.origin.y;
    tris.b.z -= wn.cam.origin.z;
    tris.c.x -= wn.cam.origin.x;
    tris.c.y -= wn.cam.origin.y;
    tris.c.z -= wn.cam.origin.z;

    result = intersect_triangle3((double[]){ray.center.x,ray.center.y,ray.center.z},
    (double[]){ray.direction.x,ray.direction.y,ray.direction.z},  
            (double[]){tris.a.x, tris.a.y, tris.a.z},
            (double[]){tris.b.x, tris.b.y, tris.b.z},
            (double[]){tris.c.x, tris.c.y, tris.c.z},
			value, &u, &v);
    *pos = calculate_pos(tris, u, v);
    return result;
}