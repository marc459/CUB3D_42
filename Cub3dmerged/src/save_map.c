/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/09/02 13:14:37 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void		loop_map(archparams_t *arch, validmap_t *map, char *line, int *x)
{
	int y;

	y = 0;
	while (line[y] == ' ' && line[y] != '\0')
		y++;
	if (line[y] == '1')
	{
		arch->worldMap[*x] = (int *)malloc(sizeof(int) * map->mapWidth);
		while (line[y] != '\0')
		{
			if (line[y] == ' ')
				arch->worldMap[*x][y] = 2;
			else if(line[y] == '0')
				arch->worldMap[*x][y] = 0;
			else if (line[y] == '1')
				arch->worldMap[*x][y] = 1;
			else if (line[y] == '2')
				arch->worldMap[*x][y] = 2;
			else
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

	x = 0;
	arch->worldMap = (int **)malloc(sizeof(int *) * map->m_line);
	fd = open(mapfile, O_RDONLY);
	while ((retorno = get_next_line(fd, &line)) == 1)
		loop_map(arch, map, line, &x);
	loop_map(arch, map, line, &x);
}
