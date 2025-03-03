NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ../minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
SRC = so_long.c map_loader.c map_render.c movement.c textures.c utils.c free_resources.c map_checks.c map_flood_fill.c map_validation.c
OBJ = $(SRC:.c=.o)
INCLUDES = -I$(MLX_DIR)
LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm ../Libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re