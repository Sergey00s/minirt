#ifndef WINDOW_H
# define WINDOW_H

#include <Cam.h>


typedef struct s_window
{
	void *mlx;
	void *win;
	t_screen sc;
	t_list	*world;
	t_cam	cam;
}				t_window;

extern t_window wn;
#endif