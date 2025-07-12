/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:57:02 by aahadji           #+#    #+#             */
/*   Updated: 2025/07/05 15:36:14 by aahadji          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Moves the player in the specified direction.
 * @param map The game map containing the player's position and the map layout.
 * @param direction The direction to move the player (e.g., up, down, left,
	right).

	keycode = 122
keycode = 113
keycode = 115
keycode = 100
 */

int	movePlayer(t_map *map, t_point direction)
{
	int	x;
	int	y;

	x = map->player.x + direction.x;
	y = map->player.y + direction.y;
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	map->player.x = x;
	map->player.y = y;
	return (isValidMove(map, x, y));
}
int	isValidMove(t_map *map, int x, int y)
{
	char new_position = map->map[y][x];
	if (new_position == '1' || new_position == 'V')
		return (0);
	if (new_position == 'C')
	{
		map->collectible.collectibles_found++;
		return (2);
	}
	if (new_position == 'E')
		if (map->collectible.collectibles_found == map->collectible.max_collectibles)
			ft_printf("You win!\n");
	return (1);
}