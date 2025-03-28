/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:03:59 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/27 14:28:44 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx-linux/mlx.h"
#include "../Libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <X11/X.h>
#include <X11/keysym.h>

// manages and holds all the images used for the textures
typedef struct s_textures
{
	void	*floor; // "empty space"
	void	*wall;
	void	*collectible;
	void	*exit;
	void	*player;
}	t_textures;

// manages minilibx initialization and the window
typedef struct s_window
{
	void		*mlx_ptr; // MLX pointer
	void		*win_ptr; // MLX window pointer
	t_textures	*img_ptr; // Image pointer
}	t_window;

// all the info about the map, such as its width, height and the player position
typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	int		player_x;
	int		player_y;
}	t_map;

// structure that keeps track of 'backend' operations
typedef struct s_calcs
{
	int		score;
	int		total_score;
	int		moves;
	int		exit_x;
	int		exit_y;
}	t_calcs;

// a strucutre that connects all previous ones
typedef struct s_game
{
	t_window	window;
	t_map		map;
	t_textures	textures;
	t_calcs		calcs;
}	t_game;

// structure that stores all the flood fill algorithm values
typedef struct s_flood_fill_params
{
	char	**map;
	int		height;
	int		width;
	int		*reachable_c;
	int		*reachable_e;
}	t_flood_fill_params;

typedef struct s_map_elements
{
	int	p;
	int	c;
	int	e;
}	t_map_elements;

void	free_grid(char **grid, int height);
void	free_textures(t_game *game);
void	free_all(t_game *game);
int		is_map_valid(t_game *game, char **grid, int height, int width);
int		on_keypress(int keysym, t_game *game);
int		move_player(t_game *game, int new_x, int new_y);
int		on_destroy(t_game *game);
void	draw_map(t_game *game);
void	load_map(t_game *game, const char *filename);
void	load_textures(t_game *game);
void	print_map(t_game *game);
void	draw_tile(t_game *game, int i, int j);
char	**copy_map(char **map, int height);
void	free_invalid(t_game *game);
int		is_symmetric(char **map, int height);
int		flood_fill_check(t_game *game, char **map_copy,
			t_flood_fill_params *found_params);
int		count_characters(char *str, int *p, int *c, int *e);
int		count_elements(char **map, int height, t_map_elements *elements);
void	find_player(t_game *game);