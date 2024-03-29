/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 16:28:12 by msantos-          #+#    #+#             */
/*   Updated: 2020/02/21 20:13:36 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_intlen(const long int value)
{
	long int l;
	long int cpy;

	cpy = value;
	l = !cpy;
	while (cpy)
	{
		l++;
		cpy = cpy / 10;
	}
	return (l);
}
