#ifndef READOBJ_H
# define READOBJ_H


typedef struct s_arr
{
	char **arr;
	int size;
}			t_arr;


char *read_my_line(int fd);
#endif