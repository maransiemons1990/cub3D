# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: msiemons <msiemons@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/02/25 15:42:59 by msiemons       #+#    #+#                 #
#    Updated: 2020/02/28 13:19:53 by msiemons      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libcub3d

MLX = mlx

LIBMLX = libmlx.dylib

SRC = main.c tutorial.c

#OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Wextra -Werror

# You may also need to specify the path to the  MiniLibX  library,  using the -L flag.
LINKING = -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

$(NAME): $(LIBMLX) $(OBJ)
	gcc $(FLAGS) -I $(MLX) -L $(MLX) $(LINKING) $(SRC) && ./a.out

$(LIBMLX):
	@make -C $(MLX)
	@cp $(MLX)/$(LIBMLX) .

clean:
	make clean -C $(MLX)
	$(RM) $(OBJ) $(LIBMLX) a.out

fclean: clean
	$(RM) $(NAME)

re: fclean all
#--------------
















# ------Voor nu werkt als ik los compile met ---------#
#gcc -Wall -Wextra -Werror -I mlx -L mlx -lmlx -framework OpenGL -framework AppKit main.c
#-----------------------------------------------------#

#gcc $(FLAGS) -I . -I mlx/. -L mlx/. $(LINKING) $(OBJS) -o $(NAME)

#-----------
# make -C --> Change to directory dir before reading the makefiles or doing anything else.
# -lm to include math library?
#$(NAME): $(OBJ)
#	make -C $(MLX)
#	cp mlx/libmlx.dylib ./$(NAME)
#	ar rcs $(NAME) $(OBJ)

# Link with the required internal MacOS API’s:
#$(NAME): $(OBJ)
#	$(CC) -Lmlx/ -lmlx -framework OpenGL -framework AppKit -o $(NAME)

# -I... oftewel 3 mappen met header files
#%.o: %.c
#	echo "Compiling $<"
#	gcc -I . -Imlx -Wall -Wextra -Werror  -c $< -o $@
#	gcc -Imlx -Wall -Wextra -Werror -L mlx -lmlx -framework OpenGL -framework AppKit -c $< -o $@

#$(NAME):
#	gcc -Wall -Wextra -Werror -I mlx -L mlx -lmlx -framework OpenGL -framework AppKit



