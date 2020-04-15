/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   print_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/15 10:53:03 by Maran         #+#    #+#                 */
/*   Updated: 2020/04/15 10:55:45 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			print_list(t_sprite *head)
{
    t_sprite *current;

	current = head;
    while (current != NULL) 
	{
        printf("y[%f]x[%f]\n", current->y, current->x);
        current = current->next;
    }
}