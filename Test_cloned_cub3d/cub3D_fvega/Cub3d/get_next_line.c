/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvega-tr <fvega-tr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:20:58 by fvega-tr          #+#    #+#             */
/*   Updated: 2020/01/12 19:06:43 by fvega-tr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	dog_of_water(char **aux, char **line, int sz)
{
	char	*str;

	if (!*aux && sz == 0)
	{
		*line = ft_strdup("");
		return (0);
	}
	if ((str = ft_strchr(*aux, '\n')))
	{
		*str++ = 0;
		str = ft_strdup(str);
		*line = ft_strdup(*aux);
		free(*aux);
		*aux = str;
		return (1);
	}
	*line = *aux;
	*aux = NULL;
	return (0);
}

int			get_next_line(const int fd, char **line)
{
	int			sz;
	static char	*aux[4000];
	char		buff[10 + 1];
	char		*sjoin;

	if (fd < 0 || !line)
		return (-1);
	while ((sz = read(fd, buff, 10)) > 0)
	{
		buff[sz] = 0;
		if (!aux[fd])
			aux[fd] = ft_strdup(buff);
		else
		{
			sjoin = ft_strjoin(aux[fd], buff);
			free(aux[fd]);
			aux[fd] = sjoin;
		}
		if (ft_strchr(aux[fd], '\n'))
			break ;
	}
	if (sz < 0)
		return (-1);
	return (dog_of_water(&aux[fd], line, sz));
}
