/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/10/19 14:26:34 by msantos-         ###   ########.fr       */
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
	rc->movespeed = 0.300;
	rc->textured = 1;
	rc->crouch = 0;
	rc->up = 0;
	rc->down = 0;
	rc->right = 0;
	rc->left = 0;

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


void floor_and_sky_draw(t_raycaster *rc, int x)
{
	int y;

	y = rc->draw_end + 1; //0 if linux
	floor_directions(rc);
	if (rc->draw_end < 0)
		rc->draw_end = rc->win_y;
	while (y < rc->win_y)
	{
		rc->currentdist = rc->win_y / (2.0 * y - rc->win_y);
		rc->weight = rc->currentdist / rc->perp_wall_dist;
		rc->currentfloorx = rc->weight * rc->floorxwall +
						   (1.0 - rc->weight) * rc->player_pos_x;
		rc->currentfloory = rc->weight * rc->floorywall +
						   (1.0 - rc->weight) * rc->player_pos_y;
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

void          draw_vert_line(t_raycaster *rc, int x)
{
	int color;
	int y;
	int pixel;
	int tmp;

	color = BLUE;
	if (rc->worldMap[rc->map_x][rc->map_y] == 1)
		color = WHITE;
	if (rc->worldMap[rc->map_x][rc->map_y] == 2)
		color = GREEN;
	if (rc->worldMap[rc->map_x][rc->map_y] == 3)
		color = GREEN;
	if(rc->worldMap[rc->map_x][rc->map_y] == 4)
		color = RED;
	if (rc->worldMap[rc->map_x][rc->map_y] == 5)
		color = BLACK;
		
	if (rc->side == 1)
		color = color + 3000;

	y = rc->draw_start;
	if (rc->bpp != 32)
    	color = mlx_get_color_value(rc->mlx_ptr, color);
	while (y < rc->draw_end)
	{
		pixel = (y * rc->win_x + x) * 4;

		if (rc->endian == 1)
	    {
	        rc->img_data[pixel + 0] = (color >> 24);
	        rc->img_data[pixel + 1] = (color >> 16) & 0xFF;
	        rc->img_data[pixel + 2] = (color >> 8) & 0xFF;
	        rc->img_data[pixel + 3] = (color) & 0xFF;
	    }
	    else if (rc->endian == 0)
	    {
	        rc->img_data[pixel + 0] = (color) & 0xFF;
	        rc->img_data[pixel + 1] = (color >> 8) & 0xFF;
	        rc->img_data[pixel + 2] = (color >> 16) & 0xFF;
	        rc->img_data[pixel + 3] = (color >> 24);
	    }
		y++;
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

int handle_events(t_raycaster *rc)
{
	double oldDirX;
	double oldPlaneX;
	/*if (key == ESC)
	{
		close_success(rc);
		return (-1);
	}
	if(key == C)
	{
		if(rc->textured == 1)
			rc->textured = 0;
		else
			rc->textured = 1;
	}
	if (key == CTRL)
	{
		
		if(rc->crouch == 0)
		{
			rc->movespeed = rc->movespeed / 2.5;
			rc->crouch = -30;
		}	
		else
		{
			rc->movespeed = rc->movespeed * 2.5;
			rc->crouch = 0;
		}
		
	}*/

	if (rc->up == 1)
	{
		if (rc->worldMap[(int)(rc->player_pos_x + rc->dirx * rc->movespeed)][(int)(rc->player_pos_y)] == 0)
			rc->player_pos_x += rc->dirx * rc->movespeed;
		if (rc->worldMap[(int)(rc->player_pos_x)][(int)(rc->player_pos_y + rc->diry * rc->movespeed)] == 0)
			rc->player_pos_y += rc->diry * rc->movespeed;
	}
	if (rc->down)
	{
		if (rc->worldMap[(int)(rc->player_pos_x - rc->dirx * rc->movespeed)][(int)(rc->player_pos_y)] == 0)
			rc->player_pos_x -= rc->dirx * rc->movespeed;
		if (rc->worldMap[(int)(rc->player_pos_x)][(int)(rc->player_pos_y - rc->diry * rc->movespeed)] == 0)
			rc->player_pos_y -= rc->diry * rc->movespeed;
	}
	if (rc->right)
	{
		oldDirX = rc->dirx;
		rc->dirx = rc->dirx * cos(-ROT_SPEED) - rc->diry * sin(-ROT_SPEED);
		rc->diry = oldDirX * sin(-ROT_SPEED) + rc->diry * cos(-ROT_SPEED);
		oldPlaneX = rc->player_plane_x;
		rc->player_plane_x = rc->player_plane_x * cos(-ROT_SPEED) - rc->player_plane_y * sin(-ROT_SPEED);
		rc->player_plane_y = oldPlaneX * sin(-ROT_SPEED) + rc->player_plane_y * cos(-ROT_SPEED);
	}
	if (rc->left)
	{
		oldDirX = rc->dirx;
		rc->dirx = rc->dirx * cos(ROT_SPEED) - rc->diry * sin(ROT_SPEED);
		rc->diry = oldDirX * sin(ROT_SPEED) + rc->diry * cos(ROT_SPEED);
		oldPlaneX = rc->player_plane_x;
		rc->player_plane_x = rc->player_plane_x * cos(ROT_SPEED) - rc->player_plane_y * sin(ROT_SPEED);
		rc->player_plane_y = oldPlaneX * sin(ROT_SPEED) + rc->player_plane_y * cos(ROT_SPEED);
	}
	return (0);
}

int raycasting(t_raycaster *rc)
{
	int x;

	x = 0;
	handle_events(rc);
	rc->img_ptr = mlx_new_image(rc->mlx_ptr, rc->win_x, rc->win_y);
	rc->img_data = mlx_get_data_addr(rc->img_ptr, &rc->bpp, &rc->size_line, &rc->endian);

	while (x < rc->win_x)
	{
		motionless_2(rc, x);
		motionless_3(rc);
		dda(rc);
		motionless_4(rc);
		calcule_wall(rc);
		if (rc->textured == 0)
			draw_vert_line(rc,x);
		else
		{
			floor_and_sky_draw(rc, x);
			draw_wall(rc, x);
		}
		x++;
	}
	mlx_put_image_to_window(rc->mlx_ptr, rc->win_ptr, rc->img_ptr, 0, rc->crouch);
	return (0);
}
