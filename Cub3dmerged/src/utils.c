/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/10/28 13:51:11 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

char	*ft_strjoin_b(char *s1, char *s2)
{
	char	*str;
	int		cont1;
	int		cont2;

	cont1 = 0;
	cont2 = 0;
	if (!s1)
		return (NULL);
	if (!(str = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	while (s1[cont1] != '\0')
	{
		str[cont1] = s1[cont1];
		cont1++;
	}
	while (s2[cont2] != '\0')
	{
		str[cont1] = s2[cont2];
		cont2++;
		cont1++;
	}
	str[cont1] = '\0';
	free(s1);
	free(s2);
	return (str);
}

int		ft_puterror(char *str)
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

int		free_return(char *str)
{
	free(str);
	return (0);
}

void	multi_free(archparams_t *arch, validmap_t *map)
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

void	multi_free_error(archparams_t *arch, validmap_t *map)
{
	free(map->colum_nums);
	free(map->colum_spaces);
	if (map->prev_line[0] != '\0')
		free(map->prev_line);
	if (arch->no_texture[0] != '\0')
		free(arch->no_texture);
	if (arch->so_texture[0] != '\0')
		free(arch->so_texture);
	if (arch->we_texture[0] != '\0')
		free(arch->we_texture);
	if (arch->ea_texture[0] != '\0')
		free(arch->ea_texture);
	if (arch->s_texture[0] != '\0')
		free(arch->s_texture);
	if (arch->f_color[0] != '\0')
		free(arch->f_color);
	if (arch->c_color[0] != '\0')
		free(arch->c_color);
}
