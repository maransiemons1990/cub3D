/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/26 11:30:21 by msiemons       #+#    #+#                */
/*   Updated: 2020/03/02 19:06:52 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>

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

	t_addr		ad;	

}               t_data;

void		my_mlx_pixel_put(t_data *data, int x, int y, int color);

//GNL
int			ft_gnl_cub3d(int fd, char **line);
size_t		ft_strlen(const char *s);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(char *s1, char *s2);

//Tutorial:
void		print_triangle(t_data *img, int x, int y, int radius);
void		print_full_square(t_data *img, int x, int xsize, int y, int ysize);
void		print_square(t_data *img, int x, int xsize, int y, int ysize);

#endif