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

void		save_map(char *line, validmap_t *map, archparams_t *arch, int i)
{
	arch->worldMap[map->m_line] = (int*)malloc(sizeof(int) * ft_strlen(line));
	while (line[i] != '\0')
	{
		if (line[i] == ' ' || line[i] == '0')
			arch->worldMap[map->m_line][i] = 0;
		else if (line[i] == '1')
			arch->worldMap[map->m_line][i] = 1;
		else if (line[i] == '2')
			arch->worldMap[map->m_line][i] = 2;
		else if (ft_strchr("NSWE", line[i]))
			arch->worldMap[map->m_line][i] = 3;
		i++;
	}
}
