#ifndef INCLUDES_H
# define INCLUDES_H

#include "../libft/libft.h"
#include "../get_next_line/get_next_line.h"

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

typedef	struct	archparams_s
{
	int			win_x;
	int			win_y;
	char		*no_texture;
	char		*so_texture;
	char		*we_texture;
	char		*ea_texture;
	char		*s_texture;
	char		*f_color;
	char		*c_color;
	int			**worldMap;
	int			parameters_count;
}				archparams_t;

typedef	struct	validmap_s
{
	int		m_top;
	int		m_bot;
	int		*colum_spaces;
	int		*colum_nums;
	int		line_width;
	int		m_line;
	char	player_dir;
}				validmap_t;

int		ft_puterror(char *str);
int		valid_map(char *line, validmap_t *map, archparams_t	*arch);
void	init_map_checking_params(validmap_t	*map);
void	init_arch_params(archparams_t *arch);
void	init_map_checking_params(validmap_t *map);
int		identifyresolution(char *line, archparams_t *arch);
char	*identifytexture(char *line);
int		texture_checker(char *line, archparams_t *arch);
int		param_sorting(archparams_t *arch, validmap_t *map, char *line, int i);
int		arch_checker(char *mapfile, archparams_t *arch, validmap_t *map);
int		check_top_map(char *line, validmap_t *map, int i, int count);
int		sourrounding_walls(char *line, validmap_t *map, int i, int count);
int		check_map_bowels(char *line, validmap_t *map, int i, int count);
int		numsearch(char *line, validmap_t *map, int *i, int *count);
int		check_bot_map(char *line, validmap_t *map, int i, int count);
int		save_map(char *line, validmap_t *map, archparams_t	*arch, int i);
int		loop_gnl(archparams_t *arch, validmap_t *map, char *line);
char	*identifycolor(char *line);
void	print_params(archparams_t	*arch, validmap_t *map);

#endif