/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 11:30:21 by msiemons      #+#    #+#                 */
/*   Updated: 2020/05/07 12:35:22 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define TWOD base->read.array
# define READ base->read

# define KEY_ESC		53
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# include "mlx/mlx.h" 
# include "libft/libft.h"

//get resolution
#include <CoreGraphics/CGDirectDisplay.h>

//Delete?:
# include <stdio.h>
# include <stdlib.h>

//GNL
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
// Open
# include <fcntl.h>
//error
# include <sys/errno.h>
//clock
# include <time.h>

//sin cos
#include <math.h>

//#include "string.h"

typedef struct			s_mlx {
    void				*mlx;
	void    			*mlx_win;
	void        		*img;
	char				*addr;
	int					bpp;
    int					line_length;
    int					endian;
}               		t_mlx;

typedef struct			s_read {
	char				**array;
	int 				render_x;
	int 				render_y;
	int					c_color;
	int					f_color;
	int					red;
	int 				blue;
	int					green;
	char 				*no;
	char 				*ea;
	char 				*so;
	char 				*we;
	char 				*sprite;
	int					map_start;
	int					map_end;
	char				pos;
	double				x_pos;
	double				y_pos;
	int					nb_sprites;
}						t_read;

//stepx y what direction to step in x or y-direction (either +1 or -1)
//sidedist: length of ray from current position to next x or y-side
// side: was a NS or a EW wall hit?

typedef struct			s_game {
	double				dirx;
	double				diry;
	int					mapx;
	int 				mapy;
	int					stepx;
    int 				stepy;
	double				raydirx;
	double				raydiry;
	double				sidedistx;
    double				sidedisty;
	double				deltadistx;
	double				deltadisty;
	double				planex;
	double				planey;
	int					side;
	int					move_front;
	int					move_back;
	int					move_right;
	int					move_left;
	int 				rotate_left;
	int					rotate_right;
	int					rotate;
	double				time;
	double				movespeed;
	double				rotspeed;
	int					update;
	int					tex_side;
	int					texwidth;
	int					texheight;
}						t_game;

typedef struct			s_tex{
	void				*xpm_img;
	char				*xpm_addr;
	int					xpm_bpp;
    int					xpm_line_length;
    int					xpm_endian;
}						t_tex;

typedef struct 			s_floor{
	float				floorstepx;
	float				floorstepy;
	float				floorx;
	float				floory;
}						t_floor;

typedef struct 			s_tex_co{
	double				step;
	double				texpos;
	int					texx;
}						t_tex_co;

typedef struct 			s_wall{
	int					lineheight;
	int					drawstart;
	int					drawend;
	double				wallx;
	double				perpwalldist;
}						t_wall;

typedef struct 			s_sprite{
	double				transformy;
	int					vmovescreen;
	int					spr_screenx;
	int					drawstartx;
	int					drawendx;
	int					drawstarty;
	int					drawendy;
	int					spr_height;
	int					spr_width;
 }						t_sprite;

typedef struct			s_ll_sprite{
	double				x;
	double				y;
	double				distance;
	struct s_ll_sprite	*next;
}						t_ll_sprite;

typedef struct			s_base{
	t_read				read;
	t_mlx				mlx;
	t_game				game;
	t_tex				tex[5];
	t_tex				tex_f;
	t_tex				tex_c;
	t_floor				floor;
	t_tex_co			tex_co;
	t_wall				wall;
	t_ll_sprite			*head;
	t_sprite			sprite;
	double				*zbuffer;
	int					save;
}						t_base;



int						error_distr(t_base *base, int errornum);
t_base					*getcubfile(char *filename);

int						read_scene_file(t_base *base, t_read *read);
void					initialise(t_read *read, t_ll_sprite **head);

void					floor_ceiling_smooth(t_mlx *mlx, t_read *read);

void            		sprite(t_base *base, t_sprite *sprite, t_game *game, t_read *read);

int             		keypress(int keycode, t_base *base);
int             		keyrelease(int keycode, t_base *base);
int						windowclose_x(t_base *img);

void		raycasting(t_base *base, t_game *game, t_read *read);

void            		my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);

void					move_rotate(t_game *game, t_read *read, char **array);

void					rotate_right(t_game *game);
void					rotate_left(t_game *game);

void		draw_calculations_wall(t_read *read, t_game *game, t_wall *wall);
void		texture_coordinates_wall(t_tex_co *tex_co, t_wall *wall, t_game *game, int render_y);
int			texture_pick_wallside(t_tex *tex, int texx, int texy, int i);

void			initialise_game(t_game *game, t_mlx *mlx, t_tex *tex, double *zbuffer);
void			orientation(t_game *game, char pos);
void			load_texture(t_base *base, t_tex *tex, t_game *game, void *mlx);



//GNL_CUB3D
char			*gnl_strjoin(char *s1, char *s2);

//ERRORMESSAGES
//int				error_distribution(t_base *base);
void			*error_gnl_cub(int error, char *line);

//READ_SCENE_FILE
void			free_cub_base(t_base *base);

//READ_SCENE_UTILS
int				cfr_itoa(int y, int *i, char **array, int cf_blue_green);
int				create_trgb_colorcode(int y, int entry_i, t_base *base, t_read *read);
int				cfr_endspaces(int y, int i, t_base *base, t_read *read);
int				check_pathstart(int y, int *i, char **array);
int				save_path_substr(int y, int i, char **identifier, t_base *base);

//Check_map_UTILS
int				check_map(int *y, t_base *base, t_read *read);
int				last_char_save_pos(int y, t_base *base, t_read *read, char **array);
int 			space_in_wall(int y, int i, char **array, t_read *read);
int				align_dif_front(char *s1, char *s2);
int				align_dif_back(int y, t_base *base, t_read *read);

//SAVE_SPRITES
void			save_sprite_coordinates(t_base *base, double y, double x);
void			ll_count_sprites(t_base *base);
void			ll_sort_sprites_swap_data(t_base  *base);


//MLX
int				mlx(t_base *base);
// int				loop(t_base *base);

//Ray
//void				raycasting(t_base *base);

//Rayhooks

//exit
void			exit_game(t_base *base, int code, int error);
void			free_array(t_read *read);

void			floor_ceiling_texture(t_base *base); //extra

//

//sprites
void			zbuffer(t_base *base, int x);

//
void		save_first_image_bmp(t_base *base);
//Tutorial:
// void		print_triangle(t_data *img, int x, int y, int radius);
// void		print_full_square(t_data *img, int x, int xsize, int y, int ysize);
// void		print_square(t_data *img, int x, int xsize, int y, int ysize);
//void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif