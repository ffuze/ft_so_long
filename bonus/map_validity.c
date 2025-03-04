/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:39:07 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/04 16:39:08 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	find_player(t_game *game)
{
	int	y;
	int	x;

	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
		{
			if (game->map.grid[y][x] == 'P')
			{
				game->map.player_x = x;
				game->map.player_y = y;
			}
			else if (game->map.grid[y][x] == 'C')
				game->calcs.total_score++;
		}
	}
}

int	validate_elements(int p, int c, int e, int n)
{
	return (p == 1 && e == 1 && c >= 1 && n >= 1);
}

int	check_walls(char **map, int height, int width)
{
	int	i;

	if (!is_symmetric(map, height))
		return (0);
	i = -1;
	while (++i < width)
		if (map[0][i] != '1' || map[height - 1][i] != '1')
			return (0);
	i = -1;
	while (++i < height)
		if (map[i][0] != '1' || map[i][width - 1] != '1')
			return (0);
	return (1);
}

static int	check_map_integrity(char **map, int height, int width)
{
	int	p;
	int	c;
	int	e;
	int	n;
	int	i;

	p = 0;
	c = 0;
	e = 0;
	n = 0;
	i = -1;
	if (!check_walls(map, height, width))
		return (0);
	while (++i < height)
	{
		if (!count_characters(map[i], &p, &c, &e, &n))
			return (0);
	}
	if (!validate_elements(p, c, e, n))
		return (0);
	return (1);
}

int	is_map_valid(t_game *game, char **map, int height, int width)
{
	char	**map_copy;
	int		reachable_c;
	int		reachable_e;

	if (!check_map_integrity(map, height, width))
		return (0);
	map_copy = copy_map(map, height);
	if (!map_copy)
		return (0);
	reachable_c = 0;
	reachable_e = 0;
	find_player(game);
	flood_fill(map_copy, game->map.player_x, game->map.player_y,
		height, width, &reachable_c, &reachable_e);
	free_grid(map_copy, height);
	return (reachable_c == game->calcs.total_score && reachable_e == 1);
}
