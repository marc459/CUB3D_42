/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/09/02 13:31:13 by msantos-         ###   ########.fr       */
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
	map->colum_spaces = malloc(sizeof(int) * 255);
	map->colum_nums = malloc(sizeof(int) * 255);
	while (i < 255)
	{
		map->colum_spaces[i] = 0;
		map->colum_nums[i] = 0;
		i++;
	}
}
