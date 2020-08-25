/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/02/24 21:23:02 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	init_arch_params(archparams_t *arch)
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

void	init_map_checking_params(validmap_t *map)
{
	int i;

	i = 0;
	map->line_width = 0;
	map->colum_spaces = malloc(sizeof(int) * 255);
	map->colum_nums = malloc(sizeof(int) * 255);
	while (i < 255)
	{
		map->colum_spaces[i] = 0;
		map->colum_nums[i] = 0;
		i++;
	}
}

int		init_raycast_params(t_raycaster *rc, archparams_t *arch, validmap_t *map)
{
  rc->mlx_ptr = NULL;
  rc->win_ptr = NULL;
  rc->win_x = arch->win_x;
  rc->win_y = arch->win_y;
  rc->worldMap = arch->worldMap;
  rc->player_pos_x = map->init_p_pos_x;
  rc->player_pos_y = map->init_p_pos_y;
  rc->player_dir_x = -1;
  rc->player_dir_y = 0;
  rc->player_plane_x = INIT_P_PLANE_X;
  rc->player_plane_y = INIT_P_PLANE_Y;

  if (!(rc->mlx_ptr = mlx_init()))
	return (ft_puterror("Inicio de Minilibx fallida\n"));
  if (!(rc->win_ptr = mlx_new_window(rc->mlx_ptr, rc->win_x, rc->win_y, "mx 42")))
	return (ft_puterror("Proceso de creacion de Ventana fallida\n"));
  return (1);
}
