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
    int		player_x;
    int		player_y;
	int		score;
	int		total_score;
}	t_map;

// a strucutre that connects all previous ones
typedef struct s_game {
    t_window	window;
    t_map		map;
    t_textures	textures;
	int moves;
}	t_game;

void	ft_free_grid(char **grid);
void	free_textures(t_game *game);
void	free_everything(t_game *game);