/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialise_game.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/07 12:28:38 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/07 12:31:11 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char			*create_path(t_base *base, t_read read, int i)
{
	char 		*path;
	
	path = NULL;
	if (i == 0)
		path = ft_strjoin(read.no, "/wall_texture.xpm");
	else if (i == 1)
		path = ft_strjoin(read.ea, "/CrateOver.xpm");
	else if (i == 2)
		path = ft_strjoin(read.so, "/dirt.xpm");
	else if (i == 3)
		path = ft_strjoin(read.we, "/OreVein.xpm");
	else if (i == 4)	
		path = ft_strjoin(read.sprite, "/barrel.xpm");
	if (path == NULL)
		exit_game(base, 1, 21);
	return (path);
}

/*
** 
** img_ptr - specifies the image to use. 
** bits_per_pixel - the number of bits needed to represent a pixel color
** (also called the depth of the image).
** size_line - the number of bytes used to store one line of the image in memory.
** This information is needed to move from one line to another in the image.
** endian - tells you wether the pixel color in the image needs to be stored in
** little endian (== 0), or big endian (== 1).
** https://opengameart.org/content/64x-textures-an-overlays
** https://gamebanana.com/textures/download/4678
** https://anyconv.com/png-to-xpm-converter/
** Tutorial states "mlx_png_file_to_image currently leaks memory".
** So changed all png functions to xpm.
** no 0, ea 1, so 2, we 3, sprite 4
*/
void			load_texture(t_base *base, t_tex *tex, t_game *game, void *mlx)
{
	char 		*path;
	int			i;

	i = 0;
	game->texwidth = 64;
	game->texheight = 64;
	while (i < 5)
	{
		path = create_path(base, base->read, i);
		tex[i].xpm_img = mlx_xpm_file_to_image(mlx, path, &game->texwidth,
			&game->texheight);
		free(path);
		if (tex[i].xpm_img == NULL)
			exit_game(base, 1, 22);
		tex[i].xpm_addr = mlx_get_data_addr(tex[i].xpm_img, &tex[i].xpm_bpp,
			&tex[i].xpm_line_length, &tex[i].xpm_endian);
		i++;
	}
}

/*
** Initial direction vector out of scene file: N, E, S, W.
** - PLANE: the 2d raycaster version of camera plane.
** Initial camera plane value. Value changes when rotating.
** Done rotating, the updated value will be the new constant value
** use to determine your rayposition.
** if (base->game.diry == 0) THEN planex = 0, planey 0.66 --> N and S 
** if (base->game.diry == 1 || == -1) THEN planex = 0.66 , planey 0 --> E and W --> otherwise skewed wall
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

//wss new_window ook nog op NULL
//win en img has to be set to NULL otherwise sefgault in exit_game
void			initialise_game(t_game *game, t_mlx *mlx, t_tex *tex,
									double *zbuffer)
{
	int 		i;
	
	i = 0;
	game->move_front = 0;
	game->move_back = 0;
	game->move_right = 0;
	game->move_left = 0;
	game->rotate_right = 0;
	game->rotate_left = 0;
	game->rotate = 0;
	mlx->img = NULL;
	mlx->mlx_win = NULL;
	while (i < 5)
	{
		tex[i].xpm_img = NULL;
		i++;
	}
	zbuffer = NULL;
}
