# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: msiemons <msiemons@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/04 17:11:26 by msiemons      #+#    #+#                  #
#    Updated: 2020/05/12 22:03:52 by Maran         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIB = libcub3d.a

MLX = mlx

LIBFT = libft

LIBMLX = libmlx.dylib

BMP = screenshot.bmp

SRC = exit_game.c\
		errormessages.c\
		get_cub/gnl_cub3d.c\
		get_cub/gnl_cub3d_utils.c\
		read_scene/read_scene.c\
		read_scene/initialise_read_scene.c\
		read_scene/read_scene_utils.c\
		read_scene/check_map.c\
		read_scene/check_map_utils.c\
		read_scene/save_sprites.c\
		read_scene/organise_sprites.c\
		game/initialise_game.c\
		game/save_first_image.c\
		game/keys.c\
		game/raycaster.c\
		game/raycaster_utils.c\
		game/move.c\
		game/rotate.c\
		game/sprites.c\

REGULAR = main.c\
		game/game_mlx.c\
		game/floor_ceiling.c\

BONUS = bonus/main_bonus.c\
		bonus/game_mlx_bonus.c\
		bonus/floor_ceiling_texture_bonus.c\

HEADER_FILES = cub3d.h bonus/cub3d_bonus.h\

CFLAGS = -Wall -Wextra -Werror

LINKING = -lmlx -framework OpenGL -framework AppKit

LINK_DISPLAY = -framework CoreGraphics

ifdef WITH_BONUS
	OBJ = $(SRC:.c=.o) $(BONUS:.c=.o)
else
	OBJ = $(SRC:.c=.o) $(REGULAR:.c=.o)
endif

all: $(NAME)

$(NAME): $(OBJ) $(LIBMLX) lib_ft
	@ar rcs $(LIB) $(OBJ)
	$(CC) -I $(MLX) -L $(MLX) $(LINKING) $(LINK_DISPLAY) $(LIB) -o $(NAME)

$(LIBMLX):
	@make -C $(MLX)
	@cp $(MLX)/$(LIBMLX) .

lib_ft:
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(LIB)

%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJ)
	WITH_BONUS=1 make all

clean:
	$(RM) $(SRC:.c=.o) $(REGULAR:.c=.o) $(BONUS:.c=.o) $(LIBMLX) $(BMP)
	@make clean -C $(LIBFT)
	@make clean -C $(MLX)

fclean: clean
	$(RM) $(LIB) $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
