/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   readmap.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/02 16:11:17 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/04 15:40:40 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char			**ft_split(char const *s, char c);
void			ft_check(t_base *base);

void	ft_readcub(int fd, t_base *base)
{
	char *line;
	//char **array;
	int y;

	y = 0;
	line = ft_gnl_cub3d(fd);
	if (line == NULL)
		printf("ERROR");
	base->read.array = ft_split(line, '\n');
	free(line);
	ft_check(base);

//------------------DELETE LATER------------------------------------
	// while(data->array[y])
	// {
	// 	printf("array[%i]: [%s]\n", y, data->array[y]);
	// 	y++;
	// }

}

int			main(int argc, char **argv)
{
	int fd;
	int y;
	t_base		base;	

	y = 0;
	if (argc == 2)
	{
		// Check of .cub file
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			printf("ERROR OPEN");
		ft_readcub(fd, &base);
//------------------DELETE LATER------------------------------------
	// while(base.read.array[y])
	// {
	// 	printf("array[%i]: [%s]\n", y, base.read.array[y]);
	// 	y++;
	// }
	}
	else
		printf("TOO MANY ARGUMENTS");	
	// while(1)
	// {

	// }
	return (0);
}


