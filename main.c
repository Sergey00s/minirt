#include <Ray.h>
#include <fcntl.h>
#include <limits.h>

// https://raytracing.github.io/

t_window wn;

t_vec3d difshader(t_hit rec, t_list *world, int depth)
{
	t_ray r;
	t_vec3d target;

	// target = vec_plus(rand_unit_vec(), rec.normal);
	target = vec_plus(rec.p, random_in_hemisphere(rec.normal));
	r = ray(rec.p, vec_plus(target, minus(rec.p)));
	return (vec_multiply_by_value(ray_color(r, world, depth - 1), 0.5));
}

t_color ray_color(t_ray r, t_list *world, int depth)
{
	double t;
	t_vec3d N;
	t_hit rec;
	t_vec3d target;

	if (depth <= 0)
		return vec3d(0, 0, 0);
	if (update(world, r, 0.001, DBL_MAX, &rec))
	{
		return difshader(rec, world, depth);
	}
	t_vec3d unit_dir;
	t_vec3d res;
	unit_dir = unit_vector(r.direction);
	t = 0.5 * (unit_dir.y + 1.0);
	res = vec_multiply_by_value(vec3d(0.5, 0.7, 1.0), t);
	res = vec_plus(vec_multiply_by_value(vec3d(1.0, 1.0, 1.0), 1.0 - t), res);
	return res;
}

static t_vec3d direction(t_cam cam, double u, double v)
{
	t_vec3d res;
	t_vec3d v1;

	v1 = minus(cam.origin);
	res = vec_multiply_by_value(cam.vertical, v);
	res = vec_plus(res, v1);
	v1 = vec_multiply_by_value(cam.horizontal, u);
	res = vec_plus(v1, res);
	res = vec_plus(cam.lower_left_corner, res);
	res = vec_plus(cam.origin, res);

	return res;
}

t_list *world_init()
{
	t_list *lst;
	t_obj *obj;

	obj = sph(vec3d(0.2, 0, -1), 0.5);
	lst = ft_lstnew(obj);
	return lst;
}



void first_render()
{
	double v;
	double u;
	t_ray r;
	t_vec3d res;

	for (int i = 0; i < wn.sc.height; ++i)
	{
		for (int j = 0; j < wn.sc.width; ++j)
		{
			t_vec3d cl = vec3d(0, 0, 0);
			for (size_t k = 0; k < 1; ++k)
			{
				u = (double)((double)j + random_double()) / (wn.sc.width - 1);
				v = (double)((double)i + random_double()) / (wn.sc.height - 1);
				r = ray(wn.cam.origin, direction(wn.cam, u, v));
				res = ray_color(r, wn.world, wn.sc.depth);
				cl = vec_plus(cl, res);
			}
			write_color(cl, 1, j, wn.sc.height - i - 1);
		}
	}
}

void ft_render()
{
	double v;
	double u;
	t_ray r;
	t_vec3d res;
	static int i;

	if (i < wn.sc.height)
	{
		for (int j = 0; j < wn.sc.width; ++j)
		{
			t_vec3d cl = vec3d(0, 0, 0);
			for (size_t k = 0; k < 500; ++k)
			{
				u = (double)((double)j + random_double()) / (wn.sc.width - 1);
				v = (double)((double)i + random_double()) / (wn.sc.height - 1);
				r = ray(wn.cam.origin, direction(wn.cam, u, v));
				res = ray_color(r, wn.world, wn.sc.depth);
				cl = vec_plus(cl, res);
			}
			write_color(cl, 500, j, wn.sc.height - i - 1);
		}

		i++;
	}
}


int run(void *arg)
{
	static int first = 1;
	if (first)
	{
		first = 0;
		first_render();
	}
	else
	{
		ft_render();
	}
	return 1;
}


int main(void)
{
	double v;
	double u;
	t_vec3d test;
	t_ray r;
	t_vec3d res;

	wn.sc.a_ratio = 16.0 / 9.0;
	wn.sc.width = 1080;
	wn.sc.height = (int)(wn.sc.width / wn.sc.a_ratio);
	wn.sc.depth = 50;
	wn.cam = s_cam(2.0, 1.0, wn.sc);

	wn.mlx = mlx_init();
	wn.win = mlx_new_window(wn.mlx, wn.sc.width, wn.sc.height, "my");

	wn.world = world_init();
	ft_lstadd_back(&wn.world, ft_lstnew(sph(vec3d(0, -100.5, -1), 100)));
	mlx_loop_hook(wn.mlx, &run, NULL);
	mlx_loop(wn.mlx);
	return 0;
}
