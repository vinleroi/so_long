/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:59:13 by aahadji           #+#    #+#             */
/*   Updated: 2025/07/12 12:43:34 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define TILE_SIZE 64

void	load_sprites(t_game *game)
{
	game->wall.ptr = mlx_xpm_file_to_image(game->mlx, "sprites/wall.xpm",
			&game->wall.w, &game->wall.h);
	game->floor.ptr = mlx_xpm_file_to_image(game->mlx, "sprites/floor.xpm",
			&game->floor.w, &game->floor.h);
	game->player.ptr = mlx_xpm_file_to_image(game->mlx, "sprites/player.xpm",
			&game->player.w, &game->player.h);
	game->exit.ptr = mlx_xpm_file_to_image(game->mlx, "sprites/exit.xpm",
			&game->exit.w, &game->exit.h);
	game->collect.ptr = mlx_xpm_file_to_image(game->mlx,
			"sprites/collectible.xpm", &game->collect.w, &game->collect.h);
}

void	render_map(t_game *game)
{
	// Exemple basique : affiche 3x3 tiles
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 3; x++)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->floor.ptr, x
				* TILE_SIZE, y * TILE_SIZE);
			mlx_put_image_to_window(game->mlx, game->win, game->wall.ptr, x
				* TILE_SIZE, y * TILE_SIZE);
		}
	}
}
static int	key_hook(int keycode)
{
	ft_printf("keycode = %d\n", keycode);
	// ex: si w
	if (keycode == 119)
		ft_printf("W pressed!\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;

	if (argc != 2 || !ft_strcmp(argv[1], ".ber", ft_strlen(argv[1])))
	{
		ft_printf("Usage: ./so_long <map_file.ber>\n");
		return (1);
	}
	if (!(map.map = create_map(argv[1])))
	{
		ft_printf("Error: Invalid map file.\n");
		return (1);
	}
	game.mlx = mlx_init();
	game.win = mlx_new_window(game.mlx, 640, 480, "So Long");
	load_sprites(&game);
	mlx_hook(game.win, 2, 1L << 0, key_hook, &game);
	render_map(&game);
	mlx_loop(game.mlx);
	return (0); // mais ton putain de truc . ber enculé
}
