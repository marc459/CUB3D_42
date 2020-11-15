/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:00:16 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/15 13:40:57 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void init_textures(t_raycaster *rc,
		t_archparams *arch)
{
	rc->no_texture = arch->no_texture;
	rc->so_texture = arch->so_texture;
	rc->we_texture = arch->we_texture;
	rc->ea_texture = arch->ea_texture;
	rc->s_texture = arch->s_texture;
	rc->f_color = ft_hextodec(arch->f_color);
	rc->c_color = ft_hextodec(arch->c_color);
}

void	init_initialparams(t_validmap *map)
{
	int i;

	i = 0;
	map->m_top = 0;
	map->m_bot = 0;
	map->m_line = 0;
	map->prev_line = "";
	map->map_width = 0;
	map->player_dir = '\0';
	map->colum_spaces = (int *)malloc(sizeof(int) * 255);
	map->colum_nums = (int *)malloc(sizeof(int) * 255);
	map->last_0 = 0;
	while (i < 255)
	{
		map->colum_spaces[i] = 0;
		map->colum_nums[i] = 0;
		i++;
	}
}
