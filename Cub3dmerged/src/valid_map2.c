/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/09/01 12:50:44 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int		numsearch(char *line, validmap_t *map, int *i, int *count)
{
	while (((line[i[0]] >= '0' && line[i[0]] <= '2')
	|| ft_strchr("NSEW", line[i[0]])) && line[i[0]] != '\0')
	{
		if (ft_strchr("NSEW", line[i[0]]) && map->player_dir == '\0')
		{
			map->player_dir = line[i[0]];
			map->init_p_pos_x = i[0];
			map->init_p_pos_y = map->m_line;
		}
		else if (ft_strchr("NSEW", line[i[0]]) && map->player_dir)
			return (0);
		map->colum_nums[count[0]]++;
		i[0]++;
	}
	return (1);
}
