/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:12:05 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/10 15:36:09 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	check_texture_existence(t_game *game)
{
	if (!game->textures.floor || !game->textures.wall
		|| !game->textures.collectible || !game->textures.exit
		|| !game->textures.enemy[0] || !game->textures.enemy[1]
		|| !game->textures.enemy[2] || !game->textures.enemy[3]
		|| !game->textures.player[0] || !game->textures.player[1]
		|| !game->textures.player[2] || !game->textures.player[3])
	{
		ft_printf("Errore nel caricamento di una o piu texture\n");
		exit(EXIT_FAILURE);
	}
}

static void	load_basic_textures(t_game *game, int *width, int *height)
{
	game->textures.floor = mlx_xpm_file_to_image(game->window.mlx_ptr,
			"./bonus/textures/floor.xpm", width, height);
	game->textures.wall = mlx_xpm_file_to_image(game->window.mlx_ptr,
			"./bonus/textures/wall.xpm", width, height);
	game->textures.collectible = mlx_xpm_file_to_image(game->window.mlx_ptr,
			"./bonus/textures/chest.xpm", width, height);
	game->textures.exit = mlx_xpm_file_to_image(game->window.mlx_ptr,
			"./bonus/textures/ladder.xpm", width, height);
}

static void	load_player_textures(t_game *game, int *width, int *height)
{
	game->textures.player[0] = mlx_xpm_file_to_image(game->window.mlx_ptr,
			"./bonus/textures/knight-right-1.xpm", width, height);
	game->textures.player[1] = mlx_xpm_file_to_image(game->window.mlx_ptr,
			"./bonus/textures/knight-right-2.xpm", width, height);
	game->textures.player[2] = mlx_xpm_file_to_image(game->window.mlx_ptr,
			"./bonus/textures/knight-right-3.xpm", width, height);
	game->textures.player[3] = mlx_xpm_file_to_image(game->window.mlx_ptr,
			"./bonus/textures/knight-right-4.xpm", width, height);
}

static void	load_enemy_textures(t_game *game, int *width, int *height)
{
	game->textures.enemy[0] = mlx_xpm_file_to_image(game->window.mlx_ptr,
			"./bonus/textures/skeleton-1.xpm", width, height);
	game->textures.enemy[1] = mlx_xpm_file_to_image(game->window.mlx_ptr,
			"./bonus/textures/skeleton-2.xpm", width, height);
	game->textures.enemy[2] = mlx_xpm_file_to_image(game->window.mlx_ptr,
			"./bonus/textures/skeleton-3.xpm", width, height);
	game->textures.enemy[3] = mlx_xpm_file_to_image(game->window.mlx_ptr,
			"./bonus/textures/skeleton-4.xpm", width, height);
}

void	load_textures(t_game *game)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	load_basic_textures(game, &width, &height);
	load_player_textures(game, &width, &height);
	load_enemy_textures(game, &width, &height);
	check_texture_existence(game);
	game->textures.sprite_index = 0;
}
