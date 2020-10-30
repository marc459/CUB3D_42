/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/10/26 12:26:43 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	dda(t_raycaster *rc)
{
	while (rc->hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->stepx;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->stepy;
			rc->side = 1;
		}
		if (rc->worldMap[rc->map_x][rc->map_y] > 0)
			rc->hit = 1;
	}
}

void	floor_directions(t_raycaster *rc)
{
	if (rc->side == 0 && rc->ray_dir_x > 0)
	{
		rc->tex_side = 1;
		rc->floorxwall = rc->map_x;
		rc->floorywall = rc->map_y + rc->wallx;
	}
	else if (rc->side == 0 && rc->ray_dir_x < 0)
	{
		rc->tex_side = 0;
		rc->floorxwall = rc->map_x + 1.0;
		rc->floorywall = rc->map_y + rc->wallx;
	}
	else if (rc->side == 1 && rc->ray_dir_y > 0)
	{
		rc->tex_side = 2;
		rc->floorxwall = rc->map_x + rc->wallx;
		rc->floorywall = rc->map_y;
	}
	else
	{
		rc->tex_side = 3;
		rc->floorxwall = rc->map_x + rc->wallx;
		rc->floorywall = rc->map_y + 1.0;
	}
}

void	draw_wall(t_raycaster *rc, int x)
{
	if (rc->draw_end < 0)
		rc->draw_end = rc->win_y;
	if (rc->side == 1)
		rc->tex_id = 2;
	else
		rc->tex_id = 1;
	while (rc->draw_start <= rc->draw_end)
	{
		rc->tex_y = abs((((rc->draw_start * 256 - rc->win_y * 128 +
						rc->line_height * 128) *
						64) /
						rc->line_height) /
						256);
		ft_memcpy(rc->img_data + 4 * rc->win_x * rc->draw_start + x * 4,
					&rc->tex[rc->tex_id].data[rc->tex_y % rc->tex_height *
					rc->tex[rc->tex_id].size_l + rc->tex_x % rc->tex_width *
					rc->tex[rc->tex_id].bpp / 8], sizeof(int));
		rc->draw_start++;
	}
}

void	calcule_wall(t_raycaster *rc)
{
	rc->tex_id = rc->worldMap[rc->map_x][rc->map_y] + rc->tex_side;
	if (rc->side == 0)
		rc->wallx = rc->player_pos_y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		rc->wallx = rc->player_pos_x + rc->perp_wall_dist * rc->ray_dir_x;
	rc->wallx -= floor(rc->wallx);
	rc->tex_x = abs((int)(rc->wallx * (double)(64)));
}
