#ifndef RAYTRACE_H
# define RAYTRACE_H

#include <Vec.h>
#include <Obj.h>

typedef struct s_ray
{
	t_point3d	center;
	t_vec3d		direction;
}				t_ray;

typedef struct s_hit
{
	t_point3d p;
	t_vec3d normal;
	double t;
	int ff;
	int shader;
}				t_hit;

t_color ray_color(t_ray r, t_list *world, int depth);
t_vec3d rand_in_unit_sphere();
t_vec3d rand_unit_mm(double min, double max);
t_vec3d rand_unit();
double random_double();
double random_double_mm(double min, double max);
int hit_sph(t_sph sph, t_ray r, double min, double max, t_hit *rec);
int	intersect_plane(t_plane plane, t_ray ray, double min, double max, t_hit *impact);
int	update(t_list *lst, t_ray r, double min, double max, t_hit *rec);
void 	set_f_normal(t_hit *self, t_ray r, t_vec3d out_norm);
t_point3d at(t_ray self, double t);
t_ray ray(t_point3d center, t_vec3d direction);
#endif