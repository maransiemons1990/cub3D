/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 11:30:21 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/05 13:19:20 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

//# include <mlx.h>

//Delete?:
#include <stdio.h>
#include <stdlib.h>

//GNL
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
// Open
#include <fcntl.h>
//error
#include <sys/errno.h>
//

typedef struct	s_addr {
	char		*addr;
	int			bits_per_pixel;
    int			line_length;
    int			endian;
} 				t_addr;

typedef struct	s_data {
    void		*mlx;
	void    	*mlx_win;
	void        *img;
}               t_data;

typedef struct	s_read {
	char		**array; //nog ergens freeen?
	int			error;
	int 		render_x;
	int 		render_y;
}				t_read;

typedef struct	s_base{
	t_read		read;		
	t_data		data;
	t_addr		addr;
}				t_base;


void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

//GET cub
t_base		*getcubfile(char *filename);
//void		check(t_base *base);
int			ft_check_line(int y, t_base *base);

//GNL
char		*ft_gnl_cub3d(int fd);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char *s1, char *s2);

//Tutorial:
void		print_triangle(t_data *img, int x, int y, int radius);
void		print_full_square(t_data *img, int x, int xsize, int y, int ysize);
void		print_square(t_data *img, int x, int xsize, int y, int ysize);

//readmap/identifiers:
char			**ft_split(char const *s, char c);
int				check(t_base *base);
void			errormessages(t_base *base);

//Overig
void		twod_checker(char **array);
void		valuechecker(t_base *base);

#endif