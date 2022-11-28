#include <Ray.h>

t_vec3d vec3d(double x, double y, double z)
{
	t_vec3d v;
    
	v.x = x;
	v.y = y;
	v.z = z;
	return v;
}

t_vec3d vec_sub(t_vec3d v1, t_vec3d v2)
{
	t_vec3d rtn;

	rtn.x = v1.x - v2.x;
	rtn.y = v1.y - v2.y;
	rtn.z = v1.z - v2.z;
	return rtn;
}

double dot_product(t_vec3d v1, t_vec3d v2)
{
	return ((v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z));
}

t_vec3d cross_product(t_vec3d v1, t_vec3d v2)
{
	t_vec3d rtn;
	
	rtn.x = (v1.y * v2.z) - (v2.y * v1.z);
	rtn.y = (v1.z * v2.x) - (v1.x * v2.z);
	rtn.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (rtn);
}

t_vec3d vec_minus(t_vec3d v1, t_vec3d v2)
{
	t_vec3d rtn;

	rtn.x = v2.x - v1.x;
	rtn.y = v2.y - v1.y;
	rtn.z = v2.z - v1.z;
	
	return rtn;
}


t_vec3d vec_plus(t_vec3d v1, t_vec3d v2)
{
	t_vec3d rtn;

	rtn.x = v2.x + v1.x;
	rtn.y = v2.y + v1.y;
	rtn.z = v2.z + v1.z;
	return rtn;
}

t_vec3d minus(t_vec3d self)
{
	self.x = -1.0 * self.x;
	self.y = -1.0 * self.y;
	self.z = -1.0 * self.z;
	return self;
}

t_vec3d vec_div(t_vec3d v, double t)
{
	t_vec3d res;

	if (t == 0)
		return vec3d(0, 0, 0);
	res.x = v.x / t;
	res.y = v.y / t;
	res.z = v.z / t;
    return res;
}

t_vec3d vec_multiply(t_vec3d v1, t_vec3d v2)
{
	t_vec3d rtn;

	rtn.x = v2.x * v1.x;
	rtn.y = v2.y * v1.y;
	rtn.z = v2.z * v1.z;
	return rtn;
}

t_vec3d vec_multiply_by_value(t_vec3d v1, double t)
{
	t_vec3d rtn;

	rtn.x = v1.x * t;
	rtn.y = v1.y * t;
	rtn.z = v1.z * t;
	return rtn;
}

double vec_len(t_vec3d v1)
{
    int sum;
	sum = (v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z);
    return sqrt(sum);
}

double lenght_squared(t_vec3d self)
{
	double rtn;

	rtn = self.x * self.x;
	rtn += self.y * self.y;
	rtn += self.z * self.z;
	return rtn;
}

double lenght(t_vec3d self)
{
	double rtn;

	rtn = self.x * self.x;
	rtn += self.y * self.y;
	rtn += self.z * self.z;
	rtn = sqrt(rtn);
	return (rtn);
}

t_vec3d unit_vector(t_vec3d v)
{
	t_vec3d rtn;

	rtn = vec_div(v, lenght(v));
	return rtn;
}

double	distance(t_vec3d p1, t_vec3d p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2)));
}

t_vec3d	normalize(t_vec3d vect)
{
	double	length;

	length = distance(vec3d(0,0,0), vect);
	return (vec3d(vect.x / length, vect.y / length, vect.z / length));
}

t_tris tri(t_vec3d a, t_vec3d b, t_vec3d c)
{
	t_tris rtn;
	
	rtn.a = a;
	rtn.b = b;
	rtn.c = c;
	return rtn;
}
