NAME = so_long
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
SRC = index.c check_map_validity.c free_functions.c get_next_line.c ft_printf.c
LIBFT = ./Libft/libft.a
OBJ = $(SRC:.c=.o)
INCLUDES = -I$(MLX_DIR)
LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(MLX) $(LIBFT) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re