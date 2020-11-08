/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/07 14:39:42 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	init_arch_params(t_archparams *arch)
{
	arch->parameters_count = 0;
	arch->win_x = 0;
	arch->win_y = 0;
	arch->no_texture = "";
	arch->so_texture = "";
	arch->we_texture = "";
	arch->ea_texture = "";
	arch->s_texture = "";
	arch->f_color = "";
	arch->c_color = "";
}

void	init_map_checking_params(t_validmap *map)
{
	int i;

	i = 0;
	map->colum_spaces = (int*)malloc(sizeof(int) * 255);
	map->colum_nums = (int*)malloc(sizeof(int) * 255);
	map->last_0 = 0;
	while (i < 255)
	{
		map->colum_spaces[i] = 0;
		map->colum_nums[i] = 0;
		i++;
	}
}

void	init_raycast_params3(t_raycaster *rc,
		t_validmap *map, t_archparams *arch)
{
	rc->win_x = arch->win_x;
	rc->win_y = arch->win_y;
	rc->world_map = arch->world_map;
	rc->tex_height = 64;
	rc->tex_width = 64;
	rc->tex_side = 1;
	rc->movespeed = 0.200;
	rc->up = 0;
	rc->down = 0;
	rc->right = 0;
	rc->left = 0;
	if (map->player_dir == 'E')
	{
		rc->player_plane_x = 0.66;
		rc->player_plane_y = 0;
		rc->dirx = 0;
		rc->diry = 1;
	}
	else if (map->player_dir == 'W')
	{
		rc->player_plane_x = -0.66;
		rc->player_plane_y = 0;
		rc->dirx = 0;
		rc->diry = -1;
	}
}

void	init_raycast_params2(t_raycaster *rc, t_validmap *map)
{
	rc->player_pos_x = map->init_p_pos_y;
	rc->player_pos_y = map->init_p_pos_x;
	rc->map_width = map->map_width;
	rc->map_height = map->m_line;
	if (map->player_dir == 'N')
	{
		rc->dirx = -1;
		rc->diry = 0;
		rc->player_plane_x = 0;
		rc->player_plane_y = 0.66;
	}
	else if (map->player_dir == 'S')
	{
		rc->player_plane_x = 0;
		rc->player_plane_y = -0.66;
		rc->dirx = 1;
		rc->diry = 0;
	}
}

int		init_raycast_params(t_raycaster *rc,
		t_archparams *arch, t_validmap *map)
{
	rc->mlx_ptr = NULL;
	rc->win_ptr = NULL;
	rc->rot_left = 0;
	rc->rot_right = 0;
	rc->sprite[0].x = 5;
	rc->sprite[0].y = 6;
	rc->numsprites = 1;
	init_raycast_params2(rc, map);
	init_raycast_params3(rc, map, arch);
	rc->spr_buffer = (double *)malloc(sizeof(double) * rc->win_x);
	if (!(rc->mlx_ptr = mlx_init()))
		return (ft_puterror("Inicio de Minilibx fallida\n"));
	if (!(rc->win_ptr =
		mlx_new_window(rc->mlx_ptr, rc->win_x, rc->win_y, "mx 42")))
		return (ft_puterror("Proceso de creacion de Ventana fallida\n"));
	return (1);
}
