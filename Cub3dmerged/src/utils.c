/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/10/19 10:44:42 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int ft_puterror(char *str)
{
	ft_putstr("Error:\n ");
	ft_putstr(str);
	ft_putstr("\n");
	return (0);
}

int		close_success(t_raycaster *rc)
{
	(void)rc;
	//mlx_destroy_window(rc->mlx_ptr, rc->win_ptr);
	exit(EXIT_SUCCESS);
	return (0);
}

int		close_failure(char *message)
{
	ft_putstr(message);
	exit(EXIT_FAILURE);
	return (1);
}

/*void ace_of_empires(int i,...)
{
va_list var_args;
va_start(var_args, str);

char *str1;
while(i > 0)
{
	str1 = va_arg ((var_args), char *);
	printf("----%s---\n",str1);
	i--;
}
	
va_end(var_args);
}*/
void multi_free(archparams_t *arch,validmap_t *map)
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
		free(arch->worldMap[x]);
		x++;
	}
	free(arch->worldMap);
}