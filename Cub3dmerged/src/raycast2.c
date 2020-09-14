/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/09/14 14:11:59 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void init(t_raycaster *rc)
{
	rc->initial_pos = 0;
	rc->map_width = 0;
	rc->map_height = 0;
	rc->tex_width = 64;
	rc->tex_height = 64;
	rc->posx = 22;
	rc->posy = 11.5;
	rc->tex_side = 0;
	rc->sprite[1].x = 1.5;
	rc->sprite[1].y = 1.5;
}

static void floor_directions(t_raycaster *rc)
{
	if (rc->side == 0 && rc->raydirx > 0)
	{
		rc->tex_side = 1;
		rc->floorxwall = rc->map_x;
		rc->floorywall = rc->map_y + rc->wallx;
	}
	else if (rc->side == 0 && rc->raydirx < 0)
	{
		rc->tex_side = 0;
		rc->floorxwall = rc->map_x + 1.0;
		rc->floorywall = rc->map_y + rc->wallx;
	}
	else if (rc->side == 1 && rc->raydiry > 0)
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

void floor_and_sky_draw(t_raycaster *rc, int x)
{
	int y;

	y = rc->draw_end + 1;
	floor_directions(rc);
	if (rc->draw_end < 0)
		rc->draw_end = rc->win_y;
	while (y < rc->win_y)
	{
		rc->currentdist = rc->win_y / (2.0 * y - rc->win_y);
		rc->weight = rc->currentdist / rc->perpwalldist;
		rc->currentfloorx = rc->weight * rc->floorxwall +
						   (1.0 - rc->weight) * rc->posx;
		rc->currentfloory = rc->weight * rc->floorywall +
						   (1.0 - rc->weight) * rc->posy;
		rc->floortexx = (int)(rc->currentfloorx * rc->tex_width) % rc->tex_width;
		rc->floortexy = (int)(rc->currentfloory * rc->tex_height) % rc->tex_height;
		ft_memcpy(rc->img_data + 4 * rc->win_x * y + x * 4,
				  &rc->tex[4].data[4 * rc->floortexx * rc->tex_width +
								  4 * rc->floortexy],
				  sizeof(int));
		ft_memcpy(rc->img_data + 4 * rc->win_x * (rc->win_y - y) + x * 4,
				  &rc->tex[7].data[4 * rc->floortexx * rc->tex_width +
								  4 * rc->floortexy],
				  sizeof(int));
		y++;
	}
}

void draw_wall(t_raycaster *rc, int x)
{
	while (rc->draw_start <= rc->draw_end)
	{
		rc->tex_y = abs((((rc->draw_start * 256 - rc->win_y * 128 +
						  rc->lineheight * 128) *
						 64) /
						rc->lineheight) /
					   256);
		ft_memcpy(rc->img_data + 4 * rc->win_x * rc->draw_start + x * 4,
				  &rc->tex[rc->tex_id].data[rc->tex_y % rc->tex_height *
											  rc->tex[rc->tex_id].sizeline +
										  rc->tex_x % rc->tex_width *
											  rc->tex[rc->tex_id].bpp / 8],
				  sizeof(int));
		rc->draw_start++;
	}
}

void calcule_wall(t_raycaster *rc, int x)
{
	rc->tex_id = rc->worldMap[rc->map_x][rc->map_y] + rc->tex_side;
	if (rc->side == 0)
		rc->wallx = rc->posy + rc->perpwalldist * rc->raydiry;
	else
		rc->wallx = rc->posx + rc->perpwalldist * rc->raydirx;
	rc->wallx -= floor(rc->wallx);
	rc->tex_x = abs((int)(rc->wallx * (double)(64)));
}

static void motionless_4(t_raycaster *rc)
{
	if (rc->side == 0)
		rc->perpwalldist = (rc->map_x - rc->posx + (1 - rc->stepx) / 2) / rc->raydirx;
	else
		rc->perpwalldist = (rc->map_y - rc->posy + (1 - rc->stepy) / 2) / rc->raydiry;
	rc->lineheight = (int)(rc->win_y / rc->perpwalldist);
	rc->draw_start = -rc->lineheight / 2 + rc->win_y / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->lineheight / 2 + rc->win_y / 2;
	if (rc->draw_end >= rc->win_y)
		rc->draw_end = rc->win_y - 1;
	rc->textnum = rc->map[rc->map_x][rc->map_y] - 1;
}

static void dda(t_raycaster *rc)
{
	while (rc->hit == 0)
	{
		if (rc->sidedistx < rc->sidedisty)
		{
			rc->sidedistx += rc->deltadistx;
			rc->map_x += rc->stepx;
			rc->side = 0;
		}
		else
		{
			rc->sidedisty += rc->deltadisty;
			rc->map_y += rc->stepy;
			rc->side = 1;
		}
		if (rc->map[rc->map_x][rc->map_y] > 0)
			rc->hit = 1;
	}
}

static void motionless_3(t_raycaster *rc)
{
	if (rc->raydirx < 0)
	{
		rc->stepx = -1;
		rc->sidedistx = (rc->posx - rc->map_x) * rc->deltadistx;
	}
	else
	{
		rc->stepx = 1;
		rc->sidedistx = (rc->map_x + 1.0 - rc->posx) * rc->deltadistx;
	}
	if (rc->raydiry < 0)
	{
		rc->stepy = -1;
		rc->sidedisty = (rc->posy - rc->map_y) * rc->deltadisty;
	}
	else
	{
		rc->stepy = 1;
		rc->sidedisty = (rc->map_y + 1.0 - rc->posy) * rc->deltadisty;
	}
}


static void motionless_2(t_raycaster *rc, int x)
{
	rc->camerax = 2 * x / (double)rc->win_x - 1;
	rc->raydirx = rc->dirx + rc->planex * rc->camerax;
	rc->raydiry = rc->diry + rc->planey * rc->camerax;
	rc->map_x = (int)rc->posx;
	rc->map_y = (int)rc->posy;
	rc->deltadistx = fabs((1 / rc->raydirx));
	rc->deltadisty = fabs((1 / rc->raydiry));
	rc->hit = 0;
}

int handle_events(int key, t_raycaster *rc)
{
	double oldDirX;
	double oldPlaneX;

	if (key == ESC)
	{
		system("killall a.out && clear");
		return (-1);
	}
	if (key == DOWN || key == UP || key == RIGHT || key == LEFT)
	{
		if (key == UP)
		{
			if (rc->worldMap[(int)(rc->player_pos_x + rc->player_dir_x * MV_SPEED)][(int)(rc->player_pos_y)] == 0)
				rc->player_pos_x += rc->player_dir_x * MV_SPEED;
			if (rc->worldMap[(int)(rc->player_pos_x)][(int)(rc->player_pos_y + rc->player_dir_y * MV_SPEED)] == 0)
				rc->player_pos_y += rc->player_dir_y * MV_SPEED;
		}
		if (key == DOWN)
		{
			if (rc->worldMap[(int)(rc->player_pos_x - rc->player_dir_x * MV_SPEED)][(int)(rc->player_pos_y)] == 0)
				rc->player_pos_x -= rc->player_dir_x * MV_SPEED;
			if (rc->worldMap[(int)(rc->player_pos_x)][(int)(rc->player_pos_y - rc->player_dir_y * MV_SPEED)] == 0)
				rc->player_pos_y -= rc->player_dir_y * MV_SPEED;
		}
		if (key == RIGHT)
		{
			oldDirX = rc->player_dir_x;
			rc->player_dir_x = rc->player_dir_x * cos(-ROT_SPEED) - rc->player_dir_y * sin(-ROT_SPEED);
			rc->player_dir_y = oldDirX * sin(-ROT_SPEED) + rc->player_dir_y * cos(-ROT_SPEED);
			oldPlaneX = rc->player_plane_x;
			rc->player_plane_x = rc->player_plane_x * cos(-ROT_SPEED) - rc->player_plane_y * sin(-ROT_SPEED);
			rc->player_plane_y = oldPlaneX * sin(-ROT_SPEED) + rc->player_plane_y * cos(-ROT_SPEED);
		}
		if (key == LEFT)
		{
			oldDirX = rc->player_dir_x;
			rc->player_dir_x = rc->player_dir_x * cos(ROT_SPEED) - rc->player_dir_y * sin(ROT_SPEED);
			rc->player_dir_y = oldDirX * sin(ROT_SPEED) + rc->player_dir_y * cos(ROT_SPEED);
			oldPlaneX = rc->player_plane_x;
			rc->player_plane_x = rc->player_plane_x * cos(ROT_SPEED) - rc->player_plane_y * sin(ROT_SPEED);
			rc->player_plane_y = oldPlaneX * sin(ROT_SPEED) + rc->player_plane_y * cos(ROT_SPEED);
		}
	}
	return (0);
}

int motionless(t_raycaster *rc)
{
	int x;

	x = 0;
	if (handle_events(key, rc) != 0)
		return (-1);
	rc->img_ptr = mlx_new_image(rc->mlx_ptr, rc->win_x, rc->win_y);
	rc->img_data = mlx_get_data_addr(rc->img_ptr, &rc->bpp, &rc->size_line,
									&rc->endian);
	while (x < rc->win_x)
	{
		motionless_2(rc, x);
		motionless_3(rc);
		dda(rc);
		motionless_4(rc);
		calcule_wall(rc, x);
		floor_and_sky_draw(t, x);
		draw_wall(rc, x);
		rc->spr_buffer[x] = rc->perpwalldist;
		x++;
	}
	mlx_put_image_to_window(rc->mlx_ptr, rc->win_ptr, rc->img_ptr, 0, 0);
	return (0);
}