/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
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
		while (line[i] != '\0')
		{
			if (line[i] == ' ' || line[i] == '1')
			{
				while (line[i] == ' ')
				{
					map->colum_spaces[count]++;
					i++;
				}
				while (line[i] == '1')
				{
					map->colum_nums[count]++;
					map->line_width++;
					i++;
				}
				count++;
			}
			else
				return (0);
				
		}
		map->m_top = 1;
	}
	else
	{
		if (map->colum_spaces[0] > 0)
			i = -1;
		while (map->colum_spaces[x] != 0 || map->colum_nums[x] != 0)
		{
			if (map->colum_spaces[x] != 0)
			{
				count = i;
				i = i + map->colum_spaces[x] + 1;
				while (count < i && count > 0)
				{
					if (!(line[count] == '1' || line[count] == ' '))
						return (0);
					count++;
				}
			}
			if (map->colum_nums[x] != 0)
			{
				i = i + map->colum_nums[x] - 1;
				if (!(line[i] == '1' || line[i] == ' '))
					return (0);
			}
			x++;
		}
		x = 0;
		i = 0;
		count = 0;
		init_map_checking_params(map);
		while (line[i] != '\0')
		{
			if (line[i] == ' ' || (line[i] >= '0' && line[i] <= '2')
			|| ft_strchr("NSEW", line[i]))
			{
				if (line[i] == ' ' && count > 0)
				{
					if (line[i - 1] != '1')
						return (0);
				}
				while (line[i] == ' ')
				{
					map->colum_spaces[count]++;
					i++;
				}
				if (line[i] != '1')
					return (0);
				while (((line[i] >= '0' && line[i] <= '2')
				|| ft_strchr("NSEW", line[i])) && line[i] != '\0')
				{
					if (ft_strchr("NSEW", line[i]) && map->player_letter == '\0')
						map->player_letter = line[i];
					else if (ft_strchr("NSEW", line[i]) && map->player_letter)
						return (0);
					map->colum_nums[count]++;
					map->line_width++;
					i++;
				}
				count++;
			}
			else
				return (0);
		}
	}
	return (1);
}
