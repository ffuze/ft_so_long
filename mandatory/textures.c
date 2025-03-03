/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:53:12 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/03 14:53:22 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_textures(t_game *game)
{
	int	width;
	int	height;

	width = 0;
	height = 0;
	game->textures.floor = mlx_xpm_file_to_image(
			game->window.mlx_ptr, "./mandatory/textures/floor.xpm",
			&width, &height);
	game->textures.wall = mlx_xpm_file_to_image(
			game->window.mlx_ptr, "./mandatory/textures/wall.xpm",
			&width, &height);
	game->textures.collectible = mlx_xpm_file_to_image(
			game->window.mlx_ptr, "./mandatory/textures/chest.xpm",
			&width, &height);
	game->textures.exit = mlx_xpm_file_to_image(
			game->window.mlx_ptr, "./mandatory/textures/ladder.xpm",
			&width, &height);
	game->textures.player = mlx_xpm_file_to_image(
			game->window.mlx_ptr, "./mandatory/textures/knight.xpm",
			&width, &height);
}
