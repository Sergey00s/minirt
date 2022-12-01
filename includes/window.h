#ifndef WINDOW_H
# define WINDOW_H

#include <Cam.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bbp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_window
{
	void *mlx;
	void *win;
	int samples_per_pixel;
	t_vec3d lamp_reel_pos;
	t_vec3d lamp;
	t_screen sc;
	t_list	*world;
	t_cam	cam;
	t_mesh *mymesh;
	float	**zBuffer;
	t_img img;
}				t_window;

void	image_pixel_put(int x, int y, int color);
extern t_window wn;
#endif