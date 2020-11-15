/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:21:29 by fvega-tr          #+#    #+#             */
/*   Updated: 2020/11/15 13:02:01 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	load_textures_2(t_raycaster *rc)
{
	rc->tex[6].img = mlx_xpm_file_to_image(rc->mlx_ptr, "sprites/barrel.xpm",
			&rc->tex_width, &rc->tex_height);
	rc->tex[6].data = mlx_get_data_addr(rc->tex[6].img, &rc->tex[6].bpp,
			&rc->tex[6].size_l, &rc->tex[6].endian);
	rc->tex[7].img = mlx_xpm_file_to_image(rc->mlx_ptr, "sprites/light.xpm",
			&rc->tex_width, &rc->tex_height);
	rc->tex[7].data = mlx_get_data_addr(rc->tex[7].img, &rc->tex[7].bpp,
			&rc->tex[7].size_l, &rc->tex[7].endian);
}

void	load_textures(t_raycaster *rc)
{
	rc->tex[1].img = mlx_xpm_file_to_image(rc->mlx_ptr, "textures/stone.xpm",
			&rc->tex_width, &rc->tex_height);
	rc->tex[1].data = mlx_get_data_addr(rc->tex[1].img, &rc->tex[1].bpp,
			&rc->tex[1].size_l, &rc->tex[1].endian);
	rc->tex[2].img = mlx_xpm_file_to_image(rc->mlx_ptr, "textures/mossy.xpm",
			&rc->tex_width, &rc->tex_height);
	rc->tex[2].data = mlx_get_data_addr(rc->tex[2].img, &rc->tex[2].bpp,
			&rc->tex[2].size_l, &rc->tex[2].endian);
	rc->tex[3].img = mlx_xpm_file_to_image(rc->mlx_ptr, "textures/redbrick.xpm",
			&rc->tex_width, &rc->tex_height);
	rc->tex[3].data = mlx_get_data_addr(rc->tex[3].img, &rc->tex[3].bpp,
			&rc->tex[3].size_l, &rc->tex[3].endian);
	rc->tex[4].img = mlx_xpm_file_to_image(rc->mlx_ptr, "textures/wood.xpm",
			&rc->tex_width, &rc->tex_height);
	rc->tex[4].data = mlx_get_data_addr(rc->tex[4].img, &rc->tex[4].bpp,
			&rc->tex[4].size_l, &rc->tex[4].endian);
	rc->tex[5].img = mlx_xpm_file_to_image(rc->mlx_ptr, "sprites/pillar.xpm",
			&rc->tex_width, &rc->tex_height);
	rc->tex[5].data = mlx_get_data_addr(rc->tex[5].img, &rc->tex[5].bpp,
			&rc->tex[5].size_l, &rc->tex[5].endian);
	load_textures_2(rc);
}
