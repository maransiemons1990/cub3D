/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   untextured_verline.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/08 10:57:28 by Maran         #+#    #+#                 */
/*   Updated: 2020/04/08 10:58:02 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

void			verLine(t_base *base, int x)
{
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		color;
    double	perpWallDist;
	
	//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
    if (base->game.side == 0)
		perpWallDist = (base->game.mapX - base->read.x_pos + (1 - base->game.stepX) / 2) / base->game.rayDirX;
	else
		perpWallDist = (base->game.mapY - base->read.y_pos + (1 - base->game.stepY) / 2) / base->game.rayDirY;
	//Calculate height of line to draw on screen
   	lineHeight = (int)(base->read.render_y / perpWallDist);
   	//calculate lowest and highest pixel to fill in current stripe
	drawStart = -lineHeight / 2 + base->read.render_y / 2;
	if(drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + base->read.render_y / 2;
	if(drawEnd >= base->read.render_y)
		drawEnd = base->read.render_y - 1;
	//   printf("----------------------------------------------\n");
    //choose wall color
    color = 16711680;
    //give x and y sides different brightness
    if (base->game.side == 1) 
	 	color = 16728899;
	//printf(" x =[%d], start=[%d], end=[%d], color=[%d]\n", x, drawStart, drawEnd, color);
	while (drawStart < drawEnd)
	{
		my_mlx_pixel_put(base, x, drawStart, color);
		drawStart++;
	}
}
