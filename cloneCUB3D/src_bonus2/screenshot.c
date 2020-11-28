/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/28 13:05:57 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int		screenshot(t_raycaster *rc)
{
	int x;

	x = 0;
	handle_events(rc);
	rc->img_ptr = mlx_new_image(rc->mlx_ptr, rc->win_x, rc->win_y);
	rc->img_data = mlx_get_data_addr(rc->img_ptr,
					&rc->bpp, &rc->size_line, &rc->endian);
	while (x < rc->win_x)
	{
		motionless_2(rc, x);
		motionless_3(rc);
		dda(rc);
		motionless_4(rc);
		calcule_wall(rc);
		floor_and_sky_draw(rc, x);
		draw_wall(rc, x);
		rc->spr_buffer[x] = rc->perp_wall_dist;
		x++;
	}
	sprite_casting(rc);
	mlx_put_image_to_window(rc->mlx_ptr, rc->win_ptr,
							rc->img_ptr, 0, 0);
	save_bmp(rc);
	return (0);
}
