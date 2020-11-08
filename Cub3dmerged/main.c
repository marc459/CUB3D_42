/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/06 13:31:17 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/includes.h"

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
	t_archparams	arch;
	t_validmap		map;
	t_raycaster		rc;

	init_initialparams(&map);
	init_arch_params(&arch);
	if (!parameter_management(argc, argv)
	|| !arch_checker(argv[1], &arch, &map))
		return (multi_free_error(&arch, &map));
	save_map(argv[1], &arch, &map);
	if (!init_raycast_params(&rc, &arch, &map))
		return (0);
	load_textures(&rc);
	mlx_hook(rc.win_ptr, 2, 1L << 0, &key_press, &rc);
	mlx_hook(rc.win_ptr, 3, 1L << 1, &key_release, &rc);
	if (argc == 3)
		mlx_loop_hook(rc.mlx_ptr, &screenshot, &rc);
	else
		mlx_loop_hook(rc.mlx_ptr, &raycasting, &rc);
	mlx_hook(rc.win_ptr, 17, 1L << 17, close_success, &rc);
	print_params(&arch, &map);
	printf("px->%f\n",rc.player_pos_x);
	printf("py->%f\n",rc.player_pos_y);
	mlx_loop(rc.mlx_ptr);
	multi_free(&arch, &map);
	close_success(&rc);
}
