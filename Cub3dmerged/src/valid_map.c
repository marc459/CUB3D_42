/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/10/21 12:56:24 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int		check_top_map(char *line, validmap_t *map, int i, int count)
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

int		sourrounding_walls(char *line, validmap_t *map, int i, int count)
{
	int x;
	int tmp;

	x = 0;
	tmp = 0;
	while (map->colum_spaces[x] != 0 || map->colum_nums[x] != 0)
	{
		if (map->colum_spaces[x] != 0)
		{
			tmp = i;
			count = i;
			i = i + map->colum_spaces[x] + 1;
			if (count == -1)
			{
				while (count < i)
				{
					count++;
					if (line[count] != '1' && line[count] != ' ')
						return(0);
				}
			}
			else
			{
				count = tmp + 1;
				while (count < i + 1 && count > 0)
				{
					if (line[count] != '1' && line[count] != ' ' && count < (int)ft_strlen(line))
						return (0);
					count++;
				}
			}
		}
		if (map->colum_nums[x] != 0)
		{
			count = map->last_0;
			i = i + map->colum_nums[x] - 1;
			/*if (line[i] != '1'  && line[i - 1] != '1' && line[i + 1] != '1' && line[i] != ' ' && line[i] != '\0')
				return (0);*/
			if ((line[i] != '1' && line[i] != ' ') && ((int)ft_strlen(line) > i))
				return (0);
			if(!line[map->last_0 + 1] || !line[map->last_0] || line[map->last_0] == '\0' || map->last_0 >= (int)ft_strlen(line))
				printf("%s\n",line);
		}
		x++;
	}
	return (1);
}

int		check_map_bowels(char *line, validmap_t *map, int i, int count)
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
			while (line[i] == ' ')
			{
				if (
				((map->prev_line[i] != '1' && map->prev_line[i] != ' ')
				|| (map->prev_line[i-1] != '1' && map->prev_line[i-1] != ' ' && i > 0)
				|| (map->prev_line[i+1] != '1' && map->prev_line[i+1] != ' ' &&  map->prev_line[i+1] != '\0'))
				&& (int)ft_strlen(map->prev_line) > i)
					return(0);
				map->colum_spaces[count]++;
				i++;
			}
			if (line[i] != '1')
				return (0);
			if (!numsearch(line, map, &i, &count))
				return (0);
			count++;
		}
		else
			return (0);
	}
	return (1);
}

int		check_bot_map(char *line, validmap_t *map, int i)
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

int		valid_map(char *line, validmap_t *map)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (map->m_top == 0)
	{
		if (!check_top_map(line, map, i, count))
			return (0);
	}
	else if (map->m_bot == 0)
	{
		if (map->colum_spaces[0] > 0)
			i = -1;
		if (!sourrounding_walls(line, map, i, count))
			return(0);
		i = 0;
		init_map_checking_params(map);
		if (!check_map_bowels(line, map, i, count)
		|| !check_bot_map(line, map, i))
			return(0);
	}
	if ((int)ft_strlen(line) > map->mapWidth)
		map->mapWidth = ft_strlen(line);
	map->m_line++;
	map->prev_line = ft_strdup(line);
	return (1);
}
