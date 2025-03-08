/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:10:10 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/06 19:38:18 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	allocate_map_grid(t_game *game)
{
	game->map.grid = malloc((game->map.height + 1) * sizeof(char *));
	if (!game->map.grid)
	{
		perror("Grid allocation failed");
		exit(EXIT_FAILURE);
	}
}

static void	check_fd_validity(int fd, t_game *game)
{
	if (fd == -1)
	{
		perror("File opening error");
		if (game->map.grid)
			free_grid(game->map.grid, game->map.height);
		mlx_destroy_display(game->window.mlx_ptr);
		free(game->window.mlx_ptr);
		exit(EXIT_FAILURE);
	}
}

void	initialize_map_values(t_game *game)
{
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

void	load_map_dimensions(t_game *game, int fd)
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

void	load_map(t_game *game, const char *filename)
{
	int		fd;
	char	*line;
	int		i;

	fd = open(filename, O_RDONLY);
	check_fd_validity(fd, game);
	initialize_map_values(game);
	load_map_dimensions(game, fd);
	allocate_map_grid(game);
	fd = open(filename, O_RDONLY);
	check_fd_validity(fd, game);
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
