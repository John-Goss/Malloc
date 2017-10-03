# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/03 17:43:42 by jle-quer          #+#    #+#              #
#    Updated: 2017/10/03 17:45:00 by jle-quer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

FLAGS = -Wall -Wextra -Werror

SCR = free.c \
	  display.c \
	  malloc.c \
	  realloc.c \
	  init.c \
	  alloc.c

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

