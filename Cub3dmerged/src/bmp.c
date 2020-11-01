/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/01 14:51:21 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	write_data_header(t_raycaster *rc, int size, int fd)
{
	unsigned char header[54];

	ft_bzero(header, 54);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(size);
	header[3] = (unsigned char)(size >> 8);
	header[4] = (unsigned char)(size >> 16);
	header[5] = (unsigned char)(size >> 24);
	header[10] = (unsigned char)(54);
	header[14] = (unsigned char)(40);
	header[18] = (unsigned char)(rc->win_x);
	header[19] = (unsigned char)(rc->win_x >> 8);
	header[20] = (unsigned char)(rc->win_x >> 16);
	header[21] = (unsigned char)(rc->win_x >> 24);
	header[22] = (unsigned char)(-rc->win_y);
	header[23] = (unsigned char)(-rc->win_y >> 8);
	header[24] = (unsigned char)(-rc->win_y >> 16);
	header[25] = (unsigned char)(-rc->win_y >> 24);
	header[26] = (unsigned char)(1);
	header[28] = (unsigned char)(32);
	write(fd, header, 54);
}

void	save_bmp(t_raycaster *rc)
{
	int		fd;
	int		res;
	int		size;
	char	*tmp;

	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT, 0777)) < 0)
		close_success(rc);
	res = rc->win_x;
	size = 54 + (res + rc->win_y) * 4;
	write_data_header(rc, size, fd);
	tmp = (char *)rc->img_ptr;
	write(fd, tmp, (res * rc->win_y * 4));
	close(fd);
	close_success(rc);
}
