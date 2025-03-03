NAME = so_long
BNAME = so_long_bonus
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_DIR = ./minilibx-linux
MLX = $(MLX_DIR)/libmlx.a
SRCPATH = mandatory/
BSRCPATH = bonus/
SRC = $(SRCPATH)so_long.c $(SRCPATH)free_resources.c $(SRCPATH)check_map_validity.c \
		$(SRCPATH)textures.c $(SRCPATH)map_loader.c $(SRCPATH)map_renderer.c $(SRCPATH)map_validity_utils.c \
		$(SRCPATH)flood_fill.c 
BSRC = $(BSRCPATH)so_long.c $(BSRCPATH)free_resources.c $(BSRCPATH)check_map_validity.c
OBJ = $(SRC:.c=.o)
BOBJ = $(BSRC:.c=.o)
INCLUDES = -I$(MLX_DIR)
LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm ./Libft/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) $(BOBJ)

fclean: clean
	rm -f $(NAME) $(BNAME)

re: fclean all

bonus: $(BOBJ)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(BOBJ) $(LIBS) -o $(NAME)_bonus
	rm -f $(BOBJ)

.PHONY: all clean fclean re bonus