#include <Ray.h>

int	update(t_list *lst, t_ray r, double min, double max, t_hit *rec)
{
	t_obj *temp;
	t_hit tempr;
	int hit;
	double clsf;

	hit = 0;
	clsf = max;
	if (!lst)
		return 0;
	while (lst)
	{
		temp = (t_obj *)lst->content;
		if (temp->type == 1)
		{
			if (hit_sph(temp->sph, r, min, clsf, &tempr))
			{
				hit = 1;
				clsf = tempr.t;
				*rec = tempr;
			}
		}
		
		lst = lst->next;
	}
	return hit;
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
