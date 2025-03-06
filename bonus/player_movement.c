/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:12:26 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/06 16:38:32 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_collectible(t_game *game, int new_x, int new_y)
{
	game->calcs.score++;
	game->map.grid[new_y][new_x] = '0';
}

void	handle_exit(t_game *game)
{
	if (game->calcs.score == game->calcs.total_score)
	{
		ft_printf("Hai vinto!\n");
		on_destroy(game);
	}
}

void	handle_enemy(t_game *game)
{
	ft_printf("WASTED\n");
	on_destroy(game);
}

int	move_player(t_game *game, int new_x, int new_y)
{
	if (new_y < 0 || new_y >= game->map.height
		|| new_x < 0 || new_x >= game->map.width)
		return (0);
	if (game->map.grid[new_y][new_x] == '1')
		return (0);
	if (game->map.grid[new_y][new_x] == 'C')
		handle_collectible(game, new_x, new_y);
	else if (game->map.grid[new_y][new_x] == 'N')
		handle_enemy(game);
	else if (game->map.grid[new_y][new_x] == 'E')
		handle_exit(game);
	game->map.grid[game->map.player_y][game->map.player_x] = '0';
	game->map.player_y = new_y;
	game->map.player_x = new_x;
	game->map.grid[new_y][new_x] = 'P';
	game->calcs.moves++;
	draw_map(game);
	display_score(game);
	return (1);
}
