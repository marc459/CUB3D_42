/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_params2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 14:00:16 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/14 14:40:34 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

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

void	reset_raycasting_params(t_raycaster *rc)
{
	rc->movespeed = 0.200;
	rc->win_x = rc->tmpx;
	rc->win_y = rc->tmpy;
}
