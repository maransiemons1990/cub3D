/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialise_game_bonus.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/07 12:28:38 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/14 20:42:53 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_bonus.h"

static char		*create_path(t_read *read, int i)
{
	if (i == 0)
		return (read->no);
	else if (i == 1)
		return (read->ea);
	else if (i == 2)
		return (read->so);
	else if (i == 3)
		return (read->we);
	else if (i == 4)
		return (read->sprite2);
	else if (i == 5)
		return (read->sprite3);
	else if (i == 6)
		return (read->sprite4);
	else if (i == 7)
		return (read->floor);
	else
		return (read->ceiling);
}

/*
** mlx_png_file_to_image currently leaks memory. Therefore using xpm function
** instead.
** i = 0: North, i = 1: East, i = 2: South , i = 3: West, i = 4: Sprite #2
** i = 5: Sprite #3, i = 6: Sprite #4, i = 7: Floor , i = 8: Ceiling
*/

void			load_texture(t_base *base, t_tex *tex, t_game *game, void *mlx)
{
	char	*path;
	int		i;

	i = 0;
	game->texwidth = 64;
	game->texheight = 64;
	while (i < 9)
	{
		path = create_path(&base->read, i);
		tex[i].xpm_img = mlx_xpm_file_to_image(mlx, path, &game->texwidth,
			&game->texheight);
		if (tex[i].xpm_img == NULL)
			exit_game(base, 1, 22);
		tex[i].xpm_addr = mlx_get_data_addr(tex[i].xpm_img, &tex[i].xpm_bpp,
			&tex[i].xpm_line_length, &tex[i].xpm_endian);
		i++;
	}
}

/*
** Initial direction vector is based on the viewing direction of the player:
** N, E, S or W.
** Plane: the 2d raycaster version of camera plane. Initial camera plane value
** changes when rotating. Done rotating, the updated value will be the new
** constant value use to determine your rayposition.
** Initial camera plane set on:
**		Planex = 0, planey = 0.66 --> N and S
**		Planex = 0.66, planey = 0 --> E and W (otherwise skewed wall)
*/

void			orientation(t_game *game, char pos)
{
	game->dirx = 0;
	game->diry = 0;
	if (pos == 'N')
		game->diry = -1;
	if (pos == 'S')
		game->diry = 1;
	if (pos == 'E')
		game->dirx = 1;
	if (pos == 'W')
		game->dirx = -1;
	game->planex = (game->diry == 0) ? 0 : 0.66;
	game->planey = (game->diry == 0) ? 0.66 : 0;
}

/*
** Mlx_win en img has to be set to NULL otherwise sefgault during the exit
** of the game
*/

void			initialise_game(t_move *move, t_mlx *mlx, t_tex *tex,
									t_base *base)
{
	int		i;

	i = 0;
	move->move_front = 0;
	move->move_back = 0;
	move->move_right = 0;
	move->move_left = 0;
	move->rotate_right = 0;
	move->rotate_left = 0;
	mlx->mlx = NULL;
	mlx->mlx_win = NULL;
	mlx->img = NULL;
	while (i < 9)
	{
		tex[i].xpm_img = NULL;
		i++;
	}
	base->zbuffer = (double *)malloc(sizeof(double) * base->read.render_x);
	if (base->zbuffer == NULL)
		exit_game(base, 1, 27);
}
