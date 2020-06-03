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
	system("clear");
	
	ft_putstr(ft_itoa(key));
	ft_putstr("\n");
	
	if (key == 123)
		f->x_position = f->x_position - 14;
	else if (key == 124)
		f->x_position = f->x_position + 14;
	else if (key == 126)
		f->y_position = f->y_position - 14;
	else if (key == 125)
		f->y_position = f->y_position + 14;
	else if (key == 53)
		system("killall a.out && clear"); //system("kill -9 | ps -ef | pgrep a.out");

	ft_putstr(ft_itoa(f->x_position));
	//mlx_string_put(f->mlx_ptr, f->win_ptr, f->x_position, f->y_position, 0x27FF00, "*");
	mlx_pixel_put(f->mlx_ptr, f->win_ptr, f->x_position, f->y_position, 0x27FF00);
	return (0);
}

int		main(void)
{
	t_cub3d		*f;
	int x;

	f = malloc(sizeof(t_cub3d));
	f->x_position = 200;
	f->y_position = 200;
	
	f->mlx_ptr = mlx_init();
	f->win_ptr = mlx_new_window(f->mlx_ptr, 800, 800, "mx 42");
		
	//mlx_pixel_put(f->mlx_ptr, f->win_ptr, f->x_position, 200, 0xFFD2C8);
	mlx_key_hook(f->win_ptr, deal_key, &(*f));

	mlx_loop(f->mlx_ptr);
}
