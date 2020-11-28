/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/28 13:04:38 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	motionless_4(t_raycaster *rc)
{
	if (rc->side == 0)
		rc->perp_wall_dist = (rc->map_x - rc->player_pos_x
							+ (1 - rc->stepx) / 2) / rc->ray_dir_x;
	else
		rc->perp_wall_dist = (rc->map_y - rc->player_pos_y
							+ (1 - rc->stepy) / 2) / rc->ray_dir_y;
	rc->line_height = (int)(rc->win_y / rc->perp_wall_dist);
	rc->draw_start = -rc->line_height / 2 + rc->win_y / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + rc->win_y / 2;
	if (rc->draw_end >= rc->win_y)
		rc->draw_end = rc->win_y - 1;
}

void	motionless_3(t_raycaster *rc)
{
	if (rc->ray_dir_x < 0)
	{
		rc->stepx = -1;
		rc->side_dist_x = (rc->player_pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->stepx = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - rc->player_pos_x)
						* rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->stepy = -1;
		rc->side_dist_y = (rc->player_pos_y - rc->map_y)
						* rc->delta_dist_y;
	}
	else
	{
		rc->stepy = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - rc->player_pos_y)
						* rc->delta_dist_y;
	}
}

void	motionless_2(t_raycaster *rc, int x)
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

int		raycasting(t_raycaster *rc)
{
	int x;

	x = 0;
	handle_events(rc);
	rc->img_ptr = mlx_new_image(rc->mlx_ptr, rc->win_x, rc->win_y);
	rc->img_data = mlx_get_data_addr(rc->img_ptr,
					&rc->bpp, &rc->size_line, &rc->endian);
	while (x < rc->win_x)
	{
		motionless_2(rc, x);
		motionless_3(rc);
		dda(rc);
		motionless_4(rc);
		calcule_wall(rc);
		floor_and_sky_draw(rc, x);
		draw_wall(rc, x);
		rc->spr_buffer[x] = rc->perp_wall_dist;
		x++;
	}
	sprite_casting(rc);
	draw_map(rc);
	mlx_put_image_to_window(rc->mlx_ptr, rc->win_ptr,
				rc->img_ptr, rc->crouch, rc->crouch);
	return (0);
}
