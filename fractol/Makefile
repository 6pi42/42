# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cboyer <cboyer@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/08 12:28:01 by cboyer            #+#    #+#              #
#    Updated: 2016/02/09 16:32:28 by cboyer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC = /

SRC =	main.c			\
		pixel_put.c		\
		mandelbrot.c	\
		utilities.c		\
		burning_ship.c	\
		event.c			\
		rabbit.c		\
		julia.c			\
		siegel.c		\
		ft_itoa.c		\

OBJ = $(SRC:.c=.o)
NAME = fractol
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

debug: $(OBJ)
	gcc -I ./libft/includes/ -I /usr/local/include -lmlx -framework OpenGL -framework AppKit -g  $(SRC) libft/libft.a

maison: lib $(OBJ)
	gcc -I./libft/includes/ -L./libft/ -lft -L./minilibx_macos/ -I./minilibx_macos/ -lmlx -framework OpenGL -framework AppKit $(SRC) -L ./libft/ -lft -o fractol

re: fclean all
