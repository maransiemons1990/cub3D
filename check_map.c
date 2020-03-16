/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 13:47:21 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/16 15:39:42 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Spaces are a valid part of the map. Except when player can reach a space.
** Or when the space is in a wall and therefore the map is not closed by walls.
** Flood fill checks if player can reach a space.
*/

static int		flood_fill(t_base *base, int y, int x)
{
	if (TWOD[y][x] == '+' || TWOD[y][x] == '1' || TWOD[y][x] == '2')
		return (0);
	if (TWOD[y][x]== '\0' || y <= base->read.map_start ||
	y >= base->read.map_end)
		return (base->read.error = 12);	
	if (TWOD[y][x] == ' ')
		return (base->read.error = 13);
    if (TWOD[y][x]!= '0' && TWOD[y][x] != base->read.pos)
		return (base->read.error = 10);
    TWOD[y][x] = '+';
    flood_fill(base, y - 1, x);
    flood_fill(base, y, x + 1);
    flood_fill(base, y + 1, x);
    flood_fill(base, y, x - 1);
    return (0);
}

/*
** When the walls don't align edges and corners are created.
** Check if all characters who touch empty space consist of 1's.
*/

static int		check_edges_wall(int *y, t_base *base)
{
	int 	back;
	int 	front;

	while (*y != base->read.map_end)
	{
		front = 0;
		back = 0;
		front = align_dif_front(TWOD[*y], TWOD[*y + 1]);
		if (front == 1)
			return (base->read.error = 12);
		back = align_dif_back(*y, base);
		if (back > 0)
			return (1);
		(*y)++;
	}
	return (0);
}

/*
** Walls can be composed of 1's and under condition of spaces.
*/

static int		check_walls_first_last(int y, t_base *base)
{
	int 	i;
	int		last;
	int 	ret;
	
	i = 0;
	last = last_char_save_pos(y, base);
	if (base->read.error > 0)
		return (1);
	while(TWOD[y][i] == ' ')
			i++;
	while (i <= last)
	{
		if (TWOD[y][i] == '1')
			i++;
		else if (TWOD[y][i] == ' ')
		{
			ret = space_in_wall(y, i, base);
			if (ret == 1)
				return (base->read.error = 12);
			i++;
		}
		else
			return (base->read.error = 12);
	}
	return (0);
}

int				check_map(int *y, t_base *base)
{
	int 	ret;

	base->read.map_start = *y;
	while (base->read.array[*y])
		(*y)++;
	base->read.map_end = *y - 1;
	*y = base->read.map_start;
	ret = check_walls_first_last(*y, base);
	if (ret > 0)
		return (1);
	ret = check_edges_wall(&(*y), base);
	if (ret > 0)
		return (1);
	ret = check_walls_first_last(*y, base);
	if (ret > 0)
		return (1);
	ret = flood_fill(base, base->read.y_pos, base->read.x_pos);
	if (ret > 0)
		return (1);
	return (0);
}
