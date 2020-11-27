/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 09:40:15 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/26 12:41:34 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	set_sprite(t_raycaster *rc)
{
	rc->i = 0;
	while (rc->i < rc->numsprites)
	{
		get_sprite(rc);
		rc->i++;
	}
	rc->i = 0;
	order_sprite(rc);
	while (rc->i < rc->numsprites)
	{
		while (rc->sprite[rc->i].stripe < rc->sprite[rc->i].drawend_x)
		{
			if (rc->sprite[rc->i].transform_y > 0 &&
				rc->sprite[rc->i].stripe >= 0 && rc->sprite[rc->i].stripe <=
				rc->win_x && rc->sprite[rc->i].transform_y <
				rc->spr_buffer[rc->sprite[rc->i].stripe])
				draw_sprite(rc);
			rc->sprite[rc->i].stripe++;
		}
		rc->i++;
	}
}

void	get_sprite(t_raycaster *rc)
{
	rc->sprite[rc->i].distance = ((rc->player_pos_x - rc->sprite[rc->i].x) *
		(rc->player_pos_x - rc->sprite[rc->i].x) + (rc->player_pos_y - rc->sprite[rc->i].y)
		* (rc->player_pos_y - rc->sprite[rc->i].y));
	rc->sprite[rc->i].sprite_x = rc->sprite[rc->i].x - rc->player_pos_x + 0.5;
	rc->sprite[rc->i].sprite_y = rc->sprite[rc->i].y - rc->player_pos_y + 0.5;
	rc->sprite[rc->i].invdet = 1.0 / (rc->player_plane_x * rc->diry -
			rc->dirx * rc->player_plane_y);
	rc->sprite[rc->i].transform_x = rc->sprite[rc->i].invdet * (rc->diry
		* rc->sprite[rc->i].sprite_x - rc->dirx * rc->sprite[rc->i].sprite_y);
	rc->sprite[rc->i].transform_y = rc->sprite[rc->i].invdet * (-rc->player_plane_y *
		rc->sprite[rc->i].sprite_x + rc->player_plane_x * rc->sprite[rc->i].sprite_y);
	rc->sprite[rc->i].screen = (int)((rc->win_x / 2) *
		(1 + rc->sprite[rc->i].transform_x / rc->sprite[rc->i].transform_y));
	rc->sprite[rc->i].height = abs((int)(rc->win_y /
		(rc->sprite[rc->i].transform_y)));
	rc->sprite[rc->i].drawstart_y = -rc->sprite[rc->i].height / 2 + rc->win_y / 2;
	get_sprite_2(rc);
}

void	get_sprite_2(t_raycaster *rc)
{
	if (rc->sprite[rc->i].drawstart_y < 0)
		rc->sprite[rc->i].drawstart_y = 0;
	rc->sprite[rc->i].drawend_y = rc->sprite[rc->i].height / 2 + rc->win_y / 2;
	if (rc->sprite[rc->i].drawend_y >= rc->win_y)
		rc->sprite[rc->i].drawend_y = rc->win_y - 1;
	rc->sprite[rc->i].width = abs((int)(rc->win_y /
		(rc->sprite[rc->i].transform_y)));
	rc->sprite[rc->i].drawstart_x = -rc->sprite[rc->i].width /
		2 + rc->sprite[rc->i].screen;
	if (rc->sprite[rc->i].drawstart_x < 0)
		rc->sprite[rc->i].drawstart_x = 0;
	rc->sprite[rc->i].drawend_x = rc->sprite[rc->i].width / 2 +
		rc->sprite[rc->i].screen;
	if (rc->sprite[rc->i].drawend_x >= rc->win_x)
		rc->sprite[rc->i].drawend_x = rc->win_x - 1;
	rc->sprite[rc->i].stripe = rc->sprite[rc->i].drawstart_x;
}

void	order_sprite(t_raycaster *rc)
{
	int			i;
	int			j;
	t_sprites	temp;

	i = 0;
	while (i < rc->numsprites)
	{
		j = 0;
		while (j < rc->numsprites)
		{
			if (rc->sprite[i].distance > rc->sprite[j].distance)
			{
				temp = rc->sprite[i];
				rc->sprite[i] = rc->sprite[j];
				rc->sprite[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void	draw_sprite(t_raycaster *rc)
{
	int	h;
	int	d;
	int	spritetex_y;
	int spritetex_x;

	h = rc->sprite[rc->i].drawstart_y;
	spritetex_x = (int)((256 * (rc->sprite[rc->i].stripe -
		(-rc->sprite[rc->i].width / 2 + rc->sprite[rc->i].screen))
		* 64 / rc->sprite[rc->i].width) / 256);
	while (h < rc->sprite[rc->i].drawend_y)
	{
		d = (h) * 256 - rc->win_y * 128 + rc->sprite[rc->i].height * 128;
		spritetex_y = ((d * 64) / rc->sprite[rc->i].height) / 256;
		h++;
		if (rc->sprite[rc->i].tex.data[4 * (spritetex_x + 64 * spritetex_y)] != (char)0)//
		{
			rc->img_data[4 * (rc->sprite[rc->i].stripe + (h * rc->win_x))] = (char)
				rc->sprite[rc->i].tex.data[4 * (spritetex_x + (64 * spritetex_y))];
			rc->img_data[4 * (rc->sprite[rc->i].stripe + (h * rc->win_x)) + 1] = (char)
				rc->sprite[rc->i].tex.data[4 * (spritetex_x + (64 * spritetex_y)) + 1];
			rc->img_data[4 * (rc->sprite[rc->i].stripe + (h * rc->win_x)) + 2] = (char)
				rc->sprite[rc->i].tex.data[4 * (spritetex_x + (64 * spritetex_y)) + 2];
		}
	}
}