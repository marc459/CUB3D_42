/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvega-tr <fvega-tr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 05:48:17 by fvega-tr          #+#    #+#             */
/*   Updated: 2020/01/13 19:36:39 by fvega-tr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	movement_sprint(t_struct *t)
{
	if (t->sprint)
	{
		t->movespeed = 0.08 * pow(1.0009, t->win_width);
		t->rotspeed = 0.08 * pow(1.0009, t->win_width);
	}
	else
	{
		t->movespeed = 0.04 * pow(1.0009, t->win_width);
		t->rotspeed = 0.04 * pow(1.0009, t->win_width);
	}
}

/*
** rotate to the right
** both camera direction and camera plane must be rotated
** rotate to the left
** both camera direction and camera plane must be rotated
*/

static void	movement_right_left(t_struct *t)
{
	if (t->right)
	{
		t->olddirx = t->dirx;
		t->dirx = t->dirx * cos(-t->rotspeed) - t->diry * sin(-t->rotspeed);
		t->diry = t->olddirx * sin(-t->rotspeed) + t->diry * cos(-t->rotspeed);
		t->oldplanex = t->planex;
		t->planex = t->planex * cos(-t->rotspeed) - t->planey *
		sin(-t->rotspeed);
		t->planey = t->oldplanex * sin(-t->rotspeed) + t->planey *
		cos(-t->rotspeed);
	}
	if (t->left)
	{
		t->olddirx = t->dirx;
		t->dirx = t->dirx * cos(t->rotspeed) - t->diry * sin(t->rotspeed);
		t->diry = t->olddirx * sin(t->rotspeed) + t->diry * cos(t->rotspeed);
		t->oldplanex = t->planex;
		t->planex = t->planex * cos(t->rotspeed) - t->planey * sin(t->rotspeed);
		t->planey = t->oldplanex * sin(t->rotspeed) + t->planey *
		cos(t->rotspeed);
	}
}

/*
** move forward if no wall in front of you
** move backwards if no wall behind you
*/

static void	movement_up_down(t_struct *t)
{
	if (t->up)
	{
		if (t->map[(int)(t->posx + t->dirx *
		t->movespeed)][(int)(t->posy)] == 0)
			t->posx += t->dirx * t->movespeed;
		if (t->map[(int)(t->posx)][(int)(t->posy + t->diry *
		t->movespeed)] == 0)
			t->posy += t->diry * t->movespeed;
	}
	if (t->down)
	{
		if (t->map[(int)(t->posx - t->dirx *
		t->movespeed)][(int)(t->posy)] == 0)
			t->posx -= t->dirx * t->movespeed;
		if (t->map[(int)(t->posx)][(int)(t->posy - t->diry *
		t->movespeed)] == 0)
			t->posy -= t->diry * t->movespeed;
	}
}

void		movement(t_struct *t)
{
	movement_up_down(t);
	movement_right_left(t);
	movement_sprint(t);
}
