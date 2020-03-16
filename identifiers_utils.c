/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   identifiers_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:25:07 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/16 16:59:58 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


/*
** base->read.error = 0 is default, 1 is error. Meaning the cub file is invalid
** Other values default -1. Because these numbers can be 0.
*/
void			initialise(t_base *base)
{
	base->read.error = 0;
	base->read.render_x = -1;
	base->read.render_y = -1;
	base->read.red = -1;
	base->read.blue = -1;
	base->read.green = -1;
	base->read.c_color = -1;
	base->read.f_color = -1;
	base->read.no = NULL;
	base->read.ea = NULL;
	base->read.so = NULL;
	base->read.we = NULL;
	base->read.sprite = NULL;
	base->read.map_start = -1;
	base->read.map_end = -1;
	base->read.pos = -1;
	base->read.x_pos = -1;
	base->read.y_pos = -1;
}
