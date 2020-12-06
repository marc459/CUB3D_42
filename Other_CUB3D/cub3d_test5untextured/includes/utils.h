/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchallie <rchallie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:10:31 by rchallie          #+#    #+#             */
/*   Updated: 2020/01/11 14:33:04 by rchallie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <fcntl.h>

void	putstr_info_int(char *str, int i, int fd);
void	putstr_info_char(char *str, char c, int fd);
void	putstr_info_str(char *str, char *st, int fd);
void	putstr_info_cmd();

int		get_next_line(int fd, char **line);

int		is_whitespace(int c);

#endif
