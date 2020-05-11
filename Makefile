# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: msiemons <msiemons@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/04 17:11:26 by msiemons      #+#    #+#                  #
#    Updated: 2020/05/11 13:53:23 by Maran         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libcub3d.a

MLX = mlx

LIBFT = libft

LIBMLX = libmlx.dylib

BMP = screenshot.bmp

SRC = main.c\
		errormessages.c\
		exit_game.c\
		get_cub/gnl_cub3d.c\
		get_cub/gnl_cub3d_utils.c\
		read_scene/read_scene.c\
		read_scene/initialise_read_scene.c\
		read_scene/read_scene_utils.c\
		read_scene/check_map.c\
		read_scene/check_map_utils.c\
		read_scene/save_sprites.c\
		read_scene/organise_sprites.c\
		game/game_mlx.c\
		game/initialise_game.c\
		game/save_first_image.c\
		game/keys.c\
		game/raycaster.c\
		game/raycaster_utils.c\
		game/move.c\
		game/rotate.c\
		game/floor_ceiling.c\
		game/sprites.c\

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

LINKING = -lmlx -framework OpenGL -framework AppKit

LINK_DISPLAY = -framework CoreGraphics

all: $(NAME)

$(NAME): $(LIBMLX) lib_ft $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	gcc $(FLAGS) -I $(MLX) -L $(MLX) $(LINKING) $(LINK_DISPLAY) $(NAME) -o cub3D

$(LIBMLX):
	@make -C $(MLX)
	@cp $(MLX)/$(LIBMLX) .

lib_ft:
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(NAME)

%.o: %.c
	gcc -Wall -Wextra -Werror -c $< -o $@

clean:
		$(RM) $(OBJ) $(LIBMLX) $(BMP)
		@make clean -C $(LIBFT)
		@make clean -C $(MLX)

fclean: clean
		$(RM) $(NAME) a.out
		@make fclean -C $(LIBFT)

re: 	fclean all