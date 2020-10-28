/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/08 13:21:32 by msantos-          #+#    #+#             */
/*   Updated: 2020/10/28 13:00:47 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <math.h>
#include <fcntl.h>

#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"
#include "../bash_prompt.h"

#if defined(__APPLE__)
#include "key_macos.h"
#include "../minilibx/mlx.h"
#define SO "MACOS"
#else
#include "key_linux.h"
#include "../minilibx_linux/mlx.h"
#define SO "LINUX"
#endif

#define INIT_P_PLANE_X 0
#define INIT_P_PLANE_Y 0.66
#define MV_SPEED 0.400 //0.199
#define ROT_SPEED 0.1745
#define AMB_LIGHT 7

// Colors
#define WHITE 0xFFFFFF
#define RED 0xFF0000
#define GREEN 0x00FF00
#define BLUE 0x0000FF
#define BLACK 0x000000

typedef struct s_img
{
	void *img;
	char *data;
	int size_l;
	int bpp;
	int endian;
} t_img;

typedef struct s_raycaster
{
	void *mlx_ptr;//
	void *win_ptr;//
	void *img_ptr;//
	char *img_data;//
	int line_height;//
	int bpp;//
	int size_line;//
	int endian;//
	int tex_height;//
	int tex_width;//
	double wall_x;//
	int tex_x;//
	int tex_y;//
	t_img tex[12];//
	int win_x; //double for untextured image
	int win_y; //double for untextured image
	int **worldMap;//
	double player_pos_x;//
	double player_pos_y;//
	double player_dir_x;//
	double player_dir_y;//
	double player_plane_x;//
	double player_plane_y;//
	double ray_dir_x;//
	double ray_dir_y;//
	int mapWidth;//
	int mapHeight;//
	int map_x;//
	int map_y;//
	double side_dist_x;//
	double side_dist_y;//
	double delta_dist_x;//
	double delta_dist_y;//
	int step_x;//
	int step_y;//
	int side;//
	int draw_start;//
	int draw_end;//
	double perp_wall_dist;//
	int	up;//
	int down;//
	int right;//
	int left;//
	int textured;//
	int crouch;//
	int sprint;//
	double camerax;
	double dirx;
	double diry;
	int stepx;
	int stepy;
	int	hit;
	double wallx;
	double movespeed;
	int tex_id;
	int tex_side;
	double floorxwall;
	double floorywall;
	double currentdist;
	double currentfloorx;
	double currentfloory;
	double weight;
	int floortexx;
	int floortexy;

} t_raycaster;

typedef struct archparams_s
{
	int win_x;
	int win_y;
	char *no_texture;
	char *so_texture;
	char *we_texture;
	char *ea_texture;
	char *s_texture;
	char *f_color;
	char *c_color;
	int **worldMap;
	int parameters_count;
} archparams_t;

typedef struct validmap_s
{
	int m_top;
	int m_bot;
	int mapWidth;
	char **map;
	int *colum_spaces;
	int *colum_nums;
	int m_line;
	char player_dir;
	int init_p_pos_x;
	int init_p_pos_y;
	int last_0;
	char *prev_line;
} validmap_t;

int ft_puterror(char *str);
int valid_map(char *line, validmap_t *map);
void init_map_checking_params(validmap_t *map);
void init_arch_params(archparams_t *arch);
void init_map_checking_params(validmap_t *map);
int identifyresolution(char *line, archparams_t *arch);
char *identifytexture(char *line, int i);
int texture_checker(char *line, archparams_t *arch);
int param_sorting(archparams_t *arch, validmap_t *map, char *line, int i);
int arch_checker(char *mapfile, archparams_t *arch, validmap_t *map);
int check_top_map(char *line, validmap_t *map, int i, int count);
int sourrounding_walls(char *line, validmap_t *map, int i, int count);
int check_map_bowels(char *line, validmap_t *map, int i, int count);
int numsearch(char *line, validmap_t *map, int *i, int *count);
int check_bot_map(char *line, validmap_t *map, int i);
void save_map(char *mapfile, archparams_t *arch, validmap_t *map);
void loop_map(archparams_t *arch, validmap_t *map, char *line, int *x);
int loop_gnl(archparams_t *arch, validmap_t *map, char *line);
char *identifycolor(char *line, int i);
int key_press(int key, t_raycaster *rc);
int key_release(int key, t_raycaster *rc);

int raycasting( t_raycaster *rc);
int init_raycast_params(t_raycaster *rc, archparams_t *arch, validmap_t *map);
void print_params(archparams_t *arch, validmap_t *map);
void refresh_screen(t_raycaster *rc);
void initial_calc(t_raycaster *rc, int x);
void perform_dda(t_raycaster *rc);
void calc_wall_height(t_raycaster *rc);
void draw_vert_line(t_raycaster *rc, int x);
int handle_events(t_raycaster *rc);
void drawMap(t_raycaster *rc);
int motionless(t_raycaster *rc);
void motionless_2(t_raycaster *rc, int x);
void motionless_3(t_raycaster *rc);
void motionless_4(t_raycaster *rc);
void dda(t_raycaster *rc);
void calcule_wall(t_raycaster *rc);
void draw_wall(t_raycaster *rc, int x);
void floor_and_sky_draw(t_raycaster *rc, int x);
void floor_directions(t_raycaster *rc);
void init(t_raycaster *rc, char *map);
void load_textures(t_raycaster *rc);
void load_textures_2(t_raycaster *rc);

int screenshot(t_raycaster *rc);
int			save_bmp(t_raycaster *rc);
int	write_bmp_data(int file, t_raycaster *rc, int pad);
int	get_color(t_raycaster *rc, int x, int y);
int	write_bmp_header(int fd, int filesize, t_raycaster *rc);
void	set_int_char(unsigned char *start, int value);
int		close_success(t_raycaster *rc);
int		close_failure(char *message);
void multi_free(archparams_t *arch,validmap_t *map);
char	*ft_strjoin_b(char *s1, char *s2);
void save_map2(archparams_t *arch, validmap_t *map, int x, int y);
int colum_spaces(char *line, validmap_t *map, int i);
int free_return(char *str);
#endif