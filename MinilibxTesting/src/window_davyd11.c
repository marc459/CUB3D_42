#include "../minilibx_opengl/mlx.h"
#include "cub3d.h"
#include "map1.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

int		main(void)
{
	int     bpp;
	int     size_line;
	int     endian;

	int     bpp_tex;
	int     size_line_tex;
	int     endian_tex;

	int wh = 600;
	int ww = 600;

	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	char *img_data;


	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, wh, ww, "Cub3D");

	img_ptr = mlx_new_image(mlx_ptr, ww, wh);
	img_data = (char *)mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);

	//g.tex_img = mlx_xpm_file_to_image(g.mlx_ptr, "/Users/davyd11/42folder/cub3d/textures/bluestone.xpm", &tex_w, &tex_h);
	//g.tex_data = (char *)mlx_get_data_addr(g.tex_img, &bpp_tex, &size_line_tex, &endian_tex);


	int color = 0xf3ff00;
	int pixel;
	int y = 0;
	int x = 0;
	while (x < ww)
	{
	if(x == 300)
		break;
	while (y < wh)
	{
		pixel = (y * ww + x) * 4;
	  //pixel = (x * 4 + 4 * f->ww * y);
		if (endian == 1)
		{
			img_data[pixel + 0] = (color >> 24);
			img_data[pixel + 1] = (color >> 16) & 0xFF;
			img_data[pixel + 2] = (color >> 8) & 0xFF;
			img_data[pixel + 3] = (color) & 0xFF;
		}
		else if (endian == 0)
		{
			img_data[pixel + 0] = (color) & 0xFF;
			img_data[pixel + 1] = (color >> 8) & 0xFF;
			img_data[pixel + 2] = (color >> 16) & 0xFF;
			img_data[pixel + 3] = (color >> 24);
		}
		y++;
	}
	y = 0;
	x++;
	}
	printf("hola");
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
	mlx_loop(mlx_ptr);
}
