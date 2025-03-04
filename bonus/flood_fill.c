/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:21:08 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/03 16:32:09 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(char **map, int x, int y, int height, int width,
		int *reachable_c, int *reachable_e)
{
	if (x < 0 || x >= width || y < 0 || y >= height
		|| map[y][x] == '1' || map[y][x] == 'F' || map[y][x] == 'N')
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

int	fill(char **map, int x, int y, int height, int width, int *reachable_c, int *reachable_e)
{
	flood_fill(map, x, y, height, width, reachable_c, reachable_e);
	return (1);
}
