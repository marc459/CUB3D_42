
#include "libft/libft.h"
#include "get_next_line/get_next_line.h"

typedef		struct	mapargs_s{
	int		win_x;
	int		win_y;
	char	*NO_texture;
	char	*SO_texture;
	char	*WE_texture;
	char	*EA_texture;
	char	*S_texture;
	char	*F_color;
	char	*C_color;
}					mapargs_t;

void	initialiteflags(mapargs_t *map)
{
	map->win_x = 0;
	map->win_y = 0;
}

int		identifyresolution(char *line, mapargs_t *map)
{
	int		i;
	int		width;

	i = 1;
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		map->win_x = map->win_x * 10 + line[i] - '0';
		i++;
	}
	while (line[i] == ' ' && line[i] != '\0')
		i++;
	while (line[i] >= '0' && line[i] <= '9')
	{
		map->win_y = map->win_y * 10 + line[i] - '0';
		i++;
	}
	if (map->win_y > 0 && map->win_x > 0)
		return (0);
	else
		return (1);
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
	dest[x] = '\0';
	return (ft_strdup(dest));
}

int		map_checker(char *mapfile, mapargs_t *map)
{
	int		fd;
	char	*line;
	int		retorno;
	int		i;

	i = 0;
	if (!(fd = open(mapfile, O_RDONLY)))
	{
		ft_putstr("Error:\n Archivo corrupto\n");
		return (0);
	}
	while ((retorno = get_next_line(fd, &line)) == 1)
	{
		while (line[i] == ' ' && line[i] != '\0')
			i++;
		if (line[0] == '\0' || retorno == 0)
			free(line);
		else if (ft_strchr("RNSWESFC", line[i]))
		{
			if (ft_strchr("NSWESFC", line[i]))
			{
				if (!(ft_strncmp(line + i, "NO ", 3)))
					map->NO_texture = identifytexture(line);
				else if (!(ft_strncmp(line + i, "SO ", 3)))
					map->SO_texture = identifytexture(line);
				else if (!(ft_strncmp(line + i, "WE ", 3)))
					map->WE_texture = identifytexture(line);
				else if (!(ft_strncmp(line + i, "EA ", 3)))
					map->EA_texture = identifytexture(line);
				else if (line[i] == 'S')
					map->S_texture = identifytexture(line);
				else if (line[i] == 'F')
					map->F_color = identifytexture(line);
				else if (line[i] == 'C')
					map->C_color = identifytexture(line);
				if (identifytexture(line)[0] == '\0')
				{
					ft_putstr("Error:\n El path de texturas es incorrecto\n");
					return (0);
				}
			}
			else if (line[i] == 'R')
			{
				if (identifyresolution(line, map))
				{
					ft_putstr("Error:\n La resolución es invalida\n");
					return (0);
				}
			}
			free(line);
		}
		i = 0;
	}
	close(fd);
	return (1);
}

int		parameter_management(int count_params, char **params)
{
	int		i;

	i = 0;
	if (count_params > 3)
	{
		ft_putstr("Error:\n Demasiados parametros introducidos\n");
		return (0);
	}
	else if (count_params < 2)
	{
		ft_putstr("Error:\n Insuficientes parametros introducidos\n");
		return (0);
	}
	else
	{
		if (count_params == 3)
		{
			if (ft_strncmp(params[2], "--save", 7))
			{
				ft_putstr("Error:\n El segundo parametro es incorrecto\n");
				return (0);
			}
		}
		while (params[1][i] != '\0')
		{
			if (params[1][i] == '.')
			{
				if (!ft_strncmp(params[1] + i, ".cub", 5))
				{
					return (1);
				}
			}
			i++;
		}
		ft_putstr("Error:\n Mapa invalido, introduzca un archivo .cub existente\n");
		return (0);
	}
}

int		main(int argc, char **argv)
{
	mapargs_t	map;

	initialiteflags(&map);
	if (!parameter_management(argc, argv) || !map_checker(argv[1], &map))
		return (0);
	ft_putstr("Entra al programa\n");
	return (0);
}
