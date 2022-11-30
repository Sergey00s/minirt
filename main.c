#include <Ray.h>
#include <fcntl.h>
#include <limits.h>

// https://raytracing.github.io/

t_window wn;

void	image_pixel_put(int x, int y, int color)
{
	if (x < 0 && x >= wn.sc.width && y < 0 && y >= wn.sc.height)
		return ;
	*((int *)(wn.img.addr + (y * wn.img.line_len) \
	+ (x * (wn.img.bbp / 8)))) = color;
}


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

int MinInt(int a, int b)
{
    return (a < b) ? a : b;
}
int MaxInt(int a, int b)
{
    return (a < b) ? b : a;
}
void clearZBuffer()
{
    for (unsigned int x = 0; x < wn.sc.width; x++)
        for (unsigned int y = 0; y < wn.sc.height; y++)
            wn.zBuffer[x][y] = 10000.0f;
}

int controlFunctionPoint(t_vec2d a, t_vec2d b, t_vec2d point)
{
    float tolorance = a.x - b.x;
    if (tolorance < EPSILON && tolorance > -EPSILON)
        return ((a.x - point.x) > 0) == (a.y < b.y);

    float inclination = (b.y - a.y) / (b.x - a.x);
    float add = a.y - (a.x * inclination);

    return ((point.x * inclination) + add < point.y) == (a.x < b.x);
}

t_tris calc_transform(t_tris tris)
{
    tris.a.x -= wn.cam.origin.x;
    tris.a.y -= wn.cam.origin.y;
    tris.a.z -= wn.cam.origin.z;
    tris.b.x -= wn.cam.origin.x;
    tris.b.y -= wn.cam.origin.y;
    tris.b.z -= wn.cam.origin.z;
    tris.c.x -= wn.cam.origin.x;
    tris.c.y -= wn.cam.origin.y;
    tris.c.z -= wn.cam.origin.z;
    return tris;
}

t_vec2d worldToScreenPoint(t_vec3d pos)
{
    float x = (-pos.x / (pos.z * wn.cam.focal_len));
    float y = (-pos.y / (pos.z * wn.cam.focal_len));
    return (t_vec2d){x + wn.sc.width * 0.5f, y + wn.sc.height * 0.5f};
}

void draw_tris(t_tris tris)
{
    tris = calc_transform(tris);
	t_vec3d worldPos[3];
	
	worldPos[0] = tris.a;
    worldPos[1] = tris.b;
    worldPos[2] = tris.c;

    t_vec2d cTris2d[3];
    cTris2d[0] = worldToScreenPoint(worldPos[0]);
    cTris2d[1] = worldToScreenPoint(worldPos[1]);
    cTris2d[2] = worldToScreenPoint(worldPos[2]);

    if (controlFunctionPoint(cTris2d[0], cTris2d[1], cTris2d[2]))
        return;

    int bA[3];
	bA[0] = cTris2d[2].y < cTris2d[0].y,
    bA[1] = cTris2d[0].y < cTris2d[1].y,
    bA[2] = cTris2d[1].y < cTris2d[2].y;

    if (!bA[0] && !bA[1] && !bA[2])
        return;

    int sIndex[3];
	sIndex[0] = bA[0] + !bA[1];
    sIndex[1] = bA[1] + !bA[2];
    sIndex[2] = bA[2] + !bA[0];

    t_vec2d tris2d[3];
    tris2d[sIndex[0]] = cTris2d[0];
    tris2d[sIndex[1]] = cTris2d[1];
    tris2d[sIndex[2]] = cTris2d[2];

    if (tris2d[2].y < 0 || tris2d[0].y > wn.sc.height)
        return;

    float zPos[3];
    zPos[sIndex[0]] = worldPos[0].z;
    zPos[sIndex[1]] = worldPos[1].z;
    zPos[sIndex[2]] = worldPos[2].z;

    t_vec3d tNormals[3];
    //printf("(%f, %f, %f)\n", tris.n_a.x, tris.n_a.y, tris.n_a.z);
    tNormals[sIndex[0]] = tris.n_a;
    tNormals[sIndex[1]] = tris.n_b;
    tNormals[sIndex[2]] = tris.n_c;

    t_vec3d tPos[3];
    //printf("(%f, %f, %f)\n", tris.n_a.x, tris.n_a.y, tris.n_a.z);
    tPos[sIndex[0]] = tris.a;
    tPos[sIndex[1]] = tris.b;
    tPos[sIndex[2]] = tris.c;

    int right = controlFunctionPoint(tris2d[0], tris2d[2], tris2d[1]);

    int indexs[3][2];
    indexs[0][0] = 1;
    indexs[0][1] = 0;
    indexs[1][0] = 2;
    indexs[1][1] = 0;
    indexs[2][0] = 2;
    indexs[2][1] = 1;  

    float inclination[3];
    float add[3];
    float lerp[3];
    for (int i = 0; i < 3; i++)
    {
        t_vec2d a = tris2d[indexs[i][0]];
        t_vec2d b = tris2d[indexs[i][1]];
        if (a.y == b.y)
            continue;

        lerp[i] = 1 / (a.y - b.y);
        inclination[i] = (b.x - a.x) / (b.y - a.y);
        add[i] = a.x - a.y * inclination[i];
    }
    int aMaxY = MinInt(tris2d[1].y, wn.sc.height - 1);
    for (int y = MaxInt(0, tris2d[0].y + 1); y <= aMaxY; y++)
    {
        int a = right;
        int b = !right;

        float max = y * inclination[a] + add[a];
        float min = y * inclination[b] + add[b];

        float aL = (y - tris2d[0].y) * lerp[b];
        float bL = (y - tris2d[0].y) * lerp[a];

        float zPosA = zPos[a + 1] * bL + zPos[0] * (1.0f - bL);
        float zPosB = zPos[b + 1] * aL + zPos[0] * (1.0f - aL);

        t_vec3d aNormal = vector3_lerp(tNormals[a + 1], tNormals[0], bL);
        t_vec3d bNormal = vector3_lerp(tNormals[b + 1], tNormals[0], aL);

        t_vec3d aPos = vector3_lerp(tPos[a + 1], tPos[0], bL);
        t_vec3d bPos = vector3_lerp(tPos[b + 1], tPos[0], aL);

        float cL = 1.0f / (max - min);
        int aMaxX = MinInt(max, wn.sc.width - 1);
        for (int x = MaxInt(0, min + 1); x <= aMaxX; x++)
        {
            float rZPos = zPosA * (x - min) * cL + zPosB * (1.0f - (x - min) * cL);
            if (rZPos < wn.zBuffer[x][y])
            {
                t_vec3d rNormal = vector3_lerp(aNormal, bNormal, (x - min) * cL);
                t_vec3d rPos = vector3_lerp(aPos, bPos, (x - min) * cL);
                wn.zBuffer[x][y] = rZPos;
                image_pixel_put(x, y, rgb2(rNormal));
            }
        }
    }

    const int bMaxY = MinInt(tris2d[2].y, wn.sc.height - 1);
    for (int y = MaxInt(0, tris2d[1].y + 1); y <= bMaxY; y++)
    {
        int a = right + 1;
        int b = !right + 1;

        float max = y * inclination[b] + add[b];
        float min = y * inclination[a] + add[a];

        float aL = (y - tris2d[1].y + ((tris2d[1].y - tris2d[0].y) * !right)) * lerp[a];
        float bL = (y - tris2d[1].y + ((tris2d[1].y - tris2d[0].y) * right)) * lerp[b];

        float zPosA = zPos[2] * bL + zPos[!right] * (1.0f - bL);
        float zPosB = zPos[2] * aL + zPos[right] * (1.0f - aL);

        t_vec3d aNormal = vector3_lerp(tNormals[2], tNormals[!right], bL);
        t_vec3d bNormal = vector3_lerp(tNormals[2], tNormals[right], aL);
        
        t_vec3d aPos = vector3_lerp(tPos[2], tPos[!right], bL);
        t_vec3d bPos = vector3_lerp(tPos[2], tPos[right], aL);
        
        float cL = 1.0f / (max - min);
        int bMaxX = MinInt(max, wn.sc.width - 1);
        for (int x = MaxInt(0, min + 1); x <= bMaxX; x++)
        {
            float rZPos = zPosA * (x - min) * cL + zPosB * (1.0f - (x - min) * cL);
            if (rZPos < wn.zBuffer[x][y])
            {
                t_vec3d rNormal = vector3_lerp(aNormal, bNormal, (x - min) * cL);
                t_vec3d rPos = vector3_lerp(aPos, bPos, (x - min) * cL);
                wn.zBuffer[x][y] = rZPos;
                image_pixel_put(x, y, rgb2(rNormal));
            }
        }
    }
}

#include <time.h>

int ft_render(int l)
{
	double v;
	double u;

	t_ray r;
	t_vec3d res;
	/*
	for (int i = l; i < wn.sc.height; ++i)
	{
		for (int j = 0; j < wn.sc.width; ++j)
		{
			t_vec3d cl = vec3d(0, 0, 0);

				u = (double)((double)j ) / (wn.sc.width - 1);
				v = (double)((double)i ) / (wn.sc.height - 1);
				r = ray(wn.cam.origin, direction(wn.cam, u, v));
				res = ray_color(r, wn.world, wn.sc.depth);
				cl = vec_plus(cl, res);
			write_color(cl, wn.samples_per_pixel, j, wn.sc.height - i - 1);
		}
		//mlx_do_sync(wn.mlx);
	}*/
    clock_t begin = clock();
	clearZBuffer();
    for (int i = 0; i < wn.mymesh->size ; i++)
    {
        draw_tris(wn.mymesh->tris[i]);
    }
    mlx_put_image_to_window(wn.mlx, wn.win, wn.img.img, 0, 0);
	//printf("time: %lf\n", (double)(clock() - begin) / CLOCKS_PER_SEC);
	return 1;
}

int key_hook(int keycode, t_window *vars)
{
	int i;

	if (keycode == 15)
	{
		
	}
	if (keycode == 53)
	{
		exit(1);
	}
	
	return 1;
}

int ft_update(void *arg)
{   
    ft_render(0);
    return 0;
}

static void cam_init()
{
	wn.cam.origin = vec3d(0, 0, -4);
	wn.sc.a_ratio = 16.0 / 9.0;
	wn.sc.width = 2000;
	wn.sc.height = (int)(wn.sc.width / wn.sc.a_ratio);
    wn.zBuffer = (float **)malloc(sizeof(float *) * wn.sc.width);

    for (int x = 0; x < wn.sc.width; x++)
        wn.zBuffer[x] = (float *)malloc(sizeof(float) * wn.sc.height);
    
	wn.sc.depth = 50;
	wn.cam = s_cam(2.0, 1.0f / (wn.sc.height * 1), wn.sc);
	wn.samples_per_pixel = 1;
	//printf("height = %d, width = %d\ncam_pos = (%f, %f, %f)\n", wn.sc.height, wn.sc.width, wn.cam.origin.x, wn.cam.origin.y, wn.cam.origin.z);
}

int main(void)
{
	cam_init();
	wn.lamp = vec3d(10, 0, 0);
	wn.mlx = mlx_init();
	wn.win = mlx_new_window(wn.mlx, wn.sc.width, wn.sc.height, "test");
	wn.world = world_init();
    wn.img.img = mlx_new_image(wn.mlx, wn.sc.width, wn.sc.height);
	wn.img.addr = mlx_get_data_addr(wn.img.img, &wn.img.bbp \
	, &wn.img.line_len, &wn.img.endian);
	wn.mymesh = import_obj("test.obj", "cube", vec3d(0,0, 0));
	ft_lstadd_back(&wn.world, ft_lstnew(sph(vec3d(0, -100.5, -1), 100)));
	mlx_key_hook(wn.win, key_hook, NULL);
    mlx_loop_hook(wn.mlx, &ft_update, NULL);
	mlx_loop(wn.mlx);
	return 0;
}