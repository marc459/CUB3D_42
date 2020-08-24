/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:55:11 by msantos-          #+#    #+#             */
/*   Updated: 2019/12/10 18:56:57 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_dectohex(long long num)
{
	int		rem;
	int		i;
	char	hex[100];

	rem = 0;
	i = 0;
	if (num == 0)
	{
		hex[0] = '0';
		hex[1] = '0';
		i = i + 2;
	}
	while (num > 0)
	{
		rem = num % 16;
		hex[i] = rem < 10 ? (char)rem + 48 : (char)rem + 55;
		num /= 16;
		i++;
	}
	hex[i] = '\0';
	return (ft_strdup(ft_strrev(hex)));
}