#include "./minilibx-linux/mlx.h"
#include "./Libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <X11/X.h>
#include <X11/keysym.h>

# define TILE_SIZE 300

// manages and holds all the images used for the textures
typedef struct s_textures {
	void	*floor; // "empty space"
    void	*wall;
    void	*collectible;
    void	*exit;
    void	*player;
	void	*enemy;
} t_textures;

// manages minilibx initialization and the window
typedef struct s_window
{
	void		*mlx_ptr; // MLX pointer
	void		*win_ptr; // MLX window pointer
	t_textures		*img_ptr; // Image pointer
}	t_window;

// all the info about the map, such as its width, height and the player position
typedef struct s_map {
    char	**grid;
    int		width;
    int		height;
    int		x;
    int		y;
}	t_map;

// a strucutre that connects all previous ones
typedef struct s_game {
    t_window	window;
    t_map		map;
    t_textures	textures;
}	t_game;

int on_destroy(t_window *window)
{
	mlx_destroy_window(window->mlx_ptr, window->win_ptr);
	mlx_destroy_display(window->mlx_ptr);
	free(window->mlx_ptr);
	exit(0);
	return (0);
}

int on_keypress(int keysym, t_window *window)
{
	(void)window;
	printf("Pressed key: %d\\n", keysym);
	return (0);
}