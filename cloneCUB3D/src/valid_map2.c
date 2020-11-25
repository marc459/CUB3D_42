/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/25 14:39:07 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int		numsearch(char *line, t_validmap *map, int *i, int *count)
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
		if (line[i[0]] == '2')
		{
			map->sprite[map->numsprites].x = i[0];
			map->sprite[map->numsprites].y = map->m_line;
			map->numsprites++;
		}
		map->colum_nums[count[0]]++;
		if (line[i[0]] == '0')
			map->last_0 = i[0];
		i[0]++;
	}
	return (1);
}

int		colum_spaces(char *line, t_validmap *map, int *i, int x)
{
	int c;

	c = *i;
	*i = *i + map->colum_spaces[x] + 1;
	x = *i;
	if (c == -1)
	{
		while (c < *i)
		{
			c++;
			if (line[c] != '1' && line[c] != ' ')
				return (0);
		}
	}
	else
	{
		c = x + 1;
		while (c < *i + 1 && c > 0)
		{
			if (line[c] != '1' && line[c] != ' ' && c < (int)ft_strlen(line))
				return (0);
			c++;
		}
	}
	return (1);
}

int		check_prev_line(char *line, t_validmap *map, int *i, int count)
{
	while (line[*i] == ' ')
	{
		if (((map->prev_line[*i] != '1' && map->prev_line[*i] != ' ')
			|| (map->prev_line[*i - 1] != '1'
			&& map->prev_line[*i - 1] != ' ' && *i > 0)
			|| (map->prev_line[*i + 1] != '1'
			&& map->prev_line[*i + 1] != ' '
			&& map->prev_line[*i + 1] != '\0'))
			&& (int)ft_strlen(map->prev_line) > *i)
			return (0);
		map->colum_spaces[count]++;
		*i = *i + 1;
	}
	return (1);
}

int		no_0_afterline(char *line, t_validmap *map)
{
	int i;
	int last0;

	i = 0;
	last0 = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '0')
			last0 = i;
		i++;
	}
	if ((int)ft_strlen(map->prev_line) <= last0)
		return (0);
	return (1);
}
