/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   identifiers.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 18:56:10 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/04 18:43:00 by msiemons      ########   odam.nl         */
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
#include "cub3d.h"

int		ft_check_line(char *line)
{
	int i;

	i = 0;
	while(line[i] == ' ')
			i++;
	if (line[i] == 'C' || line[i] == 'F')
		printf("--Ga naar functie CF--\n");
	else if (line[i] == 'R')
		printf("--Ga naar functie R--\n");
	else if ((line[i] == 'E' && line[i + 1] == 'A') || (line[i] == 'N' && 
		line[i + 1] == 'O') || (line[i] == 'W' && line[i + 1] == 'E') || 
		(line[i] == 'S' && (line[i] == 'O' || line[i] == ' ')))
		printf("--Ga naar functie path--[%s]\n", );
	else if (line[i] == '1')
		printf("--Het is een 1--\n");
	else
		return (0);
	return (1);
}

void	check(t_base *base)
{
	int y;
	int line;
	
	y = 0;
	while (base->read.array[y])
	{
		line = ft_check_line(base->read.array[y]);
		if (line == 0)
			printf("FOUTE IDENTIFIER\n");
		y++;
	}
}










	//check = "CFRENSW 1";
	//if (ft_strchr(check, line[i]))
	//	return(NULL);


		//ga naar functie pad
		// if (line[i] == 'N' && line[i + 1] == 'O')
		// 	//ga naar functie pad
		// if (line[i] == 'S')
		// {
		// 	//ga naar functie pad
		// 	if (line[i + 1] == 'O')
		// 		//ga naar functie pad
		// }
		// if (line[i] == 'W' && line[i + 1] == 'E')
		// 	//ga naar functie pad


		// if (line[i] != 'C' || line[i] == 'F' || line[i] == 'R' || line[i] == 'E'|| line[i] == 'N' 



// void	ft_check(t_base *base)
// {
// 	int y;
// 	int x;

// 	y = 0;
// 	x = 0;
// 	//printf("-------[%d]----------\n", array[5][0]);
// 	while (base->read.array[y])
// 	{
// 		while(base->read.array[y][x])
// 		{
// 			while(base->read.array[y][x] == ' ')
// 				x++;
// 			if (base->read.array[y][x] == 'C')
// 			{
// 				printf("FOUND C\n");
// 				break ;
// 			}
// 			if (base->read.array[y][x] == 'E')
// 			{
// 				if (base->read.array[y][x + 1] == 'A')
// 					printf("FOUND EA\n");
// 				break ;
// 			}
// 			if (base->read.array[y][x] == 'F')
// 			{
// 				printf("FOUND F\n");
// 				break ;
// 			}
// 			if (base->read.array[y][x] == 'N')
// 			{
// 				if (base->read.array[y][x + 1] == 'O')
// 				{
// 					printf("FOUND NO\n");
// 					break ;
// 				}	
// 			}
// 			if (base->read.array[y][x] == 'R')
// 			{
// 				printf("FOUND R\n");
// 				break;
// 			}
// 			if (base->read.array[y][x] == 'S')
// 			{
// 				if (base->read.array[y][x + 1] == 'O')
// 				{
// 					printf("FOUND SO\n");
// 					break ;
// 				}
// 				else
// 				{
// 					printf("FOUND S\n");
// 					break ;
// 				}
// 			}
// 			x++;
// 			printf("--------array[%d][%d]---------------\n", y, x);
// 		}
// 		y++;
// 	}
// }

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