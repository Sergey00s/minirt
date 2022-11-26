#include <Ray.h>


static t_vec3d lowerleft(t_cam self)
{
    t_vec3d res;
    t_vec3d v1;

    v1 = self.vertical;
    v1 = vec_div(v1, 2.0);
    v1 = minus(v1);
    res = vec_plus(v1, vec3d(0, 0, -self.focal_len));
    v1 = vec_div(self.horizontal, 2.0);
    v1 = minus(v1);
    res = vec_plus(v1, res);
    res = vec_plus(self.origin, res);
    return  res;
}

t_cam s_cam(double vp_h, double focal_len, t_screen screen)
{
    t_cam rtn;

    rtn.focal_len = focal_len;
    rtn.vp_h = vp_h;
    rtn.vp_w = screen.a_ratio * vp_h;
    rtn.origin = vec3d(0, 0, 0);
    rtn.horizontal = vec3d(rtn.vp_w, 0, 0);
    rtn.vertical = vec3d(0, vp_h, 0);
    rtn.lower_left_corner = lowerleft(rtn);
    return rtn;
}