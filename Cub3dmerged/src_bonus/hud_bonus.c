/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 14:51:37 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/14 14:55:06 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void draw_map(t_raycaster *rc)
{
	int y;
	int x;
	int printplayer_X;
	int printplayer_Y;
	int x_wall;
	int y_wall;
	int tmpx;
	int tmpy;

	x = 0;
	y = 0;
	x_wall = 10;
	y_wall = 10;
	printplayer_X = rc->player_pos_y * 10;
	printplayer_Y = rc->player_pos_x * 10;
	tmpx = printplayer_X;
	tmpy = printplayer_Y;
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx + 1, tmpy + 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx, tmpy, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx - 1, tmpy - 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx - 1, tmpy + 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx + 1, tmpy - 1, 0x33FF3C);

	while (x < rc->map_height)
	{
		while (y < rc->map_width)
		{
			if (rc->world_map[x][y] == 1 || rc->world_map[x][y] == 2)
				mlx_pixel_put(rc->mlx_ptr, rc->win_ptr,
							  x_wall, y_wall, 0xFA2C00);
			y++;
			x_wall = x_wall + 10;
		}
		y = 0;
		x++;
		x_wall = 10;
		y_wall = y_wall + 10;
	}
}