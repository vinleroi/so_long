/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 21:10:53 by aahadji           #+#    #+#             */
/*   Updated: 2025/07/04 17:29:05 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	count_map_size(int fd, t_map *map)
{
	char	*line;

	if (fd < 0)
		error_exit("Invalid file descriptor.");
	line = get_next_line(fd);
	if (!line)
	{
		free(line);
		error_exit("Empty file.");
	}
	map->width = ft_strlen(line);
	free(line);
	while ((line = get_next_line(fd)))
	{
		if ((int)ft_strlen(line) != map->width)
		{
			free(line);
			error_exit("Map not rectangular.");
		}
		map->height++;
		free(line);
	}
	close(fd);
}

void	error_exit(char *msg)
{
	ft_printf(msg);
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
