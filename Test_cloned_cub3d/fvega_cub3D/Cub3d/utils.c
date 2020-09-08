/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvega-tr <fvega-tr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 16:59:57 by fvega-tr          #+#    #+#             */
/*   Updated: 2020/01/13 17:00:01 by fvega-tr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*sd;
	const char	*ss;

	if (src == NULL && dst == NULL)
		return (NULL);
	sd = dst;
	ss = src;
	i = 0;
	while (i < n)
	{
		*sd = *ss;
		sd++;
		ss++;
		src++;
		i++;
	}
	return (dst);
}

void	ft_putstr(char *s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(1, &s[i], 1);
			i++;
		}
	}
}

char	*ft_delete_spaces(char *str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (str[i])
		i++;
	if (!(s = malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			i++;
		else
			s[j++] = str[i++];
	}
	s[j] = '\0';
	return (s);
}
