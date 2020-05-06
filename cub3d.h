/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 11:30:21 by msiemons      #+#    #+#                 */
/*   Updated: 2020/05/06 09:41:33 by Maran         ########   odam.nl         */
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

typedef struct	s_mlx {
    void		*mlx;
	void    	*mlx_win;
	void        *img;
	char		*addr;
	int			bpp;
    int			line_length;
    int			endian;
}               t_mlx;

typedef struct	s_read {
	char		**array;
//	int			error;
	int 		render_x;
	int 		render_y;
	int			c_color;
	int			f_color;
	int			red;
	int 		blue;
	int			green;
	char 		*no;
	char 		*ea;
	char 		*so;
	char 		*we;
	char 		*sprite;
	int			map_start;
	int			map_end;
	char		pos;
	double		x_pos; //
	double		y_pos; //
	int			nb_sprites; //
}				t_read;

typedef struct s_game {
	double		dirx;
	double		diry;

	int			mapx;
	int 		mapy;

	int			stepx; //what direction to step in x or y-direction (either +1 or -1)
    int 		stepy;
	
	double		raydirx;
	double		raydiry;
	
	double		sidedistx; //length of ray from current position to next x or y-side
    double		sidedisty;

	double		deltadistx;
	double		deltadisty;

	double		planex;
	double		planey;
	
	int			side; //was a NS or a EW wall hit?
	
	int			move_front;
	int			move_back;
	int			move_right;
	int			move_left;
	
	int 		rotate_left;
	int			rotate_right;
	int			rotate;

	double		time;
	double		oldtime;
	double		frametime;
	double		movespeed;
	double		rotspeed;

	int			update;

	int			tex_side;
	int			texwidth;
	int			texheight;
	
}				t_game;

typedef struct	s_tex{

	void		*xpm_img;
	char		*xpm_addr;
	int			xpm_bpp;
    int			xpm_line_length;
    int			xpm_endian;
}				t_tex;

typedef struct s_floor{
	float		floorstepx;
	float		floorstepy;
	float		floorx;
	float		floory;
}				t_floor;

typedef struct s_tex_co{
	double		step;
	double		texpos;
	int			texx;
}				t_tex_co;

typedef struct s_wall{
	int			lineheight;
	int			drawstart;
	int			drawend;
	double		wallx;
	double		perpwalldist;
}				t_wall;

typedef struct s_sprite2{
	double		transformy;
	int			vmovescreen;
	int			spritescreenx;
	//
	int			drawstartx;
	int			drawendx;
	int			drawstarty;
	int			drawendy;
	int			spriteheight;
	int			spritewidth;
	
 }				t_sprite2;

typedef struct s_sprite{
	double				x;
	double				y;
	double				distance;
	struct s_sprite		*next;
}				t_sprite;

typedef struct	s_base{
	t_read		read;
	t_mlx		mlx;
	t_game		game;

	t_tex		tex[5];
	
	t_tex		tex_f;
	t_tex		tex_c;
	t_floor		floor;
	
	t_tex_co	tex_co;
	t_wall		wall;
	
	t_sprite	*head;
	t_sprite2	sprite;
	
	double		*zbuffer;
	int			save;
}				t_base;



int				error_distr(t_base *base, int errornum);
t_base			*getcubfile(char *filename);



//GNL_CUB3D
char			*gnl_strjoin(char *s1, char *s2);

//ERRORMESSAGES
//int				error_distribution(t_base *base);
void			*error_gnl_cub(int error, char *line);

//READ_SCENE_FILE
int				read_scene_file(t_base *base);
void			initialise(t_base *base);
void			free_cub_base(t_base *base);

//READ_SCENE_UTILS
int				cfr_itoa(int y, int *i, t_base *base, int cf_blue_green);
int				create_trgb_colorcode(int y, int entry_i, t_base *base);
int				cfr_endspaces(int y, int i, t_base *base);
int				check_pathstart(int y, int *i, t_base *base);
int				save_path_substr(int y, int i, char **identifier, t_base *base);

//Check_map_UTILS
int				check_map(int *y, t_base *base);
int				last_char_save_pos(int y, t_base *base);
int 			space_in_wall(int y, int i, t_base *base);
int				align_dif_front(char *s1, char *s2);
int				align_dif_back(int y, t_base *base);

//SAVE_SPRITES
void			save_sprite_coordinates(t_base *base, double y, double x);
void			ll_count_sprites(t_base *base);
void			ll_sort_sprites_swap_data(t_base  *base);


//MLX
int				mlx(t_base *base);
int				loop(t_base *base);

//Ray
void				raycasting(t_base *base);

//Rayhooks
int             keypress(int keycode, t_base *img);
int             keyrelease(int keycode, t_base *base);
int				windowclose_x(t_base *img);

//exit
void			exit_game(t_base *base, int code, int error);
void			free_array(t_read *read);

//floor
void			floor_ceiling_smooth(t_base *base);
void			floor_ceiling_texture(t_base *base); //extra

//
void            my_mlx_pixel_put(t_base *base, int x, int y, int color);

//sprites
void			zbuffer(t_base *base, int x);
void            sprite(t_base *base);

//
void		save_first_image_bmp(t_base *base);
//Tutorial:
// void		print_triangle(t_data *img, int x, int y, int radius);
// void		print_full_square(t_data *img, int x, int xsize, int y, int ysize);
// void		print_square(t_data *img, int x, int xsize, int y, int ysize);
//void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

//Overig
void		twod_checker(char **array);
void		valuechecker(t_base *base);
void		print_list(t_base *base);

#endif