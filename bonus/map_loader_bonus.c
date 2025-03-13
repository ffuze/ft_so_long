/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:10:10 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/13 18:57:01 by adegl-in         ###   ########.fr       */
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

static void	check_fd_validity_bonus(int fd, t_game *game, const char *filename)
{
	int	dir_fd;

	dir_fd = open(filename, __O_DIRECTORY);
	if (fd == -1)
	{
		perror("File opening error");
		if (game->map.grid)
			free_grid_bonus(game->map.grid, game->map.height);
		mlx_destroy_display(game->window.mlx_ptr);
		free(game->window.mlx_ptr);
		exit(EXIT_FAILURE);
	}
	if (dir_fd != -1)
	{
		perror("Error: input might be a directory");
		close(dir_fd);
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
	size_t	len;

	i = -1;
	initialize_map_values_bonus(game);
	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(&filename[len - 4], ".ber", 4) != 0)
		return (free_invalid_bonus(game));
	fd = open(filename, O_RDONLY);
	check_fd_validity_bonus(fd, game, filename);
	load_map_dimensions_bonus(game, fd);
	allocate_map_grid_bonus(game);
	fd = open(filename, O_RDONLY);
	check_fd_validity_bonus(fd, game, filename);
	line = get_next_line(fd);
	while (++i < game->map.height && line)
	{
		game->map.grid[i] = line;
		line = get_next_line(fd);
	}
	close(fd);
}
