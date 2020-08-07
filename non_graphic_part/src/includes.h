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
}				archparams_t;

typedef	struct	validmap_s
{
	int		m_top;
	int		m_down;
	int		*colum_spaces;
	int		*colum_nums;
	int		line_width;
	char	player_letter;
}				validmap_t;

int		valid_map(char *line, validmap_t *map);

#endif