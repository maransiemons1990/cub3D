/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   save_sprites.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/04/14 18:35:38 by Maran         #+#    #+#                 */
/*   Updated: 2020/04/15 11:06:41 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_sprite		*create_node(t_sprite *next, double y, double x)
{
	t_sprite	*new_node;

	new_node = (t_sprite*)malloc(sizeof(t_sprite));
	if (!new_node)
		return (NULL);
	new_node->x = x;
	new_node->y = y;
	new_node->next = next;
	return (new_node);
}


t_sprite		*prepend(t_sprite *head, double y, double x)
{
	t_sprite	*new_node;

	new_node = create_node(head, y, x);
	head = new_node;
	return (head);
}

int				search(t_sprite *head, double y, double x)
{
	t_sprite *cursor;
	
	cursor = head;
	while (cursor != NULL)
	{
		if (cursor->x == x && cursor->y == y)
			return (1);
		cursor = cursor->next;
	}
	return (0);
}

void		save_sprite_coordinates(t_base *base, double y, double x)
{
	//t_sprite	*head;
	
	//head = NULL;            //ergens anders?
	if (search(base->head, y, x))
	{
		printf("ALREADY EXISTS\n");	
		return;
	}
	else
		base->head = prepend(base->head, y, x);
}



	//HOE KAN IK EEN ONBEKEND AANTAL SPRITES OPSLAAN ZONDER EERST TE TELLEN EN DAN NOG EEN KEER LANGS OM OP TE SLAAN.
	/*t_sprite	sprite[base->read.nb_sprites];
	int 		n;

	n = 0;
	while (n < base->read.nb_sprites)
	{
		//printf("n[%d] < nb[%d]\n", n, base->read.nb_sprites);
		if (sprite[n].x == x + 0.5 && sprite[n].y == y + 0.5)
		{
			printf("retun\n");
			return;
		}
		n++;
	}
	sprite[base->read.nb_sprites].x = x + 0.5;
	printf("Sprite[%d].x = [%f]\n", base->read.nb_sprites, sprite[base->read.nb_sprites].x);
	sprite[base->read.nb_sprites].y = y + 0.5;
	printf("Sprite[%d].y = [%f]\n", base->read.nb_sprites, sprite[base->read.nb_sprites].y);
	base->read.nb_sprites++;
	printf("---%d---\n", base->read.nb_sprites);
	printf("----Sprite.x = [%f]\n", sprite[0].x);
	printf("----Sprite.y = [%f]\n", sprite[0].y);
	*/
