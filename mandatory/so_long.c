/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:48:49 by adegl-in          #+#    #+#             */
/*   Updated: 2025/03/03 12:33:27 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	allocate_map_grid(t_game *game)
{
	// close the file so we can first allocate the necessary grid space in memory
	game->map.grid = malloc((game->map.height + 1) * sizeof(char *)); 
	if (!game->map.grid)
	{
		perror("An issue has occurred while loading the grid");
		exit(EXIT_FAILURE);
	}
}

void	print_map(t_game *game)
{
	int i = 0;
	int j = 0;

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

// function that assigns the textures to the respective structure variables
void	load_textures(t_game *game)
{
	int width;
	int	height;
	
	game->textures.floor = mlx_xpm_file_to_image(game->window.mlx_ptr, "./mandatory/textures/floor.xpm", &width, &height);
	game->textures.wall = mlx_xpm_file_to_image(game->window.mlx_ptr, "./mandatory/textures/wall.xpm", &width, &height);
	game->textures.collectible = mlx_xpm_file_to_image(game->window.mlx_ptr, "./mandatory/textures/chest.xpm", &width, &height);
	game->textures.exit = mlx_xpm_file_to_image(game->window.mlx_ptr, "./mandatory/textures/ladder.xpm", &width, &height);
	game->textures.player = mlx_xpm_file_to_image(game->window.mlx_ptr, "./mandatory/textures/knight.xpm", &width, &height);
}

void	check_fd_validity(int fd)
{
	if (fd == -1)
	{
		perror("Errore nell'apertura del file\n");
		return ;
	}
}

void	initialiaze_map_values(t_game *game)
{
	game->calcs.total_score = 0;
	game->calcs.moves = 0;
	game->calcs.score = 0;
	game->map.height = 0;
	game->map.width = 0;
	game->map.player_x = 1;
	game->map.player_y = 1;
}

// function that analyzes the .ber files, calling get_next_line(), where the map patterns are located
// count the width (length of each line) and height (number of rows) of the map
// width == number of characters minus the newline and the end of the line
// reopen and therefore use again the file to store the content of each line in the grid
void	load_map(t_game *game, const char *filename)
{
	int	fd;
	char *line;
	int	i;

	i = 0;
	fd = open(filename, O_RDONLY);
	check_fd_validity(fd);
	initialiaze_map_values(game);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (game->map.width == 0)
			game->map.width = ft_strlen(line) - 1;
		game->map.height++;
		free(line);
	}
	close(fd);
	allocate_map_grid(game);
	fd = open(filename, O_RDONLY);
	check_fd_validity(fd);
	while ((line = get_next_line(fd)) != NULL && i < game->map.width)
	{
		game->map.grid[i] = line;
		i++;
	}
}

// function that converts the textures into mlx objects
void	draw_map(t_game *game)
{
	void *texture;
	int	i;
	int	j;

	i = -1;
	while (++i < game->map.height)
	{
		j = -1;
		while (++j < game->map.width)
		{
			mlx_put_image_to_window(game->window.mlx_ptr, game->window.win_ptr, game->textures.floor, j * 32, i * 32);
			texture = NULL;
			if (game->map.grid[i][j] == '1')
				texture = game->textures.wall;
			else if (game->map.grid[i][j] == 'C')
				texture = game->textures.collectible;
			else if (game->map.grid[i][j] == 'E')
				texture = game->textures.exit;
			else if (game->map.grid[i][j] == 'P')
				texture = game->textures.player;
			if (texture)
				mlx_put_image_to_window(game->window.mlx_ptr, game->window.win_ptr, texture, j * 32, i * 32);
		}
	}
}	

int on_destroy(t_game *game)
{
	free_all(game);
	exit(0);
	return (0);
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

int on_keypress(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
	{
		ft_printf("DEFEAT.\n");
		on_destroy(game);
        exit(0);
	}
	else if (keysym == XK_w)
		move_player(game, game->map.player_x, game->map.player_y - 1);
	else if (keysym == XK_a)
		move_player(game, game->map.player_x - 1, game->map.player_y);
	else if (keysym == XK_s)
		move_player(game, game->map.player_x, game->map.player_y + 1);
	else if (keysym == XK_d)
		move_player(game, game->map.player_x + 1, game->map.player_y);
	return (0);
}

// wcc index.c check_map_validity.c free_functions.c ./Libft/libft.a -L./minilibx-linux -lmlx -lXext -lX11 -lm -o so_long
int main(int argc, char **argv)
{
	t_game game;
	
	if (argc != 2)
	{
		printf("Avvia il gioco con il seguente comando: ./so_long <nome_file>\n");
		return (0);
	}
    game.window.mlx_ptr = mlx_init();
    if (!game.window.mlx_ptr)
		return (0);	
	load_map(&game, argv[1]);
	if (!is_map_valid(&game, game.map.grid, game.map.height, game.map.width))
	{
		ft_printf("La mappa che hai scelto non e' valida\n");
		return (1);
	}
	load_textures(&game);
	game.window.win_ptr = mlx_new_window(game.window.mlx_ptr, 32*game.map.width, 32*game.map.height, "so_long");
	if (!game.window.win_ptr)
	{
		free(game.window.win_ptr);
		return (0);
	}
	draw_map(&game);
	mlx_hook(game.window.win_ptr, 2, 1L << 0, &on_keypress, &game);
	mlx_hook(game.window.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &game);
	mlx_loop(game.window.mlx_ptr);
    return (1);
}
