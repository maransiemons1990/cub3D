/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 13:47:21 by msiemons      #+#    #+#                 */
/*   Updated: 2020/05/13 15:50:40 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d_bonus.h"

/*
** Spaces are a valid part of the map. Except when player can reach a space.
** Or when the space is in a wall and therefore the map is not closed by walls.
** Flood fill checks if player can reach a space (' ').
*/

static int			flood_fill(t_base *base, int y, int x, char **array)
{
	if (array[y][x] == '+' || array[y][x] == '1')
		return (0);
	if (array[y][x] == '2')
	{
		save_sprite_coordinates(base, y, x);
		return (0);
	}
	if (array[y][x] == '\0' || y <= base->read.map_start ||
		y >= base->read.map_end)
		return (error_distr(base, 12));
	if (array[y][x] == ' ')
		return (error_distr(base, 13));
	if (array[y][x] != '0' && array[y][x] != base->read.pos)
		return (error_distr(base, 10));
	array[y][x] = '+';
	flood_fill(base, y - 1, x, array);
	flood_fill(base, y, x + 1, array);
	flood_fill(base, y + 1, x, array);
	flood_fill(base, y, x - 1, array);
	return (0);
}

/*
** When the walls don't align edges and corners are created.
** Check if all characters who touch empty space (' ') consist of 1's.
*/

static int			check_wall_edges(int *y, t_base *base, t_read *read)
{
	int		front;

	while (*y != read->map_end)
	{
		front = 0;
		front = align_dif_front(read->array[*y], read->array[*y + 1]);
		if (front == 1)
			return (error_distr(base, 12));
		align_dif_back(*y, base, read);
		(*y)++;
	}
	if (read->pos == -1)
		return (error_distr(base, 15));
	return (0);
}

/*
** Walls can be composed of 1's and under condition out of spaces.
** Spaces in walls are allowed when they don't touch empty floor space ('0').
*/

static int			check_walls_first_last(int y, t_base *base, t_read *read)
{
	int		i;
	int		last;
	int		ret;

	i = 0;
	last = last_char_save_pos(y, base, read, read->array);
	while (read->array[y][i] == ' ')
		i++;
	while (i <= last)
	{
		if (read->array[y][i] == '1')
			i++;
		else if (read->array[y][i] == ' ')
		{
			ret = space_in_wall(y, i, read->array, read);
			if (ret == 1)
				return (error_distr(base, 12));
			i++;
		}
		else
			return (error_distr(base, 12));
	}
	return (0);
}

static int			check_elements_complete(t_base *base, t_read *read)
{
	if (read->render_x == -1 || read->render_y == -1 ||
	read->c_color == -1 || read->f_color == -1 ||
	read->no == NULL || read->ea == NULL ||
	read->so == NULL || read->we == NULL ||
	read->sprite == NULL)
		return (error_distr(base, 14));
	return (0);
}

int					check_map(int *y, t_base *base, t_read *read)
{
	check_elements_complete(base, read);
	read->map_start = *y;
	while (read->array[*y])
		(*y)++;
	read->map_end = *y - 1;
	*y = read->map_start;
	check_walls_first_last(*y, base, read);
	check_wall_edges(&(*y), base, read);
	check_walls_first_last(*y, base, read);
	flood_fill(base, read->y_pos, read->x_pos, read->array);
	ll_count_sprites(base);
	ll_sort_sprites_swap_data(base);
	return (0);
}
