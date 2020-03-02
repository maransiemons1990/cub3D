/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl_cub3d.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 16:37:30 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/02 19:06:47 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//gcc -Wall -Wextra -Werror -I mlx readmap.c gnl_cub3d.c gnl_cub3d_utils.c libft/ft_split.c libft/ft_substr.c

static char		*ft_read(int fd, char *new_line, int ret)
{
	char			*buf;

	while (ret > 0)
	{
		buf = (char *)malloc(sizeof(char) * (128 + 1));
		if (buf == NULL)
		{
			free(new_line);
			return (NULL);
		}
		ret = read(fd, buf, 128);
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

int				ft_gnl_cub3d(int fd, char **line)
{
	int				ret;
	static char		*new_line;

	if (fd < 0 || !line)
		return (-1);
	ret = 1;
	if (new_line == NULL)
		new_line = ft_strdup("");
	if (new_line == NULL)
		return (-1);
	*line = ft_read(fd, new_line, ret);
	if (new_line == NULL)
		return (-1);
	return (0);
}
