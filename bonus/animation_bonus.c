/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:12:40 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/10 15:49:08 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static int	find_sprites_to_animate(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (++j < game->map.width)
		{
			if (game->map.grid[i][j] == 'N')
				mlx_put_image_to_window(game->window.mlx_ptr,
					game->window.win_ptr, game->textures.enemy[
					game->textures.sprite_index], j * 32, i * 32);
			if (game->map.grid[i][j] == 'P')
				mlx_put_image_to_window(game->window.mlx_ptr,
					game->window.win_ptr, game->textures.player[
					game->textures.sprite_index], j * 32, i * 32);
		}
	}
	return (0);
}

static int	print_sprites(t_game *game)
{
	static int	frame_counter = 0;

	if (frame_counter++ % 2000 == 0)
		game->textures.sprite_index
			= (game->textures.sprite_index + 1) % SPRITE_COUNT;
	find_sprites_to_animate(game);
	return (0);
}

void	display_score(t_game *game)
{
	char	*moves_str;
	char	*score_text;

	mlx_set_font(game->window.mlx_ptr, game->window.win_ptr, "8x16romankana");
	moves_str = ft_itoa(game->calcs.moves);
	score_text = ft_strjoin("Mosse: ", moves_str);
	mlx_string_put(game->window.mlx_ptr, game->window.win_ptr,
		game->map.text_x, game->map.text_y, 0xFFFFFF, score_text);
	free(moves_str);
	free(score_text);
}

int	update_and_animate(t_game *game)
{
	print_sprites(game);
	display_score(game);
	return (0);
}
