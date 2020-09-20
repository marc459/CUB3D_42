/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/09/14 14:09:35 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	drawMap(t_raycaster *rc)
{
	int y;
	int x;
	int printplayer_X;
	int printplayer_Y;

	int x_wall;
	int y_wall;

	x = 0;
	y = 0;

	x_wall=10;
	y_wall=10;

	printplayer_X = rc->player_pos_x;
	printplayer_Y = rc->player_pos_y;
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, printplayer_X, printplayer_Y, 0x33FF3C);
	/*mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, printplayer_X + 1, printplayer_Y - 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, printplayer_X - 1, printplayer_Y - 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, printplayer_X - 1, printplayer_Y + 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, printplayer_X + 1, printplayer_Y - 1, 0x33FF3C);*/

	while (x < rc->mapHeight)
	{
		while (y < rc->mapWidth)
		{
			if (rc->worldMap[x][y] == 1 || rc->worldMap[x][y] == 2 || rc->worldMap[x][y] == 3)
			{
				mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, x_wall, y_wall, 0xFA2C00);
				/*mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, x_wall + 1, y_wall + 1, 0xFA2C00);
				mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, x_wall - 1, y_wall - 1, 0xFA2C00);
				mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, x_wall - 1, y_wall + 1, 0xFA2C00);
				mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, x_wall + 1, y_wall - 1, 0xFA2C00);*/
			}
			y++;
			x_wall++;
		}
		y = 3;
		x++;
		x_wall=10;
		y_wall++;
	}
}

int		init_raycast_params(t_raycaster *rc, archparams_t *arch, validmap_t *map)
{
  rc->mlx_ptr = NULL;
  rc->win_ptr = NULL;
  rc->win_x = arch->win_x;
  rc->win_y = arch->win_y;
  rc->worldMap = arch->worldMap;
  rc->player_pos_x = map->init_p_pos_x;
  rc->player_pos_y = map->init_p_pos_y;
  rc->player_dir_x = -1;
  rc->player_dir_y = 1;
  rc->player_plane_x = INIT_P_PLANE_X;
  rc->player_plane_y = INIT_P_PLANE_Y;
  rc->mapWidth = map->mapWidth;
  rc->mapHeight = map->m_line;

  if (!(rc->mlx_ptr = mlx_init()))
	return (ft_puterror("Inicio de Minilibx fallida\n"));
  if (!(rc->win_ptr = mlx_new_window(rc->mlx_ptr, rc->win_x, rc->win_y, "mx 42")))
	return (ft_puterror("Proceso de creacion de Ventana fallida\n"));
  return (1);
}

void	refresh_screen(t_raycaster *rc)
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
		y=0;
		x++;
	}
}

void          initial_calc(t_raycaster *rc, int x)
{
  double      camera_x;

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

void          perform_dda(t_raycaster *rc)
{
  int         hit;

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

void          calc_wall_height(t_raycaster *rc)
{
  int         line_height;

  if (rc->side == 0)
    rc->perp_wall_dist = (rc->map_x - rc->player_pos_x + (1 - rc->step_x) / 2) / rc->ray_dir_x;
  else
    rc->perp_wall_dist = (rc->map_y - rc->player_pos_y + (1 - rc->step_y) / 2) / rc->ray_dir_y;
  line_height = (int)(rc->win_y / rc->perp_wall_dist);
  rc->draw_start = -line_height / 2 + rc->win_y / 2;
  if (rc->draw_start < 0)
    rc->draw_start = 0;
  rc->draw_end = line_height / 2 + rc->win_y / 2;
  if (rc->draw_end >= rc->win_y)
    rc->draw_end = rc->win_y - 1;
}

void          draw_vert_line(t_raycaster *rc, int x)
{
	int color;
	int y;

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
	else
		color = color;

	y = rc->draw_start;
	while (y < rc->draw_end)
	{
		mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, x, y, color);
		y++;
	}
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
	refresh_screen(rc);
	while (x < rc->win_x)
    {
		initial_calc(rc, x);
		perform_dda(rc);
    	calc_wall_height(rc);
		draw_vert_line(rc, x);
	  	x++;
    }
	
	drawMap(rc);
	return (0);
}
