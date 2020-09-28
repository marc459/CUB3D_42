/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:22:49 by msantos-          #+#    #+#             */
/*   Updated: 2020/09/28 14:19:36 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*    https: //github.com/keuhdall/images_example */
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
	printf("key->%d;\n",key);
	if (key == 65307 || key == 53)
		system("killall a.out");
	return (0);
}

int		main(void)
{
	t_cub3d *t;
	int x;
	int count_w;
	int count_h;

	count_h = -1;

	t = malloc(sizeof(t_cub3d));
	t->win_width = 2000;
	t->win_height = 1000;

	t->mlx_ptr = mlx_init();
	t->win_ptr = mlx_new_window(t->mlx_ptr, t->win_width, t->win_height, "mx 42");
	t->img_ptr = mlx_new_image(t->mlx_ptr, t->win_width, t->win_height);
	t->img_data = (int *)mlx_get_data_addr(t->img_ptr, &t->bpp, &t->size_line, &t->endian);

	t->tex[1].img = mlx_xpm_file_to_image(t->mlx_ptr, "textures/stone.xpm", &t->tex_height, &t->tex_height);
	t->tex[1].data = (int *)mlx_get_data_addr(t->tex[1].img, &t->tex[1].bpp, &t->tex[1].sizeline, &t->tex[1].endian);
	while (++count_h < t->win_height)
	{
		count_w = -1;
		while (++count_w < t->win_width)
		{
			if (count_w < 64 && count_h < 64)
				t->img_data[count_h * t->win_width + count_w] = 0xFFFFFF;
		}
	}
	mlx_put_image_to_window(t->mlx_ptr, t->win_ptr, t->img_ptr, 0, 0);
	mlx_key_hook(t->win_ptr, deal_key, &(*t));
	mlx_loop(t->mlx_ptr);
}
