/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/10/04 13:28:42 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int init_raycast_params(t_raycaster *rc, archparams_t *arch, validmap_t *map)
{
	/*rc->mlx_ptr = NULL;
	rc->win_ptr = NULL;
	rc->win_x = arch->win_x;
	rc->win_y = arch->win_y;
	rc->worldMap = arch->worldMap;
	rc->player_pos_x = map->init_p_pos_y;
	rc->player_pos_y = map->init_p_pos_x;
	rc->mapWidth = map->mapWidth;
	rc->mapHeight = map->m_line;
	rc->tex_height = 64;
	rc->tex_width = 64;*/

	rc->mlx_ptr = NULL;
	rc->win_ptr = NULL;
	rc->win_x = 1640;
	rc->win_y = 980;
	rc->worldMap = arch->worldMap;
	rc->player_pos_x = 22;
	rc->player_pos_y = 11.5;
	rc->mapWidth = 0;
	rc->mapHeight = 0;
	rc->map_x = 0;
	rc->map_y = 0;
	rc->tex_height = 64;
	rc->tex_width = 64;
	rc->movespeed = 0.400;
	if (map->player_dir == 'N')
	{
		rc->player_dir_x = -1;
		rc->player_dir_y = 0;
		rc->player_plane_x = 0;
		rc->player_plane_y = 0.66;
	}
	else if (map->player_dir == 'S')
	{
		rc->player_plane_x = 0;
		rc->player_plane_y = -0.66;
		rc->player_dir_x = 1;
		rc->player_dir_y = 0;
	}
	else if (map->player_dir == 'E')
	{
		rc->player_plane_x = 0.66;
		rc->player_plane_y = 0;
		rc->player_dir_x = 0;
		rc->player_dir_y = 1;
	}
	else if (map->player_dir == 'W')
	{
		rc->player_plane_x = -0.66;
		rc->player_plane_y = 0;
		rc->player_dir_x = 0;
		rc->player_dir_y = -1;
	}

	printf("1-\nX: %f\nY: %f\n\n", rc->player_pos_x, rc->player_pos_y);

	if (!(rc->mlx_ptr = mlx_init()))
		return (ft_puterror("Inicio de Minilibx fallida\n"));
	if (!(rc->win_ptr = mlx_new_window(rc->mlx_ptr, rc->win_x, rc->win_y, "mx 42")))
		return (ft_puterror("Proceso de creacion de Ventana fallida\n"));
	return (1);
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
	rc->textnum = rc->worldMap[rc->map_x][rc->map_y] - 1;
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

void draw_wall(t_raycaster *rc, int x)
{
	while (rc->draw_start <= rc->draw_end)
	{
		rc->tex_y = abs((((rc->draw_start * 256 - rc->win_y * 128 +
						  rc->line_height * 128) *
						 64) /
						rc->line_height) /
					   256);
		ft_memcpy(rc->img_data + 4 * rc->win_x * rc->draw_start + x * 4,
				  &rc->tex[1].data[rc->tex_y % rc->tex_height *
									  rc->tex[1].size_l +
								  rc->tex_x % rc->tex_width *
									  rc->tex[1].bpp / 8],
				  sizeof(int));
		rc->draw_start++;
	}
}

void calcule_wall(t_raycaster *rc, int x)
{
	//rc->tex_id = rc->worldMap[rc->map_x][rc->map_y] + rc->tex_side;
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

	if (key == ESC)
	{
		system("killall a.out && clear");
		return (-1);
	}
	if (key == DOWN || key == UP || key == RIGHT || key == LEFT)
	{
		if (key == UP)
		{
			if (rc->worldMap[(int)(rc->player_pos_x + rc->dirx *
										   rc->movespeed)][(int)(rc->player_pos_y)] == 0)
				rc->player_pos_x += rc->dirx * rc->movespeed;
			if (rc->worldMap[(int)(rc->player_pos_x)][(int)(rc->player_pos_y + rc->diry *
														   rc->movespeed)] == 0)
				rc->player_pos_y += rc->diry * rc->movespeed;
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
		calcule_wall(rc, x);
		draw_wall(rc, x);
		x++;
	}
	mlx_put_image_to_window(rc->mlx_ptr, rc->win_ptr, rc->img_ptr, 0, 0);
	return (0);
}
