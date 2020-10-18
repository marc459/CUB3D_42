/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:20:47 by fvega-tr          #+#    #+#             */
/*   Updated: 2020/09/11 13:18:00 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init(t_struct *t, char *map)
{
	t->win_width = 1640;
	t->win_height = 980;
	t->map_file = map;
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

int		main(int argc, char **argv)
{
	t_struct	t;

	init(&t, argv[1]);
	map_reader(&t);
	t.mlx_ptr = mlx_init();
	t.win_ptr = mlx_new_window(t.mlx_ptr, t.win_width, t.win_height,
	"wolfenstein");
	load_textures(&t);
	mlx_hook(t.win_ptr, 2, 1L << 0, key_press, &t);
	mlx_hook(t.win_ptr, 3, 1L << 1, key_release, &t);
	if (argc == 3 && ft_strncmp("--save", argv[2], ft_strlen("--save")) == 0)
		mlx_loop_hook(t.mlx_ptr, screenshot, &t);
	else
		mlx_loop_hook(t.mlx_ptr, motionless, &t);
	mlx_hook(t.win_ptr, 17, 0, close_success, &t);
	mlx_loop(t.mlx_ptr);
}
