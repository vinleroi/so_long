/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aahadji <aahadji@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 14:57:02 by aahadji           #+#    #+#             */
/*   Updated: 2025/07/13 11:48:51 by aahadji          ###   ########.fr       */
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
	int	check;

	x = map->player.x + direction.x;
	y = map->player.y + direction.y;
	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (0);
	check = isValidMove(map, x, y);
	if (check != 0 && check != 3)
	{
		map->player.x = x;
		map->player.y = y;
		map->map[map->player.y][map->player.x] = 'P';
		map->map[y][x] = '0';
		map->move_count++;
		ft_printf("Total moves: %d\n", x, y, map->move_count);
	}
	if (check == 3)
	{
		ft_printf("You win! ^^ Total moves: %d\n", map->move_count);
		exit(EXIT_SUCCESS);
	}
	return (isValidMove(map, x, y));
}
int	isValidMove(t_map *map, int x, int y)
{
	char new_position = map->map[y][x];
	if (new_position == '1')
		return (0);
	if (new_position == 'C')
	{
		map->collectible.collectibles_found++;
		return (2);
	}
	if (new_position == 'E')
		if (map->collectible.collectibles_found == map->collectible.max_collectibles)
			return (3);
	return (1);
}