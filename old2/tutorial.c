/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tutorial.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/28 13:11:26 by msiemons       #+#    #+#                */
/*   Updated: 2020/02/28 21:19:48 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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