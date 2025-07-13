/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_supp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:34:54 by aahadji           #+#    #+#             */
/*   Updated: 2025/07/13 16:43:02 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copy_map(char **map, int height)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (height + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy[i] = ft_strdup(map[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

/**
 * probably an error occure here with the J that dont go to high
 */
void	free_tab(char **map, int i)
{
	int	j;

	j = 0;
	while (j < i && map[j])
	{
		free(map[j]);
		j++;
	}
	free(map);
}

int	ft_strncmp(char *s1)
{
	size_t	i;
	int		j;
	char	*s2;

	s2 = ".ber";
	i = ft_strlen(s1);
	if (i < 4)
		return (-1);
	i -= 4;
	j = 0;
	while (s1[i])
	{
		if (s1[i] != s2[j])
			return (-1);
		i++;
	}
	return (1);
}

int	is_map_valid(char **map)
{
	int y;
	int x;

	if (!map)
		return (0);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (!is_valid_char(map[y][x]))
				return (0);
			x++;
		}
		y++;
	}
	return (1);
}