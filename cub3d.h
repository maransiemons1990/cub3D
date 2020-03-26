/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 11:30:21 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/26 20:09:04 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define TWOD base->read.array
# define READ base->read

# define X11_EVENT_KEY_PRESS		2
# define X11_EVENT_KEY_RELEASE		3
# define X11_EVENT_EXIT				17

# define KEY_ESC		53
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2

# include "mlx/mlx.h" 
# include "libft/libft.h"

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
//TEST
# include <time.h>

typedef struct	s_mlx {
    void		*mlx;
	void    	*mlx_win;
	void        *img;
	void        *new_img;
	char		*addr;
	char		*new_addr;
	int			bits_per_pixel;
    int			line_length;
    int			endian;
}               t_mlx;

typedef struct	s_read {
	char		**array;
	int			error;
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
	int			x_pos;
	int			y_pos;
}				t_read;

typedef struct s_game {
	double		dirX;
	double		dirY;

	int			mapX;
	int 		mapY;

	int			stepX; //what direction to step in x or y-direction (either +1 or -1)
    int 		stepY;
	
	double		rayDirX;
	double		rayDirY;
	
	double		sideDistX; //length of ray from current position to next x or y-side
    double		sideDistY;

	double		deltaDistX;
	double		deltaDistY;
	
	int			side; //was a NS or a EW wall hit?
	
	int			move_front;
	int			move_y;

	double		time;
	double		oldtime;
	double		frametime;
	double		movespeed;
	double		rotspeed;
}				t_game;

typedef struct	s_base{
	t_read		read;
	t_mlx		mlx;
	t_game		game;
}				t_base;


//GNL_CUB3D
char			*gnl_strjoin(char *s1, char *s2);

//ERRORMESSAGES
int				error_distribution(t_base *base);
void			*error_general(int error, char *line);
//GET_cub
t_base			*getcubfile(char *filename);

//READ_SCENE_FILE
int				read_scene_file(t_base *base);
void			initialise(t_base *base);
void			end_free(t_base *base);

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


//MLX
int				mlx(t_base *base);
int				loop(t_base *base);

//Ray
int				raycasting(t_base *base);

//Rayhooks
int             keypress(int keycode, t_base *img);
int             keyrelease(int keycode, t_base *base);
int				windowclose_x(t_base *img);

//Tutorial:
// void		print_triangle(t_data *img, int x, int y, int radius);
// void		print_full_square(t_data *img, int x, int xsize, int y, int ysize);
// void		print_square(t_data *img, int x, int xsize, int y, int ysize);
//void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

//Overig
void		twod_checker(char **array);
void		valuechecker(t_base *base);

#endif