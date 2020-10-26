/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/10/26 12:28:29 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	set_int_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

int		write_bmp_header(int fd, int filesize, t_raycaster *rc)
{
	int				i;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	set_int_char(bmpfileheader + 18, rc->win_x);
	set_int_char(bmpfileheader + 22, rc->win_y);
	bmpfileheader[27] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	return (!(write(fd, bmpfileheader, 54) < 0));
}

int		get_color(t_raycaster *rc, int x, int y)
{
	int	rgb;
	int	color;

	color = *(int*)(rc->img_data + (4 * (int)rc->win_x *
	((int)rc->win_y - 1 - y)) + (4 * x));
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

int		write_bmp_data(int file, t_raycaster *rc, int pad)
{
	const unsigned char zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					color;

	i = 0;
	while (i < (int)rc->win_y)
	{
		j = 0;
		while (j < (int)rc->win_x)
		{
			color = get_color(rc, j, i);
			if (write(file, &color, 3) < 0)
				return (0);
			if (pad > 0 && write(file, &zero, pad) < 0)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int		save_bmp(t_raycaster *rc)
{
	int	filesize;
	int	file;
	int	pad;

	pad = (4 - ((int)rc->win_x * 3) % 4) % 4;
	filesize = 54 + (3 * ((int)rc->win_x + pad)
	* (int)rc->win_y);
	if ((file = open("screenshot.bmp", O_WRONLY | O_CREAT
	| O_TRUNC | O_APPEND, 777)) < 0)
		return (0);
	if (!write_bmp_header(file, filesize, rc))
		return (0);
	if (!write_bmp_data(file, rc, pad))
		return (0);
	close(file);
	return (1);
}
