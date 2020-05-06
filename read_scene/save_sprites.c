/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 18:35:38 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/06 11:17:50 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Swapped the data content of the node. Not the whole node. So the node blocks don't move only the content.
** Adresses of the nodes stay with the node. Seemed easier then switching the whole node!
*/

static void			swap(double *i, double *j)
{
	double 		tmp;
	
	tmp = *i;
	*i = *j;
	*j = tmp;
}

void				ll_sort_sprites_swap_data(t_base  *base)
{
	t_ll_sprite	*i;
	t_ll_sprite	*j;

	i = base->head;
	while (i != NULL)
	{
		j = i->next;
		while(j != NULL)
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

/*
** Problem: how can I save the coordinates of an unknown number of sprites.
** Without counting them first and then scanning again to save them.
** Solution: linked list have a dynamic listsize contrary to the fixed size of arrays.
**
**         head             second node          third node 
**           |                   |                   |  
**           |                   |                   |  
**    +------+------+     +------+------+     +------+------+  
**    | x= 8 | o--------> | x= 15| o--------> | x= 31| NULL |
**    | y= 17| o--------> | x= 20| o--------> | y= 35| NULL |
**    +------+------+     +------+------+     +------+------+  
*/

void				ll_count_sprites(t_base *base)
{
	t_ll_sprite 	*current;
	
	base->read.nb_sprites = 0;
	current = base->head;
	while (current != NULL)
	{
		current = current->next;
		base->read.nb_sprites++;
	}
	
}

static t_ll_sprite		*ll_create_node(t_base *base, double y, double x)
{
	t_ll_sprite	*new_node;

	x = x + 0.5;
	y = y + 0.5;
	new_node = (t_ll_sprite *)malloc(sizeof(t_ll_sprite));
	if (!new_node)
		error_distr(base, 6);
	new_node->x = x;
	new_node->y = y;
	new_node->distance = ((base->read.x_pos - x) * (base->read.x_pos - x)
		+ (base->read.y_pos - y) * (base->read.y_pos - y));
	new_node->next = base->head;
	return (new_node);
}

static t_ll_sprite		*ll_add_new_front(t_base *base, double y, double x)
{
	t_ll_sprite	*new_node;

	new_node = ll_create_node(base, y, x);
	base->head = new_node;
	return (base->head);
}

static int			ll_search(t_ll_sprite *head, double y, double x)
{
	t_ll_sprite	*current;
	
	current = head;
	while (current != NULL)
	{
		if (current->x == (x + 0.5) && current->y == (y + 0.5))
			return (1);
		current = current->next;
	}
	return (0);
}

/*
** First check if node already exist in the linked list with ll_search.
** Because the floodfill function returns 4 times to the same coordinates.
*/
void		save_sprite_coordinates(t_base *base, double y, double x)
{
	if (ll_search(base->head, y, x))
		return;
	else
		base->head = ll_add_new_front(base, y, x);
}
