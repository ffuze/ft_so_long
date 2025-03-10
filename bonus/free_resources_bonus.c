/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:44:03 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/10 15:47:31 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

void	free_invalid_bonus(t_game *game)
{
	if (game->map.grid)
		free_grid_bonus(game->map.grid, game->map.height);
	if (game->window.mlx_ptr)
	{
		mlx_destroy_display(game->window.mlx_ptr);
		free(game->window.mlx_ptr);
	}
	game->map.grid = NULL;
	game->window.win_ptr = NULL;
	game->window.mlx_ptr = NULL;
}

void	free_grid_bonus(char **grid, int height)
{
	int	i;

	i = 0;
	if (!grid)
		return ;
	while (i < height)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void	free_textures_bonus(t_game *game)
{
	int	i;

	i = -1;
	mlx_destroy_image(game->window.mlx_ptr, game->textures.collectible);
	mlx_destroy_image(game->window.mlx_ptr, game->textures.exit);
	mlx_destroy_image(game->window.mlx_ptr, game->textures.floor);
	mlx_destroy_image(game->window.mlx_ptr, game->textures.wall);
	while (++i < SPRITE_COUNT)
	{
		mlx_destroy_image(game->window.mlx_ptr, game->textures.enemy[i]);
		mlx_destroy_image(game->window.mlx_ptr, game->textures.player[i]);
	}
}

void	free_all_bonus(t_game *game)
{
	if (game->map.grid)
		free_grid_bonus(game->map.grid, game->map.height);
	free_textures_bonus(game);
	if (game->window.win_ptr)
		mlx_destroy_window(game->window.mlx_ptr, game->window.win_ptr);
	if (game->window.mlx_ptr)
	{
		mlx_destroy_display(game->window.mlx_ptr);
		free(game->window.mlx_ptr);
	}
}
