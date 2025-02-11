/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:51:18 by adegl-in          #+#    #+#             */
/*   Updated: 2025/02/11 10:58:57 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int	check_map_validity(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] != '0' && game->map.grid[i][j] != '1' && game->map.grid[i][j] != 'C' && game->map.grid[i][j] != 'E' && game->map.grid[i][j] != 'P')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_wall(t_game *game)
{
	int x;
	int y;
	int i;

	x = game->map.width;
	y = game->map.height;
	i = 0;
	while (i < x)
	{
		if (game->map.grid[0][i] != '1' || game->map.grid[y - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < y)
	{
		if (game->map.grid[i][0] != '1' || game->map.grid[i][x - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_char (t_game *game)
{
	int i;
	int j;
	int p;
	int e;
	int c;

	i = 0;
	p = 0;
	e = 0;
	c = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == 'P')
				p++;
			if (game->map.grid[i][j] == 'E')
				e++;
			if (game->map.grid[i][j] == 'C')
				c++;
			j++;
		}
		i++;
	}
	if (p != 1 || e != 1 || c < 1)
		return (0);
	return (1);
}
