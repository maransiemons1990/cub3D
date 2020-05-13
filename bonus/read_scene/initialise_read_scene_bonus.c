/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialise_read_scene_bonus.c                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:25:07 by msiemons      #+#    #+#                 */
/*   Updated: 2020/05/13 15:50:49 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d_bonus.h"

void				initialise_read_scene(t_read *read, t_ll_sprite **head)
{
	read->render_x = -1;
	read->render_y = -1;
	read->c_color = -1;
	read->f_color = -1;
	read->no = NULL;
	read->ea = NULL;
	read->so = NULL;
	read->we = NULL;
	read->sprite = NULL;
	read->map_start = -1;
	read->map_end = -1;
	read->pos = -1;
	read->x_pos = -1;
	read->y_pos = -1;
	*head = NULL;
}
