/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   read_scene.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 16:11:17 by msiemons      #+#    #+#                 */
/*   Updated: 2020/04/08 11:16:20 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int		check_save_path(int y, int i, t_base *base)
{
	int i_entry;
	int ret;

	ret = 0;
	i_entry = i;
	if ((check_pathstart(y, &i, base)) == 0)
	{
		if (TWOD[y][i_entry - 2] == 'N' && TWOD[y][i_entry - 1] == 'O')
			ret = save_path_substr(y, i, &base->read.no, base);
		else if (TWOD[y][i_entry - 2] == 'E' && TWOD[y][i_entry - 1] == 'A')
			ret = save_path_substr(y, i, &base->read.ea, base);
		else if (TWOD[y][i_entry - 2] == 'W' && TWOD[y][i_entry - 1] == 'E')
			ret = save_path_substr(y, i, &base->read.we, base);
		else if (TWOD[y][i_entry - 2] == 'S' && TWOD[y][i_entry - 1] == 'O')
			ret = save_path_substr(y, i, &base->read.so, base);
		else if (TWOD[y][i_entry - 1] == 'S')
			ret = save_path_substr(y, i, &base->read.sprite, base);
	}
	else
		return (1);
	if (ret > 0)
		return (1);
	return (0);
}

static int		check_save_resolution(int y, int i, t_base *base)
{
	if ((TWOD[y][i] < '0' && TWOD[y][i] != ' ') || TWOD[y][i] > '9')
		return (base->read.error = 2);
	if (!(base->read.render_x == -1 || base->read.render_y == -1))
		return (base->read.error = 3);
	base->read.render_x = cfr_itoa(y, &i, base, 0);
	base->read.render_y = cfr_itoa(y, &i, base, 0);
	if (base->read.render_x == -1 || base->read.render_y == -1)
		return (base->read.error = 4);
	if (base->read.render_x == 0 || base->read.render_y ==0)
		return (base->read.error = 7);
	return (cfr_endspaces(y, i, base));
}

static int		check_save_colors_cf(int y, int i, t_base *base)
{
	int entry_i;
	int	ret;
	
	entry_i = i - 1;
	base->read.red = -1;
	base->read.blue = -1;
	base->read.green = -1;
	if ((TWOD[y][i] < '0' && TWOD[y][i] != ' ') || TWOD[y][i] > '9')
		return (base->read.error = 2);
	base->read.red = cfr_itoa(y, &i, base, 0);
	base->read.blue = cfr_itoa(y, &i, base, 1);
	base->read.green = cfr_itoa(y, &i, base, 1);
	if (READ.red == -1 || READ.blue == -1 || READ.green == -1)
		return (base->read.error = 4);
	if (!((READ.red >= 0 &&  READ.red <= 255) && (READ.blue >= 0 &&
	READ.blue <= 255) && (READ.green >= 0 &&  READ.green <= 255)))
		return (base->read.error = 8);
	ret = create_trgb_colorcode(y, entry_i, base);
	if (ret > 0)
		return (1);
	return (cfr_endspaces(y, i, base));
}

/*
** First information is the type identifier. Each type of information from an
** element can be separated by one or more space(s).
*/

static int		check_scene_line(int *y, t_base *base)
{
	int		i;
	int		ret;

	i = 0;
	while (TWOD[*y][i] == ' ')
		i++;
	if (TWOD[*y][i] == 'C' || TWOD[*y][i] == 'F')
		ret = check_save_colors_cf(*y, (i + 1), base);
	else if (TWOD[*y][i] == 'R')
		ret = check_save_resolution(*y, (i + 1), base);
	else if ((TWOD[*y][i] == 'E' && TWOD[*y][i + 1] == 'A') || (TWOD[*y][i] == 'N'
	&& TWOD[*y][i + 1] == 'O') || (TWOD[*y][i] == 'W' && TWOD[*y][i + 1] == 'E')
	|| (TWOD[*y][i] == 'S' && (TWOD[*y][i + 1] == 'O')))
		ret = check_save_path(*y, (i + 2), base);
	else if (TWOD[*y][i] == 'S')
		ret = check_save_path(*y, (i + 1), base);
	else if (TWOD[*y][i] == '1')
		ret = check_map(&(*y), base);
	else
		base->read.error = 1;
	if (base->read.error > 0 || ret > 0)
		return (1);
	return (0);
}

int				read_scene_file(t_base *base)
{
	int		y;
	int		line;

	y = 0;
	initialise(base);
	while (TWOD[y])
	{
		line = check_scene_line(&y, base);
		if (line > 0)
			return (1);
		y++;
	}
	if (base->read.map_start == -1)
		return (base->read.error = 16);
	return (0);
}
