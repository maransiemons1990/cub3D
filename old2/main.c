/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 20:13:12 by msiemons       #+#    #+#                */
/*   Updated: 2020/02/28 21:20:35 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->ad.addr + (y * data->ad.line_length + x * (data->ad.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             ft_keypress(int keycode, t_data *img)
{	
	if (keycode == 53)
	{
		mlx_destroy_window(img->mlx, img->mlx_win);
		exit (0);
	}
	if (keycode == 2) //move right
	{
	}
    return (0);
}

int			ft_windowclose_x(t_data *img)
{	
	(void)img;
	exit (0);
}

int     main(void)
{
	t_data	img;

/*---------------------------- */	
	int 	x;
	int		y;
	int		xsize;
    int		ysize;
	int		radius;
	
	x = 100;
	y = 100;
	xsize = 200;
	ysize = 200;
	radius = 50;
/*---------------------------- */
	
    img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(img.mlx, 1920, 1080);
	img.ad.addr = mlx_get_data_addr(img.img, &img.ad.bits_per_pixel, &img.ad.line_length, &img.ad.endian);

/*------------PRINT SQUARES ETC. --------------- */	
	//my_mlx_pixel_put(&img, 10, 10, 0x00FF0000);
	//print_square(&img, x, xsize, y, ysize);
	//print_triangle(&img, x, y, radius);
	print_full_square(&img, x, xsize, y, ysize);
/*---------------------------------------------- */	
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
/* ----------HOOKING EVENT-----------------*/ 
	mlx_hook(img.mlx_win, 2, 1L<<0, ft_keypress, &img);
	mlx_hook(img.mlx_win, 17, 1L<<17, ft_windowclose_x, &img);
	
/*----------------------------------------------*/
	mlx_loop(img.mlx);
}
