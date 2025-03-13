NAME = so_long
BNAME = so_long_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
SRCPATH = mandatory/
BSRCPATH = bonus/
SRC = $(SRCPATH)so_long.c $(SRCPATH)free_resources.c $(SRCPATH)map_validity.c $(SRCPATH)textures.c \
		$(SRCPATH)map_loader.c $(SRCPATH)map_renderer.c $(SRCPATH)map_validity_utils.c $(SRCPATH)flood_fill.c 
BSRC = $(BSRCPATH)so_long_bonus.c $(BSRCPATH)free_resources_bonus.c $(BSRCPATH)map_validity_bonus.c $(BSRCPATH)animation_bonus.c \
		$(BSRCPATH)flood_fill_bonus.c $(BSRCPATH)map_loader_bonus.c $(BSRCPATH)map_renderer_bonus.c $(BSRCPATH)map_validity_utils_bonus.c \
		$(BSRCPATH)player_movement_bonus.c $(BSRCPATH)textures_bonus.c
OBJ = $(SRC:.c=.o)
BOBJ = $(BSRC:.c=.o)
INCLUDES = -I$(MLX_DIR)
LIBFT_DIR = ./Libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm $(LIBFT)

all: $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR) all

$(NAME): $(LIBFT) $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(BOBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME) $(BNAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

bonus: $(LIBFT) $(BOBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(BOBJ) $(LIBS) $(LIBFT) -o $(BNAME)
	rm -f $(BOBJ)

.PHONY: all clean fclean re bonus
