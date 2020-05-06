/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_general.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:25:07 by msiemons      #+#    #+#                 */
/*   Updated: 2020/05/06 14:32:40 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Check of we sprites nog moeten freeeen.

void			free_array(t_read *read)
{
	int y;

	y = 0;
	while (read->array[y])
	{
		free(read->array[y]);
		y++;
	}
	free(read->array);
}

void			ll_freelist(t_ll_sprite *head)
{
	t_ll_sprite	*tmp;
	
	while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
	tmp = NULL;
}

void			free_cub_base(t_base *base)
{
	free_array(&base->read);
	if (base->read.no)
		free(base->read.no);
	if (base->read.ea)
		free(base->read.ea);
	if (base->read.so)
		free(base->read.so);
	if (base->read.we)
		free(base->read.we);
	if (base->read.sprite)
		free(base->read.sprite);
	if (base->head)
		ll_freelist(base->head);
	free(base);
}

//exit 0 is success
//exit(1) is failure
void			exit_game(t_base *base, int code, int error)
{
	int i;
	
	i = 0;
	if (base->zbuffer)
		free(base->zbuffer);
	while (i < 5)
	{
		if (base->tex[i].xpm_img)
			mlx_destroy_image(base->mlx.mlx, base->tex[i].xpm_img);
		i++;
	}
	if (base->mlx.img)
		mlx_destroy_image(base->mlx.mlx, base->mlx.img);
	if (base->mlx.mlx_win)
		mlx_destroy_window(base->mlx.mlx, base->mlx.mlx_win);
	if (code == 1)
		error_distr(base, error);
	else
	{
		free_cub_base(base);
		exit(code);
	}
}

void			initialise(t_read *read, t_ll_sprite **head)
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
