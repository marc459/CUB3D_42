/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/10/19 14:28:40 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static void motionless_4(t_raycaster *rc)
{
	if (rc->side == 0)
		rc->perp_wall_dist = (rc->map_x - rc->player_pos_x + (1 - rc->stepx) / 2) / rc->ray_dir_x;
	else
		rc->perp_wall_dist = (rc->map_y - rc->player_pos_y + (1 - rc->stepy) / 2) / rc->ray_dir_y;
	rc->line_height = (int)(rc->win_y / rc->perp_wall_dist);
	rc->draw_start = -rc->line_height / 2 + rc->win_y / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + rc->win_y / 2;
	if (rc->draw_end >= rc->win_y)
		rc->draw_end = rc->win_y - 1;
}

static void dda(t_raycaster *rc)
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

static void	floor_directions(t_raycaster *rc)
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

static void motionless_3(t_raycaster *rc)
{
	if (rc->ray_dir_x < 0)
	{
		rc->stepx = -1;
		rc->side_dist_x = (rc->player_pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->stepx = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - rc->player_pos_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->stepy = -1;
		rc->side_dist_y = (rc->player_pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->stepy = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - rc->player_pos_y) * rc->delta_dist_y;
	}
}

static void motionless_2(t_raycaster *rc, int x)
{
	rc->camerax = 2 * x / (double)rc->win_x - 1;
	rc->ray_dir_x = rc->dirx + rc->player_plane_x * rc->camerax;
	rc->ray_dir_y = rc->diry + rc->player_plane_y * rc->camerax;
	rc->map_x = (int)rc->player_pos_x;
	rc->map_y = (int)rc->player_pos_y;
	rc->delta_dist_x = fabs((1 / rc->ray_dir_x));
	rc->delta_dist_y = fabs((1 / rc->ray_dir_y));
	rc->hit = 0;
}


int screenshot(int key, t_raycaster *rc)
{
	int x;

	x = 0;
	if (handle_events(key, rc) != 0)
		return (-1);
	rc->img_ptr = mlx_new_image(rc->mlx_ptr, rc->win_x, rc->win_y);
	rc->img_data = mlx_get_data_addr(rc->img_ptr, &rc->bpp, &rc->size_line, &rc->endian);

	while (x < rc->win_x)
	{
		motionless_2(rc, x);
		motionless_3(rc);
		dda(rc);
		motionless_4(rc);
		calcule_wall(rc);
		floor_and_sky_draw(rc, x);
		draw_wall(rc, x);
		x++;
	}
	save_bmp(rc);
	close_success(rc);
	return (0);
}
