/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/14 14:44:48 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	run_crouch_on(int key, t_raycaster *rc)
{
	if (key == SHIFT_L)
	{
		rc->movespeed = rc->movespeed * 2.5;
		rc->sprint = 1;
	}
	else if (key == C)
	{
		rc->movespeed = rc->movespeed / 2.5;
		rc->crouch = -30;
		rc->win_y = rc->win_y + 30;
		rc->win_x = rc->win_x + 30;
	}
}

void	run_crouch_off(int key, t_raycaster *rc)
{
	if (key == SHIFT_L)
	{
		rc->movespeed = rc->movespeed / 2.5;
		rc->sprint = 0;
	}
	else if (key == C)
	{
		rc->movespeed = rc->movespeed * 2.5;
		rc->crouch = 0;
		rc->win_y = rc->win_y - 30;
		rc->win_x = rc->win_x - 30;
	}
}

int		key_press(int key, t_raycaster *rc)
{
	reset_raycasting_params(rc);
	if (key == UP || key == W)
		rc->up = 1;
	else if (key == DOWN || key == S)
		rc->down = 1;
	else if (key == RIGHT)
		rc->rot_right = 1;
	else if (key == D)
		rc->right = 1;
	else if (key == LEFT)
		rc->rot_left = 1;
	else if (key == A)
		rc->left = 1;
	else if (key == ESC)
		close_success(rc);
	run_crouch_on(key, rc);
	return (0);
}

int		key_release(int key, t_raycaster *rc)
{
	if (key == UP || key == W)
		rc->up = 0;
	else if (key == DOWN || key == S)
		rc->down = 0;
	else if (key == RIGHT)
		rc->rot_right = 0;
	else if (key == D)
		rc->right = 0;
	else if (key == LEFT)
		rc->rot_left = 0;
	else if (key == A)
		rc->left = 0;
	run_crouch_off(key, rc);
	return (0);
}
