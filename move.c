/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 20:46:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/06 21:19:23 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** 1st if: position East or West
** 2nd if: position South or North
*/

void				move_front(t_game *game, t_read *read, char **array)
{
	if (array[(int)read->y_pos][(int)(read->x_pos + game->dirx
		* game->movespeed)] == '+')
		read->x_pos += game->dirx * game->movespeed;
	if (array[(int)(read->y_pos + game->diry * game->movespeed)]
		[(int)read->x_pos] == '+')
		read->y_pos += game->diry * game->movespeed;
}

void				move_back(t_game *game, t_read *read, char **array)
{
	if (array[(int)read->y_pos][(int)(read->x_pos - game->dirx
		* game->movespeed)] == '+')
		read->x_pos -= game->dirx * game->movespeed;
	if (array[(int)(read->y_pos - game->diry * game->movespeed)]
		[(int)read->x_pos] == '+')
		read->y_pos -= game->diry * game->movespeed;
}

/*
** 1st if: position South or North
** 2nd if: position East or West
*/

void				move_right(t_game *game, t_read *read, char **array)
{
	if (array[(int)read->y_pos][(int)(read->x_pos - game->diry
		* game->movespeed)] == '+')
		read->x_pos -= game->diry * game->movespeed;
	if (array[(int)(read->y_pos + game->dirx * game->movespeed)]
		[(int)read->x_pos] == '+')
		read->y_pos += game->dirx * game->movespeed;
}

void				move_left(t_game *game, t_read *read, char **array)
{
	if (array[(int)read->y_pos][(int)(read->x_pos + game->diry
		* game->movespeed)] == '+')
		read->x_pos += game->diry * game->movespeed;
	if (array[(int)(read->y_pos - game->dirx * game->movespeed)]
		[(int)read->x_pos] == '+')
		read->y_pos -= game->dirx * game->movespeed;
}
