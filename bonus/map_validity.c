/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:39:07 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/06 18:48:05 by adegl-in         ###   ########.fr       */
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

int	validate_elements(t_map_characters *characters)
{
	if (characters->p == 1 && characters->e == 1 && characters->c >= 1
		&& characters->n >= 1)
	{
		return (1);
	}
	return (0);
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
	t_map_characters	characters;
	int					i;

	characters.p = 0;
	characters.c = 0;
	characters.e = 0;
	characters.n = 0;
	i = -1;
	if (!check_walls(map, height, width))
		return (0);
	while (++i < height)
	{
		if (!count_characters(map[i], &characters))
			return (0);
	}
	if (!validate_elements(&characters))
		return (0);
	return (1);
}

int	is_map_valid(t_game *game, char **map, int height, int width)
{
	char				**map_copy;
	int					reachable_c;
	int					reachable_e;
	t_flood_fill_params	params;

	if (!check_map_integrity(map, height, width))
		return (0);
	map_copy = copy_map(map, height);
	if (!map_copy)
		return (0);
	reachable_c = 0;
	reachable_e = 0;
	find_player(game);
	params.map = map_copy;
	params.height = height;
	params.width = width;
	params.reachable_c = &reachable_c;
	params.reachable_e = &reachable_e;
	if (!flood_fill_check(game, params.map, &params))
	{
		free_grid(map_copy, height);
		return (0);
	}
	free_grid(map_copy, height);
	return (reachable_c == game->calcs.total_score && reachable_e == 1);
}
