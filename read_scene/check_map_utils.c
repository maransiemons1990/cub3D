/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/16 15:34:37 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/01 19:48:48 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*
** Looks for first character in line except spaces. Returns position.
*/

static int		first_char(char *y)
{
	int 	i;

	i = 0;
	while (y[i] == ' ')
	 	i++;
	return (i);
}

/*
** Looks for last character in line except spaces. Returns position.
*/

int				last_char_save_pos(int y, t_base *base)
{
	int 	i;

	i = 0;
	while(TWOD[y][i])
	{
		if (TWOD[y][i] != '0' && TWOD[y][i] != '1' && TWOD[y][i] != '2'
		&& TWOD[y][i] != ' ' && TWOD[y][i] != 'N' && TWOD[y][i] != 'S' &&
		TWOD[y][i] != 'E' && TWOD[y][i] != 'W')
			return (error_distr(base, 10));
		if (TWOD[y][i] == 'N' || TWOD[y][i] == 'S' || TWOD[y][i] == 'E' ||
		TWOD[y][i] =='W')
		{
			if (base->read.pos != -1 && y != base->read.y_pos &&
			i != base->read.x_pos)
				return (error_distr(base, 11));
			base->read.pos = TWOD[y][i];
			base->read.x_pos = i;
			base->read.y_pos = y;
		}
		i++;
	}
	while(TWOD[y][i] == ' ' || TWOD[y][i] == '\0')
		i--;
	return (i);
}

/*
** Checks position last char (no space) of two adjacent lines.
** The difference between those 2 char's + 1 should consist of 1's.
** 0000111 --> correct.
** 00001
*/

int				align_dif_back(int y, t_base *base)
{
	int 	back1;
	int 	back2;
	int 	dif;
	int 	count;

	count = 0;
	back1 = last_char_save_pos(y, base);
	back2 = last_char_save_pos(y + 1, base);
	// if (base->read.error != 0) //! kan niet aanpassne?
	// 	return (1);
	dif = back1 - back2;
	while (dif > (count - 1))
	{
		if (TWOD[y][back1 - count] != '1' && TWOD[y][back1 - count] != ' ')
			return (error_distr(base, 12));
		count++;
	}
	while (dif < 1)
	{
		if (TWOD[y + 1][back2 + dif] != '1' && TWOD[y + 1][back2 + dif] != ' ')
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
	int 	front1;
	int 	front2;
	int 	dif;
	int 	count;

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

int 			space_in_wall(int y, int i, t_base *base)
{
	if (TWOD[y][i - 1] != '1' && TWOD[y][i - 1] != ' ')
		return (1);
	if (TWOD[y][i + 1] != '1' && TWOD[y][i + 1] != ' ')
		return (1);
	if (y == base->read.map_start)
	{
		if (TWOD[y + 1][i] != '1' && TWOD[y + 1][i] != ' ')
			return (1);
		if (TWOD[y + 1][i - 1] != '1' && TWOD[y + 1][i - 1] != ' ')
			return (1);
		if (TWOD[y + 1][i + 1] != '1' && TWOD[y + 1][i + 1] != ' ')
			return (1);
	}
	if (y == base->read.map_end)
	{
		if (TWOD[y - 1][i] != '1' && TWOD[y - 1][i] != ' ')
			return (1);
		if (TWOD[y - 1][i - 1] != '1' && TWOD[y - 1][i - 1] != ' ')
			return (1);
		if (TWOD[y - 1][i + 1] != '1' && TWOD[y - 1][i + 1] != ' ')
			return (1);
	}	
	return (0);
}
