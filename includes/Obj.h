#ifndef OBJ_H
# define OBJ_H

#include <Vec.h>

typedef struct  s_plane
{
    t_vec3d origin;
    t_vec3d normal;
    double size;
}               t_plane;

typedef struct  s_cyl
{
    t_vec3d origin;
    double rad;
}               t_cyl;

typedef struct  s_sph
{
    t_vec3d origin;
    double rad;
}               t_sph;

typedef struct  s_obj
{
    t_plane pln;
    t_cyl   cyl;
    t_sph   sph;
    int type;
}               t_obj;

t_obj  *sph(t_vec3d origin, double rad);
t_obj *pln(t_vec3d origin, t_vec3d normal);
#endif