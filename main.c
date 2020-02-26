/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/25 20:13:12 by msiemons       #+#    #+#                */
/*   Updated: 2020/02/26 18:09:24 by msiemons      ########   odam.nl         */
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

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void		print_square(t_data *img, int x, int xsize, int y, int ysize)
{
	int org_x;
	int org_xsize;

	org_x = x;
	org_xsize = xsize;
	while (xsize > 0)
	{
		my_mlx_pixel_put(&*img, x, y, 0x00FF0000);
		my_mlx_pixel_put(&*img, x, y + ysize, 0x00FF0000);
		xsize--;
		x++;
	}
	while (ysize > 0)
	{
		my_mlx_pixel_put(&*img, org_x, y, 0x00FF0000);
		my_mlx_pixel_put(&*img, org_x + org_xsize, y, 0x00FF0000);
		ysize--;
		y++;
	}
}

void	print_triangle(t_data *img, int x, int y, int radius)
{
	int org_x;
	int org_y;
	int org_radius;
	
	org_x = x;
	org_y = y;
	org_radius = radius;
	my_mlx_pixel_put(&*img, x, y, 0x00FF0000);
	while(x < org_x + radius)
	{
		my_mlx_pixel_put(&*img, x, y - radius, 0x00FF0000);
		x++;
		y++;
	}
	x = org_x;
	y = org_y;
	while(x > org_x - radius)
	{
		my_mlx_pixel_put(&*img, x, y - radius, 0x00FF0000);
		x--;
		y++;
	}
	x = org_x;
	y = org_y;
	while(radius > 0)
	{
		my_mlx_pixel_put(&*img, x - radius, y, 0x00FF0000);
		my_mlx_pixel_put(&*img, x + radius, y, 0x00FF0000);
		radius--;
	}
}

void		print_full_square(t_data *img, int x, int xsize, int y, int ysize)
{
	int org_x;
	int org_xsize;
	int color;

	org_x = x;
	org_xsize = xsize;
	color = 16711680; //16711680 == 0x00FF0000;
	while(ysize > 0)
	{
		xsize = org_xsize;
		x = org_x;
		while (xsize > 0)
		{
			my_mlx_pixel_put(&*img, x, y, color);
			xsize--;
			x++;
			color++;
		}
		y++;
		ysize--;
	}
}

int     main(void)
{
    void    *mlx;
	void    *mlx_win;
	t_data	img;
	
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
	
	
    mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	
	//my_mlx_pixel_put(&img, 10, 10, 0x00FF0000);
	//print_square(&img, x, xsize, y, ysize);
	//print_triangle(&img, x, y, radius);
	print_full_square(&img, x, xsize, y, ysize);
	
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}

/* Om een rode pixel te printen op window */
	// mlx_pixel_put(mlx, mlx_win, 10, 10, 16711680);