/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:03:29 by aahadji           #+#    #+#             */
/*   Updated: 2025/07/13 16:30:03 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**init_tab(int height)
{
	char	**temp;

	temp = (char **)ft_calloc(height + 1, sizeof(char *));
	if (!temp)
		error_exit("Init_tab error");
	return (temp);
}

char	**create_map(char *file, int height)
{
	t_map	map;
	int		i;
	int		fd;

	if (file_exists(file) == 0)
		error_exit("File does not exist.");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map.map = init_tab(height);
	if (!map.map)
	{
		close(fd);
		error_exit("Error allocating memory for map.");
	}
	i = 0;
	while (i < map.height)
	{
		map.map[i] = get_next_line(fd);
		ft_printf("line %d: %s", i, map.map[i]);
		if (!map.map[i])
		{
			free_tab(map.map, i);
			close(fd);
			return (NULL);
		}
		i++;
	}
	map.map[i] = NULL;
	close(fd);
	return (map.map);
}

void	flood_fill(char **map, int x, int y, t_utils *res)
{
	if (map[y][x] == '1' || map[y][x] == 'V')
		return ;
	if (map[y][x] == 'C')
	{
		res->max_collectibles++;
		ft_printf("Collectible found at (%d, %d)\n", x, y);
	}
	if (map[y][x] == 'E')
	{
		res->exit_found = 1;
		ft_printf("exit found at (%d, %d)\n", x, y);
	}
	map[y][x] = 'V';
	flood_fill(map, x + 1, y, res);
	flood_fill(map, x - 1, y, res);
	flood_fill(map, x, y + 1, res);
	flood_fill(map, x, y - 1, res);
}

int	check_wall(char **map, int max_width, int max_height)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (i == 0 || i == max_height - 1 || j == 0 || j == max_width - 1)
			{
				if (map[i][j] != '1')
					return (-1);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	check_map(t_map *map)
{
	t_utils	res;
	char	**map_temp;

	map_temp = copy_map(map->map, map->height);
	if (!map_temp)
	{
		ft_printf("Error: Failed to copy map.\n");
		return (-1);
	}
	res.max_collectibles = 0;
	res.max_collectibles = 0;
	res.collectibles_found = 0;
	res.exit_found = 0;
	res.player_start = 0;
	if (check_wall(map->map, map->width, map->height) == -1)
	{
		free_tab(map_temp, map->height);
		error_exit("Error: Map is not surrounded by walls.");
	}
	flood_fill(map_temp, map->player.x, map->player.y, &res);
	free_tab(map_temp, map->height);
	if (res.max_collectibles != map->collectible.max_collectibles
		|| res.exit_found == 0)
		return (-1);
	else
		return (1);
}
