#ifndef OBJ_H
# define OBJ_H

#include <Vec.h>
#include <Raytrace.h>

typedef struct  s_plane
{
    t_vec3d origin;
    t_vec3d normal;
    double size;
}               t_plane;

typedef struct s_tris
{
    t_vec3d a;
    t_vec3d b;
    t_vec3d c;
    t_vec3d n_a;
    t_vec3d n_b;
    t_vec3d n_c;
} t_tris;

typedef struct s_mesh
{
    char *name;
    t_vec3d color;
    t_tris *tris;
    int size;
} t_mesh;

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

typedef struct s_light
{
    t_vec3d origin;
    int     bright;
}               t_light;


typedef struct  s_obj
{
    t_plane pln;
    t_cyl   cyl;
    t_sph   sph;
    int type;
}               t_obj;


t_obj  *sph(t_vec3d origin, double rad);
t_obj *pln(t_vec3d origin, t_vec3d normal);
t_tris tri(t_vec3d a, t_vec3d b, t_vec3d c);
#endif