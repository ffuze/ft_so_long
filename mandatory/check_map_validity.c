/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:51:18 by adegl-in          #+#    #+#             */
/*   Updated: 2025/02/18 17:49:57 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

// flood fill to check map validity
void flood_fill(char **grid, int x, int y, int height, int width, char target, char replace)
{
    // check bounds and stop if out of bounds or not the target character
    if (x < 0 || x >= width || y < 0 || y >= height || grid[y][x] != target)
        return;

    // replace current position with a visited marker
    grid[y][x] = replace;

    flood_fill(grid, x + 1, y, height, width, target, replace); // right
    flood_fill(grid, x - 1, y, height, width, target, replace); // left
    flood_fill(grid, x, y + 1, height, width, target, replace); // down
    flood_fill(grid, x, y - 1, height, width, target, replace); // up
}

int is_map_valid(char **grid, int height, int width)
{
    int player_x = 0, player_y = 0;
    int exit_x = 0, exit_y = 0;
    int i = 0, j = 0;
	
    while (i < height)
	{
        j = 0;
        while (j < width)
		{
            if (grid[i][j] == 'P')
			{
                player_x = j;
                player_y = i;
            }
            if (grid[i][j] == 'E')
			{
                exit_x = j;
                exit_y = i;
            }
            j++;
        }
        i++;
    }

    // start flood fill starting from the player
    flood_fill(grid, player_x, player_y, height, width, '0', 'G');  // 'G' marks reachable areas

    // check if the exit and all collectibles are reachable
    if (grid[exit_y][exit_x] != 'G')
	{
        printf("Exit is unreachable\n");
        return 0;
    }

    // check if all collectibles are reachable
    i = 0;
    while (i < height)
	{
        j = 0;
        while (j < width)
		{
            if (grid[i][j] == 'C' && grid[i][j] != 'G')
			{
                printf("Collectible at (%d, %d) is unreachable\n", j, i);
                return 0;
            }
            j++;
        }
        i++;
    }

    return 1;
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
