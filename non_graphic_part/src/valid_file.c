/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/02/24 21:23:02 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int		identifyresolution(char *line, archparams_t *arch)
{
	int		i;
	int		width;

	i = 1;
	while (line[i] != ' ' && line[i] != '\0')
		i++;
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
	arch->parameters_count++;
	if (arch->win_y > 0 && arch->win_x > 0)
		return (1);
	else
		return (0);
}

char	*identifytexture(char *line)
{
	int		i;
	int		x;
	char	*dest;

	x = 0;
	i = 0;
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
	if (line[i] != '\0')
		return (ft_strdup(""));
	dest[x] = '\0';
	return (ft_strdup(dest));
}

int		texture_checker(char *line, archparams_t *arch)
{
	arch->parameters_count++;
	if (!(ft_strncmp(line, "NO ", 3)) && arch->no_texture[0] == '\0')
		arch->no_texture = identifytexture(line);
	else if (!(ft_strncmp(line, "SO ", 3)) && arch->so_texture[0] == '\0')
		arch->so_texture = identifytexture(line);
	else if (!(ft_strncmp(line, "WE ", 3)) && arch->we_texture[0] == '\0')
		arch->we_texture = identifytexture(line);
	else if (!(ft_strncmp(line, "EA ", 3)) && arch->ea_texture[0] == '\0')
		arch->ea_texture = identifytexture(line);
	else if (line[0] == 'S' && arch->s_texture[0] == '\0')
		arch->s_texture = identifytexture(line);
	else if (line[0] == 'F' && arch->f_color[0] == '\0')
		arch->f_color = identifytexture(line);
	else if (line[0] == 'C' && arch->c_color[0] == '\0')
		arch->c_color = identifytexture(line);
	else
		return (0);
	return (1);
}

int		param_sorting(archparams_t *arch, validmap_t *map, char *line, int i)
{
	if (line[i] == '\0')
		i = 0;
	else if (ft_strchr("NSWESFC", line[i]))
	{
		if (texture_checker(line + i, arch) == 0)
			return (ft_puterror("Error en el nombre de los parametros"));
		if (identifytexture(line)[0] == '\0')
			return (ft_puterror("El path de texturas es incorrecto"));
	}
	else if (line[i] == 'R')
	{
		if (!identifyresolution(line, arch))
			return (ft_puterror("La resolución es invalida"));
	}
	else if (line[i] == '1')
	{
		if (arch->parameters_count != 8)
			return (ft_puterror("Faltan parametros para recorrer el mapa"));
		if (!valid_map(line, map))
			return (ft_puterror("El mapa es invalido"));
	}
	else if (!ft_strchr("NSWESFC1", line[i]))
		return (ft_puterror("Caracter incorrecto en el archivo"));
	return (1);
}

int		arch_checker(char *mapfile, archparams_t *arch, validmap_t *map)
{
	int		fd;
	char	*line;
	int		retorno;
	int		i;

	i = 0;
	if (!(fd = open(mapfile, O_RDONLY)))
		return (ft_puterror("Error al abrir el archivo"));
	while ((retorno = get_next_line(fd, &line)) == 1)
	{
		while (line[i] == ' ' && line[i] != '\0')
			i++;
		if (map->m_top == 1 && line[0] == '\0')
			return (ft_puterror("El mapa es invalido"));
		if (!param_sorting(arch, map, line, i))
			return (0);
		i = 0;
		free(line);
	}
	if (arch->parameters_count != 8)
		return (ft_puterror("Faltan parametros en el archivo"));
	if (!map->player_dir)
		return (ft_puterror("Mapa invalido,falta la posicion del jugador"));
	close(fd);
	return (1);
}
