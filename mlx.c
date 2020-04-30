/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/24 16:30:07 by Maran         #+#    #+#                 */
/*   Updated: 2020/04/30 21:00:39 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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
void		texture(t_base *base)
{
	char *path;
	int		i;
	
	i = 0;
	base->game.texWidth = 64;
	base->game.texHeight = 64;
	while (i < 5)
	{
		if (i == 0)
			path = ft_strjoin(base->read.no, "/wall_texture.xpm"); //free
		else if (i == 1)
			path = ft_strjoin(base->read.ea, "/CrateOver.xpm");
		else if (i == 2)
			path = ft_strjoin(base->read.so, "/dirt.xpm");
		else if (i == 3)
			path = ft_strjoin(base->read.we, "/OreVein.xpm");
		else if (i == 4)	
			path = ft_strjoin(base->read.sprite, "/barrel.xpm");
		base->tex[i].png_img = mlx_xpm_file_to_image(base->mlx.mlx, path, &base->game.texWidth, &base->game.texHeight);
		base->tex[i].png_addr = mlx_get_data_addr(base->tex[i].png_img, &base->tex[i].png_bits_per_pixel, &base->tex[i].png_line_length, &base->tex[i].png_endian);
		free (path);
		i++;
	}
}

/*
** Initial direction vector out of scene file: N, E, S, W.
** - PLANE: the 2d raycaster version of camera plane.
** Initial camera plane value. Value changes when rotating.
** Done rotating, the updated value will be the new constant value
** use to determine your rayposition.
** if (base->game.dirY == 0) THEN planeX = 0, planeY 0.66 --> N and S 
** if (base->game.dirY == 1 || == -1) THEN planeX = 0.66 , planeY 0 --> E and W --> otherwise skewed wall
*/

void			orientation(t_game *game, t_read *read)
{
	game->dirX = 0; 
	game->dirY = 0; 
	if (read->pos == 'N')
		game->dirY = -1;
	if (read->pos == 'S')
		game->dirY = 1;
	if (read->pos == 'E')
		game->dirX = 1;	
	if (read->pos == 'W')
		game->dirX = -1;
	game->planeX = (game->dirY == 0) ? 0 : 0.66;
	game->planeY = (game->dirY == 0) ? 0.66 : 0;
}

void			initialise_game(t_game *game)
{
	game->move_front = 0;
	game->move_back = 0;
	game->move_right = 0;
	game->move_left = 0;
	game->rotate_right = 0;
	game->rotate_left = 0;
	game->rotate = 0;
	//base->game.update = 0;
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
*/
int				mlx(t_base *base)
{
	initialise_game(&base->game);
	orientation(&base->game, &base->read);
	base->mlx.mlx = mlx_init();
	base->mlx.mlx_win = mlx_new_window(base->mlx.mlx, base->read.render_x, base->read.render_y, "Wolfenstein 3D! | Maran Siemons");
	texture(base);
// /* ----------HOOKING EVENT-----------------*/ 
	mlx_hook(base->mlx.mlx_win, X11_EVENT_KEY_PRESS, 1L<<0, &keypress, base);				//wel of geen & voor functie? // geen & voor base!
	mlx_hook(base->mlx.mlx_win, X11_EVENT_KEY_RELEASE, 1L<<1, &keyrelease, base);
	mlx_hook(base->mlx.mlx_win, X11_EVENT_EXIT, 1L<<17, &windowclose_x, base);
	//mlx_hook(base->mlx.mlx_win, X11_EVENT_RESIZE, 1L<<18, &windowclose_x, base);
	if (base->save == 0)
	{
		loop(base);
		save_first_image_bmp(base);
		return (0);
	}
	//loop(base);
	mlx_loop_hook(base->mlx.mlx, &loop, base);
// // /*----------------------------------------------*/
 	mlx_loop(base->mlx.mlx);
	//mlx_destroy_image(base->mlx.mlx, base->mlx.new_img);
	return (0);
}
