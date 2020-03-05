/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valuechecker.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/05 11:43:48 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/05 11:48:36 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	valuechecker(t_base *base)
{
	printf("R: render_x=[%d], render_y[%d]\n", base->read.render_x, base->read.render_y);
}