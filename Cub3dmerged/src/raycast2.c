/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/10/05 12:38:21 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int init_raycast_params(t_raycaster *rc, archparams_t *arch, validmap_t *map)
{
	rc->mlx_ptr = NULL;
	rc->win_ptr = NULL;
	rc->win_x = arch->win_x;
	rc->win_y = arch->win_y;
	rc->worldMap = arch->worldMap;
	rc->player_pos_x = map->init_p_pos_y;
	rc->player_pos_y = map->init_p_pos_x;
	rc->mapWidth = map->mapWidth;
	rc->mapHeight = map->m_line;
	rc->tex_height = 64;
	rc->tex_width = 64;
	rc->tex_side = 1;
	rc->movespeed = 0.400;
	rc->wallx = 0;

	if (map->player_dir == 'N')
	{
		rc->dirx = -1;
		rc->diry = 0;
		rc->player_plane_x = 0;
		rc->player_plane_y = 0.66;
	}
	else if (map->player_dir == 'S')
	{
		rc->player_plane_x = 0;
		rc->player_plane_y = -0.66;
		rc->dirx = 1;
		rc->diry = 0;
	}
	else if (map->player_dir == 'E')
	{
		rc->player_plane_x = 0.66;
		rc->player_plane_y = 0;
		rc->dirx = 0;
		rc->diry = 1;
	}
	else if (map->player_dir == 'W')
	{
		rc->player_plane_x = -0.66;
		rc->player_plane_y = 0;
		rc->dirx = 0;
		rc->diry = -1;
	}

	if (!(rc->mlx_ptr = mlx_init()))
		return (ft_puterror("Inicio de Minilibx fallida\n"));
	if (!(rc->win_ptr = mlx_new_window(rc->mlx_ptr, rc->win_x, rc->win_y, "mx 42")))
		return (ft_puterror("Proceso de creacion de Ventana fallida\n"));
	return (1);
}

void drawMap(t_raycaster *rc)
{
	int y;
	int x;
	int printplayer_X;
	int printplayer_Y;

	int x_wall;
	int y_wall;
	char *str;

	x = 0;
	y = 0;

	x_wall = 10;
	y_wall = 10;

	printplayer_X = rc->player_pos_y * 10;
	printplayer_Y = rc->player_pos_x * 10;

	mlx_string_put(rc->mlx_ptr, rc->win_ptr, rc->win_x / 2 - 20, 10, 0x33FF3C, "CUB3D");
	int tmpx = printplayer_X;
	int tmpy = printplayer_Y;
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx + 1, tmpy + 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx, tmpy, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx - 1, tmpy - 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx - 1, tmpy + 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx + 1, tmpy - 1, 0x33FF3C);

	while (x < rc->mapHeight)
	{
		while (y < rc->mapWidth)
		{
			if (rc->worldMap[x][y] == 1 || rc->worldMap[x][y] == 2 || rc->worldMap[x][y] == 3)
			{
				mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, x_wall, y_wall, 0xFA2C00);
				mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, x_wall + 1, y_wall + 1, 0xFA2C00);
				mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, x_wall - 1, y_wall - 1, 0xFA2C00);
				mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, x_wall - 1, y_wall + 1, 0xFA2C00);
				mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, x_wall + 1, y_wall - 1, 0xFA2C00);
			}
			y++;
			x_wall = x_wall + 10;
		}
		y = 0;
		x++;
		x_wall = 10;
		y_wall = y_wall + 10;
	}
}

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

void floor_and_sky_draw(t_raycaster *rc, int x)
{
	int y;
	double currentdist;
	double currentfloorx;
	double currentfloory;
	double weight;
	int floortexx;
	int floortexy;
	double floorxwall;
	double floorywall;
	floorxwall = rc->map_x;
	floorywall = rc->map_y + rc->wallx;

	y = rc->draw_end + 1;
	if (rc->draw_end < 0)
		rc->draw_end = rc->win_y;
	while (y < rc->win_y)
	{
		currentdist = rc->win_y / (2.0 * y - rc->win_y);
		weight = currentdist / rc->perp_wall_dist;
		currentfloorx = weight * floorxwall +
						   (1.0 - weight) * rc->player_pos_x;
		currentfloory = weight * floorywall +
						   (1.0 - weight) * rc->player_pos_y;
		floortexx = (int)(currentfloorx * rc->tex_width) % rc->tex_width;
		floortexy = (int)(currentfloory * rc->tex_height) % rc->tex_height;
		ft_memcpy(rc->img_data + 4 * rc->win_x * y + x * 4,
				  &rc->tex[4].data[4 * floortexx * rc->tex_width +
								  4 * floortexy],
				  sizeof(int));
		ft_memcpy(rc->img_data + 4 * rc->win_x * (rc->win_y - y) + x * 4,
				  &rc->tex[7].data[4 * floortexx * rc->tex_width +
								  4 * floortexy],
				  sizeof(int));
		y++;
	}
}

void draw_vert_line(t_raycaster *rc, int x)
{
	int color;
	int y;
	int tmp;

	color = BLUE;
	if (rc->worldMap[rc->map_x][rc->map_y] == 1)
		color = WHITE;
	if (rc->worldMap[rc->map_x][rc->map_y] == 2)
		color = GREEN;

	if (rc->side == 1)
		color = color + 3000;

	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		tmp = y * rc->win_x + x * 4;
		rc->img_data[tmp] = color;
		//mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, x, y, color);
		y++;
	}
}
void draw_wall(t_raycaster *rc, int x)
{
	if (rc->worldMap[rc->map_x][rc->map_y] == 1)
		rc->tex_side = 1;
	/*if (rc->worldMap[rc->map_x][rc->map_y] == 2)
		rc->tex_side = 2;
	if (rc->worldMap[rc->map_x][rc->map_y] == 3)
		rc->tex_side = 3;*/
	if (rc->side == 1)
		rc->tex_side = 3;
	while (rc->draw_start <= rc->draw_end)
	{
		rc->tex_y = abs((((rc->draw_start * 256 - rc->win_y * 128 +
						   rc->line_height * 128) *
						  64) /
						 rc->line_height) /
						256);
		ft_memcpy(rc->img_data + 4 * rc->win_x * rc->draw_start + x * 4,
				  &rc->tex[rc->tex_side].data[rc->tex_y % rc->tex_height *
												  rc->tex[rc->tex_side].size_l +
											  rc->tex_x % rc->tex_width *
												  rc->tex[rc->tex_side].bpp / 8],
				  sizeof(int));
		rc->draw_start++;
	}
}

void calcule_wall(t_raycaster *rc)
{
	rc->tex_id = rc->worldMap[rc->map_x][rc->map_y] + rc->tex_side;
	if (rc->side == 0)
		rc->wallx = rc->player_pos_y + rc->perp_wall_dist * rc->ray_dir_y;
	else
		rc->wallx = rc->player_pos_x + rc->perp_wall_dist * rc->ray_dir_x;
	rc->wallx -= floor(rc->wallx);
	rc->tex_x = abs((int)(rc->wallx * (double)(64)));
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

int handle_events(int key, t_raycaster *rc)
{
	double oldDirX;
	double oldPlaneX;
	printf("%d\n",key);
	if (key == ESC)
	{
		exit(-1);
		return (-1);
	}
	if (key == DOWN || key == UP || key == RIGHT || key == LEFT)
	{
		if (key == UP)
		{
			if (rc->worldMap[(int)(rc->player_pos_x + rc->dirx * MV_SPEED)][(int)(rc->player_pos_y)] == 0)
				rc->player_pos_x += rc->dirx * MV_SPEED;
			if (rc->worldMap[(int)(rc->player_pos_x)][(int)(rc->player_pos_y + rc->diry * MV_SPEED)] == 0)
				rc->player_pos_y += rc->diry * MV_SPEED;
		}
		if (key == DOWN)
		{
			if (rc->worldMap[(int)(rc->player_pos_x - rc->dirx * MV_SPEED)][(int)(rc->player_pos_y)] == 0)
				rc->player_pos_x -= rc->dirx * MV_SPEED;
			if (rc->worldMap[(int)(rc->player_pos_x)][(int)(rc->player_pos_y - rc->diry * MV_SPEED)] == 0)
				rc->player_pos_y -= rc->diry * MV_SPEED;
		}
		if (key == RIGHT)
		{
			oldDirX = rc->dirx;
			rc->dirx = rc->dirx * cos(-ROT_SPEED) - rc->diry * sin(-ROT_SPEED);
			rc->diry = oldDirX * sin(-ROT_SPEED) + rc->diry * cos(-ROT_SPEED);
			oldPlaneX = rc->player_plane_x;
			rc->player_plane_x = rc->player_plane_x * cos(-ROT_SPEED) - rc->player_plane_y * sin(-ROT_SPEED);
			rc->player_plane_y = oldPlaneX * sin(-ROT_SPEED) + rc->player_plane_y * cos(-ROT_SPEED);
		}
		if (key == LEFT)
		{
			oldDirX = rc->dirx;
			rc->dirx = rc->dirx * cos(ROT_SPEED) - rc->diry * sin(ROT_SPEED);
			rc->diry = oldDirX * sin(ROT_SPEED) + rc->diry * cos(ROT_SPEED);
			oldPlaneX = rc->player_plane_x;
			rc->player_plane_x = rc->player_plane_x * cos(ROT_SPEED) - rc->player_plane_y * sin(ROT_SPEED);
			rc->player_plane_y = oldPlaneX * sin(ROT_SPEED) + rc->player_plane_y * cos(ROT_SPEED);
		}
	}
	return (0);
}

int raycasting(int key, t_raycaster *rc)
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
		//floor_and_sky_draw(rc, x);
		//draw_wall(rc, x);
		draw_vert_line(rc, x);
		x++;
	}
	mlx_put_image_to_window(rc->mlx_ptr, rc->win_ptr, rc->img_ptr, 0, 0);
	drawMap(rc);
	return (0);
}
