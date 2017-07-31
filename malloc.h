#include <stdlib.h>
#include <sys/mman.h>
#include "libft/libft.h"
// pour memcpy
#include <string.h>

/*
** free == 1 == is free
*/
typedef struct			s_list_heap
{
	size_t				size;
	int					free;
	struct s_list_heap	*tiny_next;
}						t_list_heap;

# define DEBUG write(2, "SALUT\n", 6);
# define META_BLOCK_SIZE sizeof(t_list_heap)
# define TNY 8
# define TINY 8 + META_BLOCK_SIZE
# define TINY_MAX (8 + META_BLOCK_SIZE) * 4096
/*
** Global var == dynamic lib
*/
extern t_list_heap		*list_head;

/*
** TODO
** # define TINY 1000
** # define MEDIUM 100000
** # define LARGE 1000000
**
** void					show_alloc_mem();
** void					show_alloc_mem();
*/

void					*malloc(size_t size);
void					free(void *ptr);
void					*realloc(void *ptr, size_t size);
