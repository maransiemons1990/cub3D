/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   move.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 20:46:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/07 12:07:57 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** 1st if: position East or West
** 2nd if: position South or North
*/

static void			move_front(t_game *game, t_read *read, char **array)
{
	if (array[(int)read->y_pos][(int)(read->x_pos + game->dirx
		* game->movespeed)] == '+')
		read->x_pos += game->dirx * game->movespeed;
	if (array[(int)(read->y_pos + game->diry * game->movespeed)]
		[(int)read->x_pos] == '+')
		read->y_pos += game->diry * game->movespeed;
}

static void			move_back(t_game *game, t_read *read, char **array)
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

static void			move_right(t_game *game, t_read *read, char **array)
{
	if (array[(int)read->y_pos][(int)(read->x_pos - game->diry
		* game->movespeed)] == '+')
		read->x_pos -= game->diry * game->movespeed;
	if (array[(int)(read->y_pos + game->dirx * game->movespeed)]
		[(int)read->x_pos] == '+')
		read->y_pos += game->dirx * game->movespeed;
}

static void			move_left(t_game *game, t_read *read, char **array)
{
	if (array[(int)read->y_pos][(int)(read->x_pos + game->diry
		* game->movespeed)] == '+')
		read->x_pos += game->diry * game->movespeed;
	if (array[(int)(read->y_pos - game->dirx * game->movespeed)]
		[(int)read->x_pos] == '+')
		read->y_pos -= game->dirx * game->movespeed;
}


void				move_rotate(t_game *game, t_read *read, char **array)
{
	if (game->move_front == 1)
		move_front(game, read, array);
	if (game->move_back == 1)
		move_back(game, read, array);
	if (game->move_right == 1)
		move_right(game, read, array);
	if (game->move_left == 1)
		move_left(game, read, array);
	if (game->rotate_right == 1)
		rotate_right(game);
	if (game->rotate_left == 1)
		rotate_left(game);
}
