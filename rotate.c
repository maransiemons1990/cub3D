/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/28 12:21:14 by Maran         #+#    #+#                 */
/*   Updated: 2020/04/28 12:22:07 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


void			rotate(t_base *base)
{
	double	oldDirX;
	double circle;
	double	oldPlaneX;
	
	circle = 
	if (base->game.rotate_right == 1)
	{
		//printf("ROTATE LEFT rotspeed[%f]", base->game.rotspeed);
		oldDirX = base->game.dirX;
		base->game.dirX = base->game.dirX * cos(base->game.rotspeed) - base->game.dirY * sin(base->game.rotspeed);
		base->game.dirY = oldDirX * sin(base->game.rotspeed) + base->game.dirY * cos(base->game.rotspeed);
		oldPlaneX = base->game.planeX;
		base->game.planeX = base->game.planeX * cos(base->game.rotspeed) - base->game.planeY * sin(base->game.rotspeed);
		base->game.planeY = oldPlaneX * sin(base->game.rotspeed) + base->game.planeY * cos(base->game.rotspeed);
		printf("ROTATE RIGHT dirX[%f], dirY[%f], planeX[%f], planeY[%f]\n", base->game.dirX, base->game.dirY, base->game.planeX, base->game.planeY);
	}
	if (base->game.rotate_left == 1)
	{
		oldDirX = base->game.dirX;
		base->game.dirX = base->game.dirX * cos(-base->game.rotspeed) - base->game.dirY * sin(-base->game.rotspeed);
		base->game.dirY = oldDirX * sin(-base->game.rotspeed) + base->game.dirY * cos(-base->game.rotspeed);
		oldPlaneX = base->game.planeX;
		base->game.planeX = base->game.planeX * cos(-base->game.rotspeed) - base->game.planeY * sin(-base->game.rotspeed);
		base->game.planeY = oldPlaneX * sin(-base->game.rotspeed) + base->game.planeY * cos(-base->game.rotspeed);
		printf("ROTATE LEFT dirX[%f], dirY[%f], planeX[%f], planeY[%f]\n", base->game.dirX, base->game.dirY, base->game.planeX, base->game.planeY);
	}
}


