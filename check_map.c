/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_map.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 13:47:21 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/11 19:12:59 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// Check of map alleen bestaat uit 0, 1, 2, N,S,E or W
// Alle zijkanten 1
// No empty lines!
// Map als laatst
// Spaces are a valid part of the map, and is up to you to handle --> empty space?
// ook tabs vooraan de regel?
	// printf("--TWOD[%d][%d] = [%c]--counter = [%d]\n", y, x, TWOD[y][x], *counter);

	// printf("----------------------------------------------------------------------------GO RIGHT----\n");
	// printf("1. y[%d], x[%d] = [%c]\n", y, x, TWOD[y][x]);
	// printf("y_start = [%d], y_end= [%d], x= [%d], strlen = [%d]\n", base->read.y_start, base->read.y_end, x, ((int)ft_strlen(TWOD[y])));
    // printf("----------------------------------------------------------------------------GO DOWN----\n");
	// printf("TWOD = [%c], pos = [%c]\n", TWOD[y][x], base->read.pos);
	// printf("Hier\n");
//    printf("----------------------------------------------------------------------------GO LEFT----\n");

void	flood_fill(t_base *base, int y, int x)
{
	if (y <= base->read.y_start || y >= base->read.y_end || x <= 0 || x >= ((int)ft_strlen(TWOD[y])))
	{
		printf("----------------------------------BAM OF MAP--TWOD[%d][%d] = [%c]--\n", y, x, TWOD[y][x]);
		return;
	}
    if (TWOD[y][x]!= '0' && TWOD[y][x]!= base->read.pos)
	{
		printf("---------------------------------------------------------------------BAM MUUR--TWOD[%d][%d] = [%c]--\n", y, x, TWOD[y][x]);
		return;
	}
    TWOD[y][x] = '+';
	printf("---YES--TWOD[%d][%d] = [%c]--\n", y, x, TWOD[y][x]);
    flood_fill(base, y - 1, x);
    flood_fill(base, y, x + 1);
    flood_fill(base, y + 1, x);
    flood_fill(base, y, x - 1);
    return;
}

// Check of alle identifiers gevuld!
// TWOD[21][29]

int	padding(int y, t_base *base)
{
	int i;
	
	while(TWOD[y])
	{
		i = 0;
		while (TWOD[y][i])
		{
			if (TWOD[y][i] == ' ')
				TWOD[y][i] = '0';
			if (TWOD[y][i] != '0' && TWOD[y][i] != '1' && TWOD[y][i] != '2' && TWOD[y][i] != 'N' && TWOD[y][i] != 'S' && TWOD[y][i] != 'E' && TWOD[y][i] !='W')
				return (base->read.error = 999);
			if (TWOD[y][i] == 'N' || TWOD[y][i] == 'S' || TWOD[y][i] == 'E' || TWOD[y][i] =='W')
			{
				if (base->read.pos != -1)
					return (base->read.error = 999);
				base->read.pos = TWOD[y][i];
				base->read.x_pos = i;
				base->read.y_pos = y;
			}
			i++;
		}
		y++;
	}
	return (0);
}

int			check_map(int *y, t_base *base) // int i, int y,
{
	int y_start2;
	int y_start3;

	base->read.y_start = *y;
	y_start2 = *y;
	y_start3= *y;

	while (base->read.array[*y])
		(*y)++;
	base->read.y_end = *y - 1;
	padding(base->read.y_start, base);
	
	//----------------------------------------------
	while(base->read.array[y_start2])
	{
		printf("[%i][%s]\n", y_start2, base->read.array[y_start2]);
		y_start2++;
	}

	// check of eerste regel uit spaties en 1 // save eerste 1
	// opvolgende regels beginnen met 1
		// 0, 1, 2, N,S,E or W
	//
	printf("--------------------------------------------\n");
	//printf("**TWOD[%d][%d] = [%c]**\n", base->read.y_pos, base->read.x_pos, TWOD[base->read.y_pos][base->read.x_pos]);
	flood_fill(base, base->read.y_pos, base->read.x_pos);

	while(base->read.array[y_start3])
	{
		printf("[%i][%s]\n", y_start3, base->read.array[y_start3]);
		y_start3++;
	}
	return (0);
}

