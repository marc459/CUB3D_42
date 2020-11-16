/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:21:29 by fvega-tr          #+#    #+#             */
/*   Updated: 2020/11/16 10:47:17 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int		load_textures_2(t_raycaster *rc)
{
	if(!(rc->tex[4].img = mlx_xpm_file_to_image(rc->mlx_ptr, rc->ea_texture,
			&rc->tex_width, &rc->tex_height)))
		return (0);
	rc->tex[4].data = mlx_get_data_addr(rc->tex[4].img, &rc->tex[4].bpp,
			&rc->tex[4].size_l, &rc->tex[4].endian);
	if(!(rc->tex[5].img = mlx_xpm_file_to_image(rc->mlx_ptr, rc->s_texture,
			&rc->tex_width, &rc->tex_height)))
		return (0);
	rc->tex[5].data = mlx_get_data_addr(rc->tex[5].img, &rc->tex[5].bpp,
			&rc->tex[5].size_l, &rc->tex[5].endian);
	return (1);
}

int		load_textures(t_raycaster *rc)
{
	if(!(rc->tex[1].img = mlx_xpm_file_to_image(rc->mlx_ptr, rc->no_texture,
			&rc->tex_width, &rc->tex_height)))
		return (0);
	rc->tex[1].data = mlx_get_data_addr(rc->tex[1].img, &rc->tex[1].bpp,
			&rc->tex[1].size_l, &rc->tex[1].endian);
	if(!(rc->tex[2].img = mlx_xpm_file_to_image(rc->mlx_ptr, rc->so_texture,
			&rc->tex_width, &rc->tex_height)))
		return (0);
	rc->tex[2].data = mlx_get_data_addr(rc->tex[2].img, &rc->tex[2].bpp,
			&rc->tex[2].size_l, &rc->tex[2].endian);
	if(!(rc->tex[3].img = mlx_xpm_file_to_image(rc->mlx_ptr, rc->we_texture,
			&rc->tex_width, &rc->tex_height)))
		return (0);
	rc->tex[3].data = mlx_get_data_addr(rc->tex[3].img, &rc->tex[3].bpp,
			&rc->tex[3].size_l, &rc->tex[3].endian);
	if(!load_textures_2(rc))
		return (0);
	return (1);
}
