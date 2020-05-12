/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_game.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/08 11:06:37 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/12 18:35:27 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void				free_array(t_read *read)
{
	int		y;

	y = 0;
	while (read->array[y])
	{
		free(read->array[y]);
		y++;
	}
	free(read->array);
}

static void			ll_freelist(t_ll_sprite *head)
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

void				free_cub_base(t_base *base)
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

/*
** Exit code (0) indicates successful program termination
** Exit code (1) indicates unsucessful termination.
*/

void				exit_game(t_base *base, int code, int error)
{
	int		i;

	i = 0;
	if (base->zbuffer)
		free(base->zbuffer);
	while (i < 5)
	{
		if (base->tex[i].xpm_img)
		{
			mlx_destroy_image(base->mlx.mlx, base->tex[i].xpm_img);
			base->tex[i].xpm_img = NULL;
		}
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

