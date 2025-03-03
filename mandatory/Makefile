NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ../minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
SRC = so_long.c check_map_validity.c free_functions.c
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