# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cboyer <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/10 17:17:48 by cboyer            #+#    #+#              #
#    Updated: 2016/01/14 15:16:54 by cboyer           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAG = -Wall -Wextra -Werror

NAME = libft.a

SRC = ft_atoi.c 			\
	  ft_bzero.c 			\
	  ft_fabs.c				\
	  ft_isblank.c			\
	  ft_isalnum.c 			\
	  ft_isalpha.c 			\
	  ft_isascii.c 			\
	  ft_isdigit.c 			\
	  ft_isprint.c 			\
	  ft_isspace.c			\
	  ft_itoa.c 			\
	  ft_memalloc.c 		\
	  ft_memccpy.c 			\
	  ft_memchr.c 			\
	  ft_memcmp.c 			\
	  ft_memcpy.c 			\
	  ft_memdel.c 			\
	  ft_memmove.c 			\
	  ft_memset.c 			\
	  ft_power.c			\
	  ft_putchar.c 			\
	  ft_putchar_fd.c 		\
	  ft_putendl.c 			\
	  ft_putendl_fd.c 		\
	  ft_putnbr.c 			\
	  ft_putnbr_fd.c 		\
	  ft_putstr.c 			\
	  ft_putstr_fd.c 		\
	  ft_strcat.c 			\
	  ft_strchr.c 			\
	  ft_strclr.c 			\
	  ft_strcmp.c 			\
	  ft_strcpy.c 			\
	  ft_strdel.c 			\
	  ft_strdup.c 			\
	  ft_strequ.c 			\
	  ft_striter.c 			\
	  ft_striteri.c 		\
	  ft_strjoin.c 			\
	  ft_strlcat.c 			\
	  ft_strlen.c 			\
	  ft_strmap.c 			\
	  ft_strmapi.c 			\
	  ft_strncat.c 			\
	  ft_strncmp.c 			\
	  ft_strncpy.c 			\
	  ft_strnequ.c 			\
	  ft_strnew.c 			\
	  ft_strnstr.c 			\
	  ft_strrchr.c 			\
	  ft_strsplit.c 		\
	  ft_strstr.c 			\
	  ft_strsub.c 			\
	  ft_strtrim.c 			\
	  ft_swap.c 			\
	  ft_tolower.c 			\
	  ft_toupper.c			\
	  ft_lstnew.c			\
	  ft_lstdelone.c		\
	  ft_lstdel.c			\
	  ft_lstadd.c			\
	  ft_lstiter.c			\
	  ft_lstmap.c			\
	  get_next_line.c		\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "libft.a created"
	@ranlib $(NAME)
	@echo "libft.a indexed"

%.o: %.c
	@gcc $(FLAG) -c $< -o $@ -I includes

clean:
	@rm -f $(OBJ)
	@echo "*.o deleted"

fclean: clean
	@rm -f $(NAME)
	@echo "libft.a deleted"

kill:
	@rm -f $(NAME)
	@rm -f $(OBJ)
	@echo "S E R I A L  K I L L E R"	

re: fclean all

.PHONY: all, clean, fclean, kill, re
