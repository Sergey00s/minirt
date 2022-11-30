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

typedef struct s_arr
{
	char **arr;
	int size;
}			t_arr;


typedef struct s_objdata
{
	t_arr *vecs;
	t_arr *faces;
	t_arr *nv;
}				t_objdata;

typedef struct s_objmesh
{
	t_tris *tris;
	int size;
}				t_objmesh;

int rgb2(t_vec3d rgb);
t_vec3d get_normal(t_tris tri);
t_arr *mk_arr();
void append(t_arr *self, char *news);
t_objdata read_my_line(int fd);
t_objmesh new_mesh(t_objdata data);
t_mesh *import_obj(char *name, char *obj_name, t_vec3d color);
int tocall(t_ray ray, t_tris tris, double *value, t_vec3d *pos);
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