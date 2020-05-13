/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   rotate_bonus.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/06 21:02:35 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/13 15:50:13 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../cub3d_bonus.h"
# include <math.h>

void				rotate_right(t_game *game)
{
	double	olddirx;
	double	oldplanex;

	olddirx = game->dirx;
	game->dirx = game->dirx * cos(game->rotspeed) - game->diry
		* sin(game->rotspeed);
	game->diry = olddirx * sin(game->rotspeed) + game->diry
		* cos(game->rotspeed);
	oldplanex = game->planex;
	game->planex = game->planex * cos(game->rotspeed) - game->planey
		* sin(game->rotspeed);
	game->planey = oldplanex * sin(game->rotspeed) + game->planey
		* cos(game->rotspeed);
}

void				rotate_left(t_game *game)
{
	double	olddirx;
	double	oldplanex;

	olddirx = game->dirx;
	game->dirx = game->dirx * cos(-game->rotspeed) - game->diry
		* sin(-game->rotspeed);
	game->diry = olddirx * sin(-game->rotspeed) + game->diry
		* cos(-game->rotspeed);
	oldplanex = game->planex;
	game->planex = game->planex * cos(-game->rotspeed) - game->planey
		* sin(-game->rotspeed);
	game->planey = oldplanex * sin(-game->rotspeed) + game->planey
		* cos(-game->rotspeed);
}
