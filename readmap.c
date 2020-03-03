/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readmap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 16:11:17 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/03 20:56:10 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char			**ft_split(char const *s, char c);
void	ft_check(char **line);

void	ft_readcub(int fd)
{
	char *line;
	char **array;
	int y;

	y = 0;
	line = ft_gnl_cub3d(fd);
	if (line == NULL)
		printf("ERROR");
	array = ft_split(line, '\n');
	free(line);
	ft_check(array);

//------------------DELETE LATER------------------------------------
	while(array[y])
	{
		printf("array[%i]: [%s]\n", y, array[y]);
		y++;
	}

}

int			main(int argc, char **argv)
{
	int fd;

	if (argc == 2)
	{
		// Check of .cub file
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			printf("ERROR OPEN");
		ft_readcub(fd);
	}
	else
		printf("TOO MANY ARGUMENTS");	
	// while(1)
	// {

	// }
	return (0);
}


