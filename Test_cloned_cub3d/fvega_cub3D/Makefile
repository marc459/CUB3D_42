# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fvega-tr <fvega-tr@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 13:34:09 by amaza-va          #+#    #+#              #
#    Updated: 2020/01/13 20:34:26 by fvega-tr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

HEADER	=	cub3d.h

SRCS	=	main.c\
			draw.c\
			get_next_line.c\
			get_next_line_utils.c\
			init_orientation.c\
			key.c\
			load_textures.c\
			map.c\
			motionless.c\
			movement.c\
			sprites.c\
			bullshit.c\
			exit.c\
			utils.c\
			utils2.c\
			screenshot.c\
			bmp.c

all		:	$(SRCS)
		@gcc $(SRCS) -lmlx -framework OpenGL -framework AppKit && ./a.out "map2iiiiiiiiii.cub"

runlinux:
	gcc $(SRCS) -lm -lbsd -lmlx -lXext -lX11

map		:	$(SRCS)
		@gcc $(SRCS) -lmlx -framework OpenGL -framework AppKit && ./a.out "map1.cub"

save	:	$(SRCS)
		@gcc $(SRCS) -lmlx -framework OpenGL -framework AppKit && ./a.out "map2.cub" --save

clean	:
		@/bin/rm -f $(OBJS)

fclean	:	clean
		@/bin/rm -f $(NAME)

re		: 	fclean all
