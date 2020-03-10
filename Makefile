# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: msiemons <msiemons@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/04 17:11:26 by msiemons       #+#    #+#                 #
#    Updated: 2020/03/10 15:26:51 by msiemons      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libcub3d.a

#MLX = mlx

LIBFT = libft

#LIBMLX = libmlx.dylib

SRC = main.c readmap.c gnl_cub3d.c gnl_cub3d_utils.c twod_checker.c valuechecker.c\
		errormessages.c check_utils.c identifiers_utils.c check_map.c

OBJ = $(SRC:.c=.o)

#FLAGS = -Wall -Wextra -Werror

# You may also need to specify the path to the  MiniLibX  library,  using the -L flag.
#LINKING = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)


$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(NAME)
	@ar rcs $(NAME) $(OBJ)
	gcc main.c $(NAME)

%.o: %.c
		gcc -I . -I libft/. -Wall -Wextra -Werror -c $< -o $@

clean:
		$(RM) $(OBJ)
		@make clean -C $(LIBFT)

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