NAME		= a.out
CC			= gcc
RM			= rm -rf
INC			= ./Vectors
INCTH		= ./Vecimprove
INCS		= ./Raytrace
INCT		= ./Scene
MYINC		= ./includes/
INCLIB		= ./libft/
LIBFT		= ./libft/libft.a
SRC			= $(wildcard *.c) $(wildcard ./Vecimprove/*.c) $(wildcard ./Vectors/*.c) $(wildcard ./Raytrace/*.c) $(wildcard ./Scene/*.c)
OBJS		= $(SRC:.c=.o)


ifeq ($(shell uname -s), Linux)
	MLX = lib/minilibx_linux
	MLXLIB = $(MLX)/libmlx_Linux.a
	MLX_FLAGS = -lXext -lX11 -lm -lz $(MLXLIB)
else
	MLX = lib/minilibx_macos
	MLXLIB = $(MLX)/libmlx.a
	MLX_FLAGS = -framework OpenGL -framework AppKit $(MLXLIB)
endif

all : $(MLXLIB) $(LIBFT) $(NAME)

$(LIBFT):
	make bonus -C ./libft

$(MLXLIB):
	make -C $(MLX)

%.o: %.c
	$(CC) -I$(INC) -I$(INCS) -I$(INCT) -I$(INCTH) -I$(MLX) -I$(MYINC) -I$(INCLIB) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) -I$(INC) -I$(INCS) -I$(INCT) -I$(INCTH) -I$(MYINC) -I$(INCLIB) $(MLX_FLAGS) -o $(NAME) $(LIBFT)

clean: 
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

ffclean: fclean
	make fclean -C ./libft

fffclean: ffclean
	make clean -C $(MLX)

re: ffclean all

.PHONY: all clean fclean re run
