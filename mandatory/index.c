/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adegl-in <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 13:48:49 by adegl-in          #+#    #+#             */
/*   Updated: 2025/02/17 18:01:24 by adegl-in         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

void	ft_free_grid(char **grid)
{
	int	i;

	i = 0;
	while (grid[i])
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

void	free_textures(t_game *game)
{
	mlx_destroy_image(game->window.mlx_ptr, game->textures.collectible);
	mlx_destroy_image(game->window.mlx_ptr, game->textures.enemy);
	mlx_destroy_image(game->window.mlx_ptr, game->textures.exit);
	mlx_destroy_image(game->window.mlx_ptr, game->textures.floor);
	mlx_destroy_image(game->window.mlx_ptr, game->textures.player);
	mlx_destroy_image(game->window.mlx_ptr, game->textures.wall);
}

void	free_all(t_game *game)
{
	ft_free_grid(game->map.grid);
	// ft_printf("sono davanti al free_grid()");
	free_textures(game);
	// ft_printf("sono davanti al free_textures()");
	if (game->window.win_ptr)
		mlx_destroy_window(game->window.mlx_ptr, game->window.win_ptr);
	if (game->window.mlx_ptr)
	{
		mlx_destroy_display(game->window.mlx_ptr);
		free(game->window.mlx_ptr);
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

int	get_total_score(t_game *game)
{
	int i;
	int j;
	int coll;

	i = 0;
	coll = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			if (game->map.grid[i][j] == 'C')
				coll++;
			j++;
		}
		i++;
	}
	return (coll);
}

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

	game->calcs.moves = 0;
	game->calcs.score = 0;
	game->map.height = 0;
	game->map.width = 0;
	game->map.player_x = 1;
	game->map.player_y = 1;

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
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("An issue has occurred while opening the file after storing grid size in memory");
		return ;
	}

	while ((line = get_next_line(fd)) != NULL && i < game->map.width)
	{
		game->map.grid[i] = line;
		i++;
	}
	game->calcs.total_score = get_total_score(game);
	print_map(game);
	// ft_printf("coordinata Y load_map(): %d\n", game->map.player_y);
}

// function that converts the textures into mlx objects
void	draw_map(t_game *game)
{
	void *texture;
	int	i;
	int	j;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
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
			else if (game->map.grid[i][j] == 'N')
				texture = game->textures.enemy;
			if (texture)
				mlx_put_image_to_window(game->window.mlx_ptr, game->window.win_ptr, texture, j * 32, i * 32);
			j++;
		}
		i++;
	}
}	

// void	swap_characters(char a, char b)
// {
// 	char temp;

// 	temp = a;
// 	a = b;
// 	b = temp;
// }

int on_destroy(t_game *game)
{
	free_all(game);
	exit(0);
	return (0);
}

// int player_is_next_to_wall(t_game *game)
// {
//     int y = game->map.player_y;
//     int x = game->map.player_x;

// 	if ((y > 0 && game->map.grid[y - 1][x] == '1') // above
// 		|| (y < game->map.height - 1 && game->map.grid[y + 1][x] == '1') // below
// 		|| (x > 0 && game->map.grid[y][x - 1] == '1') // left
// 		|| (x < game->map.width - 1 && game->map.grid[y][x + 1] == '1')) // right
// 		return (0);
//     return (0);
// }

// int player_is_in_angle(t_game *game)
// {
//     int y = game->map.player_y;
//     int x = game->map.player_x;

// 	if ((y == 0 && x == 0) // top-left corner
// 		|| (y == 0 && x == game->map.width - 1) // top-right corner
// 		|| (y == game->map.height - 1 && x == 0) // bottom-left corner
// 		|| (y == game->map.height - 1 && x == game->map.width - 1)) // bottom-right corner
// 		return (0);
// 	draw_map(game);
// 	return (1);
// }	

int move_player(t_game *game, int new_x, int new_y)
{
    if (new_y < 0 || new_y >= game->map.height || new_x < 0 || new_x >= game->map.width)
    {
        ft_printf("Posizione invalida\n");
        return (0);
	}
    if (game->map.grid[new_y][new_x] == '1')
	{
		ft_printf("Non posso andare dentro un muro...\n");
		return (0);
	}
	if (game->map.grid[new_y][new_x] == 'C')
	{
		game->calcs.score++;
		game->map.grid[new_y][new_x] = '0';
		ft_printf("Score: %d\n", game->calcs.score);
	}
	if (game->map.grid[new_y][new_x] == 'N')
	{
		ft_printf("Il cavaliere, nonostante la sua armatura, e' riuscito a morire da uno scheletro\n");
		on_destroy(game);
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
	ft_printf("Score TOTALE: %d\n", game->calcs.total_score);
	ft_printf("coordinata X move_player(): %d\n", game->map.player_x);
	ft_printf("coordinata Y move_player(): %d\n", game->map.player_y);
	draw_map(game);
    return (1);
}

// void	move_player_left(t_game *game)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	while (i < game->map.height)
// 	{
// 		j = 0;
// 		while (j < game->map.width - 1)
// 		{
// 			if (game->map.grid[i][j] == 'P')
// 			{
// 				if (game->map.grid[i][j - 1] == '0')
// 				{
// 					game->map.grid[i][j] = '0';
//                     game->map.grid[i][j - 1] = 'P';
// 					ft_printf("Moved to the right once\n");
// 				}
// 				else
// 					ft_printf("Can't move to the right, there's a wall!\n");
// 				return ;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

int on_keypress(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
        exit(0);
	else if (keysym == XK_w)
	{
		print_map(game);
		move_player(game, game->map.player_x, game->map.player_y - 1);
		ft_printf("(w)\n");
	}
	else if (keysym == XK_a)
	{
		print_map(game);
		move_player(game, game->map.player_x - 1, game->map.player_y);
		ft_printf("(a)\n");
	}
	else if (keysym == XK_s)
	{
		print_map(game);
		move_player(game, game->map.player_x, game->map.player_y + 1);
		ft_printf("(s)\n");
	}
	else if (keysym == XK_d)
	{
		print_map(game);
		move_player(game, game->map.player_x + 1, game->map.player_y);
		ft_printf("(d)\n");
	}
	return (0);
}

// wcc index.c ./Libft/libft.a -L./minilibx-linux -lmlx -lXext -lX11 -lm
int main(int argc, char **argv)
{
	t_game game;
	
	if (argc < 2)
	{
		printf("Avvia il gioco con il seguente comando: ./so_long <nome_file>\n");
		return (0);
	}
    game.window.mlx_ptr = mlx_init();
    if (!game.window.mlx_ptr)
		return (0);	
	load_map(&game, argv[1]);
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
