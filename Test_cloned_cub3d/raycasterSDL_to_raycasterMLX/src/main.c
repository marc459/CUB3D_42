/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:22:49 by msantos-          #+#    #+#             */
/*   Updated: 2020/07/02 12:41:55 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int           init(t_raycaster *rc)
{
  

  rc->mlx_ptr = NULL;
  rc->win_ptr = NULL;
  rc->player_pos_x = INIT_P_POS_X;
  rc->player_pos_y = INIT_P_POS_Y;
  rc->player_dir_x = INIT_P_DIR_X;
  rc->player_dir_y = INIT_P_DIR_Y;
  rc->player_plane_x = INIT_P_PLANE_X;
  rc->player_plane_y = INIT_P_PLANE_Y;

  rc->mlx_ptr = mlx_init();
  rc->win_ptr = mlx_new_window(rc->mlx_ptr, WIN_X, WIN_Y, "mx 42");
  /*if((rc->mlx_ptr = mlx_init()) != 0)
  {
	fprintf(stderr,"SDL initialization failed\n");
    return (-1);
  }
  if ((rc->win_ptr = mlx_new_window(rc->mlx_ptr, WIN_X, WIN_Y, "mx 42")) != 0)
  {
    fprintf(stderr,"Window creation failed\n");
    return (-1);
  }*/
  return (0);
}
void	refresh_screen(t_raycaster *rc){
	int x;
	int y;

	x = 0;
	y = 0;
	while(x < 1280)
	{
		while(y < 720)
		{
			mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, x, y, 0x000000);
			y++;
		}
		y=0;
		x++;
	}
}

int		handle_events(int key,t_raycaster *rc){

	ft_putstr(ft_itoa(key));
	ft_putstr("\n");
	
	if (key == 123)
		rc->player_pos_x = rc->player_pos_x - 15;
	else if (key == 124)
		rc->player_pos_x = rc->player_pos_x + 15;
	else if (key == 126)
		rc->player_pos_y = rc->player_pos_y - 15;
	else if (key == 125)
		rc->player_pos_y = rc->player_pos_y + 15;
	else if (key == 53)
		system("killall a.out && clear");

	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, rc->player_pos_x, rc->player_pos_y, 0x27FF00);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, rc->player_pos_x + 1, rc->player_pos_y + 1, 0x27FF00);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, rc->player_pos_x - 1, rc->player_pos_y - 1, 0x27FF00);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, rc->player_pos_x - 1, rc->player_pos_y + 1, 0x27FF00);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, rc->player_pos_x + 1, rc->player_pos_y - 1, 0x27FF00);
	return(0);

}

void          initial_calc(t_raycaster *rc, int x)
{
  double      camera_x;

  camera_x = 2 * x / (double)(WIN_X) - 1;
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
    if (worldMap[rc->map_x][rc->map_y] > 0)
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
  line_height = (int)(WIN_Y / rc->perp_wall_dist);
  rc->draw_start = -line_height / 2 + WIN_Y / 2;
  if (rc->draw_start < 0)
    rc->draw_start = 0;
  rc->draw_end = line_height / 2 + WIN_Y / 2;
  if (rc->draw_end >= WIN_Y)
    rc->draw_end = WIN_Y - 1;
}

//principal loop
int raycasting(int key, t_raycaster *rc)
{
	int x;

	x = 0;
	while(x < WIN_X)
    {
		initial_calc(rc, x);
		perform_dda(rc);
    	calc_wall_height(rc);
      	draw_vert_line(sdl, rc, x);
	  	x++;
    }

	refresh_screen(rc);
	handle_events(key,rc);
	return (0);
}

int		main(void)
{
	t_raycaster		*rc;

	rc = malloc(sizeof(t_raycaster));
	if (init(rc) != 0)
		return (-1);
	
	mlx_key_hook(rc->win_ptr, raycasting, rc);
	mlx_loop(rc->mlx_ptr);

	return(0);
}
