#include <Ray.h>

t_obj  *sph(t_vec3d origin, double rad)
{
    t_obj *rtn;

    rtn = ft_calloc(1, sizeof(t_obj));
    rtn->type = 1;
    rtn->sph.origin = origin;
    rtn->sph.rad = rad;
    return rtn;
}


t_obj *pln(t_vec3d origin, t_vec3d normal)
{
    t_obj *rtn;

    rtn = ft_calloc(1, sizeof(t_obj));
    rtn->type = 2;
    rtn->pln.origin = origin;
    rtn->pln.normal = normal;
    rtn->pln.size = 2;
    return rtn;
}