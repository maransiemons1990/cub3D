/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   gnl_cub3d.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 16:37:30 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/17 17:38:10 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define BUFFER_SIZE 128


static char		*gnl_cub3d_read(int fd, char *new_line)
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
		new_line = gnl_strjoin(new_line, buf);
		if (new_line == NULL)
			return (NULL);
	}
	return (new_line);
}

static char		*gnl_cub3d(int fd)
{
	static char		*new_line;
	char			*line;
	
	if (fd < 0)
		return (NULL);
	if (new_line == NULL)
		new_line = ft_strdup("");
	if (new_line == NULL)
		return (NULL);
	line = gnl_cub3d_read(fd, new_line);
	if (line == NULL)
		return (NULL); 
	return (line);
}


static int		check_filetype(char *s)
{
	int		i;

	i = 0;
	while (s[i])
		i++;
	i--;
	if (s[i] == 'b' && s[i - 1] == 'u' && s[i - 2] == 'c' && s[i - 3] == '.')
		return (0);
	return (1);
}

t_base			*getcubfile(char *filename)
{
	t_base	*new;
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (check_filetype(filename) || fd < 0)
		return (error_general(2, NULL));
	line = gnl_cub3d(fd);
	if (line == NULL)
		return (error_general(3, NULL));
	new = (t_base *)malloc(sizeof(t_base));
	if (new == NULL)
		return (error_general(4, line));
	new->read.array = ft_split(line, '\n');
	if (new->read.array == NULL)
	{
		free(new);
		return (error_general(4, line));
	}
	free(line);
	return (new);
}
