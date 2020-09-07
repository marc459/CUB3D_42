/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvega-tr <fvega-tr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 18:21:18 by fvega-tr          #+#    #+#             */
/*   Updated: 2020/01/13 19:47:41 by fvega-tr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	map_reader_2(t_struct *t, int fd)
{
	char *line;

	get_next_line(fd, &line);
	if (line[0] != 'R' || line[1] != ' ')
		close_failure("Error\nNo resolution defined\n");
	if (!(t->win_width = ft_atoi(line + 2)))
		close_failure("Error\nNo resolution defined\n");
	line += ft_strlen(ft_itoa(t->win_width)) + 3;
	if (!(t->win_height = ft_atoi(line)))
		close_failure("Error\nNo resolution defined\n");
	get_next_line(fd, &line);
	if (ft_strlen(line) > 0)
		close_failure("Error\nNo correct file format\n");
}

void		map_reader(t_struct *t)
{
	int		fd;
	char	*line;
	int		i;

	if ((fd = open(t->map_file, O_RDONLY)) == -1)
		close_failure("Map ERROR: map file doesn't exist\n");
	map_reader_2(t, fd);
	while (get_next_line(fd, &line))
	{
		i = -1;
		line = ft_delete_spaces(line);
		if (!t->map_width)
			t->map_width = ft_strlen(line);
		while (line[++i])
			t->map[t->map_height][i] = line[i] - '0';
		t->map_height++;
	}
	i = -1;
	while (++i < t->map_width)
		t->map[t->map_height][i] = line[i] - '0';
	t->map_height++;
	free(line);
	map_position(t);
	map_error_check(t);
}

void		map_position(t_struct *t)
{
	int i;
	int j;

	i = -1;
	while (++i < t->map_height)
	{
		j = -1;
		while (++j < t->map_width)
		{
			if (t->map[i][j] == 'N' - '0' || t->map[i][j] == 'S' - '0' ||
				t->map[i][j] == 'E' - '0' || t->map[i][j] == 'W' - '0')
			{
				if (t->map[i][j] == 'N' - '0')
					orientation_n(t, i, j);
				else if (t->map[i][j] == 'S' - '0')
					orientation_s(t, i, j);
				else if (t->map[i][j] == 'E' - '0')
					orientation_e(t, i, j);
				else if (t->map[i][j] == 'W' - '0')
					orientation_w(t, i, j);
				t->map[i][j] = 0;
			}
		}
	}
}

void		map_error_check(t_struct *t)
{
	int i;

	if (t->map_height < 3 || t->map_width < 3)
		close_failure("Map ERROR: this map is too small\n");
	if (!t->initial_pos)
		close_failure("Map ERROR: there isn't an initial position\n");
	if (t->initial_pos > 1)
		close_failure("Map ERROR: there's more than one initial position\n");
	i = -1;
	while (++i < t->map_width)
		if (t->map[0][i] == 0 || t->map[t->map_height - 1][i] == 0)
			close_failure("Map ERROR: this map isn't completely walled\n");
	i = -1;
	while (++i < t->map_height)
		if (t->map[i][0] == 0 || t->map[i][t->map_width - 1] == 0)
			close_failure("Map ERROR: this map isn't completely walled\n");
}
