# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/08 12:28:01 by cboyer            #+#    #+#              #
#    Updated: 2016/03/10 14:16:08 by cboyer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC = /

SRC =	main.c			\
		pixel_put.c		\
		utilities.c		\
		hook.c			\
		raytracer.c		\
		error.c			\
		multithreading.c\
		parse.c			\
		get.c			\
		get_object.c	\
		sphere.c		\
		plan.c			\
		get_object2.c	\
		vector.c		\
		sphere_lumos.c	\
		shadow.c		\
		cylinder.c		\
		cone.c			\
		reflection.c	\
		soft_shadow.c	\

OBJ = $(SRC:.c=.o)
NAME = rtv1
CC = gcc
RM = rm -f
CFLAGS = -Wall -Werror -Wextra

LIB_PATH = ./libft/ /usr/local/lib/ #/usr/X11/lib/
LIB_NAME = -lft -lmlx -framework OpenGL -framework AppKit
LIB = $(addprefix -L,$(LIB_PATH))
LFLAGS = $(LIB) $(LIB_NAME)

INC_PATH = ./libft/includes/ /usr/local/include/ /usr/X11/lib
INC = $(addprefix -I,$(INC_PATH))

all: lib $(NAME)

lib:
	make -C ./libft

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJ) -o $@

%.o: %.c
	$(CC) $(INC) -o $@ -c $^ $(CFLAGS)

clean:
	$(RM) $(OBJ)
	make clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	make fclean -C ./libft

debug: lib $(OBJ)
	gcc -I ./libft/includes/ -I /usr/local/include -lmlx -framework OpenGL -framework AppKit -g -L./libft/ -lft $(SRC) -o $(NAME)

mlibx:
	make -C minilibx_macos

maison: lib mlibx $(OBJ)
	gcc -Wall -Werror -Wextra -I./libft/includes/ -L./libft/ -L./minilibx_macos/ -lft -I./minilibx_macos/ -lmlx -framework OpenGL -framework AppKit $(OBJ) -o $(NAME)

seg: lib $(OBJ)
	gcc -I ./libft/includes/ -I /usr/local/include -lmlx -framework OpenGL -framework AppKit -fsanitize=address -L./libft/ -lft $(SRC) -o $(NAME)

re_maison: fclean mlibx maison

re: fclean all
