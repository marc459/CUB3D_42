/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/09/17 11:22:43 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes.h"

int		ft_puterror(char *str)
{
	ft_putstr("Error:\n ");
	ft_putstr(str);
	ft_putstr("\n");
	return (0);
}

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
	archparams_t	arch;
	validmap_t		map;
	t_raycaster		rc;

	map.m_top = 0;
	map.m_bot = 0;
	map.m_line = 0;
	map.mapWidth = 0;
	map.player_dir = '\0';
	init_map_checking_params(&map);
	init_arch_params(&arch);
	if (!parameter_management(argc, argv)
	|| !arch_checker(argv[1], &arch, &map))
		return (0);
	save_map(argv[1], &arch, &map);
	print_params(&arch, &map);
	printf("Entra al programa\n");
	if (!init_raycast_params(&rc, &arch, &map))
		return (0);
	//mlx_key_hook(rc.win_ptr, motionless, &rc);
	//mlx_key_hook(rc.win_ptr, raycasting, &rc);
	//mlx_loop_hook(rc.win_ptr, raycasting, &rc);
	mlx_hook(rc.win_ptr, 2, 1L << 0, &raycasting, &rc);
	mlx_hook(rc.win_ptr, 3, 1L << 1, &raycasting, &rc);
	mlx_loop(rc.mlx_ptr);

	return (0);
}
