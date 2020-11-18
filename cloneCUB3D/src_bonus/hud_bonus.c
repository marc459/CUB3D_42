/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 14:51:37 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/15 12:48:05 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	draw_player(t_raycaster *rc, int num)
{
	int x;
	int y;
	int color;
	int pixel;

	color = RED;
	y = rc->player_pos_y * num - 1;
	while (y < (rc->player_pos_y * num + 1))
	{
		x = rc->player_pos_x * num - 1;
		while (x < (rc->player_pos_x * num + 1))
		{
			pixel = (y * rc->win_x + x) * 4;
			if (rc->endian == 1)
			{
				rc->img_data[pixel + 0] = (color >> 24);
				rc->img_data[pixel + 1] = (color >> 16) & 0xFF;
				rc->img_data[pixel + 2] = (color >> 8) & 0xFF;
				rc->img_data[pixel + 3] = (color) & 0xFF;
			}
			else if (rc->endian == 0)
			{
				rc->img_data[pixel + 0] = (color) & 0xFF;
				rc->img_data[pixel + 1] = (color >> 8) & 0xFF;
				rc->img_data[pixel + 2] = (color >> 16) & 0xFF;
				rc->img_data[pixel + 3] = (color >> 24);
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_life_bar(t_raycaster *rc)
{
	int x;
	int y;
	int color;
	int pixel;

	color = GREEN;
	y = 20;
	x = rc->win_x / 2;
	while (y < 30)
	{
		while (x < rc->win_x - 50)
		{
			pixel = (y * rc->win_x + x) * 4;
			if (rc->endian == 1)
			{
				rc->img_data[pixel + 0] = (color >> 24);
				rc->img_data[pixel + 1] = (color >> 16) & 0xFF;
				rc->img_data[pixel + 2] = (color >> 8) & 0xFF;
				rc->img_data[pixel + 3] = (color) & 0xFF;
			}
			else if (rc->endian == 0)
			{
				rc->img_data[pixel + 0] = (color) & 0xFF;
				rc->img_data[pixel + 1] = (color >> 8) & 0xFF;
				rc->img_data[pixel + 2] = (color >> 16) & 0xFF;
				rc->img_data[pixel + 3] = (color >> 24);
			}
			x++;
		}
		x = rc->win_x / 2;
		y++;
	}
}

void	draw_map(t_raycaster *rc)
{
	int y;
	int x;
	int num;
	int color;
	int pixel;

	if (2000 < rc->win_x)
		num = 5;
	else if (1000 < rc->win_x)
		num = 3;
	else
		num = 2;
	x = 0;
	y = 0;
	color = BLACK;
	draw_player(rc, num);
	draw_life_bar(rc);
	while (x < rc->map_height)
	{
		while (y < rc->map_width)
		{
			if (rc->world_map[x][y] == 1 || rc->world_map[x][y] == 2)
			{
				pixel = ((y * num) * rc->win_x + (x * num)) * 4;
				if (rc->endian == 1)
				{
					rc->img_data[pixel + 0] = (color >> 24);
					rc->img_data[pixel + 1] = (color >> 16) & 0xFF;
					rc->img_data[pixel + 2] = (color >> 8) & 0xFF;
					rc->img_data[pixel + 3] = (color) & 0xFF;
				}
				else if (rc->endian == 0)
				{
					rc->img_data[pixel + 0] = (color) & 0xFF;
					rc->img_data[pixel + 1] = (color >> 8) & 0xFF;
					rc->img_data[pixel + 2] = (color >> 16) & 0xFF;
					rc->img_data[pixel + 3] = (color >> 24);
				}
			}
			y++;
		}
		y = 0;
		x++;
	}
}
