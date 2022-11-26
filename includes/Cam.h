#ifndef CAM_H
# define CAM_H

#include <Vec.h>

typedef struct	s_screen
{
	int height;
	int width;
	double a_ratio;
    int depth;
}				t_screen;

typedef struct  s_cam
{
    double vp_h;
    double vp_w;
    double focal_len;
    t_point3d origin;
    t_vec3d   horizontal;
    t_vec3d   vertical;
    t_vec3d   lower_left_corner;
}               t_cam;

t_cam s_cam(double vp_h, double focal_len, t_screen screen);
#endif