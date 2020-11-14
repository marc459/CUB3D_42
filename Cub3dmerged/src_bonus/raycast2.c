/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/14 14:46:02 by msantos-         ###   ########.fr       */
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
		if (rc->world_map[rc->map_x][rc->map_y] == 1)
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

void	floor_and_sky_draw(t_raycaster *rc, int x)
{
	int y;

	y = rc->draw_end + 1;
	floor_directions(rc);
	while (y < rc->win_y)
	{
		rc->currentdist = rc->win_y / (2.0 * y - rc->win_y);
		rc->weight = rc->currentdist / rc->perp_wall_dist;
		rc->currentfloorx = rc->weight * rc->floorxwall +
							(1.0 - rc->weight) * rc->player_pos_x;
		rc->currentfloory = rc->weight * rc->floorywall +
							(1.0 - rc->weight) * rc->player_pos_y;
		rc->floortexx = (int)(rc->currentfloorx
						* rc->tex_width) % rc->tex_width;
		rc->floortexy = (int)(rc->currentfloory
						* rc->tex_height) % rc->tex_height;
		ft_memcpy(rc->img_data + 4 * rc->win_x * y + x * 4,
				&rc->tex[4].data[4 * rc->floortexx * rc->tex_width +
				4 * rc->floortexy], sizeof(int));
		ft_memcpy(rc->img_data + 4 * rc->win_x * (rc->win_y - y) + x * 4,
				&rc->tex[7].data[4 * rc->floortexx * rc->tex_width +
				4 * rc->floortexy],
				sizeof(int));
		y++;
	}
}

void	draw_wall(t_raycaster *rc, int x)
{
	if (rc->draw_end < 0)
		rc->draw_end = rc->win_y;
	if (rc->world_map[rc->map_x][rc->map_y] == 2)
		rc->tex_id = 6;
	else
		rc->tex_id = rc->tex_id + rc->side;
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
	rc->tex_id = rc->world_map[rc->map_x][rc->map_y];
	if (rc->side == 0)
		rc->wallx = rc->player_pos_y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		rc->wallx = rc->player_pos_x + rc->perp_wall_dist * rc->ray_dir_x;
	rc->wallx -= floor(rc->wallx);
	rc->tex_x = abs((int)(rc->wallx * (double)(64)));
}
