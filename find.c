/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:04:58 by aahadji           #+#    #+#             */
/*   Updated: 2025/07/13 17:49:05 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <unistd.h>

static void	print_map(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (i <= 4)
	{
		j = 0;
		while (j <= 6)
		{
			write(1, &map[i][j], 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

void	find_collectibles(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	map->collectible.max_collectibles = 0;
	print_map(map->map);
	while (x < map->height && map->map[x])
	{
		y = 0;
		while (map->map[x][y])
		{
			ft_printf("%c", map->map[x][y]);
			if (map->map[x][y] == 'C')
			{
				map->collectible.max_collectibles++;
			}
			y++;
		}
		x++;
	}
}

void	find_exit(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	map->collectible.exit_found = 0;
	print_map(map->map);
	while (x < map->height && map->map[x])
	{
		y = 0;
		while (map->map[x][y])
		{
			if (map->map[x][y] == 'E')
			{
				map->collectible.exit_found++;
			}
			y++;
		}
		x++;
	}
}

char	*ft_strdup(char *s)
{
	char	*dup;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

int	find_map_height(char *file)
{
	int		fd;
	int		height;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (-1);
	height = 0;
	while ((line = get_next_line(fd)))
	{
		if (line[0] != '\n' && line[0] != '\0')
			height++;
		free(line);
	}
	close(fd);
	return (height);
}

int	is_valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'P' || c == 'E' || c == 'C');
}
