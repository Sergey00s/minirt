#include <Ray.h>

t_tris *arr()
{
	t_tris *rtn;

	rtn = malloc(sizeof(t_tris) * 12);

	t_vec3d bir = vec3d(-1.000000, -1.000000, 1.000000);
	t_vec3d iki = vec3d(-1.000000, 1.000000, 1.000000);
	t_vec3d uc = vec3d(-1.000000, -1.000000, -1.000000);
	t_vec3d dort = vec3d(-1.000000, 1.000000, -1.000000);
	t_vec3d bes = vec3d(1.000000, -1.000000, 1.000000);
	t_vec3d alti = vec3d(1.000000, 1.000000, 1.000000);
	t_vec3d yedi = vec3d(1.000000, -1.000000, -1.000000);
	t_vec3d sekiz = vec3d(1.000000, 1.000000, -1.000000);

	rtn[0] = tri(iki, uc, bir);
	rtn[1] = tri(dort, yedi, uc);
	rtn[2] = tri(sekiz, bes, yedi);
	rtn[3] = tri(alti, bir, bes);
	rtn[4] = tri(yedi, bir, uc);
	rtn[5] = tri(dort, alti, sekiz);
	rtn[6] = tri(iki, dort, uc);
	rtn[7] = tri(dort, sekiz, yedi);
	rtn[8] = tri(sekiz, alti, bes);
	rtn[9] = tri(alti, iki, bir);
	rtn[10] = tri(yedi, bes, bir);
	rtn[11] = tri(dort, iki, alti);
	return rtn;
}

t_vec3d get_normal(t_tris tri)
{
	t_vec3d rtn;

	rtn = cross_product(vec_sub(tri.a, tri.b), vec_sub(tri.c, tri.a));
	rtn = normalize(rtn);
	return rtn;
}

int	update(t_list *lst, t_ray r, double min, double max, t_hit *rec)
{
	double t;
	t_vec3d pos;
	int found_index = -1;
	double min_distance_sqr = DBL_MAX;
	int tris_length = 12;
	t_tris *tris;
	t_vec3d tmp_pos;
	//tris = arr();
	t_mesh *a = wn.mymesh;
	tris = a->tris;
	tris_length = a->size;
	
	
	// for (size_t i = 0; i < tris_length; i++)
	// {
	// 	printf("a(%f, %f, %f) b(%f, %f, %f) c(%f, %f, %f)\n"
	// 		, tris[i].a.x, tris[i].a.y, tris[i].a.z
	// 		, tris[i].b.x, tris[i].b.y, tris[i].b.z
	// 		, tris[i].c.x, tris[i].c.y, tris[i].c.z);
	// }
	//exit(0);
	double tmp_t;
	double tmp_distance;

	while(tris_length--)
	{
		//if (!tocall(r, tris[tris_length], &tmp_t, &tmp_pos))
		//	continue;
		tmp_distance = -tmp_t;
		if (min_distance_sqr > tmp_distance)
		{
			found_index = tris_length;
			min_distance_sqr = tmp_distance;
			rec->p = vec_plus(r.center, vec_multiply_by_value(r.direction, tmp_distance));
			t = tmp_t;
			rec->normal = get_normal(tris[tris_length]);
		}
	}
	return found_index != -1;
}

t_ray ray(t_point3d center, t_vec3d direction)
{
	t_ray rtn;

	rtn.center = center;
	rtn.direction = direction;
	return rtn;
}

t_point3d at(t_ray self, double t)
{
	return (vec_plus(self.center, vec_multiply_by_value(self.direction, t)));
}

void 	set_f_normal(t_hit *self, t_ray r, t_vec3d out_norm)
{
	self->ff = 0; 
	if (dot_product(r.direction, out_norm) < 0.0)
		self->ff = 1;
	if (self->ff)
		self->normal = out_norm;
	else
		self->normal = minus(out_norm);
}
