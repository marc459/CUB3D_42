/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msantos- <msantos-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 07:11:34 by msantos-          #+#    #+#             */
/*   Updated: 2020/11/03 12:18:07 by msantos-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

typedef struct s_bitmap
{
	unsigned int filesize;
	unsigned short reserved1;
	unsigned short reserved2;
	unsigned int pixeldataoffset;
	unsigned int headersize;
	unsigned int imagewidth;
	unsigned int imageheight;
	unsigned short planes;
	unsigned short bitsperpixel;
	unsigned int compression;
	unsigned int imagesize;
	unsigned int xpixelspermeter;
	unsigned int ypixelspermeter;
	unsigned int totalcolors;
	unsigned int importantcolors;
} t_bitmap;

static t_bitmap fill_header(t_raycaster *rc)
{
	t_bitmap header;

	ft_memset(&header, 0, sizeof(header));
	header.filesize = (rc->win_x * rc->win_y * (rc->bpp / 8)) + 54;
	header.pixeldataoffset = 54;
	header.headersize = 40;
	header.imagewidth = rc->win_x;
	header.imageheight = rc->win_y;
	header.planes = 1;
	header.bitsperpixel = rc->bpp;
	header.imagesize = rc->win_x * rc->win_y * (rc->bpp / 8);
	return (header);
}

static void file_write( int fd, const void *buf, ssize_t len)
{
	if (write(fd, buf, len) != len)
	{
		perror("Error\nfile_write");
		exit(-1);
	}
}

int save_bmp(t_raycaster *rc)
{
	int fd;
	t_bitmap bmp;
	int i;
	unsigned int *line;

	rc->img_data = mlx_get_data_addr(rc->img_ptr,
					&rc->bpp, &rc->size_line, &rc->endian);
	fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	bmp = fill_header(rc);
	if (fd < 0)
		return (1);
	file_write( fd, "BM", 2);
	file_write( fd, &bmp, sizeof(bmp));
	i = 0;
	while (i < rc->win_y)
	{
		line = (unsigned int *)&rc->img_data[(rc->win_y - i - 1) *
												 rc->size_line];
		file_write( fd, line, rc->size_line);
		i++;
	}
	if (close(fd) == -1)
		return (1);
	return (0);
}