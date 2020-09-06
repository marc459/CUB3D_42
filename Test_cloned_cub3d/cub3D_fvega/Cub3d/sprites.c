/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvega-tr <fvega-tr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 23:02:53 by fvega-tr          #+#    #+#             */
/*   Updated: 2020/01/13 21:11:13 by fvega-tr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	sprite_drawing(t_struct *t, int i)
{
	int y;

	t->stripe = t->drawstartx;
	while (t->stripe < t->drawendx)
	{
		t->sprtexx = (int)(256 * (t->stripe - (-t->spritewidth /
		2 + t->spritescreenx)) * t->tex_width / t->spritewidth) / 256;
		y = t->drawstarty;
		if (t->transformy > 0 && t->stripe > 0 && t->stripe < t->win_width &&
		t->transformy < t->spr_buffer[t->stripe])
			while (y < t->drawendy)
			{
				t->d = (y) * 256 - t->win_height * 128 + t->spriteheight * 128;
				t->sprtexy = ((t->d * t->tex_height) / t->spriteheight) / 256;
				if (++y < t->win_height && t->sprite[i].tex.data[t->sprtexy %
				t->tex_height * t->sprite[i].tex.sizeline + t->sprtexx %
				t->tex_width * t->sprite[i].tex.bpp / 8])
					ft_memcpy(t->img_data + 4 * t->win_width * y + t->stripe *
					4, &t->sprite[i].tex.data[t->sprtexy % t->tex_height *
					t->sprite[i].tex.sizeline + t->sprtexx % t->tex_width *
					t->sprite[i].tex.bpp / 8], sizeof(int));
				y++;
			}
		t->stripe++;
	}
}

static void	enemy_movement_x(t_struct *t, double x, double y)
{
	t->enem_stepx = (t->posx - x) / 700;
	t->enem_stepy = (t->posy - y) / 700;
	t->sprite[1].x = t->sprite[1].x + t->enem_stepx;
	t->sprite[1].y = t->sprite[1].y + t->enem_stepy;
	if ((t->posx - x) < 0.8 && (t->posy - y) < 0.8)
	{
		t->life_bar -= 1;
		t->sprite[1].tex = t->tex[9];
	}
	else
		t->sprite[1].tex = t->tex[8];
}

static void	sprite_casting2(t_struct *t)
{
	t->invdet = 1.0 / (t->planex * t->diry - t->dirx * t->planey);
	t->transformx = t->invdet * (t->diry * t->spritex - t->dirx *
		t->spritey);
	t->transformy = t->invdet * (-t->planey * t->spritex + t->planex
		* t->spritey);
	t->spritescreenx = (int)((t->win_width / 2) * (1 + t->transformx /
		t->transformy));
	t->spriteheight = abs((int)(t->win_height / (t->transformy)));
	t->drawstarty = -t->spriteheight / 2 + t->win_height / 2;
	if (t->drawstarty < 0)
		t->drawstarty = 0;
	t->drawendy = t->spriteheight / 2 + t->win_height / 2;
	if (t->drawendy >= t->win_height)
		t->drawendy = t->win_height - 1;
	t->spritewidth = abs((int)(t->win_height / (t->transformy)));
	t->drawstartx = -t->spritewidth / 2 + t->spritescreenx;
	if (t->drawstartx < 0)
		t->drawstartx = 0;
	t->drawendx = t->spritewidth / 2 + t->spritescreenx;
	if (t->drawendx >= t->win_width)
		t->drawendx = t->win_width - 1;
}

void		sprite_casting(t_struct *t)
{
	int i;

	i = 0;
	while (i < NUMSPRITES)
	{
		t->spritex = t->sprite[i].x - t->posx;
		t->spritey = t->sprite[i].y - t->posy;
		sprite_casting2(t);
		enemy_movement_x(t, t->sprite[1].x, t->sprite[1].y);
		sprite_drawing(t, i);
		i++;
	}
}
