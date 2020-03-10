/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   identifiers_utils.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:25:07 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/10 15:49:46 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			check_identifiers_valid(t_base *base)
{
	if (base->read.render_x > 0 && base->read.render_y > 0 &&
		(base->read.c_red >= 0 && base->read.c_red <= 255) &&
		(base->read.c_blue >= 0 && base->read.c_blue <= 255) &&
		(base->read.c_green >= 0 && base->read.c_green <= 255) &&
		(base->read.f_red >= 0 && base->read.f_red <= 255) &&
		(base->read.f_blue >= 0 && base->read.f_blue <= 255) &&
		(base->read.f_green >= 0 && base->read.f_green <= 255) &&
		base->read.no != NULL && base->read.ea != NULL && 
		base->read.so != NULL && base->read.we != NULL && 
		base->read.sprite != NULL)
		return (0);
	else
		return (1);
	
}

/*
** base->read.error = 0 is default, 1 is error. Meaning the cub file is invalid
** Other values default -1. Because these numbers can be 0.
*/
void			initialise(t_base *base)
{
	base->read.error = 0;
	base->read.render_x = -1;
	base->read.render_y = -1;
	base->read.c_red = -1;
	base->read.c_blue = -1;
	base->read.c_green = -1;
	base->read.f_red = -1;
	base->read.f_blue = -1;
	base->read.f_green = -1;
	base->read.no = NULL;
	base->read.ea = NULL;
	base->read.so = NULL;
	base->read.we = NULL;
	base->read.sprite = NULL;
}

//open(str, O_RDONLY )
// if -1 bestaat niet.
