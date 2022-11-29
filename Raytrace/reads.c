#include <Ray.h>


t_arr *mk_arr()
{
	t_arr *arr;

	arr = malloc(sizeof(arr) * 1);
	arr->size = 0;
	arr->arr = ft_calloc((arr->size), (sizeof(char *)));
	return arr;
}

void append(t_arr *self, char *news)
{
	char **old;

	old = self->arr;
	self->arr = ft_calloc(self->size + 1, sizeof(char *));
	
	int i;

	i = 0;
	while (i < self->size)
	{
		self->arr[i] = old[i];
		i++;
	}
	self->arr[i] = news;
	self->size++;
	free(old);
}

char *alls(int fd)
{
	int i;
	int byte;
	char buf[2];
	char *all;
	char *temp;

	buf[1] = 0;
	i = 0;
	byte = 1;
	all = NULL;
	temp = NULL;
	while (byte > 0)
	{
		byte = read(fd, buf, 1);
		temp = all;
		all = ft_strjoin(all, buf);
		free(temp);
	}
	return all;
}

t_objdata read_my_line(int fd)
{
	char *all;
	char **lines;
	t_arr *obj;
	t_arr *face;
	t_objdata rtn;
	
	all = alls(fd);
	
	lines = ft_split(all, '\n');
	int i = 0;
	int j = 0;
	obj = mk_arr();
	face = mk_arr();

	while (lines[i])
	{
		if (lines[i][0] == 'v' && lines[i][1] == ' ')
			append(obj, lines[i] + 2);
		if (lines[i][0] == 'f' && lines[i][1] == ' ')
			append(face, lines[i] + 2);
		i++;
	}
	rtn.faces = face;
	rtn.vecs = obj;
	return rtn;
}

long	ft_atol(const char *str)
{
	long	rtn;
	long	isneg;

	rtn = 0;
	isneg = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		isneg -= (*str++ == '-') * 2;
	while (ft_isdigit(*str))
		rtn = *str++ - '0' + rtn * 10;
	return (rtn * isneg);
}

double atod(char *str)
{
	double result;
	char *right;

	right = ft_strchr(str, '.');
	ft_memmove(right, right + 1, ft_strlen(right));
	result = ft_atol(str);
	return result / 1000000;
}

t_vec3d makevec(char *a)
{
	char **each;
	double x;
	double b;
	double c;

	each = ft_split(a, ' ');

	x = atod(each[0]);
	b = atod(each[1]);
	c = atod(each[2]);
	free(each);
	return vec3d(x, b, c);
}

t_objmesh new_mesh(t_objdata data)
{
	int i;
	char **temp;
	char **temp2;
	t_objmesh mesh;

	i = 0;
	mesh.tris = ft_calloc(sizeof(t_tris), (data.faces->size + 1));
	mesh.size = data.faces->size;
	while (i < data.faces->size)
	{
		temp = ft_split(data.faces->arr[i], ' ');
		temp2 = ft_split(temp[0], '/');
		mesh.tris[i].a = makevec((data.vecs->arr)[ft_atoi(temp2[0]) - 1]);
		temp2 = ft_split(temp[1], '/');
		mesh.tris[i].b = makevec((data.vecs->arr)[ft_atoi(temp2[0]) - 1]);
		temp2 = ft_split(temp[2], '/');
		mesh.tris[i].c = makevec((data.vecs->arr)[ft_atoi(temp2[0]) - 1]);
		i++;
	}
	mesh.size =  data.faces->size;
	return mesh;	
}


t_mesh *import_obj(char *name, char *obj_name, t_vec3d color)
{
	t_mesh *rtn;
	int		fd;
	t_objmesh temp;

	rtn = malloc(sizeof(t_mesh) * 1);
	fd = open(name, O_RDONLY);
	temp = new_mesh(read_my_line(fd));
	rtn->tris = temp.tris;
	rtn->size = temp.size;
	return rtn;
}