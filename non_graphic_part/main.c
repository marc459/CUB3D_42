/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/02/24 21:23:02 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes.h"

void	init_arch_params(archparams_t *arch)
{
	arch->parameters_count = 0;
	arch->win_x = 0;
	arch->win_y = 0;
	arch->no_texture = "";
	arch->so_texture = "";
	arch->we_texture = "";
	arch->ea_texture = "";
	arch->s_texture = "";
	arch->f_color = "";
	arch->c_color = "";
}

void	init_map_checking_params(validmap_t	*map)
{
	int i;

	i = 0;
	map->m_down = 0;
	map->line_width = 0;
	map->player_letter = '\0';
	map->colum_spaces = malloc(sizeof(int) * 255);
	map->colum_nums = malloc(sizeof(int) * 255);
	while(i < 255)
	{
		map->colum_spaces[i] = 0;
		map->colum_nums[i] = 0;
		i++;
	}

}

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
	if(line[i] != '\0')
		return (ft_strdup(""));
	dest[x] = '\0';
	return (ft_strdup(dest));
}

int		texture_checker(char *line, archparams_t *arch)
{
	arch->parameters_count++;
	if (!(ft_strncmp(line, "NO ", 3)) && arch->no_texture == "")
		arch->no_texture = identifytexture(line);
	else if (!(ft_strncmp(line, "SO ", 3)) && arch->so_texture == "")
		arch->so_texture = identifytexture(line);
	else if (!(ft_strncmp(line, "WE ", 3)) && arch->we_texture == "")
		arch->we_texture = identifytexture(line);
	else if (!(ft_strncmp(line, "EA ", 3)) && arch->ea_texture == "")
		arch->ea_texture = identifytexture(line);
	else if (line[0] == 'S' && arch->s_texture == "")
		arch->s_texture = identifytexture(line);
	else if (line[0] == 'F' && arch->f_color == "")
		arch->f_color = identifytexture(line);
	else if (line[0] == 'C' && arch->c_color == "")
		arch->c_color = identifytexture(line);
	else
	{
		printf("line->%s\n",line);
		return (0);
	}
		
	return (1);
}

int		ft_puterror(char *str)
{
	ft_putstr("Error:\n ");
	ft_putstr(str);
	ft_putstr("\n");
	return (0);
}

int		arch_checker(char *mapfile, archparams_t *arch, validmap_t *map)
{
	int		fd;
	char	*line;
	int		retorno;
	int		i;

	i = 0;
	if (!(fd = open(mapfile, O_RDONLY)))
		return (ft_puterror("Archivo corrupto"));
	while ((retorno = get_next_line(fd, &line)) == 1)
	{
		//printf("line -> <%s> ",line);
		while (line[i] == ' ' && line[i] != '\0')
			i++;
		if (line[0] == '\0' || retorno == 0)
			i = 0;
		else if (ft_strchr("NSWESFC", line[i]))
		{
			if(texture_checker(line + i, arch) == 0)
				return (ft_puterror("Algun parametro ha sido duplicado"));
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
			if(arch->parameters_count != 7)
				return (ft_puterror("Faltan parametros antes de recorrer el mapa"));
			if (!valid_map(line, map))
				return (ft_puterror("El mapa es invalido"));
		}
		else if(!ft_strchr("NSWESFC1", line[i]))
			return (ft_puterror("Caracter incorrecto en el archivo"));
		i = 0;
		free(line);
	}
	if(arch->parameters_count != 7)
			return (ft_puterror("Faltan parametros en el archivo"));
	close(fd);
	return (1);
}

int		parameter_management(int count_params, char **params)
{
	int		i;

	i = 0;
	if (count_params > 3)
		return (ft_puterror("Demasiados parametros introducidos"));
	else if (count_params < 2)
		return (ft_puterror("Insuficientes parametros introducidos"));
	else
	{
		if (count_params == 3)
		{
			if (ft_strncmp(params[2], "--save", 7))
				return (ft_puterror("El segundo parametro es incorrecto"));
		}
		while (params[1][i] != '\0')
		{
			if (params[1][i] == '.')
			{
				if (!ft_strncmp(params[1] + i, ".cub", 5))
					return (1);
			}
			i++;
		}
		return (ft_puterror("Introduzca un archivo .cub existente valido"));
	}
}

int		main(int argc, char **argv)
{
	//mapa vacio,faltan elementos, tabuladores
	archparams_t arch;
	validmap_t	map;

	map.m_top = 0;
	init_map_checking_params(&map);
	init_arch_params(&arch);
	if (!parameter_management(argc, argv) || !arch_checker(argv[1], &arch, &map))
		return (0);
	printf("Entra al programa\n");
	return (0);
}
