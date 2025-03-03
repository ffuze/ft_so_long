#include "../minilibx-linux/mlx.h"
#include "../Libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <X11/X.h>
#include <X11/keysym.h>

#define SPRITE_COUNT 4

// manages and holds all the images used for the textures
typedef struct s_textures {
	void	*floor; // "empty space"
    void	*wall;
    void	*collectible;
    void	*exit;
    void	*player[SPRITE_COUNT];
	void	*enemy[SPRITE_COUNT];
	int	sprite_index;
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
	int		text_x;
	int		text_y;
}	t_map;

// structure that keeps track of 'backend' operations
typedef struct s_calcs {
	int		score;
	int		total_score;
	int 	moves;
}	t_calcs;

// a strucutre that connects all previous ones
typedef struct s_game {
    t_window	window;
    t_map		map;
    t_textures	textures;
	t_calcs		calcs;
}	t_game;

void	free_grid(char **grid, int height);
void	free_textures(t_game *game);
void	free_all(t_game *game);
int		is_map_valid(t_game *game, char **grid, int height, int width);
int		on_keypress(int keysym, t_game *game);
int		move_player(t_game *game, int new_x, int new_y);
int		on_destroy(t_game *game);
void	draw_map(t_game *game);
void	load_map(t_game *game, const char *filename);
void	load_textures(t_game *game);
void	print_map(t_game *game);
int	update_and_animate(t_game *game);
void	display_score(t_game *game);
int	print_sprites(t_game *game);
int	is_map_valid(t_game *game, char **map, int height, int width);
int	ft_strlen_no_newline(char *str);
void	count_map_elements(char **map, int height, int *p, int *c, int *e, int *n);
int	check_walls(char **map, int height, int width);
int	validate_elements(int p, int c, int e, int n);
void	find_player(t_game *game);
void	flood_fill(char **map, int x, int y, int h, int w, int *rc, int *re);
