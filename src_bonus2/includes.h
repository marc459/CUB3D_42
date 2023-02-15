/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:21:32 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/28 13:05:33 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <strings.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include "../bash_prompt.h"

# if defined(__APPLE__)
#  include "key_macos.h"
#  include "../minilibx/mlx.h"
#  define SO "MACOS"
# else
#  include "key_linux.h"
#  include "../minilibx_linux/mlx.h"
#  define SO "LINUX"
# endif

# define INIT_P_PLANE_X 0
# define INIT_P_PLANE_Y 0.66
# define MV_SPEED 0.200
# define ROT_SPEED 0.1345
# define AMB_LIGHT 7

# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GREEN 0x00FF00
# define BLUE 0x0000FF
# define BLUESKY 0X9DF6FF
# define BROWN 0xB8761C
# define BLACK 0x000000

typedef struct		s_bitmap
{
	unsigned int	filesize;
	unsigned short	reserved1;
	unsigned short	reserved2;
	unsigned int	pixeldataoffset;
	unsigned int	headersize;
	unsigned int	imagewidth;
	unsigned int	imageheight;
	unsigned short	planes;
	unsigned short	bitsperpixel;
	unsigned int	compression;
	unsigned int	imagesize;
	unsigned int	xpixelspermeter;
	unsigned int	ypixelspermeter;
	unsigned int	totalcolors;
	unsigned int	importantcolors;
}					t_bitmap;

typedef struct		s_img
{
	void			*img;
	char			*data;
	int				size_l;
	int				bpp;
	int				endian;
}					t_img;

typedef struct		s_sprites
{
	double			x;
	double			y;
	double			distance;
	double			sprite_x;
	double			sprite_y;
	double			invdet;
	double			transform_x;
	double			transform_y;
	int				screen;
	int				height;
	int				width;
	int				drawstart_x;
	int				drawstart_y;
	int				drawend_x;
	int				drawend_y;
	int				stripe;
	t_img			tex;
}					t_sprites;

typedef struct		s_raycaster
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_data;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	char			*s_texture;
	int				f_color;
	int				c_color;
	int				line_height;
	int				bpp;
	int				size_line;
	int				endian;
	int				tex_height;
	int				tex_width;
	double			wall_x;
	int				tex_x;
	int				tex_y;
	t_img			tex[12];
	int				win_x;
	int				win_y;
	int				**world_map;
	double			player_pos_x;
	double			player_pos_y;
	double			player_dir_x;
	double			player_dir_y;
	double			player_plane_x;
	double			player_plane_y;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_width;
	int				map_height;
	int				map_x;
	int				map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int				step_x;
	int				step_y;
	int				side;
	int				draw_start;
	int				draw_end;
	double			perp_wall_dist;
	int				up;
	int				down;
	int				right;
	int				rot_right;
	int				rot_left;
	int				left;
	int				textured;
	int				crouch;
	int				sprint;
	double			camerax;
	double			dirx;
	double			diry;
	int				stepx;
	int				stepy;
	int				hit;
	double			wallx;
	double			movespeed;
	int				tex_id;
	int				tex_side;
	double			floorxwall;
	double			floorywall;
	double			currentdist;
	double			currentfloorx;
	double			currentfloory;
	double			weight;
	int				floortexx;
	int				floortexy;
	int				save_bmp;
	int				numsprites;
	t_sprites		sprite[255];
	double			spritex;
	double			spritey;
	int				sprtexx;
	int				sprtexy;
	double			invdet;
	double			transformx;
	double			transformy;
	int				spritescreenx;
	int				spriteheight;
	int				drawstarty;
	int				drawendy;
	int				spritewidth;
	int				drawstartx;
	int				drawendx;
	int				stripe;
	int				d;
	double			*spr_buffer;
	double			enem_stepx;
	double			enem_stepy;
	int				i;
	int				steps;
	int				tmpx;
	int				tmpy;
}					t_raycaster;

typedef struct		s_archparams
{
	int				win_x;
	int				win_y;
	char			*no_texture;
	char			*so_texture;
	char			*we_texture;
	char			*ea_texture;
	char			*s_texture;
	char			*f_color;
	char			*c_color;
	int				**world_map;
	int				parameters_count;
}					t_archparams;

typedef struct		s_validmap
{
	int				m_top;
	int				m_bot;
	int				map_width;
	char			**map;
	int				*colum_spaces;
	int				*colum_nums;
	int				m_line;
	char			player_dir;
	int				init_p_pos_x;
	int				init_p_pos_y;
	int				last_0;
	char			*prev_line;
	t_sprites		sprite[255];
	int				numsprites;
}					t_validmap;

int					ft_puterror(char *str);
int					valid_map(char *line, t_validmap *map, int i);
void				init_map_checking_params(t_validmap *map);
void				init_arch_params(t_archparams *arch);
int					identifyresolution(char *line, t_archparams *arch);
char				*identifytexture(char *line, int i);
int					texture_checker(char *line, t_archparams *arch);
int					param_sorting(t_archparams *arch,
					t_validmap *map, char *line, int i);
int					arch_checker(char *mapfile,
					t_archparams *arch, t_validmap *map);
int					check_top_map(char *line, t_validmap *map,
					int i, int count);
int					sourrounding_walls(char *line,
					t_validmap *map, int i, int x);
int					check_map_bowels(char *line,
					t_validmap *map, int i, int count);
int					numsearch(char *line, t_validmap *map, int *i, int *count);
int					check_bot_map(char *line, t_validmap *map, int i);
void				save_map(char *mapfile,
					t_archparams *arch, t_validmap *map);
void				loop_map(t_archparams *arch,
					t_validmap *map, char *line, int *x);
int					loop_gnl(t_archparams *arch, t_validmap *map, char *line);
char				*identifycolor(char *line, int i);
int					key_press(int key, t_raycaster *rc);
int					key_release(int key, t_raycaster *rc);
int					raycasting(t_raycaster *rc);
int					init_raycast_params(t_raycaster *rc,
					t_archparams *arch, t_validmap *map);
void				print_params(t_archparams *arch, t_validmap *map);
void				refresh_screen(t_raycaster *rc);
void				initial_calc(t_raycaster *rc, int x);
void				perform_dda(t_raycaster *rc);
void				calc_wall_height(t_raycaster *rc);
void				draw_vert_line(t_raycaster *rc, int x);
int					handle_events(t_raycaster *rc);
void				draw_map(t_raycaster *rc);
int					motionless(t_raycaster *rc);
void				motionless_2(t_raycaster *rc, int x);
void				motionless_3(t_raycaster *rc);
void				motionless_4(t_raycaster *rc);
void				dda(t_raycaster *rc);
void				calcule_wall(t_raycaster *rc);
void				draw_wall(t_raycaster *rc, int x);
void				floor_and_sky_draw(t_raycaster *rc, int x);
void				floor_directions(t_raycaster *rc);
void				init(t_raycaster *rc, char *map);
int					load_textures(t_raycaster *rc);
int					load_textures_2(t_raycaster *rc);
int					screenshot(t_raycaster *rc);
int					save_bmp(t_raycaster *rc);
int					write_bmp_data(int file, t_raycaster *rc, int pad);
int					get_color(t_raycaster *rc, int x, int y);
int					write_bmp_header(int fd, int filesize, t_raycaster *rc);
void				set_int_char(unsigned char *start, int value);
int					close_success(t_raycaster *rc);
int					close_failure(char *message);
void				multi_free(t_archparams *arch, t_validmap *map);
char				*ft_strjoin_b(char *s1, char *s2);
void				save_map2(t_archparams *arch,
					t_validmap *map, int x, int y);
int					colum_spaces(char *line, t_validmap *map, int *i, int x);
int					free_return(char *str);
int					multi_free_error(t_archparams *arch, t_validmap *map);
int					check_prev_line(char *line,
					t_validmap *map, int *i, int count);
int					color_checker(char *line, t_archparams *arch);
int					identifycolor2(char *line, int i, char *str, int count);
char				*free_return_str(char *str);
void				init_raycast_params2(t_raycaster *rc, t_validmap *map);
void				init_raycast_params3(t_raycaster *rc,
					t_validmap *map, t_archparams *arch);
void				handle_events2(t_raycaster *rc);
void				write_data_header(t_raycaster *rc, int size, int fd);
void				init_initialparams(t_validmap *map);
void				sprite_casting(t_raycaster *rc);
void				sprite_casting2(t_raycaster *rc);
void				sprite_drawing(t_raycaster *rc, int i, int y);
void				init_textures(t_raycaster *rc, t_archparams *arch);
int					min_max_resolution(t_archparams *arch);
int					no_0_afterline(char *line, t_validmap *map);
void				reset_raycasting_params(t_raycaster *rc);
#endif
