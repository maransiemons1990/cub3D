# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: msiemons <msiemons@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/04 17:11:26 by msiemons      #+#    #+#                  #
#    Updated: 2020/05/13 17:07:06 by Maran         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

LIB = libcub3d.a

MLX = mlx

LIBFT = libft

LIBMLX = libmlx.dylib

BMP = screenshot.bmp

SRC = main.c\
		exit_game.c\
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
		game/game_mlx.c\
		game/floor_ceiling.c\
		game/initialise_game.c\
		game/save_first_image.c\
		game/keys.c\
		game/raycaster.c\
		game/raycaster_utils.c\
		game/move.c\
		game/rotate.c\
		game/sprites.c\

BONUS = bonus/main_bonus.c\
		bonus/exit_game_bonus.c\
		bonus/errormessages_bonus.c\
		bonus/get_cub/gnl_cub3d_bonus.c\
		bonus/get_cub/gnl_cub3d_utils_bonus.c\
		bonus/read_scene/read_scene_bonus.c\
		bonus/read_scene/initialise_read_scene_bonus.c\
		bonus/read_scene/read_scene_utils_bonus.c\
		bonus/read_scene/check_map_bonus.c\
		bonus/read_scene/check_map_utils_bonus.c\
		bonus/read_scene/save_sprites_bonus.c\
		bonus/read_scene/organise_sprites_bonus.c\
		bonus/game/game_mlx_bonus.c\
		bonus/game/floor_ceiling_texture_bonus.c\
		bonus/game/initialise_game_bonus.c\
		bonus/game/save_first_image_bonus.c\
		bonus/game/keys_bonus.c\
		bonus/game/raycaster_bonus.c\
		bonus/game/raycaster_utils_bonus.c\
		bonus/game/move_bonus.c\
		bonus/game/rotate_bonus.c\
		bonus/game/sprites_bonus.c\

HEADER_FILES = cub3d.h game/bmp.h bonus/cub3d_bonus.h bonus/game/bmp_bonus.h\

CFLAGS = -Wall -Wextra -Werror

LINKING = -lmlx -framework OpenGL -framework AppKit

LINK_DISPLAY = -framework CoreGraphics

OBJ = $(SRC:.c=.o)

OBJ_BONUS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(LIBMLX) lib_ft
	@ar rcs $(LIB) $(OBJ)
	$(CC) -I $(MLX) -L $(MLX) $(LINKING) $(LINK_DISPLAY) $(LIB) -o $(NAME)
	@echo "\n>>>>>Finished making<<<<<"

bonus_cub3D: $(OBJ_BONUS) $(LIBMLX) lib_ft
	@ar rcs $(LIB) $(OBJ_BONUS)
	$(CC) -I $(MLX) -L $(MLX) $(LINKING) $(LINK_DISPLAY) $(LIB) -o $(NAME)
	@echo "\n>>>>>Finished making bonus<<<<<"

$(LIBMLX):
	@make -C $(MLX)
	@cp $(MLX)/$(LIBMLX) .

lib_ft:
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(LIB)

%.o: %.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJ_BONUS) bonus_cub3D

clean:
	$(RM) $(SRC:.c=.o) $(BONUS:.c=.o) $(LIBMLX) $(BMP)
	@make clean -C $(LIBFT)
	@make clean -C $(MLX)

fclean: clean
	$(RM) $(LIB) $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re
