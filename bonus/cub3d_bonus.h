/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 11:30:21 by msiemons      #+#    #+#                 */
/*   Updated: 2020/05/13 15:28:24 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# define KEY_ESC	53
# define KEY_LEFT	123
# define KEY_RIGHT	124
# define KEY_W		13
# define KEY_A		0
# define KEY_S		1
# define KEY_D		2
# define UDIV		1
# define VDIV		1
# define VMOVE		0.0

# include "../mlx/mlx.h"
# include "../libft/libft.h"
# include <unistd.h>

typedef struct			s_mlx {
	void				*mlx;
	void				*mlx_win;
	void				*img;
	char				*addr;
	int					bpp;
	int					line_length;
	int					endian;
}						t_mlx;

typedef struct			s_read {
	char				**array;
	char				*no;
	char				*ea;
	char				*so;
	char				*we;
	char				*sprite;
	double				x_pos;
	double				y_pos;
	int					render_x;
	int					render_y;
	int					c_color;
	int					f_color;
	int					red;
	int					blue;
	int					green;
	int					map_start;
	int					map_end;
	int					nb_sprites;
	char				pos;
}						t_read;

typedef struct			s_game{
	double				dirx;
	double				diry;
	double				raydirx;
	double				raydiry;
	double				sidedistx;
	double				sidedisty;
	double				deltadistx;
	double				deltadisty;
	double				planex;
	double				planey;
	double				time;
	double				movespeed;
	double				rotspeed;
	int					mapx;
	int					mapy;
	int					stepx;
	int					stepy;
	int					side;
	int					update;
	int					tex_side;
	int					texwidth;
	int					texheight;
}						t_game;

typedef struct			s_move{
	int					move_front;
	int					move_back;
	int					move_right;
	int					move_left;
	int					rotate_left;
	int					rotate_right;
}						t_move;

typedef struct			s_tex{
	void				*xpm_img;
	char				*xpm_addr;
	int					xpm_bpp;
	int					xpm_line_length;
	int					xpm_endian;
}						t_tex;

typedef struct			s_tex_co{
	double				step;
	double				texpos;
	int					texx;
}						t_tex_co;

typedef struct			s_wall{
	double				wallx;
	double				perpwalldist;
	int					lineheight;
	int					drawstart;
	int					drawend;
}						t_wall;

typedef struct			s_sprite{
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

typedef struct			s_floor{
	float				floorstepx;
	float				floorstepy;
	float				floorx;
	float				floory;
	float				posz;
	float				rowdistance;
	int					tx;
	int					ty;
	int					p;
}						t_floor;

typedef struct			s_base{
	t_read				read;
	t_mlx				mlx;
	t_game				game;
	t_move				move;
	t_tex				tex[5];
	t_tex				tex_fc[2];
	t_tex_co			tex_co;
	t_wall				wall;
	t_ll_sprite			*head;
	t_sprite			sprite;
	double				*zbuffer;
	int					save;
}						t_base;

t_base					*get_cub_file(char *filename);
char					*gnl_strjoin(char *s1, char *s2);
int						read_scene_file(t_base *base, t_read *read);
void					initialise_read_scene(t_read *read, t_ll_sprite **head);
int						cfr_itoa(int y, int *i, char **array,
							int cf_blue_green);
int						create_trgb_colorcode(int y, int entry_i, t_base *base,
							t_read *read);
int						cfr_endspaces(int y, int i, t_base *base, t_read *read);
int						check_pathstart(int y, int *i, char **array);
int						save_path_substr(int y, int i, char **identifier,
							t_base *base);
int						check_map(int *y, t_base *base, t_read *read);
int						last_char_save_pos(int y, t_base *base, t_read *read,
							char **array);
int						space_in_wall(int y, int i, char **array, t_read *read);
int						align_dif_front(char *s1, char *s2);
int						align_dif_back(int y, t_base *base, t_read *read);
void					save_sprite_coordinates(t_base *base, double y,
							double x);
void					ll_count_sprites(t_base *base);
void					ll_sort_sprites_swap_data(t_base *base);





int						game_mlx(t_base *base);
void					floor_ceiling_texture(t_base *base);
void					exit_game(t_base *base, int code, int error);






void					initialise_game(t_move *move, t_mlx *mlx, t_tex *tex,
							t_base *base);
void					orientation(t_game *game, char pos);
void					load_texture(t_base *base, t_tex *tex, t_game *game,
							void *mlx);
int						keypress(int keycode, t_base *base);
int						keyrelease(int keycode, t_base *base);
int						windowclose_x(t_base *img);
void					save_first_image_bmp(t_base *base);
void					move_rotate(t_game *game, t_read *read, t_move *move,
							char **array);
void					rotate_right(t_game *game);
void					rotate_left(t_game *game);


void					raycasting(t_base *base, t_game *game, t_read *read);
void					draw_calculations_wall(t_read *read, t_game *game,
							t_wall *wall);
void					texture_coordinates_wall(t_tex_co *tex_co,
							t_wall *wall, t_game *game, int render_y);
int						texture_pick(t_tex *tex, int texx, int texy, int i);
void					my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color);
void					sprite(t_base *base, t_sprite *sprite, t_game *game,
							t_read *read);
int						error_distr(t_base *base, int errornum);
void					free_cub_base(t_base *base);
void					free_array(t_read *read);

#endif
