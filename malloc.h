/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 13:42:31 by jle-quer          #+#    #+#             */
/*   Updated: 2017/09/28 18:04:39 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <sys/mman.h>
# include <stdio.h>
# include "./libft/INCLUDES/libft.h"
# include <pthread.h>

/*
**# define DBG ft_putstr(__func__); ft_putstr(" in "); \
**ft_putstr(__FILE__); ft_putstr(" at line : "); \
**ft_putnbr(__LINE__); ft_putchar('\n')
*/

# define LOCK_INIT g_zone.locked
# define TINY_HEAP g_zone.tiny_heap
# define SMALL_HEAP g_zone.small_heap
# define LARGE_HEAP g_zone.large_heap
# define META_BLOCK_SIZE (sizeof(t_block) - sizeof(char *))
# define TINY_HEAP_SIZE ((size_t)getpagesize() * 64)
# define SMALL_HEAP_SIZE ((size_t)getpagesize() * 512)
# define TINY_ALLOC_LIMIT (1024)
# define SMALL_ALLOC_LIMIT (1024 * 16)
# define ALLOC_MIN (sizeof(int) * 2)
# define ALIGN_BLOCK_SIZE_8(x) (((((x) - 1) >> 3) << 3) + 8)
# define ALIGN_BLOCK_SIZE_4096(x) (((((x) - 1) >> 12) << 12) + 4096)

typedef enum			e_type
{
	TINY,
	SMALL,
	LARGE,
	NONE
}						t_type;

typedef struct			s_block
{
	size_t				size;
	size_t				allocsize;
	int					free;
	struct s_block		*next;
	char				data[1];
}						t_block;

typedef struct			s_zone
{
	void				*tiny_heap;
	void				*small_heap;
	void				*large_heap;
	int					locked;
}						t_zone;

extern t_zone			g_zone;
extern pthread_mutex_t	g_locker;

void					*malloc(size_t size);
void					*exec_malloc(size_t size);
void					*calloc(size_t count, size_t size);
void					*realloc(void *ptr, size_t size);
void					*exec_realloc(void *addr, size_t size);
void					*reallocf(void *ptr, size_t size);
void					free(void *ptr);
void					exec_free(void *ptr);
void					*find_free_block(t_block **last, size_t blocksize,
						t_type type);
t_block					*is_valid_block(t_block *ptr);
void					*alloc_zone(t_block *last, size_t blocksize,
						t_type type, size_t allocated_size);
void					*alloc_large_zone(size_t size);
void					*extend_heap(t_block *last, size_t size);
void					split_block(t_block *block, size_t size);
void					defrag_blocks(t_block *block, t_block *prev);
void					remove_large_alloc(t_block *block, t_block *prev);
t_type					get_block_type(t_block *block);
t_type					get_alloc_type(size_t size);

int						heap_init(void);
int						init(void);
int						in_my_address_range(size_t address);

void					show_alloc_mem(void);
void					print_alloc_info(t_block *block);
void					dump_zone(t_type type);
void					dump_block(t_block *block, int lock);
char					digit(int nb, int maj);
void					ft_putnbr_base(intmax_t nb, int base);

#endif
