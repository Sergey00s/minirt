#ifndef RAY_H
# define RAY_H

# define PI 3.14159
# define IMAX 2147483647
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




# include <unistd.h>
# include <stdio.h>
# include <math.h>
# include <string.h>
# include <float.h>
# include <mlx.h>

# include <libft.h>
# include <Vec.h>
# include <color.h>
# include <Raytrace.h>
# include <Obj.h>
# include <Cam.h>
# include <window.h>
# include <Utils.h>

#endif
