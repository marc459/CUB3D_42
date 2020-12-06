/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/28 12:00:53 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int		key_press(int key, t_raycaster *rc)
{
	if (key == UP || key == W)
		rc->up = 1;
	else if (key == DOWN || key == S)
		rc->down = 1;
	else if (key == RIGHT)
		rc->rot_right = 1;
	else if (key == D)
		rc->right = 1;
	else if (key == LEFT)
		rc->rot_left = 1;
	else if (key == A)
		rc->left = 1;
	else if (key == ESC)
		close_success(rc);
	return (0);
}

int		key_release(int key, t_raycaster *rc)
{
	if (key == UP || key == W)
		rc->up = 0;
	else if (key == DOWN || key == S)
		rc->down = 0;
	else if (key == RIGHT)
		rc->rot_right = 0;
	else if (key == D)
		rc->right = 0;
	else if (key == LEFT)
		rc->rot_left = 0;
	else if (key == A)
		rc->left = 0;
	return (0);
}
