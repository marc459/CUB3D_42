/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 05:37:19 by fvega-tr          #+#    #+#             */
/*   Updated: 2020/09/08 12:58:20 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_press(int key, t_struct *t)
{
	printf("key->%d;\n",key);
	if (key == UP || key == W)
		t->up = 1;
	if (key == DOWN || key == S)
		t->down = 1;
	if (key == RIGHT || key == D)
		t->right = 1;
	if (key == LEFT || key == A)
		t->left = 1;
	if (key == SHIFT_L || key == SHIFT_R)
		t->sprint = 1;
	if (key == ESC)
		close_success(t);
	return (0);
}

int		key_release(int key, t_struct *t)
{
	if (key == UP || key == W)
		t->up = 0;
	if (key == DOWN || key == S)
		t->down = 0;
	if (key == RIGHT || key == D)
		t->right = 0;
	if (key == LEFT || key == A)
		t->left = 0;
	if (key == SHIFT_L || key == SHIFT_R)
		t->sprint = 0;
	return (0);
}
