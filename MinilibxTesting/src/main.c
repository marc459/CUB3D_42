/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:22:49 by msantos-          #+#    #+#             */
/*   Updated: 2020/09/11 13:20:49 by msantos-         ###   ########.fr       */
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

void init(t_struct *t)
{
	t->win_width = 1640;
	t->win_height = 980;
	t->initial_pos = 0;
	t->map_width = 0;
	t->map_height = 0;
	t->tex_width = 64;
	t->tex_height = 64;
	t->posx = 22;
	t->posy = 11.5;
	t->up = 0;
	t->down = 0;
	t->right = 0;
	t->left = 0;
	t->sprint = 0;
	t->tex_side = 0;
	t->life_bar = 200;
	t->sprite[1].x = 1.5;
	t->sprite[1].y = 1.5;
}

void		draw_wall(t_struct *t, int x)
{
	//printf("%d,%d,%d,%d,%d,%d\n", t->drawstart, t->drawend, t->lineheight, t->win_width, t->tex_id,x);
	while (t->drawstart <= t->drawend)
	{
		t->tex_y = abs((((t->drawstart * 256 - t->win_height * 128 +
					t->lineheight * 128) * 64) / t->lineheight) / 256);
		ft_memcpy(t->img_data + 4 * t->win_width * t->drawstart + x * 4,
				&t->tex[t->tex_id].data[t->tex_y % t->tex_height *
				t->tex[t->tex_id].sizeline + t->tex_x % t->tex_width *
				t->tex[t->tex_id].bpp / 8], sizeof(int));
		t->drawstart++;
	}
}

int deal_key(int key, t_cub3d *f)
{
	printf("key->%d;\n",key);
	if (key == 65307 || key == 53)
		system("killall a.out");
	return (0);
}

int		main(void)
{
	t_struct	*t;
	int x;
	

	t = malloc(sizeof(t_struct));
	init(t);

	t->mlx_ptr = mlx_init();
	t->win_ptr = mlx_new_window(t->mlx_ptr, t->win_width, t->win_height, "mx 42");
	t->tex[1].img = mlx_xpm_file_to_image(t->mlx_ptr, "textures/stone.xpm", &t->tex_height + 40, &t->tex_height);
	t->tex[1].data = mlx_get_data_addr(t->tex[1].img, &t->tex[1].bpp, &t->tex[1].sizeline, &t->tex[1].endian);
	
	//t->img_ptr = mlx_new_image(t->mlx_ptr, t->win_width, t->win_height);
	t->img_ptr = t->tex[1].img;

	mlx_put_image_to_window(t->mlx_ptr, t->win_ptr, t->img_ptr, 700, 350);
	mlx_key_hook(t->win_ptr, deal_key, &(*t));
	mlx_loop(t->mlx_ptr);
}
