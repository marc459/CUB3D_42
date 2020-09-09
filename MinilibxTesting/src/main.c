/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:22:49 by msantos-          #+#    #+#             */
/*   Updated: 2020/09/09 13:47:40 by msantos-         ###   ########.fr       */
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
	printf("key->%d;\n",key);
	return (0);
}

void draw_wall(t_struct *t, int x)
{
	while (t->drawstart <= t->drawend)
	{
		t->tex_y = abs((((t->drawstart * 256 - t->win_height * 128 +
						  t->lineheight * 128) *
						 64) /
						t->lineheight) /
					   256);
		ft_memcpy(t->img_data + 4 * t->win_width * t->drawstart + x * 4,
				  &t->tex[t->tex_id].data[t->tex_y % t->tex_height *
											  t->tex[t->tex_id].sizeline +
										  t->tex_x % t->tex_width *
											  t->tex[t->tex_id].bpp / 8],
				  sizeof(int));
		t->drawstart++;
	}
}

int		main(void)
{
	t_cub3d		*f;
	t_struct	*t;

	int x;

	f = malloc(sizeof(t_cub3d));
	
	f->mlx_ptr = mlx_init();
	f->win_ptr = mlx_new_window(f->mlx_ptr, screenWidth, screenHeight, "mx 42");

	//mlx_pixel_put(f->mlx_ptr, f->win_ptr, f->x_position, 200, 0xFFD2C8);
	t->tex[0].img = mlx_xpm_file_to_image(f->mlx_ptr, "textures/stone.xpm", &t->tex_height, &t->tex_height);
	//t->tex[0].data = mlx_get_data_addr(t->tex[0].img, &t->tex[0].bpp, &t->tex[0].sizeline, &t->tex[0].endian);

	/*t->drawstart = 300;
	t->drawend = 800;
	t->lineheight = 470;
	t->win_width = screenWidth;
	t->win_height = screenHeight;
	t->tex_id = 0;
	x = 800;*/
	//draw_wall(t,x);
	
	//mlx_key_hook(f->win_ptr, deal_key, &(*f));
	mlx_loop(f->mlx_ptr);
}
