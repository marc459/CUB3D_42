NAME = Cub3D
CC = gcc

FLAGS = -Wall -Wextra -Werror

#NORMINETTE LINUX
#echo 'alias norminette="~/.norminette/norminette.rb"' >> ~/.zshrc
#source ~/.zshrc
#norminette main.c

ifeq ($(OS),Windows_NT) 
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

ifeq ($(detected_OS),Darwin)
    MLXFLAGS = -I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL -framework AppKit
endif
ifeq ($(detected_OS),Linux)
    MLXFLAGS = -lm -lbsd -lmlx -lXext -lX11
endif

CHECKLEAKS=/Applications/Xcode.app/Contents/Developer/usr/lib/libLeaksAtExit.dylib leaks -atExit -- ./a.out map.cub

SRC_PATH = ./src
SRC_BONUS_PATH = ./src_bonus
GNL_PATH = ./get_next_line
LIB_PATH = ./libft
OBJ_PATH = ./objs

LIB_NAME = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
ft_memcmp.c ft_strlen.c ft_strlcat.c ft_strlcpy.c ft_strchr.c \
ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c \
ft_isdigit.c ft_isalnum.c ft_isascii.c \
ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c ft_strdup.c \
ft_strjoin.c ft_substr.c ft_split.c ft_strtrim.c ft_itoa.c \
ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c \
ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c \
ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
ft_lstmap_bonus.c \
ft_intlen.c ft_len.c \
ft_itoa_without_minus.c \
ft_putchar.c ft_strrev.c \
ft_putstr.c ft_dectohex.c \
ft_hextodec.c

GNL_NAME = get_next_line.c

SRC_NAME = init_params.c init_params2.c valid_file.c valid_file2.c valid_map.c valid_map2.c save_map.c

RAYCASTING = utils.c utils2.c load_textures.c raycast.c raycast2.c handle_events.c bmp.c screenshot.c key.c sprite.c

OBJ_NAME = $(SRC_NAME:.c=.o)
OBJLIB_NAME = $(LIB_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/, $(SRC_NAME))
RAY_C = $(addprefix $(SRC_PATH)/, $(RAYCASTING))
GNL = $(addprefix $(GNL_PATH)/, $(GNL_NAME))
LIB = $(addprefix $(LIB_PATH)/, $(LIB_NAME))
SRC_BONUS = $(addprefix $(SRC_BONUS_PATH)/, $(SRC_NAME))
RAY_C_BONUS = $(addprefix $(SRC_BONUS_PATH)/, $(RAYCASTING))

OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
OBJLIB = $(addprefix $(OBJ_PATH)/,$(OBJLIB_NAME))

all: run
	./$(NAME) map.cub

compile:
	@$(CC) $(FLAGS) main.c  testing.c $(LIB) $(SRC) $(GNL) src/utils.c src/utils2.c
run:
	@$(CC) $(FLAGS) main.c  testing.c $(LIB) $(SRC) $(RAY_C) $(GNL) $(MLXFLAGS) -o $(NAME)
runbonus:
	@$(CC) $(FLAGS) main.c  testing.c $(LIB) $(SRC_BONUS) $(RAY_C_BONUS) src_bonus/hud_bonus.c $(GNL) $(MLXFLAGS) -o $(NAME)
normi:
	#echo 'alias norminette="~/.norminette/norminette.rb"' >> ~/.zshrc 
	#source ~/.zshrc
	norminette src/*.c src/*.h libft/*.c libft/*.h get_next_line/*.c get_next_line/*.h main.c
clean:
    @rm -rf $(NAME)

fclean: clean
    @rm -rf $(NAME) screenshot.bmp

re: fclean all

.PHONY: fclean clean re
