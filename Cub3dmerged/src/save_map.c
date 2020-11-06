/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/06 14:38:01 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	loop_map(t_archparams *arch, t_validmap *map, char *line, int *x)
{
	int y;

	y = 0;
	while (line[y] == ' ')
		y++;
	if (line[y] == '1')
	{
		y = 0;
		arch->world_map[*x] = (int *)malloc(sizeof(int) * map->map_width);
		while (line[y] != '\0')
		{
			if (line[y] == '1')
				arch->world_map[*x][y] = 1;
			else if (line[y] == '2')
				arch->world_map[*x][y] = 2;
			else
				arch->world_map[*x][y] = 0;
			y++;
		}
		while (y < map->map_width)
			arch->world_map[*x][y++] = 0;
		(*x)++;
	}
	free(line);
}

void	save_map2(t_archparams *arch, t_validmap *map, int x, int y)
{
	while (x < map->m_line)
	{
		arch->world_map[x] = (int *)malloc(sizeof(int) * map->map_width);
		while (y < map->map_width)
		{
			arch->world_map[x][y] = 0;
			y++;
		}
		y = 0;
		x++;
	}
	x = 0;
	y = 0;
	while (x < map->m_line)
	{
		while (y < map->map_width)
		{
			if (x == 0 || x == (map->m_line - 1)
				|| y == 0 || y == (map->map_width - 1))
				arch->world_map[x][y] = 1;
			y++;
		}
		y = 0;
		x++;
	}
}

void	save_map(char *mapfile, t_archparams *arch, t_validmap *map)
{
	int		fd;
	char	*line;
	int		retorno;
	int		x;
	int		y;

	x = 0;
	y = 0;
	if (map->m_line > map->map_width)
		map->map_width = map->m_line;
	else
		map->m_line = map->map_width;
	arch->world_map = (int **)malloc(sizeof(int *) * map->m_line);
	fd = open(mapfile, O_RDONLY);
	while ((retorno = get_next_line(fd, &line)) == 1)
		loop_map(arch, map, line, &x);
	loop_map(arch, map, line, &x);
	save_map2(arch, map, x, y);
}
