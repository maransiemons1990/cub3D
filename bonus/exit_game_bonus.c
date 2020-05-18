/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit_game_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/08 11:06:37 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/14 20:43:32 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	if (base->read.sprite2)
		free(base->read.sprite2);
	if (base->read.sprite3)
		free(base->read.sprite3);
	if (base->read.sprite4)
		free(base->read.sprite4);
	if (base->read.floor)
		free(base->read.floor);
	if (base->read.ceiling)
		free(base->read.ceiling);
	if (base->head)
		ll_freelist(base->head);
	free(base);
}

static void			destroy_texture(t_base *base)
{
	int		i;

	i = 0;
	while (i < 9)
	{
		if (base->tex[i].xpm_img)
		{
			mlx_destroy_image(base->mlx.mlx, base->tex[i].xpm_img);
			base->tex[i].xpm_img = NULL;
		}
		i++;
	}
}

/*
** Exit code (0) indicates successful program termination
** Exit code (1) indicates unsucessful termination.
*/

void				exit_game(t_base *base, int code, int error)
{
	if (base->zbuffer)
		free(base->zbuffer);
	destroy_texture(base);
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
