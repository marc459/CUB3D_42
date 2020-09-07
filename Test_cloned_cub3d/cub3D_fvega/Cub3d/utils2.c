/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvega-tr <fvega-tr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 19:22:43 by fvega-tr          #+#    #+#             */
/*   Updated: 2020/01/13 20:31:22 by fvega-tr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	ft_size(unsigned int un)
{
	unsigned int size;

	size = 1;
	while (un > 9)
	{
		un /= 10;
		size++;
	}
	return (size);
}

char		*ft_itoa(int n)
{
	char			*str;
	unsigned int	un;
	unsigned int	i;
	unsigned int	size;

	if (n < 0)
		un = (unsigned int)(n * -1);
	else
		un = (unsigned int)n;
	size = ft_size(un);
	if (!(str = (char*)malloc(sizeof(char) * (size + 1 + (n < 0 ? 1 : 0)))))
		return (NULL);
	i = 0;
	if (n < 0 && (str[i] = '-'))
		size++;
	i = size - 1;
	while (un >= 10)
	{
		str[i--] = (char)(un % 10 + '0');
		un /= 10;
	}
	str[i] = (char)(un % 10 + '0');
	str[size] = 0;
	return (str);
}

int			ft_atoi(const char *str)
{
	int		num;
	int		i;
	int		neg;

	neg = 1;
	i = 0;
	num = 0;
	while (((str[i] > 8) && (str[i] < 14)) || (str[i] == 32))
		i++;
	if ((str[i] == 43) || (str[i] == 45))
	{
		if (str[i] == 45)
			neg *= -1;
		i++;
	}
	while (str[i] > 47 && str[i] < 58)
	{
		num = num * 10 + str[i] - 48;
		i++;
	}
	return (num * neg);
}

int			ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	int				num;

	num = 0;
	i = 0;
	while ((s1[i] != '\0') && (s2[i] != '\0') && (num == 0 && i < n))
	{
		num += (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	if (num == 0 && i < n)
	{
		num = (unsigned char)s1[i] - (unsigned char)s2[i];
	}
	return (num);
}
