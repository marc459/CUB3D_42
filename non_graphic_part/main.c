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

int		ft_puterror(char *str)
{
	ft_putstr("Error:\n ");
	ft_putstr(str);
	ft_putstr("\n");
	return (0);
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

	map.m_top = 0;
	map.player_dir = '\0';
	init_map_checking_params(&map);
	init_arch_params(&arch);
	if (!parameter_management(argc, argv)
	|| !arch_checker(argv[1], &arch, &map))
		return (0);
	printf("Entra al programa\n");
	return (0);
}
