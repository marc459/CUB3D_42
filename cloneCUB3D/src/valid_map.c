/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/24 14:47:41 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int		check_top_map(char *line, t_validmap *map, int i, int count)
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
				i++;
			}
			count++;
		}
		else
			return (0);
	}
	map->m_top = 1;
	return (1);
}

int		sourrounding_walls(char *line, t_validmap *map, int i, int x)
{
	while (map->colum_spaces[x] != 0 || map->colum_nums[x] != 0)
	{
		if (map->colum_spaces[x] != 0)
		{
			if (!colum_spaces(line, map, &i, x))
				return (0);
		}
		if (map->colum_nums[x] != 0)
		{
			i = i + map->colum_nums[x] - 1;
			if ((line[i] != '1' && line[i] != ' ')
				&& ((int)ft_strlen(line) > i))
				return (0);

			if (!line[map->last_0 + 1] || !line[map->last_0]
				|| line[map->last_0] == '\0' || !no_0_afterline(line, map)
				|| map->last_0 >= (int)ft_strlen(line))
				return (0);
		}
		x++;
	}
	free(map->colum_spaces);
	free(map->colum_nums);
	return (1);
}

int		check_map_bowels(char *line, t_validmap *map, int i, int count)
{
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || (line[i] >= '0' && line[i] <= '2')
		|| ft_strchr("NSEW", line[i]))
		{
			if ((line[i] == ' ' && count > 0) || line[i] == '\0')
			{
				if (line[i - 1] != '1')
					return (0);
			}
			if (!check_prev_line(line, map, &i, count))
				return (0);
			if (line[i] != '1')
				return (0);
			if (!numsearch(line, map, &i, &count))
				return (0);
			count++;
		}
		else
			return (0);
	}
	free(map->prev_line);
	return (1);
}

int		check_bot_map(char *line, t_validmap *map, int i)
{
	int bottom;

	bottom = 1;
	if (map->m_top && map->player_dir && map->m_bot == 0)
	{
		while (line[i] != '\0')
		{
			if (line[i] != ' ' && line[i] != '1')
				bottom = 0;
			i++;
		}
		if (bottom == 1)
			map->m_bot = 1;
	}
	else if (map->player_dir && map->m_bot == 1)
	{
		while (line[i] != '\0')
		{
			if (line[i] != ' ' && line[i] != '1')
				return (0);
			i++;
		}
	}
	return (1);
}

int		valid_map(char *line, t_validmap *map, int i)
{
	int c;

	i = 0;
	c = 0;
	if (map->m_top == 0)
	{
		if (!check_top_map(line, map, i, c))
			return (0);
	}
	else if (map->m_bot == 0)
	{
		if (map->colum_spaces[0] > 0)
			i = -1;
		if (!sourrounding_walls(line, map, i, c))
			return (0);
		i = 0;
		init_map_checking_params(map);
		if (!check_map_bowels(line, map, i, c) || !check_bot_map(line, map, i))
			return (0);
	}
	if ((int)ft_strlen(line) > map->map_width)
		map->map_width = ft_strlen(line);
	map->m_line++;
	map->prev_line = ft_strdup(line);
	return (1);
}
