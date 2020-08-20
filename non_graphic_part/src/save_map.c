/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/02/24 21:23:02 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int		valid_map(char *line, validmap_t *map)
{
	int i;
	int x;
	int count;

	i = 0;
	x = 0;
	count = 0;
	if (map->m_top == 0)
	{
		if (!check_top_map(line, map, i, count))
			return (0);
	}
	else
	{
		if (map->colum_spaces[0] > 0)
			i = -1;
		if (!sourrounding_walls(line, map, i, count) || line[0] == '\0')
			return (0);
		i = 0;
		init_map_checking_params(map);
		if (!check_map_bowels(line, map, i, count)
		|| !check_bot_map(line, map, i, count))
			return (0);
	}
	return (1);
}
