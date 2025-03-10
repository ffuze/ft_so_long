/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_renderer_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:11:53 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/10 15:52:53 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	draw_tile(t_game *game, int i, int j)
{
	void	*texture;

	texture = NULL;
	mlx_put_image_to_window(game->window.mlx_ptr,
		game->window.win_ptr, game->textures.floor, j * 32, i * 32);
	if (game->map.grid[i][j] == '1')
		texture = game->textures.wall;
	else if (game->map.grid[i][j] == 'C')
		texture = game->textures.collectible;
	else if (game->map.grid[i][j] == 'E')
		texture = game->textures.exit;
	else if (game->map.grid[i][j] == 'P')
		texture = game->textures.player[game->textures.sprite_index];
	else if (game->map.grid[i][j] == 'N')
		texture = game->textures.enemy[game->textures.sprite_index];
	if (texture)
		mlx_put_image_to_window(game->window.mlx_ptr,
			game->window.win_ptr, texture, j * 32, i * 32);
}

void	draw_map_bonus(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (++j < game->map.width)
			draw_tile(game, i, j);
	}
}

void	print_map_bonus(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	ft_printf("\n");
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			ft_printf("%c", game->map.grid[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
