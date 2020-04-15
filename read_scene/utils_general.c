/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_general.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:25:07 by msiemons      #+#    #+#                 */
/*   Updated: 2020/04/15 11:05:38 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Check of we sprites nog moeten freeeen.

void			end_free(t_base *base)
{
	int y;

	y = 0;
	while (base->read.array[y])
	{
		free(base->read.array[y]);
		y++;
	}
	free(base->read.array);
	free(base->read.no);
	free(base->read.ea);
	free(base->read.so);
	free(base->read.we);
	free(base->read.sprite);
	free(base);
}

void			initialise(t_base *base)
{
	base->read.error = 0;
	base->read.render_x = -1;
	base->read.render_y = -1;
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
	//
	base->head = NULL;
	//
}
