/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   motionless.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvega-tr <fvega-tr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:02:32 by fvega-tr          #+#    #+#             */
/*   Updated: 2020/11/17 12:16:17 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
**	Calculate distance projected on camera direction
**	(Euclidean distance will give fisheye effect!).
**	Calculate height of line to draw on screen.
**	Calculate lowest and highest pixel to fill in current stripe.
**	1 subtracted from texture number so that texture 0 can be used.
*/

static void	motionless_4(t_struct *t)
{
	if (t->side == 0)
		t->perpwalldist = (t->mapx - t->posx + (1 - t->stepx) / 2) / t->raydirx;
	else
		t->perpwalldist = (t->mapy - t->posy + (1 - t->stepy) / 2) / t->raydiry;
	t->lineheight = (int)(t->win_height / t->perpwalldist);
	t->drawstart = -t->lineheight / 2 + t->win_height / 2;
	if (t->drawstart < 0)
		t->drawstart = 0;
	t->drawend = t->lineheight / 2 + t->win_height / 2;
	if (t->drawend >= t->win_height)
		t->drawend = t->win_height - 1;
	t->textnum = t->map[t->mapx][t->mapy] - 1;
}

/*
**	perform DDA.
**	Jump to next map square, OR in x-direction, OR in y-direction.
**	Check if ray has hit a wall.
*/

static void	dda(t_struct *t)
{
	while (t->hit == 0)
	{
		if (t->sidedistx < t->sidedisty)
		{
			t->sidedistx += t->deltadistx;
			t->mapx += t->stepx;
			t->side = 0;
		}
		else
		{
			t->sidedisty += t->deltadisty;
			t->mapy += t->stepy;
			t->side = 1;
		}
		if (t->map[t->mapx][t->mapy] > 0)
			t->hit = 1;
	}
}

/*
** 	calculate step and initial sideDist
*/

static void	motionless_3(t_struct *t)
{
	if (t->raydirx < 0)
	{
		t->stepx = -1;
		t->sidedistx = (t->posx - t->mapx) * t->deltadistx;
	}
	else
	{
		t->stepx = 1;
		t->sidedistx = (t->mapx + 1.0 - t->posx) * t->deltadistx;
	}
	if (t->raydiry < 0)
	{
		t->stepy = -1;
		t->sidedisty = (t->posy - t->mapy) * t->deltadisty;
	}
	else
	{
		t->stepy = 1;
		t->sidedisty = (t->mapy + 1.0 - t->posy) * t->deltadisty;
	}
}

/*
**	calculate ray position and direction, which box of the map we're in,
**	length of ray from one x or y-side to next x or y-side,
**	what direction to step in x or y-direction (either +1 or -1),
**	was there a wall hit?
*/

static void	motionless_2(t_struct *t, int x)
{
	t->camerax = 2 * x / (double)t->win_width - 1;
	t->raydirx = t->dirx + t->planex * t->camerax;
	t->raydiry = t->diry + t->planey * t->camerax;
	t->mapx = (int)t->posx;
	t->mapy = (int)t->posy;
	t->deltadistx = fabs((1 / t->raydirx));
	t->deltadisty = fabs((1 / t->raydiry));
	t->hit = 0;
}

int			motionless(t_struct *t)
{
	printf("%f\n",t->posx);
	printf("%f\n", t->posy);
	int x;

	x = 0;
	movement(t);
	t->img_ptr = mlx_new_image(t->mlx_ptr, t->win_width, t->win_height);
	t->img_data = mlx_get_data_addr(t->img_ptr, &t->bpp, &t->size_line,
		&t->endian);
	while (x < t->win_width)
	{
		motionless_2(t, x);
		motionless_3(t);
		dda(t);
		motionless_4(t);
		calcule_wall(t, x);
		floor_and_sky_draw(t, x);
		draw_wall(t, x);
		t->spr_buffer[x] = t->perpwalldist;
		x++;
	}
	sprite_casting(t);
	//sound_damage(t);
	game_over(t);
	mlx_put_image_to_window(t->mlx_ptr, t->win_ptr, t->img_ptr, 0, 0);
	life_bar(t);
	return (0);
}
