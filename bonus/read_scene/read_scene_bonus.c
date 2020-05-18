/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_scene_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 16:11:17 by msiemons      #+#    #+#                 */
/*   Updated: 2020/05/14 20:19:07 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static void		check_which_s(int y, int i_entry, int i, t_base *base)
{
	if (base->read.array[y][i_entry - 1] == '2')
		save_path_substr(y, i, &base->read.sprite2, base);
	else if (base->read.array[y][i_entry - 1] == '3')
		save_path_substr(y, i, &base->read.sprite3, base);
	else if (base->read.array[y][i_entry - 1] == '4')
		save_path_substr(y, i, &base->read.sprite4, base);
	else if (base->read.array[y][i_entry - 1] == 'O')
		save_path_substr(y, i, &base->read.so, base);
}

static int		check_save_path(int y, int i, t_base *base, t_read *read)
{
	int		i_entry;

	i_entry = i;
	if ((check_pathstart(y, &i, read->array)) == 0)
	{
		if (read->array[y][i_entry - 1] == 'C')
			save_path_substr(y, i, &read->ceiling, base);
		else if (read->array[y][i_entry - 1] == 'F')
			save_path_substr(y, i, &read->floor, base);
		else if (read->array[y][i_entry - 2] == 'N' &&
			read->array[y][i_entry - 1] == 'O')
			save_path_substr(y, i, &read->no, base);
		else if (read->array[y][i_entry - 2] == 'E' &&
			read->array[y][i_entry - 1] == 'A')
			save_path_substr(y, i, &read->ea, base);
		else if (read->array[y][i_entry - 2] == 'W' &&
			read->array[y][i_entry - 1] == 'E')
			save_path_substr(y, i, &read->we, base);
		else if (read->array[y][i_entry - 2] == 'S')
			check_which_s(y, i_entry, i, base);
	}
	else
		return (error_distr(base, 5));
	return (0);
}

static int		check_save_resolution(int y, int i, t_base *base, t_read *read)
{
	if ((read->array[y][i] < '0' && read->array[y][i] != ' ') ||
		read->array[y][i] > '9')
		return (error_distr(base, 2));
	if (!(read->render_x == -1 || read->render_y == -1))
		return (error_distr(base, 3));
	read->render_x = cfr_itoa(y, &i, read->array);
	read->render_y = cfr_itoa(y, &i, read->array);
	if (read->render_x == -1 || read->render_y == -1)
		return (error_distr(base, 4));
	if (read->render_x == 0 || read->render_y == 0)
		return (error_distr(base, 7));
	cfr_endspaces(y, i, base, read);
	return (0);
}

/*
** First information on the line in the .cub file is the type identifier.
** Each type of information from an element can be separated by one
** or more space(s).
*/

static int		check_scene_line(int *y, t_base *base, char **array)
{
	int		i;

	i = 0;
	while (array[*y][i] == ' ')
		i++;
	if (array[*y][i] == 'C' || array[*y][i] == 'F')
		check_save_path(*y, (i + 1), base, &base->read);
	else if ((array[*y][i] == 'E' && array[*y][i + 1] == 'A') ||
		(array[*y][i] == 'N' && array[*y][i + 1] == 'O') ||
		(array[*y][i] == 'W' && array[*y][i + 1] == 'E') ||
		(array[*y][i] == 'S' && array[*y][i + 1] == 'O') ||
		(array[*y][i] == 'S' &&
		(array[*y][i + 1] >= '2' && array[*y][i + 1] <= '4')))
		check_save_path(*y, (i + 2), base, &base->read);
	else if (array[*y][i] == 'R')
		check_save_resolution(*y, (i + 1), base, &base->read);
	else if (array[*y][i] == '1')
		check_map(&(*y), base, &base->read);
	else
		return (error_distr(base, 1));
	return (0);
}

int				read_scene_file(t_base *base, t_read *read)
{
	int		y;

	y = 0;
	initialise_read_scene(read, &base->head);
	while (read->array[y])
	{
		check_scene_line(&y, base, read->array);
		y++;
	}
	if (read->map_start == -1)
		return (error_distr(base, 16));
	return (0);
}
