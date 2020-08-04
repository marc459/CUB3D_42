/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:41:04 by msantos-          #+#    #+#             */
/*   Updated: 2020/01/30 17:54:34 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	long	i;

	nb = n;
	i = ft_len(nb);
	if (n == 0)
		return (ft_strdup("0"));
	if (!(str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (nb == 0)
		return (str);
	if (nb < 0)
		nb = nb * -1;
	str[i] = '\0';
	i--;
	while (i >= 0)
	{
		str[i] = 48 + (nb % 10);
		nb = nb / 10;
		i--;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}
