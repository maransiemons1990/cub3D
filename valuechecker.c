/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valuechecker.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 11:43:48 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/05 18:50:59 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	valuechecker(t_base *base)
{
	printf("R: render_x=[%d], render_y[%d]\n", base->read.render_x, base->read.render_y);
	
	printf("C: c_red=[%d], c__blue[%d], c_green[%d]\n", base->read.c_red, base->read.c_blue, base->read.c_green);
	printf("F: f_red=[%d], f__blue[%d], f_green[%d]\n", base->read.f_red, base->read.f_blue, base->read.f_green);

	printf("NO: no=[%s]\n", base->read.no);
	printf("SO: so=[%s]\n", base->read.so);
	printf("EA: ea=[%s]\n", base->read.ea);
	printf("WE: we=[%s]\n", base->read.we);

	printf("S: sprite=[%s]\n", base->read.sprite);
}