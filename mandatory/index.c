/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:48:49 by adegl-in          #+#    #+#             */
/*   Updated: 2025/02/10 16:14:19 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

// function that assigns the textures to the respective structure variables
void	load_textures(t_game *game)
{
	int width;
	int	height;

	game->textures.floor = mlx_xpm_file_to_image(game->window.mlx_ptr, "./textures/floor.xpm", &width, &height);
	game->textures.wall = mlx_xpm_file_to_image(game->window.mlx_ptr, "./textures/wall.xpm", &width, &height);
	game->textures.collectible = mlx_xpm_file_to_image(game->window.mlx_ptr, "./textures/torch.xpm", &width, &height);
	game->textures.exit = mlx_xpm_file_to_image(game->window.mlx_ptr, "./textures/ladder.xpm", &width, &height);
	game->textures.player = mlx_xpm_file_to_image(game->window.mlx_ptr, "./textures/knight.xpm", &width, &height);
	game->textures.enemy = mlx_xpm_file_to_image(game->window.mlx_ptr, "./textures/skeleton.xpm", &width, &height);
}

// function that analyzes the .ber files, calling get_next_line(), where the map patterns are located
void	load_map(t_game *game, const char *filename)
{
	int	fd;
	char *line;
	int	i;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("An issue has occurred while opening the file");
		return ;
	}

	game->map.height = 0;
	game->map.width = 0;

	// count the width (length of each line) and height (number of rows) of the map 
	while ((line = get_next_line(fd)) != NULL)
	{
		if (game->map.width == 0)
			game->map.width = ft_strlen(line) - 1; // width == number of characters minus the newline and the end of the line
		
		game->map.height++;
		free(line);
	}
	close(fd);

	// close the file so we can first allocate the necessary grid space in memory
	game->map.grid = malloc((game->map.height + 1) * sizeof(char *));
	if (!game->map.grid)
	{
		perror("An issue has occurred while loading the grid");
		exit(EXIT_FAILURE);
	}

	// reopen and therefore use again the file to store the content of each line in the grid
	fd = open(filename, fd);
	if (fd == -1)
	{
		perror("An issue has occurred while opening the file after storing grid size in memory");
		return ;
	}

	while ((line = get_next_line(fd)) != NULL && i < game->map.width)
	{
		game->map.grid[i] = line;
		printf("%s", game->map.grid[i]);
		i++;
	}
	printf("altezza: %d, larghezza: %d", game->map.height, game->map.width);
	// game.map.grid[i] = NULL;
}

// function that converts the textures into mlx objects
void	draw_map(t_game *game)
{
	void *texture;
	int width;
	int	height;
	int	i;
	int	j;

	width = 16;
	height = 16;
	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == '0')
				texture = game->textures.floor;
			else if (game->map.grid[i][j] == '1')
				texture = game->textures.wall;
			else if (game->map.grid[i][j] == 'C')
				texture = game->textures.collectible;
			else if (game->map.grid[i][j] == 'E')
				texture = game->textures.exit;
			else if (game->map.grid[i][j] == 'P')
				texture = game->textures.player;
			if (texture)
				mlx_put_image_to_window(game->window.mlx_ptr, game->window.win_ptr, texture, j * width, i * height);
			j++;
		}
		i++;
	}
}

// wcc index.c ./Libft/libft.a -L./minilibx-linux -lmlx -lXext -lX11 -lm
int main(void)
{
	t_game game;

    game.window.mlx_ptr = mlx_init();
    if (!game.window.mlx_ptr)
        return (0);
    game.window.win_ptr = mlx_new_window(game.window.mlx_ptr, 600, 400, "so_long");
    if (!game.window.win_ptr)
	{
		free(game.window.win_ptr);
		return (0);
	}
	load_map(&game, "./maps/map_easy.ber");
	load_textures(&game);
	draw_map(&game);
    mlx_hook(game.window.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &game);
    mlx_hook(game.window.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &game);
    mlx_loop(game.window.mlx_ptr);

    return (0);
}
