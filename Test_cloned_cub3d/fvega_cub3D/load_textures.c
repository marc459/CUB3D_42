/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:21:29 by fvega-tr          #+#    #+#             */
/*   Updated: 2020/09/14 11:55:06 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_textures_2(t_struct *t)
{
	t->tex[6].img = mlx_xpm_file_to_image(t->mlx_ptr, "sprites/barrel.xpm",
			&t->tex_width, &t->tex_height);
	t->tex[6].data = mlx_get_data_addr(t->tex[6].img, &t->tex[6].bpp,
			&t->tex[6].sizeline, &t->tex[6].endian);
	t->tex[7].img = mlx_xpm_file_to_image(t->mlx_ptr, "sprites/light.xpm",
			&t->tex_width, &t->tex_height);
	t->tex[7].data = mlx_get_data_addr(t->tex[7].img, &t->tex[7].bpp,
			&t->tex[7].sizeline, &t->tex[7].endian);
	t->tex[8].img = mlx_xpm_file_to_image(t->mlx_ptr, "sprites/ghostred.xpm",
			&t->tex_width, &t->tex_height);
	t->tex[8].data = mlx_get_data_addr(t->tex[8].img, &t->tex[8].bpp,
			&t->tex[8].sizeline, &t->tex[8].endian);
	t->tex[9].img = mlx_xpm_file_to_image(t->mlx_ptr, "sprites/destruction.xpm",
			&t->tex_width, &t->tex_height);
	t->tex[9].data = mlx_get_data_addr(t->tex[9].img, &t->tex[9].bpp,
			&t->tex[9].sizeline, &t->tex[9].endian);
	t->tex[10].img = mlx_xpm_file_to_image(t->mlx_ptr, "sprites/dead.xpm",
			&t->tex_width, &t->tex_height);
	t->tex[10].data = mlx_get_data_addr(t->tex[10].img, &t->tex[10].bpp,
			&t->tex[10].sizeline, &t->tex[10].endian);
}

void		load_textures(t_struct *t)
{
	t->tex[1].img = mlx_xpm_file_to_image(t->mlx_ptr, "textures/stone.xpm",
			&t->tex_width, &t->tex_height);
	t->tex[1].data = mlx_get_data_addr(t->tex[1].img, &t->tex[1].bpp,
			&t->tex[1].sizeline, &t->tex[1].endian);
	t->tex[2].img = mlx_xpm_file_to_image(t->mlx_ptr, "textures/mossy.xpm",
			&t->tex_width, &t->tex_height);
	t->tex[2].data = mlx_get_data_addr(t->tex[2].img, &t->tex[2].bpp,
			&t->tex[2].sizeline, &t->tex[2].endian);
	t->tex[3].img = mlx_xpm_file_to_image(t->mlx_ptr, "textures/redbrick.xpm",
			&t->tex_width, &t->tex_height);
	t->tex[3].data = mlx_get_data_addr(t->tex[3].img, &t->tex[3].bpp,
			&t->tex[3].sizeline, &t->tex[3].endian);
	t->tex[4].img = mlx_xpm_file_to_image(t->mlx_ptr, "textures/wood.xpm",
			&t->tex_width, &t->tex_height);
	t->tex[4].data = mlx_get_data_addr(t->tex[4].img, &t->tex[4].bpp,
			&t->tex[4].sizeline, &t->tex[4].endian);
	t->tex[5].img = mlx_xpm_file_to_image(t->mlx_ptr, "sprites/pillar.xpm",
			&t->tex_width, &t->tex_height);
	t->tex[5].data = mlx_get_data_addr(t->tex[5].img, &t->tex[5].bpp,
			&t->tex[5].sizeline, &t->tex[5].endian);
	load_textures_2(t);
}
