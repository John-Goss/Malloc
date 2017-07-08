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

