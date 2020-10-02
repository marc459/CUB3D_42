/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/10/02 13:56:42 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

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
	printf("2-\nX: %f\nY: %f\n\n", rc->player_pos_x, rc->player_pos_y);

	mlx_string_put(rc->mlx_ptr, rc->win_ptr, rc->win_x / 2 - 20, 10, 0x33FF3C, "CUB3D");
	int tmpx = printplayer_X;
	int tmpy = printplayer_Y;
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx, tmpy, 0x33FF3C);

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
	rc->spr_buffer = malloc(sizeof(double) * arch->win_x);
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

void refresh_screen(t_raycaster *rc)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < rc->win_x)
	{
		while (y < rc->win_y)
		{
			mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, x, y, 0x000000);
			y++;
		}
		y = 0;
		x++;
	}
}

void initial_calc(t_raycaster *rc, int x)
{
	double camera_x;

	camera_x = 2 * x / rc->win_x - 1;
	rc->ray_dir_x = rc->player_dir_x + rc->player_plane_x * camera_x;
	rc->ray_dir_y = rc->player_dir_y + rc->player_plane_y * camera_x;
	rc->map_x = (int)(rc->player_pos_x);
	rc->map_y = (int)(rc->player_pos_y);
	rc->delta_dist_x = sqrt(1 + pow(rc->ray_dir_y, 2) / pow(rc->ray_dir_x, 2));
	rc->delta_dist_y = sqrt(1 + pow(rc->ray_dir_x, 2) / pow(rc->ray_dir_y, 2));
	if (rc->ray_dir_x < 0)
	{
		rc->step_x = -1;
		rc->side_dist_x = (rc->player_pos_x - rc->map_x) * rc->delta_dist_x;
	}
	else
	{
		rc->step_x = 1;
		rc->side_dist_x = (rc->map_x + 1.0 - rc->player_pos_x) * rc->delta_dist_x;
	}
	if (rc->ray_dir_y < 0)
	{
		rc->step_y = -1;
		rc->side_dist_y = (rc->player_pos_y - rc->map_y) * rc->delta_dist_y;
	}
	else
	{
		rc->step_y = 1;
		rc->side_dist_y = (rc->map_y + 1.0 - rc->player_pos_y) * rc->delta_dist_y;
	}
}

void perform_dda(t_raycaster *rc)
{
	int hit;

	hit = 0;
	while (hit == 0)
	{
		if (rc->side_dist_x < rc->side_dist_y)
		{
			rc->side_dist_x += rc->delta_dist_x;
			rc->map_x += rc->step_x;
			rc->side = 0;
		}
		else
		{
			rc->side_dist_y += rc->delta_dist_y;
			rc->map_y += rc->step_y;
			rc->side = 1;
		}
		if (rc->worldMap[rc->map_x][rc->map_y] > 0)
			hit = 1;
	}
}

void calc_wall_height(t_raycaster *rc)
{
	if (rc->side == 0)
		rc->perp_wall_dist = (rc->map_x - rc->player_pos_x + (1 - rc->step_x) / 2) / rc->ray_dir_x;
	else
		rc->perp_wall_dist = (rc->map_y - rc->player_pos_y + (1 - rc->step_y) / 2) / rc->ray_dir_y;
	rc->line_height = (int)(rc->win_y / rc->perp_wall_dist);
	rc->draw_start = -rc->line_height / 2 + rc->win_y / 2;
	if (rc->draw_start < 0)
		rc->draw_start = 0;
	rc->draw_end = rc->line_height / 2 + rc->win_y / 2;
	if (rc->draw_end >= rc->win_y)
		rc->draw_end = rc->win_y - 1;

	if (rc->side == 0)
		rc->wall_x = rc->player_pos_y + rc->perp_wall_dist * rc->ray_dir_x;
	else
		rc->wall_x = rc->player_pos_x + rc->perp_wall_dist * rc->ray_dir_y;
	rc->wall_x -= floor(rc->wall_x);
	rc->tex_x = abs((int)(rc->wall_x * (double)(64)));
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
	if (rc->worldMap[rc->map_x][rc->map_y] == 3)
		color = GREEN;
	if (rc->worldMap[rc->map_x][rc->map_y] == 4)
		color = RED;
	if (rc->worldMap[rc->map_x][rc->map_y] == 5)
		color = BLACK;

	if (rc->side == 1)
		color = color + 3000;
	else
		color = color;

	y = rc->draw_start;
	printf("%d\n", x);
	while (y < rc->draw_end)
	{
		tmp = y * rc->win_x + x;
		rc->img_data[tmp] = color;
		//mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, x, y, color);
		y++;
	}
}
static void motionless_4(t_raycaster *rc)
{
	if (t->side == 0)
		t->perpwalldist = (t->mapx - t->posx + (1 - t->stepx) / 2) / t->raydirx;
	else
		t->perpwalldist = (t->mapy - t->posy + (1 - t->stepy) / 2) / t->raydiry;
	t->lineheight = (int)(t->win_height / t->perpwalldist);
	t->drawstart = -t->lineheight / 2 + t->win_height / 2;
	if (t->drawstart < 0)
		t->drawstart = 0;
	t->drawend = t->lineheight / 2 + t->win_height / 2;
	if (t->drawend >= t->win_height)
		t->drawend = t->win_height - 1;
	t->textnum = t->map[t->mapx][t->mapy] - 1;
}

static void dda(t_raycaster *rc)
{
	while (t->hit == 0)
	{
		if (t->sidedistx < t->sidedisty)
		{
			t->sidedistx += t->deltadistx;
			t->mapx += t->stepx;
			t->side = 0;
		}
		else
		{
			t->sidedisty += t->deltadisty;
			t->mapy += t->stepy;
			t->side = 1;
		}
		if (t->map[t->mapx][t->mapy] > 0)
			t->hit = 1;
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

static void motionless_3(t_raycaster *rc)
{
	if (t->raydirx < 0)
	{
		t->stepx = -1;
		t->sidedistx = (t->posx - t->mapx) * t->deltadistx;
	}
	else
	{
		t->stepx = 1;
		t->sidedistx = (t->mapx + 1.0 - t->posx) * t->deltadistx;
	}
	if (t->raydiry < 0)
	{
		t->stepy = -1;
		t->sidedisty = (t->posy - t->mapy) * t->deltadisty;
	}
	else
	{
		t->stepy = 1;
		t->sidedisty = (t->mapy + 1.0 - t->posy) * t->deltadisty;
	}
}

static void motionless_2(t_raycaster *rc, int x)
{
	t->camerax = 2 * x / (double)t->win_width - 1;
	t->raydirx = t->dirx + t->planex * t->camerax;
	t->raydiry = t->diry + t->planey * t->camerax;
	t->mapx = (int)t->posx;
	t->mapy = (int)t->posy;
	t->deltadistx = fabs((1 / t->raydirx));
	t->deltadisty = fabs((1 / t->raydiry));
	t->hit = 0;
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

int raycasting(int key, t_raycaster *rc)
{
	int x;

	x = 0;

	if (handle_events(key, rc) != 0)
		return (-1);
	rc->img_ptr = mlx_new_image(rc->mlx_ptr, rc->win_x, rc->win_y);
	rc->img_data = mlx_get_data_addr(rc->img_ptr, &rc->bpp, &rc->size_line, &rc->endian);

	rc->tex[1].img = mlx_xpm_file_to_image(rc->mlx_ptr, "textures/stone.xpm", &rc->tex_width, &rc->tex_height);
	rc->tex[1].data = mlx_get_data_addr(rc->tex[1].img, &rc->tex[1].bpp, &rc->tex[1].size_l, &rc->tex[1].endian);
	//refresh_screen(rc);
	while (x < rc->win_x)
	{
		motionless_2(rc, x);
		motionless_3(rc);
		dda(rc);
		motionless_4(rc);
		calcule_wall(rc, x);
		draw_wall(rc, x);
		rc->spr_buffer[x] = rc->perp_wall_dist;
		x++;
	}

	mlx_put_image_to_window(rc->mlx_ptr, rc->win_ptr, rc->img_ptr, 0, 0);
	drawMap(rc);
	return (0);
}
