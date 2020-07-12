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


#include "../minilibx_opengl/mlx.h"
#include "cub3d.h"
#include "map1.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

int deal_key(int key, t_cub3d *f)
{
	/*system("clear");*/
	
	ft_putstr(ft_itoa(key));
	ft_putstr("\n");
	
	if (key == 123)
		f->x_position = f->x_position - 15;
	else if (key == 124)
		f->x_position = f->x_position + 15;
	else if (key == 126)
		f->y_position = f->y_position - 15;
	else if (key == 125)
		f->y_position = f->y_position + 15;
	else if (key == 53)
		system("killall a.out && clear"); //system("kill -9 | ps -ef | pgrep a.out");

	ft_putstr(ft_itoa(f->x_position));
	//mlx_string_put(f->mlx_ptr, f->win_ptr, f->x_position, f->y_position, 0x27FF00, "*");
	//mlx_pixel_put(f->mlx_ptr, f->win_ptr, f->x_position, f->y_position, 0x27FF00);
	mlx_pixel_put(f->mlx_ptr, f->win_ptr, f->x_position, f->y_position, 0x27FF00);
	mlx_pixel_put(f->mlx_ptr, f->win_ptr, f->x_position + 1, f->y_position + 1, 0x27FF00);
	mlx_pixel_put(f->mlx_ptr, f->win_ptr, f->x_position - 1, f->y_position - 1, 0x27FF00);
	mlx_pixel_put(f->mlx_ptr, f->win_ptr, f->x_position - 1, f->y_position + 1, 0x27FF00);
	mlx_pixel_put(f->mlx_ptr, f->win_ptr, f->x_position + 1, f->y_position - 1, 0x27FF00);
	return (0);
}

void drawMap(t_cub3d *f)
{
	int y;
	int x;

	int x_wall;
	int y_wall;
	
	x = 0;
	y = 0;

	x_wall = 15;
	y_wall = 15;

	while (y < mapHeight)
	{
		
		while (x < mapWidth)
		{
			/*printf("Casillas: %i",x);*/
			if (worldMap[x][y] == 1 || worldMap[x][y] == 2 || worldMap[x][y] == 3 || worldMap[x][y] == 4 || worldMap[x][y] == 5)
			{
				/*mlx_string_put(f->mlx_ptr, f->win_ptr, x_wall, y_wall, 0xFA2C00, "*");*/
				
				mlx_pixel_put(f->mlx_ptr, f->win_ptr, x_wall, y_wall, 0xFA2C00);
				mlx_pixel_put(f->mlx_ptr, f->win_ptr, x_wall+1, y_wall+1, 0xFA2C00);
				mlx_pixel_put(f->mlx_ptr, f->win_ptr, x_wall-1, y_wall-1, 0xFA2C00);
				mlx_pixel_put(f->mlx_ptr, f->win_ptr, x_wall - 1, y_wall + 1, 0xFA2C00);
				mlx_pixel_put(f->mlx_ptr, f->win_ptr, x_wall + 1, y_wall - 1, 0xFA2C00);
			}
			x++;
			x_wall += 15;
		}
		x = 0;
		x_wall = 15;
		
		y++;
		y_wall += 15;
	}
}

void raycasting (t_cub3d *f)
{


	ft_putstr("hola");
}

int		main(void)
{
	t_cub3d		*f;
	int x;

	f = malloc(sizeof(t_cub3d));

	f->x_position = 30;
	f->y_position = 30;
	
	f->mlx_ptr = mlx_init();
	f->win_ptr = mlx_new_window(f->mlx_ptr, screenWidth, screenHeight, "mx 42");

	//mlx_pixel_put(f->mlx_ptr, f->win_ptr, f->x_position, 200, 0xFFD2C8);
	drawMap(&(*f));
	raycasting(&(*f));
	mlx_key_hook(f->win_ptr, deal_key, &(*f));
	
	mlx_loop(f->mlx_ptr);
}
