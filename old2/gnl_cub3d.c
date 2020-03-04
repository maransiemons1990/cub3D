/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl_cub3d.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 16:37:30 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/03 20:11:59 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define BUFFER_SIZE 128

//gcc -Wall -Wextra -Werror -I mlx readmap.c gnl_cub3d.c gnl_cub3d_utils.c libft/ft_split.c libft/ft_substr.c

static char		*ft_read(int fd, char *new_line)
{
	char			*buf;
	int				ret;

	ret = 1;
	while (ret > 0)
	{
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
		{
			free(new_line);
			return (NULL);
		}
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free(new_line);
			free(buf);
			return (NULL);
		}
		buf[ret] = '\0';
		new_line = ft_strjoin(new_line, buf);
		if (new_line == NULL)
			return (NULL);
	}
	return (new_line);
}

char		*ft_gnl_cub3d(int fd)
{
	static char		*new_line;
	char			*line;
	
	if (fd < 0)
		return (NULL);
	if (new_line == NULL)
		new_line = ft_strdup("");
	if (new_line == NULL)
		return (NULL);
	line = ft_read(fd, new_line);
	if (line == NULL)
		return (NULL); //volgens mij free(new_line nu 1 te weinig, die van r==0)
	return (line);
}
