NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -I/opt/X11/include -g
MLX_DIR = ./minilibx-linux
MLX_LIB = $(MLX_DIR)/libmlx.a -L/opt/X11/lib -lX11 -lXext -lm

SRCS    = so_long.c \
		  main.c \
          graphics.c \
          move.c \
          utils.c \
          utils_supp.c \
          gnl/get_next_line.c \
          gnl/get_next_line_utils.c \
          printf/ft_printf.c \
          printf/ft_utils.c \
          printf/ft_utils_hex.c\
          find.c


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_LIB) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
