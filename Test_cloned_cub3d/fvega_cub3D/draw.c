/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:27:04 by fvega-tr          #+#    #+#             */
/*   Updated: 2020/09/09 13:39:01 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	floor_directions(t_struct *t)
{
	if (t->side == 0 && t->raydirx > 0)
	{
		t->tex_side = 1;
		t->floorxwall = t->mapx;
		t->floorywall = t->mapy + t->wallx;
	}
	else if (t->side == 0 && t->raydirx < 0)
	{
		t->tex_side = 0;
		t->floorxwall = t->mapx + 1.0;
		t->floorywall = t->mapy + t->wallx;
	}
	else if (t->side == 1 && t->raydiry > 0)
	{
		t->tex_side = 2;
		t->floorxwall = t->mapx + t->wallx;
		t->floorywall = t->mapy;
	}
	else
	{
		t->tex_side = 3;
		t->floorxwall = t->mapx + t->wallx;
		t->floorywall = t->mapy + 1.0;
	}
}

void		floor_and_sky_draw(t_struct *t, int x)
{
	int y;

	y = t->drawend + 1;
	floor_directions(t);
	if (t->drawend < 0)
		t->drawend = t->win_height;
	while (y < t->win_height)
	{
		t->currentdist = t->win_height / (2.0 * y - t->win_height);
		t->weight = t->currentdist / t->perpwalldist;
		t->currentfloorx = t->weight * t->floorxwall +
			(1.0 - t->weight) * t->posx;
		t->currentfloory = t->weight * t->floorywall +
			(1.0 - t->weight) * t->posy;
		t->floortexx = (int)(t->currentfloorx * t->tex_width) % t->tex_width;
		t->floortexy = (int)(t->currentfloory * t->tex_height) % t->tex_height;
		ft_memcpy(t->img_data + 4 * t->win_width * y + x * 4,
			&t->tex[4].data[4 * t->floortexx * t->tex_width +
			4 * t->floortexy], sizeof(int));
		ft_memcpy(t->img_data + 4 * t->win_width * (t->win_height - y) + x * 4,
			&t->tex[7].data[4 * t->floortexx * t->tex_width +
			4 * t->floortexy], sizeof(int));
		y++;
	}
}

void		draw_wall(t_struct *t, int x)
{
	printf("%d,%d,%d,%d,%d,%d\n", t->drawstart, t->drawend, t->lineheight, t->win_width, t->tex_id,x);
	while (t->drawstart <= t->drawend)
	{
		t->tex_y = abs((((t->drawstart * 256 - t->win_height * 128 +
					t->lineheight * 128) * 64) / t->lineheight) / 256);
		ft_memcpy(t->img_data + 4 * t->win_width * t->drawstart + x * 4,
				&t->tex[t->tex_id].data[t->tex_y % t->tex_height *
				t->tex[t->tex_id].sizeline + t->tex_x % t->tex_width *
				t->tex[t->tex_id].bpp / 8], sizeof(int));
		t->drawstart++;
	}
}

/*
**	calculate value of wallx
**	where exactly the wall was hit
*/

void		calcule_wall(t_struct *t, int x)
{
	t->tex_id = t->map[t->mapx][t->mapy] + t->tex_side;
	if (t->side == 0)
		t->wallx = t->posy + t->perpwalldist * t->raydiry;
	else
		t->wallx = t->posx + t->perpwalldist * t->raydirx;
	t->wallx -= floor(t->wallx);
	t->tex_x = abs((int)(t->wallx * (double)(64)));
}
