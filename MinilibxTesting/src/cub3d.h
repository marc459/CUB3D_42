/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:05:26 by msantos-          #+#    #+#             */
/*   Updated: 2020/05/26 21:42:04 by msantos-         ###   ########.fr       */
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

#include "../minilibx/mlx.h"
#include "../libft/libft.h"

typedef struct	s_cub3d
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		posX;
	int		posY;
	double	posX;
	double	posY;	  //x and y start position
	
	double	dirX;
	double	dirY;		  //initial direction vector
	
	double	planeX;
	double	planeY; //the 2d raycaster version of camera plane
	
	double	time;	//time of current frame
	double	oldTime; //time of previous frame
}				t_cub3d;

#endif
