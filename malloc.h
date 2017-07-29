#include <stdlib.h>
#include <sys/mman.h>
#include "libft/libft.h"


/*
** free == 1 == is free
*/
typedef struct			s_link_heap
{
	size_t				size;
	int					free;
	struct s_link_heap	*next;
}						t_link_heap;

# define META_BLOCK_SIZE sizeof(t_link_heap)

/*
** Global var == dynamic lib
*/
extern t_link_heap *link_head;

/*
** TODO
** # define TINY 1000
** # define MEDIUM 100000
** # define LARGE 1000000
**
** void					show_alloc_mem();
** void					free(void *ptr);
** void					*realloc(void *ptr, size_t size);
** void					show_alloc_mem();
*/

void					*ft_malloc(size_t size);
