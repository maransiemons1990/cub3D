/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/24 16:30:07 by Maran          #+#    #+#                */
/*   Updated: 2020/03/24 18:33:47 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void            my_mlx_pixel_put(t_base *base, int x, int y, int color)
{
    char    *dst;

    dst = base->mlx.addr + (y * base->mlx.line_length + x * (base->mlx.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void		print_full_square(t_base *base, int x, int xsize, int y, int ysize)
{
	int org_x;
	int org_xsize;
	int color;

	org_x = x;
	org_xsize = xsize;
	color = 65280; //16711680 == 0x00FF0000;
	while(ysize > 0)
	{
		xsize = org_xsize;
		x = org_x;
		while (xsize > 0)
		{
			my_mlx_pixel_put(base, x, y, color);
			xsize--;
			x++;
			color++;
		}
		y++;
		ysize--;
	}
}

//Segfault met destroy window. Uitzoeken.
int             ft_keypress(int keycode, t_base *img)
{	
	if (keycode == 53)
	{
		(void)img;
		//mlx_destroy_window(img->mlx.mlx, img->mlx.mlx_win);
		exit (0);
	}
    return (0);
}

int			ft_windowclose_x(t_base *img)
{	
	(void)img;
	exit (0);
}

int				mlx(t_base *base)
{
	base->mlx.mlx = mlx_init();
	base->mlx.mlx_win = mlx_new_window(base->mlx.mlx, 1920, 1080, "Hello world!");
	base->mlx.img = mlx_new_image(base->mlx.mlx, 600, 800);
	base->mlx.addr = mlx_get_data_addr(base->mlx.img, &base->mlx.bits_per_pixel, &base->mlx.line_length, &base->mlx.endian);
	
	print_full_square(base, 100, 200, 100, 200);

	mlx_put_image_to_window(base->mlx.mlx, base->mlx.mlx_win, base->mlx.img, 0, 0);
// /* ----------HOOKING EVENT-----------------*/ 
	mlx_hook(base->mlx.mlx_win, 2, 1L<<0, ft_keypress, &base);
	mlx_hook(base->mlx.mlx_win, 17, 1L<<17, ft_windowclose_x, &base);
	
// /*----------------------------------------------*/
	mlx_loop(base->mlx.mlx);
	return (0);
}