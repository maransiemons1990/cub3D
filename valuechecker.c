/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valuechecker.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 11:43:48 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/11 17:07:59 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	valuechecker(t_base *base)
{
	printf("R: render_x=[%d], render_y[%d]\n", base->read.render_x, base->read.render_y);
	
	//printf("C: c_red=[%d], c__blue[%d], c_green[%d]\n", base->read.c_red, base->read.c_blue, base->read.c_green);

	printf("C: c_color=[%d]\n", base->read.c_color);
	printf("F: f_color=[%d]\n", base->read.f_color);
	
	printf("NO: no=[%s]\n", base->read.no);
	printf("SO: so=[%s]\n", base->read.so);
	printf("EA: ea=[%s]\n", base->read.ea);
	printf("WE: we=[%s]\n", base->read.we);

	printf("S: sprite=[%s]\n", base->read.sprite);

	printf("POS: pos=[%c], x_pos[%d], y_pos[%d]\n", base->read.pos, base->read.x_pos, base->read.y_pos);
	
}