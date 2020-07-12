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

int           init(t_sdl *sdl, t_raycaster *rc)
{
  rc->mlx_ptr = NULL;
  rc->win_ptr = NULL;
  rc->player_pos_x = INIT_P_POS_X;
  rc->player_pos_y = INIT_P_POS_Y;
  rc->player_dir_x = INIT_P_DIR_X;
  rc->player_dir_y = INIT_P_DIR_Y;
  rc->player_plane_x = INIT_P_PLANE_X;
  rc->player_plane_y = INIT_P_PLANE_Y;

  if((rc->mlx_ptr = mlx_init()) != 0)
  {
	fprintf(stderr,"SDL initialization failed\n");
    return (-1);
  }
  if ((rc->win_ptr = mlx_new_window(rc->mlx_ptr, WIN_X, WIN_Y, "mx 42")) != 0)
  {
    fprintf(stderr,"Window creation failed\n");
    return (-1);
  }
  return (0);
}
int deal_key(int key, t_cub3d *rc)
{
	raycasting(&(*f));
	ft_putstr(ft_itoa(key));
	ft_putstr("\n");
	
	if (key == 123)
		rc->x_position = rc->x_position - 15;
	else if (key == 124)
		rc->x_position = rc->x_position + 15;
	else if (key == 126)
		rc->y_position = rc->y_position - 15;
	else if (key == 125)
		rc->y_position = rc->y_position + 15;
	else if (key == 53)
		system("killall a.out && clear");

	ft_putstr(ft_itoa(rc->x_position));
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, rc->x_position, rc->y_position, 0x27FF00);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, rc->x_position + 1, rc->y_position + 1, 0x27FF00);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, rc->x_position - 1, rc->y_position - 1, 0x27FF00);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, rc->x_position - 1, rc->y_position + 1, 0x27FF00);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, rc->x_position + 1, rc->y_position - 1, 0x27FF00);
	return (0);
}

void raycasting (t_cub3d *rc)
{
	ft_putstr("hola");
}

int		main(void)
{
	t_raycaster		*rc;

	if (init(&sdl) != 0)
		return (-1);
	raycaster(&rc);
	
	mlx_key_hook(rc->win_ptr, deal_key, &(*f));
	
	mlx_loop(rc->mlx_ptr);
}
