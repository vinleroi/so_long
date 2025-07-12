/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 10:03:29 by aahadji           #+#    #+#             */
/*   Updated: 2025/07/05 16:52:30 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static char	**init_tab(int height, int width)
{
	char	**temp;
	int		i;

	i = 0;
	temp = calloc(height, sizeof(char));
	if (!temp)
		ft_printf("Init tab error"); // free
	while (i < height)
	{
		temp = calloc(width, sizeof(char));
		if (!temp)
			ft_printf("Init tab error"); // free
	}
	return (temp);
}

char	**create_map(char *file)
{
	t_map	map;
	int		i;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	count_map_size(fd, &map);
	close(fd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	map.map = init_tab(map.height, map.width);
	if (!map.map)
		return (NULL);
	i = 0;
	while (i < map.height)
	{
		map.map[i] = get_next_line(fd);
		if (!map.map[i])
		{
			free_tab(map.map, i); // Free toutes les lignes déjà lues
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
		res->max_collectibles++;
	if (map[y][x] == 'E')
		res->exit_found = 1;
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
			if (i == 0 || i == max_height || j == 0 || j == max_width)
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

	map_temp = copy_map(map->map, map->width, map->height);
	res.max_collectibles = 0;
	if (check_wall(map->map, map->width, map->height) == -1)
		return (-1);
	flood_fill(map_temp, map->player.x, map->player.y, &res);
	free(map_temp);
	if (res.max_collectibles != map->collectible.max_collectibles)
		return (-1);
	else
		return (1);
}
