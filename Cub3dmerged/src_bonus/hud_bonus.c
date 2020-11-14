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

void draw_player(t_raycaster *rc, int num)
{
	int printplayer_X;
	int printplayer_Y;

	printplayer_X = rc->player_pos_y * num;
	printplayer_Y = rc->player_pos_x * num;
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, printplayer_X + 1, printplayer_Y + 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, printplayer_X, printplayer_Y, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, printplayer_X - 1, printplayer_Y - 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, printplayer_X - 1, printplayer_Y + 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, printplayer_X + 1, printplayer_Y - 1, 0x33FF3C);
}

void draw_map(t_raycaster *rc)
{
	int y;
	int x;
	int x_wall;
	int y_wall;
	int num;

	if(2000 < rc->win_x)
		num = 5;
	else if(1000 < rc->win_x)
		num = 3;
	else
		num = 2;
	x = 0;
	y = 0;
	draw_player(rc, num);
	while (x < rc->map_height)
	{
		while (y < rc->map_width)
		{
			if (rc->world_map[x][y] == 1 || rc->world_map[x][y] == 2)
			{
				mlx_pixel_put(rc->mlx_ptr, rc->win_ptr,
							x_wall, y_wall, 0xFA2C00);
			}
				
			y++;
			x_wall = x_wall + num;
		}
		y = 0;
		x++;
		x_wall = num;
		y_wall = y_wall + num;
	}
}