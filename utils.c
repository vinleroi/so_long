/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:10:53 by aahadji           #+#    #+#             */
/*   Updated: 2025/07/13 15:09:12 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_map_size(t_map *map)
{
	int	i;
	int	width;

	if (!map || !map->map || !map->map[0])
		error_exit("Map is empty or NULL.");
	width = ft_strlen(map->map[0]);
	map->width = width;
	map->height = 0;
	i = 0;
	while (map->map[i])
	{
		if ((int)ft_strlen(map->map[i]) != width)
			error_exit("Map is not rectangular.");
		map->height++;
		i++;
	}
}

void	error_exit(char *msg)
{
	ft_putstr_fd(msg, 2);
	exit(EXIT_FAILURE);
}

size_t	ft_strlen(char *tab)
{
	size_t	res;

	res = 0;
	while (tab[res])
		res++;
	return (res);
}

t_point	find_player(char **map)
{
	t_point	p;
	int		i;
	int		j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'P')
			{
				p.x = j;
				p.y = i;
				return (p);
			}
			j++;
		}
		i++;
	}
	p.x = -1;
	p.y = -1;
	return (p);
}

int	file_exists(char *path)
{
	int fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	close(fd);
	return (1);
}