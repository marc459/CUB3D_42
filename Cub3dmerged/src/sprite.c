/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/10 09:40:15 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/10 14:36:19 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	sprite_drawing(t_raycaster *rc, int i, int y)
{
	rc->stripe = rc->drawstartx;
	while (rc->stripe < rc->drawendx)
	{
		rc->sprtexx = (int)(256 * (rc->stripe - (-rc->spritewidth / 2
			+ rc->spritescreenx)) * rc->tex_width / rc->spritewidth) / 256;
		y = rc->drawstarty;
		if (rc->transformy > 0 && rc->stripe > 0 && rc->stripe < rc->win_x &&
			rc->transformy < rc->spr_buffer[rc->stripe])
			while (y < rc->drawendy)
			{
				rc->d = (y) * 256 - rc->win_y * 128 + rc->spriteheight * 128;
				rc->sprtexy = ((rc->d *
				rc->tex_height) / rc->spriteheight) / 256;
				if (++y < rc->win_y && rc->sprite[i].tex.data[rc->sprtexy %
				rc->tex_height * rc->sprite[i].tex.size_l +
				rc->sprtexx % rc->tex_width * rc->sprite[i].tex.bpp / 8])
					ft_memcpy(rc->img_data + 4 * rc->win_x * y + rc->stripe * 4,
						&rc->sprite[i].tex.data[rc->sprtexy % rc->tex_height *
						rc->sprite[i].tex.size_l + rc->sprtexx % rc->tex_width
						* rc->sprite[i].tex.bpp / 8], sizeof(int));
				y++;
			}
		rc->stripe++;
	}
}

void	sprite_casting2(t_raycaster *rc)
{
	rc->invdet = 1.0 / (rc->player_plane_x *
				rc->diry - rc->dirx * rc->player_plane_y);
	rc->transformx = rc->invdet * (rc->diry * rc->spritex - rc->dirx *
																rc->spritey);
	rc->transformy = rc->invdet * (-rc->player_plane_y * rc->spritex +
					rc->player_plane_x * rc->spritey);
	rc->spritescreenx = (int)((rc->win_x / 2) * (1 + rc->transformx /
						rc->transformy));
	rc->spriteheight = abs((int)(rc->win_y / (rc->transformy)));
	rc->drawstarty = -rc->spriteheight / 2 + rc->win_y / 2;
	if (rc->drawstarty < 0)
		rc->drawstarty = 0;
	rc->drawendy = rc->spriteheight / 2 + rc->win_y / 2;
	if (rc->drawendy >= rc->win_y)
		rc->drawendy = rc->win_y - 1;
	rc->spritewidth = abs((int)(rc->win_y / (rc->transformy)));
	rc->drawstartx = -rc->spritewidth / 2 + rc->spritescreenx;
	if (rc->drawstartx < 0)
		rc->drawstartx = 0;
	rc->drawendx = rc->spritewidth / 2 + rc->spritescreenx;
	if (rc->drawendx >= rc->win_x)
		rc->drawendx = rc->win_x - 1;
}

void	sprite_casting(t_raycaster *rc)
{
	int i;
	int y;

	i = 0;
	y = 0;
	while (i < rc->numsprites)
	{
		rc->sprite[i].tex = rc->tex[6];
		rc->spritex = rc->sprite[i].x - rc->player_pos_x;
		rc->spritey = rc->sprite[i].y - rc->player_pos_y;
		sprite_casting2(rc);
		sprite_drawing(rc, i, y);
		i++;
	}
}
