/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_scene_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 16:11:17 by msiemons      #+#    #+#                 */
/*   Updated: 2020/05/13 15:50:58 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d_bonus.h"

static int		check_save_path(int y, int i, t_base *base, t_read *read)
{
	int		i_entry;

	i_entry = i;
	if ((check_pathstart(y, &i, read->array)) == 0)
	{
		if (read->array[y][i_entry - 2] == 'N' &&
			read->array[y][i_entry - 1] == 'O')
			save_path_substr(y, i, &read->no, base);
		else if (read->array[y][i_entry - 2] == 'E' &&
			read->array[y][i_entry - 1] == 'A')
			save_path_substr(y, i, &read->ea, base);
		else if (read->array[y][i_entry - 2] == 'W' &&
			read->array[y][i_entry - 1] == 'E')
			save_path_substr(y, i, &read->we, base);
		else if (read->array[y][i_entry - 2] == 'S' &&
			read->array[y][i_entry - 1] == 'O')
			save_path_substr(y, i, &read->so, base);
		else if (read->array[y][i_entry - 1] == 'S')
			save_path_substr(y, i, &read->sprite, base);
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
	read->render_x = cfr_itoa(y, &i, read->array, 0);
	read->render_y = cfr_itoa(y, &i, read->array, 0);
	if (read->render_x == -1 || read->render_y == -1)
		return (error_distr(base, 4));
	if (read->render_x == 0 || read->render_y == 0)
		return (error_distr(base, 7));
	cfr_endspaces(y, i, base, read);
	return (0);
}

static int		check_save_colors_cf(int y, int i, t_base *base, t_read *read)
{
	int		entry_i;

	entry_i = i - 1;
	read->red = -1;
	read->blue = -1;
	read->green = -1;
	if ((read->array[y][i] < '0' && read->array[y][i] != ' ') ||
		read->array[y][i] > '9')
		return (error_distr(base, 2));
	read->red = cfr_itoa(y, &i, read->array, 0);
	read->green = cfr_itoa(y, &i, read->array, 1);
	read->blue = cfr_itoa(y, &i, read->array, 1);
	if (read->red == -1 || read->blue == -1 || read->green == -1)
		return (error_distr(base, 4));
	if (!((read->red >= 0 && read->red <= 255) && (read->blue >= 0 &&
		read->blue <= 255) && (read->green >= 0 && read->green <= 255)))
		return (error_distr(base, 8));
	create_trgb_colorcode(y, entry_i, base, read);
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
		check_save_colors_cf(*y, (i + 1), base, &base->read);
	else if (array[*y][i] == 'R')
		check_save_resolution(*y, (i + 1), base, &base->read);
	else if ((array[*y][i] == 'E' && array[*y][i + 1] == 'A') ||
		(array[*y][i] == 'N' && array[*y][i + 1] == 'O') ||
		(array[*y][i] == 'W' && array[*y][i + 1] == 'E') ||
		(array[*y][i] == 'S' && (array[*y][i + 1] == 'O')))
		check_save_path(*y, (i + 2), base, &base->read);
	else if (array[*y][i] == 'S')
		check_save_path(*y, (i + 1), base, &base->read);
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
