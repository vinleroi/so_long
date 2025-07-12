/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_supp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:34:54 by aahadji           #+#    #+#             */
/*   Updated: 2025/07/12 12:22:02 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**copy_map(char **map, int width, int height)
{
	char	**temp;
	int		i;
	int		j;

	i = 0;
	temp = (char **)malloc(width * sizeof(char *));
	if (!temp)
		return (NULL);
	while (temp[i])
	{
		temp[i] = (char *)malloc(height * sizeof(char));
		if (!temp)
			return (NULL);
		i++;
	}
	i = 0;
	j = 0;
	while (temp[i])
	{
		while (temp[j])
		{
			temp[i][j] = map[i][j];
			j++;
		}
		j = 0;
		i++;
	}
	return (temp);
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}