/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/10/26 12:26:43 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int		handle_events2(t_raycaster *rc)
{
	double olddirx;
	double oldplanex;

	if (rc->right)
	{
		olddirx = rc->dirx;
		rc->dirx = rc->dirx * cos(-ROT_SPEED) - rc->diry * sin(-ROT_SPEED);
		rc->diry = olddirx * sin(-ROT_SPEED) + rc->diry * cos(-ROT_SPEED);
		oldplanex = rc->player_plane_x;
		rc->player_plane_x = rc->player_plane_x * cos(-ROT_SPEED)
							- rc->player_plane_y * sin(-ROT_SPEED);
		rc->player_plane_y = oldplanex * sin(-ROT_SPEED)
							+ rc->player_plane_y * cos(-ROT_SPEED);
	}
	if (rc->left)
	{
		olddirx = rc->dirx;
		rc->dirx = rc->dirx * cos(ROT_SPEED) - rc->diry * sin(ROT_SPEED);
		rc->diry = olddirx * sin(ROT_SPEED) + rc->diry * cos(ROT_SPEED);
		oldplanex = rc->player_plane_x;
		rc->player_plane_x = rc->player_plane_x * cos(ROT_SPEED)
							- rc->player_plane_y * sin(ROT_SPEED);
		rc->player_plane_y = oldplanex * sin(ROT_SPEED)
							+ rc->player_plane_y * cos(ROT_SPEED);
	}
}

int		handle_events(t_raycaster *rc)
{
	if (rc->up == 1)
	{
		if (rc->worldMap[(int)(rc->player_pos_x + rc->dirx
			* rc->movespeed)][(int)(rc->player_pos_y)] == 0)
			rc->player_pos_x += rc->dirx * rc->movespeed;
		if (rc->worldMap[(int)(rc->player_pos_x)]
			[(int)(rc->player_pos_y + rc->diry * rc->movespeed)] == 0)
			rc->player_pos_y += rc->diry * rc->movespeed;
	}
	if (rc->down)
	{
		if (rc->worldMap[(int)(rc->player_pos_x - rc->dirx
			* rc->movespeed)][(int)(rc->player_pos_y)] == 0)
			rc->player_pos_x -= rc->dirx * rc->movespeed;
		if (rc->worldMap[(int)(rc->player_pos_x)]
			[(int)(rc->player_pos_y - rc->diry * rc->movespeed)] == 0)
			rc->player_pos_y -= rc->diry * rc->movespeed;
	}
	handle_events2(rc);
	return (0);
}
