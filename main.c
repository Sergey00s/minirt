#include <Ray.h>
#include <fcntl.h>
#include <limits.h>

// https://raytracing.github.io/

t_window wn;




t_vec3d difshader(t_hit rec, t_list *world, int depth)
{
	t_ray r;
	t_vec3d target;

	
	// if (tolight(rec, wn.light))
	// {
	// 	printf("hitt\n");
	// }else
	// 	return (vec3d(5,25,125));
	
	r = ray(rec.p, vec3d(random_double(), random_double(), random_double()));
	return (vec_multiply_by_value(ray_color(r, world, depth - 1), 0.5));
	// target = vec_plus(rand_unit_vec(), rec.normal);
	// target = vec_plus(rec.p, random_in_hemisphere(rec.normal));
	// r = ray(rec.p, vec_plus(target, minus(rec.p)));
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
		t_vec3d light_dir = normalize(vec_sub(wn.lamp, rec.p));
		return vec_multiply_by_value(vec3d(1,1,1), dot_product(rec.normal, light_dir));
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
	res = normalize(res);
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



int ft_render()
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
			for (size_t k = 0; k < wn.samples_per_pixel; ++k)
			{
				u = (double)((double)j ) / (wn.sc.width - 1);
				v = (double)((double)i ) / (wn.sc.height - 1);
				r = ray(wn.cam.origin, direction(wn.cam, u, v));
				res = ray_color(r, wn.world, wn.sc.depth);
				cl = vec_plus(cl, res);
			}
			write_color(cl, wn.samples_per_pixel, j, wn.sc.height - i - 1);
		}
		//mlx_do_sync(wn.mlx);
	}	
	return 1;
}

int key_hook(int keycode, t_window *vars)
{
	if (keycode == 15)
	{
		ft_render();

	}
	if (keycode == 53)
	{
		exit(1);
	}
	
	return 1;
}

static void cam_init()
{
	wn.cam.origin = vec3d(0, 2, 5);
	wn.sc.a_ratio = 16.0 / 9.0;
	wn.sc.width = 800;
	wn.sc.height = (int)(wn.sc.width / wn.sc.a_ratio);
	wn.sc.depth = 50;
	wn.cam = s_cam(2.0, 1.0, wn.sc);
	wn.samples_per_pixel = 1;
	printf("height = %d, width = %d\ncam_pos = (%f, %f, %f)\n", wn.sc.height, wn.sc.width, wn.cam.origin.x, wn.cam.origin.y, wn.cam.origin.z);
}



int main(void)
{
	cam_init();
	wn.lamp = vec3d(1, 1, 1);
	wn.mlx = mlx_init();
	wn.win = mlx_new_window(wn.mlx, wn.sc.width, wn.sc.height, "test");
	wn.world = world_init();
	ft_lstadd_back(&wn.world, ft_lstnew(sph(vec3d(0, -100.5, -1), 100)));
	mlx_key_hook(wn.win, key_hook, NULL);
	mlx_loop(wn.mlx);
	return 0;
}
