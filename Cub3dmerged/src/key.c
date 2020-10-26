/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/10/26 12:37:40 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int		key_press(int key, t_raycaster *rc)
{
	if (key == UP || key == W)
		rc->up = 1;
	if (key == DOWN || key == S)
		rc->down = 1;
	if (key == RIGHT || key == D)
		rc->right = 1;
	if (key == LEFT || key == A)
		rc->left = 1;
	if (key == ESC)
		close_success(rc);
	return (0);
}

int		key_release(int key, t_raycaster *rc)
{
	if (key == UP || key == W)
		rc->up = 0;
	if (key == DOWN || key == S)
		rc->down = 0;
	if (key == RIGHT || key == D)
		rc->right = 0;
	if (key == LEFT || key == A)
		rc->left = 0;
	return (0);
}
