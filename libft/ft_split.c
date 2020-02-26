/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 10:08:48 by msiemons      #+#    #+#                 */
/*   Updated: 2019/11/22 13:00:21 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_count(const char *s, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (c == '\0' && s[i] != '\0')
		return (1);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		while (s[i] == c)
			i++;
	}
	return (count);
}

static	int		ft_start(const char *s, char c, int i, size_t len)
{
	i = i + len;
	while (s[i] == c)
		i++;
	return (i);
}

static	int		ft_end(const char *s, char c, int i)
{
	size_t len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

static	char	**ft_execute(char const *s, char c, char **array, int count)
{
	int		i;
	int		y;
	size_t	len;

	i = 0;
	y = 0;
	len = 0;
	while (y < count)
	{
		i = ft_start(s, c, i, len);
		len = ft_end(s, c, i);
		array[y] = ft_substr(s, i, len);
		if (array[y] == NULL)
		{
			while (y > 0)
			{
				y--;
				free(array[y]);
			}
			free(array);
			return (NULL);
		}
		y++;
	}
	return (array);
}

char			**ft_split(char const *s, char c)
{
	char	**array;
	int		count;

	if (!s)
		return (NULL);
	count = ft_count(s, c);
	array = (char **)malloc((count + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	array = ft_execute(s, c, array, count);
	if (array)
		array[count] = 0;
	return (array);
}
