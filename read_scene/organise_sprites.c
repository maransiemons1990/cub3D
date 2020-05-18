/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   organise_sprites.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/08 11:12:10 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/11 15:53:46 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Swapped the data content of the node. Not the whole node. So the node blocks
** don't move only the content. Adresses of the nodes stay with the node.
*/

static void			swap(double *i, double *j)
{
	double			tmp;

	tmp = *i;
	*i = *j;
	*j = tmp;
}

void				ll_sort_sprites_swap_data(t_base *base)
{
	t_ll_sprite		*i;
	t_ll_sprite		*j;

	i = base->head;
	while (i != NULL)
	{
		j = i->next;
		while (j != NULL)
		{
			if (i->distance < j->distance)
			{
				swap(&i->x, &j->x);
				swap(&i->y, &j->y);
				swap(&i->distance, &j->distance);
			}
			j = j->next;
		}
		i = i->next;
	}
}

void				ll_count_sprites(t_base *base)
{
	t_ll_sprite		*current;

	base->read.nb_sprites = 0;
	current = base->head;
	while (current != NULL)
	{
		current = current->next;
		base->read.nb_sprites++;
	}
}
