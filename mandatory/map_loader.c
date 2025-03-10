/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 14:53:07 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/10 19:48:17 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	allocate_map_grid(t_game *game)
{
	game->map.grid = malloc((game->map.height + 1) * sizeof(char *));
	if (!game->map.grid)
	{
		perror("An issue has occurred while loading the grid");
		exit(EXIT_FAILURE);
	}
}

void	check_fd_validity(int fd, t_game *game)
{
	if (fd == -1)
	{
		perror("Errore nell'apertura del file\n");
		if (game->map.grid)
			free_grid(game->map.grid, game->map.height);
		mlx_destroy_display(game->window.mlx_ptr);
		free(game->window.mlx_ptr);
		exit(EXIT_FAILURE);
	}
	else if (fd != -1)
	{
		perror("Error: input might be a directory");
		close(fd);
		free_invalid(game);
		exit(EXIT_FAILURE);
	}
}

void	initialize_map_values(t_game *game)
{
	game->map.grid = NULL;
	game->calcs.total_score = 0;
	game->calcs.moves = 0;
	game->calcs.score = 0;
	game->map.height = 0;
	game->map.width = 0;
	game->map.player_x = 1;
	game->map.player_y = 1;
}

void	load_map_dimensions(t_game *game, int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (game->map.width == 0)
			game->map.width = ft_strlen(line) - 1;
		game->map.height++;
		free(line);
	}
}

void	load_map(t_game *game, const char *filename)
{
	int		fd;
	char	*line;
	int		i;

	i = 0;
	fd = open(filename, O_RDONLY);
	check_fd_validity(fd, game);
	initialize_map_values(game);
	load_map_dimensions(game, fd);
	close(fd);
	fd = open(filename, O_RDONLY);
	check_fd_validity(fd, game);
	allocate_map_grid(game);
	while (i < game->map.height)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		game->map.grid[i] = line;
		i++;
	}
	close(fd);
}
