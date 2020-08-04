/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:25:39 by msantos-          #+#    #+#             */
/*   Updated: 2019/11/21 15:52:01 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
	return (str);
}
