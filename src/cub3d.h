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
	int		x_position;
	int		y_position;
	double	posX;
	double	posY;	  //x and y start position
	
	double	dirX;
	double	dirY;		  //initial direction vector
	
	double	planeX;
	double	planeY; //the 2d raycaster version of camera plane
	
	double	time;	//time of current frame
	double	oldTime; //time of previous frame
}				t_cub3d;

int deal_key(int key, t_cub3d *f);



/*
 Defines for the width and height of your window. I suggest you to do the same so
 you can change easily the size of your window later if needed.
*/
#define WIN_WIDTH 800
#define WIN_HEIGHT 600

/*
 Here I built a struct of the MLX image :
 It contains everything you need.
 - img_ptr to store the return value of mlx_new_image
 - data to store the return value of mlx_get_data_addr
 - the 3 other variables are pretty much useless, but you'll need
 them in the prototype of mlx_get_data_addr (see the man page for that)
 */
typedef struct s_img
{
	void *img_ptr;
	int *data; //Here you got an int * even though mlx_get_data_addr returns
			   //a char *, i'll talk more about this in the .c file.
			   //Here are the 3 "useless" variables. You can find more informations about these in the man page.
	int size_l;
	int bpp;
	int endian;
} t_img;

/*
 Here is my main struct containing every variables needed by the MLX.
 - mlx_ptr stores the return value of mlx_init
 - win stores the return value of mlx_new_window
 - img will store everything we need for the image part, the struct is described above.
 */
typedef struct s_mlx
{
	void *mlx_ptr;
	void *win;
	t_img img;
}				t_mlx;

#endif
