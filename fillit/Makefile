# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cboyer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/03 17:58:29 by cboyer            #+#    #+#              #
#    Updated: 2015/12/09 17:44:01 by cboyer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_NAME =	main.c			\
			check.c			\
			tetraupleft.c	\
			solver.c		\
			ft_grid.c		\
			ft_solve.c

SRC_PATH = ./
SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
SRC_OBJ = $(SRC:.c=.o)

LIB_NAME = libft.a
LIB_PATH = ./lib/
LIB = $(addprefix $(LIB_PATH), $(LIB_NAME))

NAME = fillit

CC = @gcc
RM = @rm -f
NORMINETTE = @norminette
WHITE = "\033[33;37m"
GREEN = "\033[33;32m"
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(SRC_OBJ)
	$(CC) $(CFLAGS) $(LIB) $(SRC_OBJ) -o $(NAME)

%.o: %.c
	$(CC) -o $@ -c $^ $(CFLAGS)

clean:
	$(RM) $(SRC_OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: $(SRC_OBJ)
	$(CC) $(CFLAGS) -g $(LIB) $(SRC_OBJ) -o $(NAME)


norme:
	$(NORMINETTE) $(SRC_PATH)*.[ch]

.PHONY: clean fclean all re norme
