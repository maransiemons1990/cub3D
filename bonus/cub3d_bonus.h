/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d_bonus.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/05/11 22:59:56 by Maran         #+#    #+#                 */
/*   Updated: 2020/05/12 23:40:03 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void					floor_ceiling_texture(t_base *base);
int						game_mlx_bonus(t_base *base);

