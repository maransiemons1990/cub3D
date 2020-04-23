# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: msiemons <msiemons@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/04 17:11:26 by msiemons      #+#    #+#                  #
#    Updated: 2020/04/23 16:03:51 by Maran         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libcub3d.a

MLX = mlx

LIBFT = libft

LIBMLX = libmlx.dylib

BMP = screenshot.bmp

SRC = main.c errormessages.c read_scene/gnl_cub3d.c read_scene/gnl_cub3d_utils.c\
		read_scene/read_scene.c\
		read_scene/utils_general.c read_scene/read_scene_utils.c\
		read_scene/check_map.c read_scene/check_map_utils.c\
		mlx.c raycaster.c keys.c floor_ceiling.c\
		sprites.c read_scene/save_sprites.c\
		save_first_image.c

#twod_checker.c valuechecker.c\#
OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

# You may also need to specify the path to the  MiniLibX  library,  using the -L flag.
LINKING = -lmlx -framework OpenGL -framework AppKit

LINK_DISPLAY = -framework CoreGraphics

all: $(NAME)

$(NAME): $(LIBMLX) lib_ft $(OBJ)
	@ar rcs $(NAME) $(OBJ)
	gcc $(FLAGS) -I $(MLX) -L $(MLX) $(LINKING) $(LINK_DISPLAY) $(NAME)
#	./a.out	example.cub

$(LIBMLX):
	@make -C $(MLX)
	@cp $(MLX)/$(LIBMLX) .

lib_ft:
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(NAME)

%.o: %.c
	gcc -Wall -Wextra -Werror -c $< -o $@
#	gcc -I . -I libft/. -Wall -Wextra -Werror -c $< -o $@

clean:
		$(RM) $(OBJ) $(LIBMLX) $(BMP)
		@make clean -C $(LIBFT)
		@make clean -C $(MLX)

fclean: clean
		$(RM) $(NAME) a.out
		@make fclean -C $(LIBFT)

re: 	fclean all


#$(NAME): $(LIBMLX) $(OBJ)
#	gcc $(FLAGS) -I $(MLX) -L $(MLX) $(LINKING) $(SRC) && ./a.out

#$(LIBMLX):
#	@make -C $(MLX)
#	@cp $(MLX)/$(LIBMLX) .

#$(LIBFT):
#	make -C $(LIBFT)
#	cp $(LIBFT)/$(LIBFT).a .

#clean:
#	make clean -C $(MLX)
#	$(RM) $(OBJ) $(LIBMLX) a.out

#fclean: clean
#	$(RM) $(NAME)

#re: fclean all
#--------------