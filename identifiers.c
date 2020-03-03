/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   identifiers.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 18:56:10 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/03 21:21:13 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// gcc -Wall -Wextra -Werror -I mlx readmap.c gnl_cub3d.c gnl_cub3d_utils.c libft/ft_split.c libft/ft_substr.c identifiers.c

/* 
R 1920 1080\nNO ./path_to_the_north_texture\nSO ./path_to_the_south_texture\nWE ./path_to_the_west_texture\n
EA ./path_to_the_east_texture\nS ./path_to_the_sprite_texture\nF 220,100,0\nC 225,30,0\n
*/ 

/*
** each type of element can be separated by one or more empty line(s).
** each type of element can be set in any order in the file.
** each type of information from an element can be separated by one or more space(s).
** Each element of the map must be separated by exactly one space. Spaces are valid elements of the map,
meaning there is nothing, and are up to you to handle.
** Each element firsts information is the type identifier (composed by one or two character(s)), 
followed by all specific informations for each object in a strict order such as :
*/
/* 
R, 
NO, 
WE
EA
SO, S,
F,
C
*/

// *( *(arr + i) + j)
#include <stdio.h>


void	ft_check(char **array)
{
	int y;
	int x;

	y = 0;
	x = 0;
	//printf("-------[%d]----------\n", array[5][0]);
	while (array[y])
	{
		while(array[y][x])
		{
			while(array[y][x] == ' ')
				x++;
			if (array[y][x] == 'C')
			{
				printf("FOUND C\n");
				break ;
			}
			if (array[y][x] == 'E')
			{
				if (array[y][x + 1] == 'A')
					printf("FOUND EA\n");
				break ;
			}
			if (array[y][x] == 'F')
			{
				printf("FOUND F\n");
				break ;
			}
			if (array[y][x] == 'N')
			{
				if (array[y][x + 1] == 'O')
				{
					printf("FOUND NO\n");
					break ;
				}	
			}
			if (array[y][x] == 'R')
			{
				printf("FOUND R\n");
				break;
			}
			if (array[y][x] == 'S')
			{
				if (array[y][x + 1] == 'O')
				{
					printf("FOUND SO\n");
					break ;
				}
				else
				{
					printf("FOUND S\n");
					break ;
				}
			}
			x++;
			printf("--------array[%d][%d]---------------\n", y, x);
		}
		y++;
	}
}

// void	ft_error_check(char **line)
// {
// 	int y;
// 	int x;

// 	while (*(line + y))
// 	{
// 		while(*(*(line + y) + x))
// 		{
// 			if (*(*(line + y) + x) == 'N')
// 				printf("FOUND N");
// 			x++;
// 		}
// 		y++;
// 	}
// }