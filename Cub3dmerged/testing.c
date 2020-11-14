/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/14 14:54:15 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes.h"

void	print_params(t_archparams *arch, t_validmap *map)
{
	int x;
	int y;

	x = 0;
	y = 0;
	printf("%s-------YOU ARE IN %s OPERARIVE SYSTEM-------%s\n\n", Red, SO, Color_Off);
	printf("Resolution: %d*%d\n", arch->win_x, arch->win_y);
	printf("Dimensiones: %d,%d\n", map->map_width,map->m_line);
	printf("no_texture: %s\n", arch->no_texture);
	printf("so_texture: %s\n", arch->so_texture);
	printf("we_texture: %s\n", arch->we_texture);
	printf("ea_texture: %s\n", arch->ea_texture);
	printf("s_texture: %s\n", arch->s_texture);
	printf("c_color: %s\n", arch->c_color);
	printf("f_color: %s\nMap:\n", arch->f_color);
	while (x < map->m_line)
	{
		while (y < map->map_width)
		{
			printf("%d", arch->world_map[x][y]);
			y++;
		}
		printf("\n");
		y = 0;
		x++;
	}
	printf("\n\n");
}

/*void	draw_map(t_raycaster *rc)
{
	int y;
	int x;
	int printplayer_X;
	int printplayer_Y;
	int x_wall;
	int y_wall;
	int tmpx;
	int tmpy;

	x = 0;
	y = 0;
	x_wall = 10;
	y_wall = 10;
	printplayer_X = rc->player_pos_y * 10;
	printplayer_Y = rc->player_pos_x * 10;
	tmpx = printplayer_X;
	tmpy = printplayer_Y;
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx + 1, tmpy + 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx, tmpy, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx - 1, tmpy - 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx - 1, tmpy + 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx + 1, tmpy - 1, 0x33FF3C);

	while (x < rc->map_height)
	{
		while (y < rc->map_width)
		{
			if (rc->world_map[x][y] == 1 || rc->world_map[x][y] == 2)
				mlx_pixel_put(rc->mlx_ptr, rc->win_ptr,
							x_wall, y_wall, 0xFA2C00);
			y++;
			x_wall = x_wall + 10;
		}
		y = 0;
		x++;
		x_wall = 10;
		y_wall = y_wall + 10;
	}
}*/

/*void ace_of_empires(int i,...)
{
va_list var_args;
va_start(var_args, str);

char *str1;
while(i > 0)
{
	str1 = va_arg ((var_args), char *);
	printf("----%s---\n",str1);
	i--;
}
	
va_end(var_args);
}

void	draw_map(t_raycaster *rc)
{
	int y;
	int x;
	int printplayer_X;
	int printplayer_Y;
	int x_wall;
	int y_wall;
	int tmpx;
	int tmpy;

	x = 0;
	y = 0;
	tmpx = printplayer_X;
	tmpy = printplayer_Y;
	x_wall = 10;
	y_wall = 10;
	printplayer_X = rc->player_pos_y * 10;
	printplayer_Y = rc->player_pos_x * 10;
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx + 1, tmpy + 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx, tmpy, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx - 1, tmpy - 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx - 1, tmpy + 1, 0x33FF3C);
	mlx_pixel_put(rc->mlx_ptr, rc->win_ptr, tmpx + 1, tmpy - 1, 0x33FF3C);

	while (x < rc->map_height)
	{
		while (y < rc->map_width)
		{
			if (rc->world_map[x][y] == 1 || rc->world_map[x][y] == 2)
				mlx_pixel_put(rc->mlx_ptr, rc->win_ptr,
							x_wall, y_wall, 0xFA2C00);
			y++;
			x_wall = x_wall + 10;
		}
		y = 0;
		x++;
		x_wall = 10;
		y_wall = y_wall + 10;
	}
}

	int		key_press(int key, t_raycaster *rc)
	{
		if (key == UP || key == W)
			rc->up = 1;
		if (key == DOWN || key == S)
			rc->down = 1;
		if (key == RIGHT || key == D)
			rc->right = 1;
		if (key == LEFT || key == A)
			rc->left = 1;
		if (key == SHIFT_L)
		{
			rc->movespeed = rc->movespeed * 2.5;
			rc->sprint = 1;
		}
		if (key == CTRL)
		{
			rc->movespeed = rc->movespeed / 2.5;
			rc->crouch = -30;
			rc->win_y = rc->win_y + 30;
			rc->win_x = rc->win_x + 30;
		}
		if (key == C)
		{
			if (rc->textured == 1)
				rc->textured = 0;
			else
				rc->textured = 1;
		}
		if (key == ESC)
			close_success(rc);
		return (0);
	}

	int		key_release(int key, t_raycaster *rc)
	{
		if (key == UP || key == W)
			rc->up = 0;
		if (key == DOWN || key == S)
			rc->down = 0;
		if (key == RIGHT || key == D)
			rc->right = 0;
		if (key == LEFT || key == A)
			rc->left = 0;
		if (key == SHIFT_L)
		{
			rc->movespeed = rc->movespeed / 2.5;
			rc->sprint = 0;
		}
		if (key == CTRL)
		{
			rc->movespeed = rc->movespeed * 2.5;
			rc->crouch = 0;
			rc->win_y = rc->win_y - 30;
			rc->win_x = rc->win_x - 30;
		}
		return (0);
	}

void	draw_vert_line(t_raycaster *rc, int x)
{
	int color;
	int y;
	int pixel;

	color = BLUE;
	if (rc->world_map[rc->map_x][rc->map_y] == 1)
		color = WHITE;
	if (rc->world_map[rc->map_x][rc->map_y] == 2)
		color = GREEN;
	if (rc->world_map[rc->map_x][rc->map_y] == 3)
		color = GREEN;
	if (rc->world_map[rc->map_x][rc->map_y] == 4)
		color = RED;
	if (rc->world_map[rc->map_x][rc->map_y] == 5)
		color = BLACK;
	if (rc->side == 1)
		color = color + 3000;
	y = rc->draw_start;
	if (rc->bpp != 32)
		color = mlx_get_color_value(rc->mlx_ptr, color);
	while (y < rc->draw_end)
	{
		pixel = (y * rc->win_x + x) * 4;
		if (rc->endian == 1)
		{
			rc->img_data[pixel + 0] = (color >> 24);
			rc->img_data[pixel + 1] = (color >> 16) & 0xFF;
			rc->img_data[pixel + 2] = (color >> 8) & 0xFF;
			rc->img_data[pixel + 3] = (color) & 0xFF;
		}
		else if (rc->endian == 0)
		{
			rc->img_data[pixel + 0] = (color) & 0xFF;
			rc->img_data[pixel + 1] = (color >> 8) & 0xFF;
			rc->img_data[pixel + 2] = (color >> 16) & 0xFF;
			rc->img_data[pixel + 3] = (color >> 24);
		}
		y++;
	}
}

void	floor_and_sky_draw(t_raycaster *rc, int x)
{
	int y;

	y = rc->draw_end + 1; //0 if linux
	floor_directions(rc);
	while (y < rc->win_y)
	{
		rc->currentdist = rc->win_y / (2.0 * y - rc->win_y);
		rc->weight = rc->currentdist / rc->perp_wall_dist;
		rc->currentfloorx = rc->weight * rc->floorxwall +
							(1.0 - rc->weight) * rc->player_pos_x;
		rc->currentfloory = rc->weight * rc->floorywall +
							(1.0 - rc->weight) * rc->player_pos_y;
		rc->floortexx = (int)(rc->currentfloorx
						* rc->tex_width) % rc->tex_width;
		rc->floortexy = (int)(rc->currentfloory
						* rc->tex_height) % rc->tex_height;
		ft_memcpy(rc->img_data + 4 * rc->win_x * y + x * 4,
				&rc->tex[4].data[4 * rc->floortexx * rc->tex_width +
				4 * rc->floortexy],	sizeof(int));
		ft_memcpy(rc->img_data + 4 * rc->win_x * (rc->win_y - y) + x * 4,
				&rc->tex[7].data[4 * rc->floortexx * rc->tex_width +
				4 * rc->floortexy],
				sizeof(int));
		y++;
	}
}

int		raycasting(t_raycaster *rc)
{
	int x;

	x = 0;
	handle_events(rc);
	rc->img_ptr = mlx_new_image(rc->mlx_ptr, rc->win_x, rc->win_y);
	rc->img_data = mlx_get_data_addr(rc->img_ptr,
					&rc->bpp, &rc->size_line, &rc->endian);
	while (x < rc->win_x)
	{
		motionless_2(rc, x);
		motionless_3(rc);
		dda(rc);
		motionless_4(rc);
		calcule_wall(rc);
		if (rc->textured == 0)
			draw_vert_line(rc, x);
		else
		{
			floor_and_sky_draw(rc, x);
			draw_wall(rc, x);
		}
		x++;
	}
	mlx_put_image_to_window(rc->mlx_ptr, rc->win_ptr,
						rc->img_ptr, rc->crouch, rc->crouch);
	return (0);
}
//mlx_mouse_hook(rc.win_ptr, &key_press, &rc);

*/