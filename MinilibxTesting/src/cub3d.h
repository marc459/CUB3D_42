/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:05:26 by msantos-          #+#    #+#             */
/*   Updated: 2020/09/29 11:10:45 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <math.h>

#include "../minilibx_linux/mlx.h"
#include "../libft/libft.h"

#define SCREENWIDTH 2640
#define NUMSPRITES 10

typedef struct s_images
{
	void *img;
	int *data;
	int bpp;
	int sizeline;
	int endian;
}				t_images;

typedef struct s_cub3d
{
	void *mlx_ptr;
	void *win_ptr;
	int win_width;
	int win_height;
	int tex_width;
	int tex_height;
	void *img_ptr;
	int *img_data;
	int bpp;
	int size_line;
	int endian;
	t_images tex[12];
} t_cub3d;

#endif
