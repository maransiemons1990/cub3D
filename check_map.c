/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 13:47:21 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/16 12:07:57 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Looks for first character in line except spaces. Returns position.
*/

int				first_char(char *y)
{
	int 	i;

	i = 0;
	while(y[i] == ' ')
	 	i++;
	return(i);
}

/*
** Looks for last character in line except spaces. Returns position.
*/

int				last_char(char *y)
{
	int 	i;

	i = 0;	
	while(y[i])
		i++;
	while(y[i] == ' ' || y[i] == '\0')
		i--;
	return(i);
}

/*
** Checks position last char (No space) of two adjacent lines.
** The difference between those 2 char's + 1 should consist of 1's.
** 0000111 --> correct.
** 00001
*/

int				align_dif_back(char *s1, char *s2)
{
	int 	back1;
	int 	back2;
	int 	dif;
	int 	count;

	count = 0;
	back1 = last_char(s1);
	back2 = last_char(s2);
	dif = back1 - back2;
	if (s1[back1]!= '1' || s2[back2]!= '1')
		return (1);
	while (dif > (count - 1))
	{
		if (s1[back1 - count] != '1' && s1[back1 - count] != ' ')
			return (1);
		count++;
	}
	while (dif < 1)
	{
		if (s2[back2 + dif] != '1' && s2[back2 + dif] != ' ')
			return (1);
		dif++;
	}
	return (0);
}

/*
** Checks position first char (No space) of two adjacent lines.
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
	if (s1[front1]!= '1' || s2[front2]!= '1')
		return (1);
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
** When a space characters in a wall appears, 
** the adjacent elements can only consist of 1's and spaces.
*/

int 			space_in_wall(int y, int i, t_base *base)
{
	if (TWOD[y][i - 1] != '1' && TWOD[y][i - 1] != ' ')
		return (1);
	if (TWOD[y][i + 1] != '1' && TWOD[y][i + 1] != ' ')
		return (1);
	if (y == base->read.y_start)
	{
		if (TWOD[y + 1][i] != '1' && TWOD[y + 1][i] != ' ')
			return (1);
		if (TWOD[y + 1][i - 1] != '1' && TWOD[y + 1][i - 1] != ' ')
			return (1);
		if (TWOD[y + 1][i + 1] != '1' && TWOD[y + 1][i + 1] != ' ')
			return (1);
	}
	if (y == base->read.y_end)
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

/*
** Walls can be composed of 1's and under condition of spaces.
*/

int				check_walls_first_last(int y, t_base *base)
{
	int 	i;
	int		last;
	int 	ret;
	
	i = 0;
	last = last_char(TWOD[y]);
	while(TWOD[y][i] == ' ')
			i++;
	//printf("first/last y=[%d] {%s}, last_char = [%d]\n" , y, TWOD[y], last);
	while (i <= last)
	{
		if (TWOD[y][i] == '1')
			i++;
		else if (TWOD[y][i] == ' ')
		{
			ret = space_in_wall(y, i, base);
			if (ret == 1)
				printf("INVALID SPACE[%d][%i]\n", y, i);
				//return (1); //invalid space surroundings
			i++;
		}
		else
		{
			printf("FIRST LAST[%d][%i]\n", y, i);
			//return (1); //invalid wall
		}
	}
	return (0);
}

/*
** When the walls don't align edges and corners are created.
** Check if all characters who touch empty space consist of 1's.
*/

int				check_edges_wall(int *y, t_base *base)
{
	int 	back;
	int 	front;
	int 	ret;

	while (TWOD[*y])
	{
		front = 0;
		back = 0;
		if (*y != base->read.y_end)
		{
			front = align_dif_front(TWOD[*y], TWOD[*y + 1]);
			back = align_dif_back(TWOD[*y], TWOD[*y + 1]);
		}
		else
		{
			ret = check_walls_first_last(*y, base);
			if (ret == 	1)
				printf("LAST LINE ERROR [%d]\n", *y);
		}
		if 	(front != 0 || back != 0)
			printf("SIDE WALLS ERROR [%d]\n", *y);
		(*y)++;
	}
	return(0);
}

int				check_map(int *y, t_base *base)
{
	int 	ret;
	int		y_start2;

	base->read.y_start = *y;
	y_start2 = *y;
	while (base->read.array[*y])
		(*y)++;
	base->read.y_end = *y - 1;
	*y = base->read.y_start;
	
	printf("y start = [%d], *y = [%d]\n", base->read.y_start, *y);
//-----------------------------
	while(base->read.array[y_start2])
	{
		printf("[%i][%s]\n", y_start2, base->read.array[y_start2]);
		y_start2++;
	}
	printf("--------------------------------------------------\n");
//------------------------------

	ret = check_walls_first_last(*y, base);
	if (ret == 	1)
		printf("ERROR MAP: INVALID FIRST\n");
	ret = check_edges_wall(&(*y), base);
	if (ret == 1)
		printf("ERROR MAP: return 1\n");
	return (0);
}

//padding(base->read.y_start, base);

//tabs
//checken voor spaties in zijwall.