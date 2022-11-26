#include <Ray.h>

double my_clamp(double num, double low, double high)
{
    if (num < low)
        return low;
    else if (num > high)
        return high;
    return num;
}

int rgb1(int r, int g, int b)
{
  int c;

  c = r;
  c = (c << 8) | g;
  c = (c << 8) | b;
  return c;
}

void write_color(t_color px_color, int samples, int x, int y)
{
     double r;
     double g;
     double b;
     char *out;
     double scl;

     scl = 1.0 / samples;

    r = px_color.x;
    g = px_color.y;
    b = px_color.z;

    r = sqrt(scl * r);
    g = sqrt(scl * g);
    b = sqrt(scl * b);

    int ri = (int)(256 * my_clamp(r, 0.0, 0.999));
    int gi = (int)(256 * my_clamp(g, 0.0, 0.999));
    int bi = (int)(256 * my_clamp(b, 0.0, 0.999));

    mlx_pixel_put(wn.mlx, wn.win, x, y, rgb1(ri, gi, bi));
}