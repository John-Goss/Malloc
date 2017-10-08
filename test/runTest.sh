#!/bin/sh

cd .. && make re && make clean && cd -

gcc -o ../test0 ./test0.c -I ../includes/ -I ../libft/INCLUDES/
gcc -o ../test1 ./test1.c -I ../includes/ -I ../libft/INCLUDES/
gcc -o ../test2 ./test2.c -I ../includes/ -I ../libft/INCLUDES/
gcc -o ../test3 ./test3.c -I ../includes/ -I ../libft/INCLUDES/
gcc -o ../test3-2 ./test3-2.c -I ../includes/ -I ../libft/INCLUDES/
gcc -o ../test4 ./test4.c -I ../includes/ -I ../libft/INCLUDES/
gcc -o ../test5 ./test5.c ../libft/libft.a -I ../includes/ -I ../libft/INCLUDES/ -L./.. -lft_malloc ../libft_malloc_x86_64_Darwin.so
gcc -o ../testMultiThread ./multi_thread_malloc.c ../libft/libft.a -I ../includes/ -I ../libft/INCLUDES/ ../libft_malloc_x86_64_Darwin.so
gcc -o ../testShowCalloc ./show_calloc.c -I ../includes/ -I ../libft/INCLUDES/ ../libft_malloc_x86_64_Darwin.so
