/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullshit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvega-tr <fvega-tr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 17:42:40 by fvega-tr          #+#    #+#             */
/*   Updated: 2020/01/13 17:47:17 by fvega-tr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sound_damage(t_struct *t)
{
	if (t->life_bar < 195 && t->life_bar > 180)
		system("say -v Monica espabila");
	if (t->life_bar < 140 && t->life_bar > 150)
		system("say -v Monica a");
	if (t->life_bar < 110 && t->life_bar > 100)
		system("say -v Monica a");
	if (t->life_bar < 60 && t->life_bar > 50)
		system("say -v Monica a");
	if (t->life_bar < 20 && t->life_bar > 10)
		system("say -v Monica a");
}

void	game_over(t_struct *t)
{
	if (t->life_bar <= 0)
	{
		t->tex[11].img = mlx_xpm_file_to_image(t->mlx_ptr,
		"sprites/game_over.xpm",
		&t->tex_width, &t->tex_height);
		t->img_ptr = t->tex[11].img;
	}
}

void	life_bar(t_struct *t)
{
	int i;

	i = 0;
	while (i < (t->life_bar * (t->win_width - 200)) / 250)
	{
		mlx_pixel_put(t->mlx_ptr, t->win_ptr, i + 100, 20, RGB_GREEN);
		mlx_pixel_put(t->mlx_ptr, t->win_ptr, i + 100, 22, RGB_GREEN);
		mlx_pixel_put(t->mlx_ptr, t->win_ptr, i + 100, 24, RGB_GREEN);
		mlx_pixel_put(t->mlx_ptr, t->win_ptr, i + 100, 26, RGB_GREEN);
		mlx_pixel_put(t->mlx_ptr, t->win_ptr, i + 100, 28, RGB_GREEN);
		i++;
	}
}
