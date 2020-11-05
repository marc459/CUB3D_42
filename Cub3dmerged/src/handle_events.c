/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/05 11:16:36 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	handle_events2(t_raycaster *rc)
{
	double olddirx;
	double oldplanex;

	if (rc->rot_right)
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
	if (rc->rot_left)
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

void	move_right(t_raycaster *rc)
{
	if (rc->right)
	{
		if (rc->world_map[(int)rc->player_pos_y]
			[(int)(rc->player_pos_x + rc->player_plane_x
			* rc->movespeed)] == 0)
			rc->player_pos_x += rc->player_plane_x
			* rc->movespeed;
		if (rc->world_map[(int)(rc->player_pos_y
			+ rc->player_plane_y * rc->movespeed)]
			[(int)rc->player_pos_x] == 0)
			rc->player_pos_y += rc->player_plane_y
			* rc->movespeed;
	}
}

void	move_left(t_raycaster *rc)
{
	if (rc->left)
	{
		if (rc->world_map[(int)rc->player_pos_y]
			[(int)(rc->player_pos_x + rc->player_plane_x
			* rc->movespeed)] == 0)
			rc->player_pos_x -= rc->player_plane_x
			* rc->movespeed;
		if (rc->world_map[(int)(rc->player_pos_y
			+ rc->player_plane_y * rc->movespeed)]
			[(int)rc->player_pos_x] == 0)
			rc->player_pos_y -= rc->player_plane_y
			* rc->movespeed;
	}
}

int		handle_events(t_raycaster *rc)
{
	if (rc->up == 1)
	{
		if (rc->world_map[(int)(rc->player_pos_x + rc->dirx
			* rc->movespeed)][(int)(rc->player_pos_y)] == 0)
			rc->player_pos_x += rc->dirx * rc->movespeed;
		if (rc->world_map[(int)(rc->player_pos_x)]
			[(int)(rc->player_pos_y + rc->diry * rc->movespeed)] == 0)
			rc->player_pos_y += rc->diry * rc->movespeed;
	}
	if (rc->down)
	{
		if (rc->world_map[(int)(rc->player_pos_x - rc->dirx
			* rc->movespeed)][(int)(rc->player_pos_y)] == 0)
			rc->player_pos_x -= rc->dirx * rc->movespeed;
		if (rc->world_map[(int)(rc->player_pos_x)]
			[(int)(rc->player_pos_y - rc->diry * rc->movespeed)] == 0)
			rc->player_pos_y -= rc->diry * rc->movespeed;
	}
	handle_events2(rc);
	move_right(rc);
	move_left(rc);
	return (0);
}
