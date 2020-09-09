/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:05:26 by msantos-          #+#    #+#             */
/*   Updated: 2020/09/09 13:42:21 by msantos-         ###   ########.fr       */
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

#define SCREENWIDTH 2640
#define NUMSPRITES 10

typedef struct s_images
{
	void *img;
	char *data;
	int bpp;
	int sizeline;
	int endian;
} t_images;

typedef struct	s_cub3d
{
	void	*mlx_ptr;
	void	*win_ptr;
	double	posX;
	double	posY;	  //x and y start position
	t_images tex[12];

	double	dirX;
	double	dirY;		  //initial direction vector
	
	double	planeX;
	double	planeY; //the 2d raycaster version of camera plane
	
	double	time;	//time of current frame
	double	oldTime; //time of previous frame
}				t_cub3d;

typedef struct s_sprites
{
	double x;
	double y;
	t_images tex;
} t_sprites;

typedef struct s_struct
{
	void *mlx_ptr;
	void *win_ptr;
	int win_width;
	int win_height;
	int map_width;
	int map_height;
	int tex_width;
	int tex_height;
	int map[1000][1000];
	char *map_file;
	int initial_pos;
	double posx;
	double posy;
	double dirx;
	double diry;
	double planex;
	double planey;
	double camerax;
	double raydirx;
	double raydiry;
	int mapx;
	int mapy;
	double sidedistx;
	double sidedisty;
	double deltadistx;
	double deltadisty;
	double perpwalldist;
	int stepx;
	int stepy;
	int hit;
	int side;
	int lineheight;
	int drawstart;
	int drawend;
	unsigned int color;
	unsigned int ceiling_color;
	unsigned int floor_color;
	double movespeed;
	double rotspeed;
	double olddirx;
	double oldplanex;
	int up;
	int down;
	int right;
	int left;
	int sprint;
	int textnum;
	double wallx;
	void *img_ptr;
	char *img_data;
	int bpp;
	int size_line;
	int endian;
	int *xpmw;
	int *xpmh;
	t_images tex[12];
	int tex_id;
	int tex_x;
	int tex_y;
	int tex_side;
	double floorxwall;
	double floorywall;
	double distwall;
	double distplayer;
	double currentdist;
	double weight;
	double currentfloorx;
	double currentfloory;
	int floortexx;
	int floortexy;
	t_sprites sprite[10];
	double spr_buffer[SCREENWIDTH];
	int spr_order[10];
	double spr_dist[10];
	int sprtexx;
	int sprtexy;
	double spritex;
	double spritey;
	double invdet;
	double transformx;
	double transformy;
	int spritescreenx;
	int spriteheight;
	int drawstarty;
	int drawendy;
	int spritewidth;
	int drawstartx;
	int drawendx;
	int stripe;
	int d;
	double enem_stepx;
	double enem_stepy;
	double life_bar;
	int test;
	int test2;
} t_struct;

#endif
