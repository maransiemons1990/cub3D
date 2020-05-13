/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_sprites_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 18:35:38 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/13 17:59:51 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static t_ll_sprite	*ll_create_node(t_base *base, double y, double x)
{
	t_ll_sprite		*new_node;

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

static t_ll_sprite	*ll_add_new_front(t_base *base, double y, double x)
{
	t_ll_sprite		*new_node;

	new_node = ll_create_node(base, y, x);
	base->head = new_node;
	return (base->head);
}

/*
** First check if node already exist in the linked list with ll_search.
** Because the floodfill function returns 4 times to the same coordinates.
** Otherwise each sprite coordinate would be saved 4 times.
*/

static int			ll_search(t_ll_sprite *head, double y, double x)
{
	t_ll_sprite		*current;

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
** How can I save the coordinates of an unknown number of sprites.
** Without counting them first and then scanning again to save them.
** Solution: linked list have a dynamic listsize contrary to the
** fixed size of arrays.
**
**         head             second node          third node
**           |                   |                   |
**           |                   |                   |
**    +------+------+     +------+------+     +------+------+
**    | x= 8 | o--------> | x= 15| o--------> | x= 31| NULL |
**    | y= 17| o--------> | y= 20| o--------> | y= 35| NULL |
**    +------+------+     +------+------+     +------+------+
*/

void				save_sprite_coordinates(t_base *base, double y, double x)
{
	if (ll_search(base->head, y, x))
		return ;
	else
		base->head = ll_add_new_front(base, y, x);
}
