/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 12:39:34 by msiemons      #+#    #+#                 */
/*   Updated: 2019/11/14 12:52:29 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int c;

	c = 0;
	while (lst)
	{
		lst = lst->next;
		c++;
	}
	return (c);
}
