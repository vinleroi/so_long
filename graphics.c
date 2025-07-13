/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 23:39:23 by aahadji           #+#    #+#             */
/*   Updated: 2025/07/13 12:23:02 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	free_images(t_game *game)
{
	if (game->wall.ptr)
		mlx_destroy_image(game->mlx, game->wall.ptr);
	if (game->floor.ptr)
		mlx_destroy_image(game->mlx, game->floor.ptr);
	if (game->player.ptr)
		mlx_destroy_image(game->mlx, game->player.ptr);
	if (game->exit.ptr)
		mlx_destroy_image(game->mlx, game->exit.ptr);
	if (game->collect.ptr)
		mlx_destroy_image(game->mlx, game->collect.ptr);
}

void	render_map(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (game->map->map[x])
	{
		y = 0;
		while (game->map->map[x][y])
		{
			if (game->map->map[x][y] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall.ptr, y
					* TILE, x * TILE);
			else if (game->map->map[x][y] == '0')
				mlx_put_image_to_window(game->mlx, game->win, game->floor.ptr, y
					* TILE, x * TILE);
			else if (game->map->map[x][y] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->player.ptr,
					y * TILE, x * TILE);
			else if (game->map->map[x][y] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit.ptr, y
					* TILE, x * TILE);
			else if (game->map->map[x][y] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->collect.ptr,
					y * TILE, x * TILE);
			y++;
		}
		x++;
	}
}

int	handle_key(int key, t_game *game)
{
	if (key == XK_Escape)
	{
		close_window(game);
	}
	else if (key == XK_w)
		movePlayer(game->map, (t_point){0, -1});
	else if (key == XK_s)
		movePlayer(game->map, (t_point){0, 1});
	else if (key == XK_a)
		movePlayer(game->map, (t_point){-1, 0});
	else if (key == XK_d)
		movePlayer(game->map, (t_point){1, 0});
	return (0);
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	free_images(game);
	free_tab(game->map->map, game->map->height);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
	return (0);
}
