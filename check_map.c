/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 13:47:21 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/13 18:24:36 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int space(int y, int i, t_base *base)
{
	//Links	
	if (TWOD[y][i - 1] != '1' && TWOD[y][i - 1] != ' ')
		return (1);
	//rechts
	if (TWOD[y][i + 1] != '1' && TWOD[y][i + 1] != ' ')
		return (1);
	//y = base->read.y_start;
	if (y == base->read.y_start)
	{
		//onder
		if (TWOD[y + 1][i] != '1' && TWOD[y + 1][i] != ' ')
			return (1);
		//onder links
		if (TWOD[y + 1][i - 1] != '1' && TWOD[y + 1][i - 1] != ' ')
			return (1);
		//onder rechts
		if (TWOD[y + 1][i + 1] != '1' && TWOD[y + 1][i + 1] != ' ')
			return (1);
	}
	if (y == base->read.y_end)
	{
		//boven
		if (TWOD[y - 1][i] != '1' && TWOD[y - 1][i] != ' ')
			return (1);
		//boven links
		if (TWOD[y - 1][i - 1] != '1' && TWOD[y - 1][i - 1] != ' ')
			return (1);
		//onder rechts
		if (TWOD[y - 1][i + 1] != '1' && TWOD[y - 1][i + 1] != ' ')
			return (1);
	}
	
	return (0);
}

int				flood_fill(t_base *base, int y, int x)
{
	if (TWOD[y][x] == '+' || TWOD[y][x] == '1' || TWOD[y][x] == '2')
		return (0);
	if (TWOD[y][x]== '\0' || y <= base->read.y_start || y >= base->read.y_end)
	{
		printf("--error 12--[%d][%d]----\n", y, x);
		return (base->read.error = 12);	
	}
	if (TWOD[y][x] == ' ')
	{
		printf("--error 10--[%d][%d]----\n", y, x);
		return (base->read.error = 10);
	}
    if (TWOD[y][x]!= '0' && TWOD[y][x] != base->read.pos)
	{
		printf("--error 11--[%d][%d]----\n", y, x);
		return (base->read.error = 11);
	}
    TWOD[y][x] = '+';
	//printf("---YES--TWOD[%d][%d] = [%c]--\n", y, x, TWOD[y][x]);
    flood_fill(base, y - 1, x);
    flood_fill(base, y, x + 1);
    flood_fill(base, y + 1, x);
    flood_fill(base, y, x - 1);
    return (0);
}

int	padding(int y, t_base *base)
{
	int i;
	
	while(TWOD[y])
	{
		i = 0;
		while (TWOD[y][i])
		{
			//if (TWOD[y][i] == ' ')
			//	TWOD[y][i] = '0';
			if (TWOD[y][i] != '0' && TWOD[y][i] != '1' && TWOD[y][i] != '2' && TWOD[y][i] != 'N' && TWOD[y][i] != 'S' && TWOD[y][i] != 'E' && TWOD[y][i] !='W' && TWOD[y][i] !=' ')
				return (base->read.error = 99);
			if (TWOD[y][i] == 'N' || TWOD[y][i] == 'S' || TWOD[y][i] == 'E' || TWOD[y][i] =='W')
			{
				if (base->read.pos != -1)
					return (base->read.error = 999);
				base->read.pos = TWOD[y][i];
				base->read.x_pos = i;
				base->read.y_pos = y;
			}
			i++;
			if (i > base->read.big_strlen)
				base->read.big_strlen = i;
		}
		y++;
	}
	return (0);
}

int		last_filled(char *y)
{
	int i;
	int last;

	i = 0;	
	while(y[i])
		i++;
	while(y[i] == ' ' || y[i] == '\0')
		i--;
	last = i;
	//printf("last filled[%d] = [%c]\n", last, y[last]);
	return(last);
}

int		first_filled(char *y)
{
	int i;
	int first;

	i = 0;
	while(y[i] == ' ')
	 	i++;
	first = i;

	return(first);
}

int		strlen_dif_front(char *s1, char *s2)
{
	int strlen1;
	int strlen2;
	int dif;
	int count;

	count = 0;
	strlen1 = first_filled(s1);
	strlen2 = first_filled(s2);
	dif = strlen1 - strlen2;
	if (s1[strlen1]!= '1' || s2[strlen2]!= '1')
		return (1);
	while (dif > (count - 1))
	{
		if (s2[strlen2 + count] != '1')
			return (1);
		count++;
	}
	while (dif < 1)
	{
		if (s1[strlen1 - dif] != '1')
			return (1);
		dif++;
	}
	return(0);
}

int		strlen_dif(char *s1, char *s2)
{
	int strlen1;
	int strlen2;
	int dif;
	int count;

	count = 0;
	strlen1 = last_filled(s1);
	strlen2 = last_filled(s2);
	dif = strlen1 - strlen2;
	if (s1[strlen1]!= '1' || s2[strlen2]!= '1')
		return (1);
	while (dif > (count - 1))
	{
		if (s1[strlen1 - count] != '1')
			return (1);
		count++;
	}
	while (dif < 1)
	{
		if (s2[strlen2 + dif] != '1')
			return (1);
		dif++;
	}
	return(0);
}

int		first_last_line(int y, t_base *base)
{
	int i;
	int ret;
	
	i = 0;
	while(TWOD[y][i] == ' ')
			i++;
	while (i <= last_filled(TWOD[y]))
	{
		if (TWOD[y][i] == '1')
			i++;
		else if (TWOD[y][i] == ' ')
		{
			ret = space(y, i, base);
			if (ret == 1)
			{
				printf("---error--[%d][%i]---\n", y, i);
				return (1);
			}
			i++;
		}
		else
			return (1);
	}
	return (0);
}



int		edges(t_base *base)
{
	int plus;
	int front;
	int y;
	int ret;

	y = base->read.y_start;
	ret = first_last_line(y, base);
	if (ret == 	1)
		return (1);
	while (TWOD[y])
	{
		front = 0;
		plus = 0;
		if (y != base->read.y_end)
		{
			front = strlen_dif_front(TWOD[y], TWOD[y+1]);
			plus = strlen_dif(TWOD[y], TWOD[y + 1]);
		}
		else
		{
			ret = first_last_line(y, base);
			if (ret == 	1)
				return (1);
		}
		if (plus != 0 || front != 0)
			printf("ERROR MAP in strlen dif[%d]\n", y);
		y++;
	}
	return(0);
}

int			check_map(int *y, t_base *base) // int i, int y,
{
	int y_start2;
	int y_start3;
	int ret;

	base->read.y_start = *y; //Y_START
	y_start2 = *y;
	y_start3= *y;

	while (base->read.array[*y])
		(*y)++;
	base->read.y_end = *y - 1; // Y END
	padding(base->read.y_start, base);
	//printf("BIGGEST: [%d]\n", base->read.big_strlen);
	
	//----------------------------------------------

	printf("------------------BEFORE--------------------------\n");
	while(base->read.array[y_start2])
	{
		printf("[%i][%s]\n", y_start2, base->read.array[y_start2]);
		y_start2++;
	}
	printf("--------------------------------------------------\n");

	ret = edges(base);
	if (ret == 1)
		printf("ERROR MAP: return 1\n");
	
	//fill_up(base);

	
	//
	// printf("-----------------AFTER---------------------------\n");
	// while(base->read.array[y_start3])
	// {
	// 	printf("[%i][%s]\n", y_start3, base->read.array[y_start3]);
	// 	y_start3++;
	// }
	
	//printf("**TWOD[%d][%d] = [%c]**\n", base->read.y_pos, base->read.x_pos, TWOD[base->read.y_pos][base->read.x_pos]);
	//flood_fill(base, base->read.y_pos, base->read.x_pos);
	//printf("ERROR SIGN = [%d]\n", base->read.error); 
	return (0);
}
