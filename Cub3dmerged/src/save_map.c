/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/09/23 11:37:52 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void		loop_map(archparams_t *arch, validmap_t *map, char *line, int *x)
{
	int y;

	y = 0;
	while(line[y] == ' ')
		y++;
	if (line[y] == '1')
	{
		y = 0;
		arch->worldMap[*x] = (int *)malloc(sizeof(int) * map->mapWidth);
		while (line[y] != '\0')
		{
			if (line[y] == '1')
				arch->worldMap[*x][y] = 1;
			else if (line[y] == '2')
				arch->worldMap[*x][y] = 2;
			else
				arch->worldMap[*x][y] = 0;
			y++;
		}
		while(y < map->mapWidth)
		{
			arch->worldMap[*x][y] = 0;
			y++;
		}
		(*x)++;
	}
}

void		save_map(char *mapfile, archparams_t *arch, validmap_t *map)
{
	int fd;
	char *line;
	int retorno;
	int x;
	int y;

	x = 0;
	y = 0;
	if(map->m_line > map->mapWidth)
		map->mapWidth = map->m_line;
	else
		map->m_line = map->mapWidth;

	arch->worldMap = (int **)malloc(sizeof(int *) * map->m_line);
	fd = open(mapfile, O_RDONLY);
	while ((retorno = get_next_line(fd, &line)) == 1)
		loop_map(arch, map, line, &x);
	loop_map(arch, map, line, &x);
	
	while(x < map->m_line)
	{
		arch->worldMap[x] = (int *)malloc(sizeof(int) * map->mapWidth);
		while(y < map->mapWidth)
		{
			arch->worldMap[x][y] = 0;
			y++;
		}
		y=0;
		x++;
	}
	x = 0;
	y = 0;
	while(x < map->m_line)
	{
		while(y < map->mapWidth)
		{
			if (x == 0 || x == (map->m_line-1) || y == 0 || y == (map->mapWidth-1))
				arch->worldMap[x][y] = 1;
			y++;
		}
		y=0;
		x++;
	}
}
