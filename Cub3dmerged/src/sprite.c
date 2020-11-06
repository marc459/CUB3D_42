/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 13:06:20 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/06 14:34:00 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void print_sprite(t_raycaster *rc, int x)
{
	while (rc->draw_start <= rc->draw_end)
	{
		rc->tex_y = abs((((rc->draw_start * 256 - rc->win_y * 128 +
						   rc->line_height * 128) *
						  64) /
						 rc->line_height) /
						256);
		ft_memcpy(rc->img_data + 4 * rc->win_x * rc->draw_start + x * 4,
				  &rc->tex[6].data[rc->tex_y % rc->tex_height *
												rc->tex[6].size_l +
											rc->tex_x % rc->tex_width *
												rc->tex[6].bpp / 8],
				  sizeof(int));
		rc->draw_start++;
	}
}