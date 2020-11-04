/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/04 13:52:15 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	multi_free(t_archparams *arch, t_validmap *map)
{
	int x;

	x = 0;
	free(arch->f_color);
	free(arch->c_color);
	free(arch->s_texture);
	free(arch->no_texture);
	free(arch->so_texture);
	free(arch->we_texture);
	free(arch->ea_texture);
	free(map->prev_line);
	free(map->colum_spaces);
	free(map->colum_nums);
	while (x < map->m_line)
	{
		free(arch->world_map[x]);
		x++;
	}
	free(arch->world_map);
}

int		multi_free_error(t_archparams *arch, t_validmap *map)
{
	free(map->colum_nums);
	free(map->colum_spaces);
	if (map->prev_line[0] != '\0')
		free(map->prev_line);
	if (arch->no_texture[0] != '\0')
		free(arch->no_texture);
	if (arch->so_texture[0] != '\0')
		free(arch->so_texture);
	if (arch->we_texture[0] != '\0')
		free(arch->we_texture);
	if (arch->ea_texture[0] != '\0')
		free(arch->ea_texture);
	if (arch->s_texture[0] != '\0')
		free(arch->s_texture);
	if (arch->f_color[0] != '\0')
		free(arch->f_color);
	if (arch->c_color[0] != '\0')
		free(arch->c_color);
	return (0);
}

char	*free_return_str(char *str)
{
	free(str);
	return (ft_strdup(""));
}

int		identifycolor2(char *line, int i, char *str, int count)
{
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			free(str);
			return (0);
		}
		i++;
	}
	if (ft_strlen(str) != 8 || count != 3)
	{
		free(str);
		return (0);
	}
	return (1);
}
