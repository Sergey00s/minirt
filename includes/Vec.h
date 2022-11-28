#ifndef VEC_H
# define VEC_H

#define EPSILON 0.000001
#define CROSS(dest,v1,v2) \
          dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
          dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
          dest[2]=v1[0]*v2[1]-v1[1]*v2[0];
#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define SUB(dest,v1,v2) \
          dest[0]=v1[0]-v2[0]; \
          dest[1]=v1[1]-v2[1]; \
          dest[2]=v1[2]-v2[2]; 


typedef struct s_vec3d
{
    double x;
    double y;
    double z;
}              t_vec3d;

int tocall(t_ray ray, t_tris tris, double *value);
typedef t_vec3d t_color;
typedef t_vec3d t_point3d;
t_vec3d vec_div(t_vec3d v, double t);
t_vec3d vec_multiply(t_vec3d v1, t_vec3d v2);
t_vec3d vec_multiply_by_value(t_vec3d v1, double t);
t_vec3d vec3d(double x, double y, double z);
double dot_product(t_vec3d v1, t_vec3d v2);
t_vec3d vec_sub(t_vec3d v1, t_vec3d v2);
t_vec3d vec_minus(t_vec3d v1, t_vec3d v2);
t_vec3d vec_plus(t_vec3d v1, t_vec3d v2);
double lenght_squared(t_vec3d self);
double lenght(t_vec3d self);
t_vec3d unit_vector(t_vec3d v);
double  normalize(t_vec3d v1);
t_vec3d minus(t_vec3d self);
t_vec3d rand_unit_vec();
t_vec3d random_in_hemisphere(t_vec3d normal);
double	distance(t_vec3d p1, t_vec3d p2);
t_vec3d	normalize2(t_vec3d vect);

#endif
