/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   floor_ceiling.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 14:53:21 by Maran         #+#    #+#                 */
/*   Updated: 2020/04/30 14:12:55 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	floor_ceiling_smooth(t_base *base)
{
	int y;
	int x;
	int color;

	y = base->read.render_y / 2 + 1;
	while (y < base->read.render_y)
    {
		x = 0;
		while (x < base->read.render_x)
      	{
			color = base->read.f_color;
        	//color = (color >> 1) & 8355711; // make a bit darker
			my_mlx_pixel_put(base, x, y, color);
        	color = base->read.c_color;
        	//color = (color >> 1) & 8355711; // make a bit darker
			my_mlx_pixel_put(base, x, (base->read.render_y - y - 1), color);
			x++;
      	}
	  y++;
    }
}
