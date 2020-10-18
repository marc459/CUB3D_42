/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/10/04 13:07:44 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes.h"

void	print_params(archparams_t *arch, validmap_t *map)
{
	int x;
	int y;

	x = 0;
	y = 0;
	printf("%s-------YOU ARE IN %s OPERARIVE SYSTEM-------%s\n\n", Red, SO, Color_Off);
	printf("Resolution: %d*%d\n", arch->win_x, arch->win_y);
	printf("Dimensiones: %d,%d\n", map->mapWidth,map->m_line);
	printf("no_texture: %s\n", arch->no_texture);
	printf("so_texture: %s\n", arch->so_texture);
	printf("we_texture: %s\n", arch->we_texture);
	printf("ea_texture: %s\n", arch->ea_texture);
	printf("s_texture: %s\n", arch->s_texture);
	printf("c_color: %s\n", arch->c_color);
	printf("f_color: %s\nMap:\n", arch->f_color);
	while (x < map->m_line)
	{
		while (y < map->mapWidth)
		{
			printf("%d", arch->worldMap[x][y]);
			y++;
		}
		printf("\n");
		y = 0;
		x++;
	}
	printf("\n\n");
}