/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 16:44:03 by adegl-in          #+#    #+#             */
/*   Updated: 2025/02/11 16:20:50 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

void	ft_free_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free (grid);
}

void	free_textures(t_game *game)
{
	mlx_destroy_image(game->window.mlx_ptr, game->textures.collectible);
	mlx_destroy_image(game->window.mlx_ptr, game->textures.enemy);
	mlx_destroy_image(game->window.mlx_ptr, game->textures.exit);
	mlx_destroy_image(game->window.mlx_ptr, game->textures.floor);
	mlx_destroy_image(game->window.mlx_ptr, game->textures.player);
	mlx_destroy_image(game->window.mlx_ptr, game->textures.wall);
}

void	free_everything(t_game *game)
{
	ft_free_maps(game->map);
	free_textures(game);
	if (game->window.win_ptr)
		mlx_destroy_window(game->window.mlx_ptr, game->window.win_ptr);
	if (game->window.mlx_ptr)
	{
		mlx_destroy_display(game->window.mlx_ptr);
		free(game->window.mlx_ptr);
	}
}