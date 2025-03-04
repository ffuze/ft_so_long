/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:06:49 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/04 19:06:50 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(char **map, int x, int y, int height, int width,
		int *reachable_c, int *reachable_e)
{
	if (x < 0 || x >= width || y < 0 || y >= height
		|| map[y][x] == '1' || map[y][x] == 'F')
		return ;
	if (map[y][x] == 'C')
		(*reachable_c)++;
	else if (map[y][x] == 'E')
		(*reachable_e)++;
	map[y][x] = 'F';
	flood_fill(map, x + 1, y, height, width, reachable_c, reachable_e);
	flood_fill(map, x - 1, y, height, width, reachable_c, reachable_e);
	flood_fill(map, x, y + 1, height, width, reachable_c, reachable_e);
	flood_fill(map, x, y - 1, height, width, reachable_c, reachable_e);
}

int	flood_fill_check(t_game *game, char **map_copy, int height, int width, int c)
{
	int	reachable_c;
	int	reachable_e;

	reachable_c = 0;
	reachable_e = 0;
	flood_fill(map_copy, game->map.player_x, game->map.player_y,
		height, width, &reachable_c, &reachable_e);
	return (reachable_c == c && reachable_e == 1);
}
