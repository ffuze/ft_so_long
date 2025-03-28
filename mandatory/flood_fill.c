/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 19:06:49 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/20 15:04:03 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	flood_fill(t_flood_fill_params *found_params, int x, int y)
{
	if (x < 0 || x >= found_params->width || y < 0 || y >= found_params->height
		|| found_params->map[y][x] == '1' || found_params->map[y][x] == 'F')
		return ;
	if (found_params->map[y][x] == 'C')
		(*found_params->reachable_c)++;
	else if (found_params->map[y][x] == 'E')
		(*found_params->reachable_e)++;
	found_params->map[y][x] = 'F';
	flood_fill(found_params, x + 1, y);
	flood_fill(found_params, x - 1, y);
	flood_fill(found_params, x, y + 1);
	flood_fill(found_params, x, y - 1);
}

int	flood_fill_check(t_game *game, char **map_copy,
	t_flood_fill_params *found_params)
{
	t_flood_fill_params	init_params;

	init_params.map = map_copy;
	init_params.height = found_params->height;
	init_params.width = found_params->width;
	init_params.reachable_c = found_params->reachable_c;
	init_params.reachable_e = found_params->reachable_e;
	flood_fill(&init_params, game->map.player_x, game->map.player_y);
	if (!(init_params.reachable_c == found_params->reachable_c
			&& *found_params->reachable_e == 1))
	{
		return (0);
	}
	return (1);
}
