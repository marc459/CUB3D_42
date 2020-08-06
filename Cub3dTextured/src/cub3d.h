/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:05:26 by msantos-          #+#    #+#             */
/*   Updated: 2020/07/14 12:17:51 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <math.h>

#include "../minilibx/mlx.h"
#include "../libft/libft.h"
#include "map1.h"

// Initial values
//1280*620
#define WIN_X           640
#define WIN_Y           480
#define INIT_P_POS_X    22
#define INIT_P_POS_Y    12
#define INIT_P_DIR_X    -1
#define INIT_P_DIR_Y    0

#define INIT_P_PLANE_X  0
#define INIT_P_PLANE_Y  0.66
#define MV_SPEED 		0.199		//0.199
#define ROT_SPEED		0.1745		//0.1745
#define AMB_LIGHT       7

// Colors
#define WHITE           0xFFFFFF
#define RED             0xFF0000
#define GREEN           0x00FF00
#define BLUE            0x0000FF
#define BLACK           0x000000

typedef struct      s_raycaster
{
  void	          *mlx_ptr;
  void	          *win_ptr;
  double          player_pos_x;
  double          player_pos_y;
  double          player_dir_x;
  double          player_dir_y;
  double          player_plane_x;
  double          player_plane_y;
  double          ray_dir_x;
  double          ray_dir_y;
  int             map_x;
  int             map_y;
  double          side_dist_x;
  double          side_dist_y;
  double          delta_dist_x;
  double          delta_dist_y;
  int             step_x;
  int             step_y;
  int             side;
  int             draw_start;
  int             draw_end;
  double          perp_wall_dist;
} t_raycaster;


#endif
