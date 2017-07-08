# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csellier <csellier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/07/08 14:00:09 by csellier          #+#    #+#              #
#    Updated: 2017/07/08 18:17:27 by csellier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft_malloc_$(HOSTTYPE).so

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

FLAGS = -Wall -Wextra -Werror #-fPIC

SCR = free.c

LINK = libft_malloc.so

OBJ = $(SCR:.c=.o)

$(NAME) : link $(OBJ)
	make -C libft/
	gcc -o $(NAME) -shared $(FLAGS) $(OBJ) -L libft -lft

all : $(NAME)

link :
	ln -s $(NAME) $(LINK)

%.o: %.c
	gcc $(FLAGS) -I. -c $<

clean :
	make -C libft/ clean
	rm -f $(OBJ)

fclean : clean
	make -C libft/ fclean
	rm -rf $(NAME) $(LINK)

re : fclean all

