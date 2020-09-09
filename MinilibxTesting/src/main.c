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
	if(key == 65307)
		system("killall a.out && clear");
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
	t_struct	*t;
	int x;

	t = malloc(sizeof(t_struct));
	
	t->mlx_ptr = mlx_init();
	t->win_ptr = mlx_new_window(t->mlx_ptr, screenWidth, screenHeight, "mx 42");
	t->tex[1].img = mlx_xpm_file_to_image(t->mlx_ptr, "textures/stone.xpm", &t->tex_height, &t->tex_height);
	t->tex[1].data = mlx_get_data_addr(t->tex[1].img, &t->tex[1].bpp, &t->tex[1].sizeline, &t->tex[1].endian);

	/*t->drawstart = 300;
	t->drawend = 800;
	t->lineheight = 470;
	t->win_width = screenWidth;
	t->win_height = screenHeight;
	t->tex_id = 0;
	x = 800;*/
	//draw_wall(t,x);
	
	mlx_key_hook(t->win_ptr, deal_key, &(*t));
	mlx_loop(t->mlx_ptr);
}
