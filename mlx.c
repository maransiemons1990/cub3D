/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/24 16:30:07 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/06 16:51:22 by Maran         ########   odam.nl         */
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
static void			load_texture(t_base *base, t_tex *tex, t_game *game,
								void *mlx)
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

static void			orientation(t_game *game, char pos)
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
static void			initialise_game(t_game *game, t_mlx *mlx, t_tex *tex,
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

/*
** mlx_init: This will establish a connection to the correct graphical system
** and will return a void * which holds the location of our current MLX instance/ connection identifier.
** mlx_new_window: creating a window. Return a pointer to the window we have just created.
** mlx_loop: to initiate the window rendering. It is an infinite loop that waits for
** an event, and then calls a user-defined function associated with this event.
** Loop over the given mlx pointer. Each hook that was registered prior to this will be called accordingly by order of registration.
** mlx_new_image creates a new image in memory.
** The user can draw inside the image, and can dump the image inside a specified window
** at any  time  to  display  it  on  the screen. This is done using **mlx_put_image_to_window ()**.
** mlx_get_data_addr: returns information about the created image, allowing a user to modify it later.
** returns a char * address that represents the begining of the memory area where the image is stored.
** We should ALWAYS calculate the memory offset using the line length set by mlx_get_data_addr.
** TO DO: temporary image aanmaken.
** X11_EVENT_KEY_PRESS 2, X11_EVENT_KEY_RELEASE 3, X11_EVENT_EXIT 17
*/
int				mlx(t_base *base)
{
	initialise_game(&base->game, &base->mlx, base->tex, base->zbuffer);
	orientation(&base->game, base->read.pos);
	base->mlx.mlx = mlx_init();
	if (base->mlx.mlx == NULL)
		exit_game(base, 1, 29);
	base->mlx.mlx_win = mlx_new_window(base->mlx.mlx, base->read.render_x,
		base->read.render_y, "Wolfenstein 3D! | Maran Siemons");
	if (base->mlx.mlx_win == NULL)
		exit_game(base, 1, 20);
	load_texture(base, base->tex, &base->game, base->mlx.mlx);
	mlx_hook(base->mlx.mlx_win, 2, 1L<<0, &keypress, base);
	mlx_hook(base->mlx.mlx_win, 3, 1L<<1, &keyrelease, base);
	mlx_hook(base->mlx.mlx_win, 17, 1L<<17, &windowclose_x, base);
	if (base->save == 0)
	{
		loop(base);
		save_first_image_bmp(base);
		return (0);
	}
	mlx_loop_hook(base->mlx.mlx, &loop, base);
 	mlx_loop(base->mlx.mlx);
	return (0);
}
