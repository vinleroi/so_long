/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 17:52:08 by aahadji           #+#    #+#             */
/*   Updated: 2025/07/12 13:11:36 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "gnl/get_next_line.h"
# include "minilibx-linux/mlx.h"
# include "printf/ft_printf.h"
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
}			t_map;

typedef struct s_game
{
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
char		**create_map(char *file);
int			check_position_start(char **map);
void		count_map_size(int fd, t_map *map);
void		error_exit(char *msg);
int			check_wall(char **map, int max_width, int max_height);

/**
 * utils
 */
size_t		ft_strlen(char *tab);
t_point		find_player(char **map);
void		free_tab(char **map, int i);

int			movePlayer(t_map *map, t_point direction);
char		**copy_map(char **map, int width, int height);
int			isValidMove(t_map *map, int x, int y);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif
