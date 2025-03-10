/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:10:10 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/10 19:26:48 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long_bonus.h"

static void	allocate_map_grid_bonus(t_game *game)
{
	game->map.grid = malloc((game->map.height + 1) * sizeof(char *));
	if (!game->map.grid)
	{
		perror("Grid allocation failed");
		exit(EXIT_FAILURE);
	}
}

static void	check_fd_validity_bonus(int fd, t_game *game)
{
	if (fd == -1)
	{
		perror("File opening error");
		if (game->map.grid)
			free_grid_bonus(game->map.grid, game->map.height);
		mlx_destroy_display(game->window.mlx_ptr);
		free(game->window.mlx_ptr);
		exit(EXIT_FAILURE);
	}
	else if (fd != -1)
	{
		perror("Error: input might be a directory");
		close(fd);
		free_invalid_bonus(game);
		exit(EXIT_FAILURE);
	}
}

void	initialize_map_values_bonus(t_game *game)
{
	game->map.grid = NULL;
	game->calcs.total_score = 0;
	game->calcs.moves = 0;
	game->calcs.score = 0;
	game->map.height = 0;
	game->map.width = 0;
	game->map.player_x = 1;
	game->map.player_y = 1;
	game->map.text_x = 22;
	game->map.text_y = 22;
}

void	load_map_dimensions_bonus(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		if (game->map.width == 0)
			game->map.width = ft_strlen(line) - 1;
		game->map.height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	load_map_bonus(t_game *game, const char *filename)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY | __O_DIRECTORY);
	check_fd_validity_bonus(fd, game);
	initialize_map_values_bonus(game);
	load_map_dimensions_bonus(game, fd);
	allocate_map_grid_bonus(game);
	fd = open(filename, O_RDONLY);
	check_fd_validity_bonus(fd, game);
	i = 0;
	line = get_next_line(fd);
	while (line && i < game->map.height)
	{
		game->map.grid[i] = line;
		i++;
		line = get_next_line(fd);
	}
	close(fd);
}
