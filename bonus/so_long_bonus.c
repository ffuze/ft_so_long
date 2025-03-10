/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:48:49 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/10 15:47:04 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

int	on_destroy(t_game *game)
{
	free_all_bonus(game);
	exit(0);
}

int	on_keypress(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
	{
		ft_printf("WASTED");
		on_destroy(game);
		exit(0);
	}
	else if (keysym == XK_w)
		move_player_bonus(game, game->map.player_x, game->map.player_y - 1);
	else if (keysym == XK_a)
		move_player_bonus(game, game->map.player_x - 1, game->map.player_y);
	else if (keysym == XK_s)
		move_player_bonus(game, game->map.player_x, game->map.player_y + 1);
	else if (keysym == XK_d)
		move_player_bonus(game, game->map.player_x + 1, game->map.player_y);
	return (0);
}

void	call_hooks(t_game game)
{
	mlx_loop_hook(game.window.mlx_ptr, update_and_animate, &game);
	mlx_hook(game.window.win_ptr, 2, 1L << 0, &on_keypress, &game);
	mlx_hook(game.window.win_ptr, DestroyNotify, StructureNotifyMask,
		&on_destroy, &game);
	mlx_loop(game.window.mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (0);
	game.window.mlx_ptr = mlx_init();
	if (!game.window.mlx_ptr)
		return (0);
	load_map_bonus(&game, argv[1]);
	if (!is_map_valid(&game, game.map.grid, game.map.height, game.map.width))
	{
		ft_printf("Mappa non valida\n");
		free_invalid_bonus(&game);
		return (0);
	}
	load_textures(&game);
	game.window.win_ptr = mlx_new_window(game.window.mlx_ptr,
			32 * game.map.width, 32 * game.map.height, "so_long");
	if (!game.window.win_ptr)
		return (0);
	draw_map_bonus(&game);
	call_hooks(game);
	free_all_bonus(&game);
	return (1);
}
