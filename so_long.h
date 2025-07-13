/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:52:08 by aahadji           #+#    #+#             */
/*   Updated: 2025/07/13 16:44:02 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# define TILE 64
# include "gnl/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include "printf/ft_printf.h"
# include <X11/keysym.h>
# include <fcntl.h>

typedef struct s_imgbis
{
	void	*ptr;
	int		w;
	int		h;
}			t_img;

typedef struct s_point
{
	int		x;
	int		y;
}			t_point;

typedef struct s_utils
{
	int		max_collectibles;
	int		collectibles_found;
	int		exit_found;
	int		player_start;
}			t_utils;

typedef struct s_map
{
	char	**map;
	t_point	player;
	int		width;
	int		height;
	t_utils	collectible;
	int		move_count;
}			t_map;

typedef struct s_game
{
	t_map	*map;
	void	*mlx;
	void	*win;
	t_img	wall;
	t_img	floor;
	t_img	player;
	t_img	exit;
	t_img	collect;
}			t_game;

/**
 * pour la map
 */
char		**create_map(char *file, int height);
int			check_position_start(char **map);
void		count_map_size(t_map *map);
void		error_exit(char *msg);
int			check_wall(char **map, int max_width, int max_height);
int			check_map(t_map *map_data);

/**
 * utils
 */
size_t		ft_strlen(char *tab);
t_point		find_player(char **map);
void		free_tab(char **map, int i);

int			movePlayer(t_map *map, t_point direction);
char		**copy_map(char **map, int width);
int			isValidMove(t_map *map, int x, int y);
int			ft_strncmp(char *s1);

int			handle_key(int key, t_game *game);
int			close_window(t_game *game);
void		render_map(t_game *game);
int			file_exists(char *path);

void		find_collectibles(t_map *map);
void		find_exit(t_map *map);
char		*ft_strdup(char *s);

int			find_map_height(char *file);

int			is_valid_char(char c);
int			is_map_valid(char **map);

#endif
