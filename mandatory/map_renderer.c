/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:53:09 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/03 15:51:33 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_map(t_game *game)
{
	int		i;
	int		j;

	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (++j < game->map.width)
		{
			draw_tile(game, i, j);
		}
	}
}

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
		texture = game->textures.player;
	if (texture)
		mlx_put_image_to_window(game->window.mlx_ptr,
			game->window.win_ptr, texture, j * 32, i * 32);
}

void	print_map(t_game *game)
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

int move_player(t_game *game, int new_x, int new_y)
{
    if (new_y < 0 || new_y >= game->map.height || new_x < 0 || new_x >= game->map.width)
        return (0);
    if (game->map.grid[new_y][new_x] == '1')
		return (0);
	if (game->map.grid[new_y][new_x] == 'C')
	{
		game->calcs.score++;
		game->map.grid[new_y][new_x] = '0';
	}
    if (game->map.grid[new_y][new_x] == 'E')
    {
        if (game->calcs.score == game->calcs.total_score)
        {
            ft_printf("Hai vinto!\n");
            on_destroy(game);
        }
        return (0);
    }
	game->map.grid[game->map.player_y][game->map.player_x] = '0';
    game->map.player_y = new_y;
    game->map.player_x = new_x;
    game->map.grid[new_y][new_x] = 'P';
	game->calcs.moves++;
	ft_printf("Mosse: %d\n", game->calcs.moves);
	draw_map(game);
    return (1);
}
