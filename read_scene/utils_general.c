/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_general.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/10 15:25:07 by msiemons      #+#    #+#                 */
/*   Updated: 2020/05/01 19:16:13 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// Check of we sprites nog moeten freeeen.

void			free_array(t_read *read)
{
	int y;

	y = 0;
	while (read->array[y])
	{
		free(read->array[y]);
		y++;
	}
	free(read->array);
}

void			free_cub_base(t_base *base)
{
	free_array(&base->read);
	if (base->read.no)
		free(base->read.no);
	if (base->read.ea)
		free(base->read.ea);
	if (base->read.so)
		free(base->read.so);
	if (base->read.we)
		free(base->read.we);
	if (base->read.sprite)
		free(base->read.sprite);
	free (base);
}

//exit 0 is success
//exit(1) is failure
void			exit_game(t_base *base, int code, int error)
{
	int i;
	
	i = 0;
	
	if (base->ZBuffer)
		free (base->ZBuffer);
	while (i < 5)
	{
		if (base->tex[i].xpm_img)
			mlx_destroy_image(base->mlx.mlx, base->tex[i].xpm_img);
		i++;
	}
	if (base->mlx.img)
		mlx_destroy_image(base->mlx.mlx, base->mlx.img);
	if (base->mlx.mlx_win)
		mlx_destroy_window(base->mlx.mlx, base->mlx.mlx_win);
	if (code == 1)
		error_distr(base, error);
	else
		free_cub_base(base);
	exit(code);
	//	printf("Waar segfault? error %d\n", error);
}

void			initialise(t_base *base)
{
	base->read.render_x = -1;
	base->read.render_y = -1;
	base->read.c_color = -1;
	base->read.f_color = -1;
	base->read.no = NULL;
	base->read.ea = NULL;
	base->read.so = NULL;
	base->read.we = NULL;
	base->read.sprite = NULL;
	base->read.map_start = -1;
	base->read.map_end = -1;
	base->read.pos = -1;
	base->read.x_pos = -1;
	base->read.y_pos = -1;
	//
	base->head = NULL;
	//
}
