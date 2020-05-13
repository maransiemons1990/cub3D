/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_utils_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/16 15:34:37 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/13 15:50:45 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d_bonus.h"

/*
** Looks for first character in line except spaces. Returns position.
*/

static int		first_char(char *y)
{
	int		i;

	i = 0;
	while (y[i] == ' ')
		i++;
	return (i);
}

/*
** Looks for last character in line except spaces. Returns position.
*/

int				last_char_save_pos(int y, t_base *base, t_read *read,
									char **array)
{
	int		i;

	i = 0;
	while (array[y][i])
	{
		if (array[y][i] != '0' && array[y][i] != '1' && array[y][i] != '2'
			&& array[y][i] != ' ' && array[y][i] != 'N' && array[y][i] != 'S'
			&& array[y][i] != 'E' && array[y][i] != 'W')
			return (error_distr(base, 10));
		if (array[y][i] == 'N' || array[y][i] == 'S' || array[y][i] == 'E' ||
		array[y][i] == 'W')
		{
			if (read->pos != -1 && y != read->y_pos &&
			i != read->x_pos)
				return (error_distr(base, 11));
			read->pos = array[y][i];
			read->x_pos = i;
			read->y_pos = y;
		}
		i++;
	}
	while (array[y][i] == ' ' || array[y][i] == '\0')
		i--;
	return (i);
}

/*
** Checks position last char (no space) of two adjacent lines.
** The difference between those 2 char's + 1 should consist of 1's.
** 0000111 --> correct.
** 00001
*/

int				align_dif_back(int y, t_base *base, t_read *read)
{
	int		back1;
	int		back2;
	int		dif;
	int		count;

	count = 0;
	back1 = last_char_save_pos(y, base, read, read->array);
	back2 = last_char_save_pos(y + 1, base, read, read->array);
	dif = back1 - back2;
	while (dif > (count - 1))
	{
		if (read->array[y][back1 - count] != '1' &&
			read->array[y][back1 - count] != ' ')
			return (error_distr(base, 12));
		count++;
	}
	while (dif < 1)
	{
		if (read->array[y + 1][back2 + dif] != '1' &&
			read->array[y + 1][back2 + dif] != ' ')
			return (error_distr(base, 12));
		dif++;
	}
	return (0);
}

/*
** Checks position first char (no space) of two adjacent lines.
** The difference between those 2 char's + 1 should consist of 1's.
**   1000 --> correct.
** 111000
*/

int				align_dif_front(char *s1, char *s2)
{
	int		front1;
	int		front2;
	int		dif;
	int		count;

	count = 0;
	front1 = first_char(s1);
	front2 = first_char(s2);
	dif = front1 - front2;
	while (dif > (count - 1))
	{
		if (s2[front2 + count] != '1' && s2[front2 + count] != ' ')
			return (1);
		count++;
	}
	while (dif < 1)
	{
		if (s1[front1 - dif] != '1' && s1[front1 - dif] != ' ')
			return (1);
		dif++;
	}
	return (0);
}

/*
** When a space (' ') character appears in a wall,
** the adjacent elements can only consist of 1's and spaces.
*/

int				space_in_wall(int y, int i, char **array, t_read *read)
{
	if (array[y][i - 1] != '1' && array[y][i - 1] != ' ')
		return (1);
	if (array[y][i + 1] != '1' && array[y][i + 1] != ' ')
		return (1);
	if (y == read->map_start)
	{
		if (array[y + 1][i] != '1' && array[y + 1][i] != ' ')
			return (1);
		if (array[y + 1][i - 1] != '1' && array[y + 1][i - 1] != ' ')
			return (1);
		if (array[y + 1][i + 1] != '1' && array[y + 1][i + 1] != ' ')
			return (1);
	}
	if (y == read->map_end)
	{
		if (array[y - 1][i] != '1' && array[y - 1][i] != ' ')
			return (1);
		if (array[y - 1][i - 1] != '1' && array[y - 1][i - 1] != ' ')
			return (1);
		if (array[y - 1][i + 1] != '1' && array[y - 1][i + 1] != ' ')
			return (1);
	}
	return (0);
}
