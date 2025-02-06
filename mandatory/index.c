#include "index.h"

// function that assigns the textures to the respective structure variables
void	load_textures(t_game game)
{
	int width;
	int	height;

	game.textures.floor = mlx_xpm_file_to_image(game.window.mlx_ptr, "./textures/floor.xpm", &width, &height);
	game.textures.wall = mlx_xpm_file_to_image(game.window.mlx_ptr, "./textures/wall.xpm", &width, &height);
	game.textures.collectible = mlx_xpm_file_to_image(game.window.mlx_ptr, "./textures/torch.xpm", &width, &height);
	game.textures.exit = mlx_xpm_file_to_image(game.window.mlx_ptr, "./textures/ladder.xpm", &width, &height);
	game.textures.player = mlx_xpm_file_to_image(game.window.mlx_ptr, "./textures/knight.xpm", &width, &height);
	game.textures.enemy = mlx_xpm_file_to_image(game.window.mlx_ptr, "./textures/skeleton.xpm", &width, &height);
}

// function that outputs the textures into the window.
// it doesnt yet analyze the .ber files where the map patterns are located.
void	draw_map(t_game game)
{
	void *texture;
	int width;
	int	height;
	int	i;
	int	j;

	width = 16;
	height = 16;
	i = 0;
	j = 0;
	while (i < game.map.height)
	{
		while (j < game.map.width)
		{
			if (game.map.grid[i][j] == '0')
				texture = game.textures.floor;
			else if (game.map.grid[i][j] == '1')
				texture = game.textures.wall;
			else if (game.map.grid[i][j] == 'C')
				texture = game.textures.collectible;
			else if (game.map.grid[i][j] == 'E')
				texture = game.textures.exit;
			else if (game.map.grid[i][j] == 'P')
				texture = game.textures.player;
			if (texture)
				mlx_xpm_file_to_image(game.window.mlx_ptr, texture, j*width, i*height);
		}
	}
}

// gcc index.c -L./minilibx-linux -lmlx -lXext -lX11 -lm
int main(void)
{
    t_window window;
    t_textures *img = NULL;
    int width, height;

    window.mlx_ptr = mlx_init();
    if (!window.mlx_ptr)
        return (1);
    window.win_ptr = mlx_new_window(window.mlx_ptr, 600, 400, "so_long");
    if (!window.win_ptr)
        return (free(window.win_ptr), 1);
    img = mlx_xpm_file_to_image(window.mlx_ptr, "./textures/db1.xpm", &width, &height);
    if (!img)
    {
        printf("There has been a problem while inserting the image\n");
        return (1);
    }

    mlx_put_image_to_window(window.mlx_ptr, window.win_ptr, img, 300, 300);
    mlx_hook(window.win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, &window);
    mlx_hook(window.win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, &window);
    mlx_loop(window.mlx_ptr);

    return (0);
}
