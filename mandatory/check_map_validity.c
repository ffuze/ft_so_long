/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:51:18 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/03 14:41:02 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_strlen_no_newline(char *str)
{
	int len = 0;

	while (str[len] && str[len] != '\n')
		len++;
	return (len);
}
static int	is_symmetric(char **map, int height)
{
	int i, width, widthf;

	if (!map || !map[0])
		return (0);
	widthf = ft_strlen_no_newline(map[0]);
	i = 0;
	while (i < height)
	{
		width = (int)ft_strlen_no_newline(map[i]);
		if (width != widthf)
			return (0);
		i++;
	}
	return (1);
}

int	check_walls(char **map, int height, int width)
{
	int i;

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

void	find_player(t_game *game)
{
	int y, x;
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

int	validate_elements(int p, int c, int e)
{
	return (p == 1 && e == 1 && c >= 1);
}

int	count_characters(char *str, int *p, int *c, int *e)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1')
		{
			i++;
			continue;
		}
		else if (str[i] == 'P')
			(*p)++;
		else if (str[i] == 'C')
			(*c)++;
		else if (str[i] == 'E')
			(*e)++;
		if (str[i] != 'C' && str[i] != 'P' && str[i] != 'E'
			&& str[i] != '1' && str[i] != '0' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

void	flood_fill(char **map, int x, int y, int height, int width, int *reachable_c, int *reachable_e)
{
	if (x < 0 || x >= width || y < 0 || y >= height || map[y][x] == '1' || map[y][x] == 'F')
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

int	is_map_valid(t_game *game, char **map, int height, int width)
{
	int p;
	int c;
	int e;
	int i;
	char **map_copy;
	int reachable_c = 0, reachable_e = 0;

	p = 0;
	c = 0;
	e = 0;
	i = -1;
	while (++i < height)
	{
		if (!count_characters(map[i], &p, &c, &e))
			return (0);
	}
	if (!check_walls(map, height, width) || !validate_elements(p, c, e))
		return (0);
	map_copy = malloc(height * sizeof(char *));
	if (!map_copy)
		return (0);
	i = 0;
	while (i < height)
	{
		map_copy[i] = ft_strdup(map[i]);
		if (!map_copy[i])
        {
            while (--i >= 0)
                free(map_copy[i]);
            free(map_copy);
            return (0);
        }
		i++;
	}
	find_player(game);
	flood_fill(map_copy, game->map.player_x, game->map.player_y, height, width, &reachable_c, &reachable_e);
	free_grid(map_copy, height);
	if (reachable_c != c || reachable_e != 1)
		return (0);
	return (1);
}
