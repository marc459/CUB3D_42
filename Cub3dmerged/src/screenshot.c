/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/10/05 14:04:15 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int screenshot(int key, t_raycaster *rc)
{
	int x;

	x = 0;
	rc->img_ptr = mlx_new_image(rc->mlx_ptr, rc->win_x, rc->win_y);
	rc->img_data = mlx_get_data_addr(rc->img_ptr, &rc->bpp, &rc->size_line, &rc->endian);

	while (x < rc->win_x)
	{
		motionless_2(rc, x);
		motionless_3(rc);
		dda(rc);
		motionless_4(rc);
		calcule_wall(rc);
		if (rc->textured == 0)
			draw_vert_line(rc,x);
		else
		{
			floor_and_sky_draw(rc, x);
			draw_wall(rc, x);
		}
		x++;
	}
	save_bmp(rc);
	close_success(rc);
	return (0);
}
