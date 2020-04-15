/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 10:53:03 by Maran         #+#    #+#                 */
/*   Updated: 2020/04/15 14:36:53 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			print_list(t_base *base)
{
    t_sprite *current;

	current = base->head;
    while (current != NULL) 
	{
        printf("[%p] -- y[%f]x[%f] - distance[%f]\n", current, current->y, current->x, current->distance);
        current = current->next;
    }
    //printf("Nb_sprites: %d\n", base->read.nb_sprites);
}