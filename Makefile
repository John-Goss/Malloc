# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/03 17:43:42 by jle-quer          #+#    #+#              #
#    Updated: 2017/10/06 13:49:04 by jle-quer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

LINK_NAME = libft_malloc.so

SRC =	src/malloc.c \
		src/display.c \
		src/memorydump.c \
		src/realloc.c \
		src/free.c \
		src/init.c \
		src/alloc.c

OBJ = $(SRC:.c=.o)

CFLAGS = -Wextra -Wall -Werror

LIBFT_INC = -I libft/INCLUDES

INC = -I includes

all: $(NAME)

$(NAME): $(OBJ)
	make -C libft
	gcc $(CFLAGS) -shared -o $(NAME) $(OBJ) -lft -L libft $(INC) $(LIBFT_INC)
	ln -s $(NAME) $(LINK_NAME)

%.o: %.c
	gcc -c $(CFLAGS) $(INC) $(LIBFT_INC) $^ -o $@ -fPIC

clean:
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)
	rm -f $(LINK_NAME)

re: fclean all

.PHONY: all clean fclean re
