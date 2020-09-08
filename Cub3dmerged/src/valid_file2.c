/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/09/08 12:43:31 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

char	*identifycolor(char *line, int i)
{
	int		count;
	int		num;
	char	*str;

	str = (char*)malloc(sizeof(char) * 8);
	str = "0x";
	count = 0;
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	while (line[i] != '\0' && count <= 2)
	{
		num = 0;
		while (line[i] >= '0' && line[i] <= '9')
			num = num * 10 + line[i++] - '0';
			
		str = ft_strjoin(str, ft_dectohex(num));
		if (line[i] != ',' && count <= 1)
			return (ft_strdup(""));
		if (line[i] != '\0')
			i++;
		count++;
	}
	while (line[i] != '\0')
	{
		if (line[i++] != ' ')
			return (ft_strdup(""));
			
	}
	if (ft_strlen(str) != 8 || count != 3)
		return (ft_strdup(""));
	return (str);
}

int		identifyresolution(char *line, archparams_t *arch)
{
	int		i;

	i = 1;
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		arch->win_x = arch->win_x * 10 + line[i] - '0';
		i++;
	}
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		arch->win_y = arch->win_y * 10 + line[i] - '0';
		i++;
	}
	while (line[i] != '\0')
	{
		if(line[i++] != ' ')
			return (0);
	}
		
	arch->parameters_count++;
	if (arch->win_y > 0 && arch->win_x > 0)
		return (1);
	else
		return (0);
}

char	*identifytexture(char *line, int i)
{
	int		x;
	char	*dest;

	x = 0;
	if (!(dest = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1))))
		return (NULL);
	while (line[i] != ' ' && line[i] != '\0')
		i++;
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	while (line[i] != ' ' && line[i] != '\0')
	{
		dest[x] = line[i];
		x++;
		i++;
	}
	while (line[i] != '\0')
	{
		if (line[i++] != ' ')
			return (ft_strdup(""));
	}
	dest[x] = '\0';
	return (ft_strdup(dest));
}

int		texture_checker(char *line, archparams_t *arch)
{
	int i;

	i = 1;
	arch->parameters_count++;
	if (identifytexture(line, i)[0] == '\0' && ft_strchr("NSWE", line[0]))
		return (0);
	if (!(ft_strncmp(line, "NO ", 3)) && arch->no_texture[0] == '\0')
		arch->no_texture = identifytexture(line, i);
	else if (!(ft_strncmp(line, "SO ", 3)) && arch->so_texture[0] == '\0')
		arch->so_texture = identifytexture(line, i);
	else if (!(ft_strncmp(line, "WE ", 3)) && arch->we_texture[0] == '\0')
		arch->we_texture = identifytexture(line, i);
	else if (!(ft_strncmp(line, "EA ", 3)) && arch->ea_texture[0] == '\0')
		arch->ea_texture = identifytexture(line, i);
	else if (line[0] == 'S' && arch->s_texture[0] == '\0')
		arch->s_texture = identifytexture(line, i);
	else if (identifycolor(line, i)[0] == '\0' && ft_strchr("FC", line[0]))
		return (0);
	else if (line[0] == 'F' && arch->f_color[0] == '\0')
		arch->f_color = identifycolor(line, i);
	else if (line[0] == 'C' && arch->c_color[0] == '\0')
		arch->c_color = identifycolor(line, i);
	else
		return (0);
	return (1);
}
