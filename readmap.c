/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readmap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 16:11:17 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/02 19:10:39 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char			**ft_split(char const *s, char c);

int		main(int argc, char **argv)
{
	int ret;
	int fd;
	char *line;
	char **array;
	int y;
	
	y = 0;
	ret = 1;
	if (argc == 2)
		fd = open(argv[1], O_RDONLY);
	while (ret > 0)
	{
		ret = ft_gnl_cub3d(fd, &line);
		if (ret == 1)
			printf("ERROR");
		//printf("[%d] - [%s]\n", ret, line);
	}
	
	array = ft_split(line, '\n');
	free(line);
	while(array[y])
	{
		printf("array[%i]: [%s]\n", y, array[y]);
		y++;
	}
	// while(1)
	// {
		
	// }
}


