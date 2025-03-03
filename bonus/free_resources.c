/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_resources.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:44:03 by adegl-in          #+#    #+#             */
/*   Updated: 2025/02/28 18:14:00 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_grid(char **grid, int height)
{
	int	i;

	i = 0;
	while (i < height)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void	free_textures(t_game *game)
{
    int i;

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

void	free_all(t_game *game)
{
	free_grid(game->map.grid, game->map.height);
	free_textures(game);
	mlx_destroy_window(game->window.mlx_ptr, game->window.win_ptr);
	mlx_destroy_display(game->window.mlx_ptr);
	free(game->window.mlx_ptr);
}