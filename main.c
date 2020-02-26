/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 20:13:12 by msiemons       #+#    #+#                */
/*   Updated: 2020/02/26 14:04:17 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// man mlx
// https://stackoverflow.com/c/42network/questions/531
// gcc -Wall -Wextra -Werror -I mlx -L mlx -lmlx -framework OpenGL -framework AppKit main.c

#include <mlx.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

int     main(void)
{
    void    *mlx;
	t_data	img;
    // void    *mlx_win;

    mlx = mlx_init();

/* Om een rode pixel te printen op window */
	// mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	// mlx_pixel_put(mlx, mlx_win, 10, 10, 16711680);
	
//
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

/* nog testen: */
	// mlx_put_image_to_window (mlx, mlx_win, img.img, 50, 50);

	mlx_loop(mlx);
}  
