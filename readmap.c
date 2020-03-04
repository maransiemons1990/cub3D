/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readmap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 16:11:17 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/04 16:32:59 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// char			**ft_split(char const *s, char c);
// void			ft_check(t_base *base);

void	ft_readcub(char **argv, t_base *base)
{
	char *line;
	int fd;
	
	fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			printf("ERROR OPEN");
	line = ft_gnl_cub3d(fd);
	if (line == NULL)
		printf("ERROR");
	base->read.array = ft_split(line, '\n');
	free(line);
	//ft_check(base);
}

int			main(int argc, char **argv)
{	
	t_base		*base;
	int y;

	y = 0;
	if (argc == 2)
		ft_readcub(argv[1], &base);
	//------------------DELETE LATER------------------------------------
	while(base.read.array[y])
	{
		printf("array[%i]: [%s]\n", y, base.read.array[y]);
		y++;
	}
	return (0);
}



//--------------------------------------------------------------------
	
// 	int fd;
// 	int y;
// 	t_base		base;	

// 	y = 0;
// 	if (argc == 2)
// 	{
// 		// Check of .cub file
// 		fd = open(argv[1], O_RDONLY);
// 		if (fd < 0)
// 			printf("ERROR OPEN");
// 		ft_readcub(fd, &base);
// 
// 	}
// 	else
// 		printf("TOO MANY ARGUMENTS");	
// 	// while(1)
// 	// {

// 	// }