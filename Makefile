NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Imlx -I/usr/include

MLX_DIR = ./minilibx-linux
MLX_LIB = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

SRCS = so_long.c \
	   main.c \
	   graphics.c \
	   move.c \
	   utils.c \
	   utils_supp.c \
	   gnl/get_next_line.c \
	   gnl/get_next_line_utils.c \
	   printf/ft_printf.c \
	   printf/ft_utils.c \
	   printf/ft_utils_hex.c \
	   find.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) -o $(NAME)

clean:
	rm -f $(OBJS)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(MLX_DIR)

re: fclean all

run: all
	./$(NAME) map/map.ber
