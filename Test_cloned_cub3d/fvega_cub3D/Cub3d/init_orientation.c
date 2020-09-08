/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_orientation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvega-tr <fvega-tr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 18:01:35 by fvega-tr          #+#    #+#             */
/*   Updated: 2020/01/13 18:43:56 by fvega-tr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	orientation_n(t_struct *t, int i, int j)
{
	t->dirx = -1;
	t->diry = 0;
	t->planex = 0;
	t->planey = 0.66;
	t->initial_pos++;
	t->posx = (double)i + 0.5;
	t->posy = (double)j + 0.5;
}

void	orientation_s(t_struct *t, int i, int j)
{
	t->dirx = 1;
	t->diry = 0;
	t->planex = 0;
	t->planey = -0.66;
	t->initial_pos++;
	t->posx = (double)i + 0.5;
	t->posy = (double)j + 0.5;
}

void	orientation_e(t_struct *t, int i, int j)
{
	t->dirx = 0;
	t->diry = 1;
	t->planex = 0.66;
	t->planey = 0;
	t->initial_pos++;
	t->posx = (double)i + 0.5;
	t->posy = (double)j + 0.5;
}

void	orientation_w(t_struct *t, int i, int j)
{
	t->dirx = 0;
	t->diry = -1;
	t->planex = -0.66;
	t->planey = 0;
	t->initial_pos++;
	t->posx = (double)i + 0.5;
	t->posy = (double)j + 0.5;
}
