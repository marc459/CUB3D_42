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

void ace_of_empires(char *str,...)
{
va_list var_args;
 va_start(var_args, str);
 int i;

 i = 0;
char *str1;
while(i < (int)var_args)
{
	str1 = va_arg ((var_args), char *);
	printf("----%s---\n",str1);
	i++;
}
va_end(var_args);
}