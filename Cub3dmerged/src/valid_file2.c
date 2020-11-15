/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/15 13:31:00 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

char	*identifycolor(char *line, int i)
{
	int		count;
	int		num;
	char	*str;

	str = ft_strdup("0x");
	count = 0;
	while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
		i++;
	while (line[i] != '\0' && count <= 2)
	{
		num = 0;
		while (line[i] >= '0' && line[i] <= '9')
			num = num * 10 + line[i++] - '0';
		str = ft_strjoin_b(str, ft_dectohex(num));
		if (line[i] != ',' && count <= 1)
			return (free_return_str(str));
		if (line[i] != '\0')
			i++;
		count++;
	}
	if (!identifycolor2(line, i, str, count))
		return (ft_strdup(""));
	return (str);
}

int		identifyresolution(char *line, t_archparams *arch)
{
	int		i;

	i = 1;
	while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
		i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		arch->win_x = arch->win_x * 10 + line[i] - '0';
		i++;
	}
	while ((line[i] == ' ' || line[i] == '\t') && line[i] != '\0')
		i++;
	while (line[i] >= '0' && line[i] <= '9')
		arch->win_y = arch->win_y * 10 + line[i++] - '0';
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (0);
		i++;
	}
	arch->parameters_count++;
	if (!((arch->win_y > 100 && arch->win_x > 100)
		&& (arch->win_y < 1440 && arch->win_x < 2560)))
		return (0);
	return (1);
}

char	*identifytexture(char *line, int i)
{
	int		x;
	char	*dest;

	x = 0;
	if (!(dest = (char *)malloc(sizeof(char) * (ft_strlen(line) + 1))))
		return (NULL);
	while ((line[i] != ' ' && line[i] != '\t') && line[i] != '\0')
		i++;
	while ((line[i] == '\t' || line[i] == ' ') && line[i] != '\0')
		i++;
	while ((line[i] != ' ' && line[i] != '\t') && line[i] != '\0')
		dest[x++] = line[i++];
	while (line[i] != '\0')
	{
		if (line[i] != ' ' && line[i] != '\t')
		{
			free(dest);
			return (ft_strdup(""));
		}
		i++;
	}
	dest[x] = '\0';
	return (dest);
}

int		color_checker(char *line, t_archparams *arch)
{
	int		i;
	char	*tex;

	i = 1;
	tex = identifycolor(line, i);
	if (tex[0] == '\0' && ft_strchr("FC", line[0]))
		return (free_return(tex));
	else if (line[0] == 'F' && arch->f_color[0] == '\0')
		arch->f_color = identifycolor(line, i);
	else if (line[0] == 'C' && arch->c_color[0] == '\0')
		arch->c_color = identifycolor(line, i);
	free(tex);
	return (1);
}

int		texture_checker(char *line, t_archparams *arch)
{
	int		i;
	char	*tex;

	i = 1;
	tex = identifytexture(line, i);
	if (tex[0] == '\0' && ft_strchr("NSWE", line[0]))
		return (free_return(tex));
	if (!(ft_strncmp(line, "NO", 2)) && arch->no_texture[0] == '\0')
		arch->no_texture = identifytexture(line, i);
	else if (!(ft_strncmp(line, "SO", 2)) && arch->so_texture[0] == '\0')
		arch->so_texture = identifytexture(line, i);
	else if (!(ft_strncmp(line, "WE", 2)) && arch->we_texture[0] == '\0')
		arch->we_texture = identifytexture(line, i);
	else if (!(ft_strncmp(line, "EA", 2)) && arch->ea_texture[0] == '\0')
		arch->ea_texture = identifytexture(line, i);
	else if (line[0] == 'S' && arch->s_texture[0] == '\0')
		arch->s_texture = identifytexture(line, i);
	free(tex);
	if (!color_checker(line, arch))
		return (0);
	return (1);
}
