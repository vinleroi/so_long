/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 20:59:13 by aahadji           #+#    #+#             */
/*   Updated: 2025/07/13 16:44:35 by aahadji          ###   ########.fr       */
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

static void	graphics(t_game game)
{
	game.mlx = mlx_init();
	if (!game.mlx)
	{
		ft_printf("Error initializing MLX.\n");
		exit(EXIT_FAILURE);
	}
	game.win = mlx_new_window(game.mlx, 800, 600, "So Long");
	if (!game.win)
	{
		ft_printf("Error creating window.\n");
		exit(EXIT_FAILURE);
	}
	load_sprites(&game);
	render_map(&game);
	mlx_key_hook(game.win, handle_key, &game);
	mlx_hook(game.win, 17, 0, close_window, &game);
	mlx_loop(game.mlx);
}

static void	init_game(t_map *map)
{
	find_collectibles(map);
	find_exit(map);
	find_player(map->map);
	if (map->collectible.max_collectibles == 0)
	{
		free_tab(map->map, map->height);
		error_exit("Error: No collectibles found in the map.");
	}
	if (map->collectible.exit_found == 0 || map->collectible.exit_found > 1)
	{
		free_tab(map->map, map->height);
		error_exit("Error: No exit found or to much in the map.");
	}
	if (find_player(map->map).x == -1 || find_player(map->map).y == -1)
	{
		free_tab(map->map, map->height);
		error_exit("Invalid player position.");
	}
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;

	if (argc != 2 || !ft_strncmp(argv[1]))
		error_exit("Usage: ./so_long <map_file.ber>\n");
	map.height = find_map_height(argv[1]);
	map.map = create_map(argv[1], map.height);
	if (is_map_valid(map.map) == -1)
	{
		ft_printf("Error: Could not create map from file. main\n");
		return (1);
	}
	init_game(&map);
	if (check_map(&map) == -1)
	{
		ft_printf("Error: Invalid map.\n");
		free_tab(map.map, map.height);
		return (1);
	}
	game.map = &map;
	game.map->move_count = 0;
	graphics(game);
	return (0);
}
