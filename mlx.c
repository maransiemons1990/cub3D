/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mlx.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/24 16:30:07 by Maran         #+#    #+#                 */
/*   Updated: 2020/04/28 22:45:15 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Initial direction vector out of scene file: N, E, S, W.
** - PLANE: the 2d raycaster version of camera plane.
** Initial camera plane value. Value changes when rotating.
** Done rotating, the updated value will be the new constant value
** use to determine your rayposition.
** if (base->game.dirY == 0) THEN planeX = 0, planeY 0.66 --> N and S
** if (base->game.dirY == 1 || == -1) THEN planeX = 0.66 , planeY 0 --> E and W
*/

void			orientation(t_base *base)
{
	base->game.dirX = 0; 
	base->game.dirY = 0; 
	if (base->read.pos == 'N')
		base->game.dirY = -1;
	if (base->read.pos == 'S')
		base->game.dirY = 1;
	if (base->read.pos == 'E')
		base->game.dirX = 1;	
	if (base->read.pos == 'W')
		base->game.dirX = -1;
	base->game.planeX = (base->game.dirY == 0) ? 0 : 0.66;
	base->game.planeY = (base->game.dirY == 0) ? 0.66 : 0;
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
*/
void		texture(t_base *base)
{
	char *path_no;
	char *path_so;
	char *path_we;
	char *path_ea;
	char *path_s;
	
	base->game.texWidth = 64;
	base->game.texHeight = 64;
	path_no = ft_strjoin(base->read.no, "/wall_texture.xpm"); //free
	path_so = ft_strjoin(base->read.so, "/dirt.xpm");
	path_we = ft_strjoin(base->read.we, "/OreVein.xpm");
	path_ea = ft_strjoin(base->read.ea, "/CrateOver.xpm");
	path_s = ft_strjoin(base->read.sprite, "/barrel.xpm");
	base->tex_no.png_img = mlx_xpm_file_to_image(base->mlx.mlx, path_no, &base->game.texWidth, &base->game.texHeight);
	base->tex_no.png_addr = mlx_get_data_addr(base->tex_no.png_img, &base->tex_no.png_bits_per_pixel, &base->tex_no.png_line_length, &base->tex_no.png_endian);
	base->tex_so.png_img = mlx_xpm_file_to_image(base->mlx.mlx, path_so, &base->game.texWidth, &base->game.texHeight);
	base->tex_so.png_addr = mlx_get_data_addr(base->tex_so.png_img, &base->tex_so.png_bits_per_pixel, &base->tex_so.png_line_length, &base->tex_so.png_endian);
	base->tex_ea.png_img = mlx_xpm_file_to_image(base->mlx.mlx, path_ea, &base->game.texWidth, &base->game.texHeight);
	base->tex_ea.png_addr = mlx_get_data_addr(base->tex_ea.png_img, &base->tex_ea.png_bits_per_pixel, &base->tex_ea.png_line_length, &base->tex_ea.png_endian);
	base->tex_we.png_img = mlx_xpm_file_to_image(base->mlx.mlx, path_we, &base->game.texWidth, &base->game.texHeight);
	base->tex_we.png_addr = mlx_get_data_addr(base->tex_we.png_img, &base->tex_we.png_bits_per_pixel, &base->tex_we.png_line_length, &base->tex_we.png_endian);
	
	// base->tex_f.png_img = mlx_png_file_to_image(base->mlx.mlx, "./64x/dirt.png", &base->game.texWidth, &base->game.texHeight);
	// base->tex_f.png_addr = mlx_get_data_addr(base->tex_f.png_img, &base->tex_f.png_bits_per_pixel, &base->tex_f.png_line_length, &base->tex_f.png_endian);
	// base->tex_c.png_img = mlx_png_file_to_image(base->mlx.mlx,"./Textures_png/stars.png", &base->game.texWidth, &base->game.texHeight);
	// base->tex_c.png_addr = mlx_get_data_addr(base->tex_c.png_img, &base->tex_c.png_bits_per_pixel, &base->tex_c.png_line_length, &base->tex_c.png_endian);

	base->tex_s.png_img = mlx_xpm_file_to_image(base->mlx.mlx, path_s, &base->game.texWidth, &base->game.texHeight);
	base->tex_s.png_addr = mlx_get_data_addr(base->tex_s.png_img, &base->tex_s.png_bits_per_pixel, &base->tex_s.png_line_length, &base->tex_s.png_endian);
}

void			initialise_game(t_base *base)
{
	base->game.move_front = 0;
	base->game.move_back = 0;
	base->game.move_right = 0;
	base->game.move_left = 0;
	base->game.rotate_right = 0;
	base->game.rotate_left = 0;
	base->game.rotate = 0;
	//base->game.update = 0;
}

/*
** mlx_init: This will establish a connection to the correct graphical system
** and will return a void * which holds the location of our current MLX instance/ connection identifier.
** mlx_new_window: creating a window. Return a pointer to the window we have just created.
** mlx_loop: to initiate the window rendering. It is an infinite loop that waits for
** an event, and then calls a user-defined function associated with this event
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
	base->game.count = 0;
	initialise_game(base);
	orientation(base);
	base->mlx.mlx = mlx_init();
	base->mlx.mlx_win = mlx_new_window(base->mlx.mlx, base->read.render_x, base->read.render_y, "Wolfenstein 3D! | Maran Siemons");
	//base->mlx.img = mlx_new_image(base->mlx.mlx, base->read.render_x, base->read.render_y);
	//base->mlx.addr = mlx_get_data_addr(base->mlx.img, &base->mlx.bits_per_pixel, &base->mlx.line_length, &base->mlx.endian);
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
