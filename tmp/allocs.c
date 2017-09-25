#include <malloc.h>
#include <stdlib.h>
#include <libft.h>
#include <sys/mman.h>

t_malloc	g_malloc = {NULL, NULL, NULL, 0};
pthread_mutex_t	g_locker;

int			ft_init_malloc(void)
{
	t_memblock	*cast;

	if (TINY_HEAP || SMALL_HEAP)
		return (0);
	TINY_HEAP = mmap(0, TINY_HEAP_SIZE, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!TINY_HEAP)
		return (1);
	cast = (t_memblock *)TINY_HEAP;
	cast->size = TINY_HEAP_SIZE - BLOCK_SIZE;
	cast->next = NULL;
	cast->free = 1;
	SMALL_HEAP = mmap(0, SMALL_HEAP_SIZE, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!SMALL_HEAP)
		return (1);
	cast = (t_memblock *)SMALL_HEAP;
	cast->size = SMALL_HEAP_SIZE - BLOCK_SIZE;
	cast->next = NULL;
	cast->free = 1;
	LARGE_HEAP = NULL;
	return (0);
}

void		*ft_alloc(t_memblock *last, size_t block_size,
		t_alloc_type type, size_t alloc_size)
{
	t_memblock	*block;

	block = ft_find_block(&last, block_size, type);
	if (block && ((block->size - block_size) >= (BLOCK_SIZE + 8)))
		ft_split_block(block, block_size);
	else if (!block)
	{
		block = ft_extend_heap(last,
				(type == TINY ? TINY_HEAP_SIZE : SMALL_HEAP_SIZE));
		if (!block)
			return (NULL);
		return (ft_alloc(block, block_size, type, alloc_size));
	}
	if (block)
	{
		block->alloc_size = alloc_size;
		block->free = 0;
	}
	return (block->data);
}

t_memblock	*ft_is_valid_block(t_memblock *block)
{
	t_memblock	*tmp;
	t_memblock	*prev;

	if (block == NULL)
		return (NULL);
	if (block->size <= TINY_ALLOC_LIMIT)
		tmp = TINY_HEAP;
	else if (block->size <= SMALL_ALLOC_LIMIT)
		tmp = SMALL_HEAP;
	else
		tmp = LARGE_HEAP;
	prev = tmp;
	while (tmp)
	{
		if (tmp == block)
			return (prev);
		prev = tmp;
		tmp = tmp->next;
	}
	return (NULL);
}

void		ft_merge_blocks(t_memblock *block, t_memblock *prev)
{
	if (block->next == NULL)
		return ;
	while (block->next != NULL && block->next->free == 1)
	{
		block->size += block->next->size + BLOCK_SIZE;
		block->next = block->next->next;
	}
	if (block != NULL && prev != NULL && block != prev && prev->free == 1 &&
			block->free == 1)
	{
		prev->size += block->size + BLOCK_SIZE;
		prev->next = block->next;
	}
}
