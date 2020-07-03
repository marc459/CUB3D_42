/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:22:49 by msantos-          #+#    #+#             */
/*   Updated: 2020/05/26 21:41:38 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minilibx_opengl/mlx.h"
#include "cub3d.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

int deal_key(int key, t_cub3d *f)
{
	ft_putstr(ft_itoa(key));
	
	if (key == 123)
		f->posX = f->posX - 14;
	else if (key == 124)
		f->posX = f->posX + 14;
	else if (key == 126)
		f->posY = f->posY - 14;
	else if (key == 125)
		f->posY = f->posY + 14;
	else if (key == 53)
		system("killall a.out && clear"); //system("kill -9 | ps -ef | pgrep a.out");

	mlx_string_put(f->mlx_ptr, f->win_ptr, f->x_position, f->y_position, 0x27FF00, "*");
	//mlx_pixel_put(f->mlx_ptr, f->win_ptr, f->x_position, f->y_position, 0x27FF00);
	return (0);
}

int		main(void)
{
	t_cub3d		*f;
	int x;

	f = malloc(sizeof(t_cub3d));

	//x and y start position
	f->posX = 22;
	f->posY = 12;  

	//initial direction vector
	f->dirX = -1;
	f->dirY = 0;

	 //the 2d raycaster version of camera plane
  	f->planeX = 0;
	f->planeY = 0.66;

  	f->time = 0; //time of current frame
	f->oldTime = 0; //time of previous frame

	
	f->mlx_ptr = mlx_init();
	f->win_ptr = mlx_new_window(f->mlx_ptr, 800, 800, "mx 42");
		
	//mlx_pixel_put(f->mlx_ptr, f->win_ptr, f->x_position, 200, 0xFFD2C8);
	mlx_key_hook(f->win_ptr, deal_key, &(*f));
	while (!done())
	{
		mlx_loop(f->mlx_ptr);
	}
}
