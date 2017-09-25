#include <malloc.h>
#include <unistd.h>
#include <sys/mman.h>
#include <libft.h>

t_memblock	*ft_find_block(t_memblock **last, size_t size, t_alloc_type type)
{
	t_memblock *b;

	if (type == TINY)
		b = (t_memblock *)(TINY_HEAP);
	else if (type == SMALL)
		b = (t_memblock *)(SMALL_HEAP);
	else
		b = (t_memblock *)(LARGE_HEAP);
	while (b && !(b->free && b->size >= size))
	{
		*last = b;
		b = b->next;
	}
	return (b);
}

t_memblock	*ft_extend_heap(t_memblock *last, size_t size)
{
	t_memblock	*b;

	b = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE,
			-1, 0);
	if (b)
	{
		b->size = size - BLOCK_SIZE;
		b->next = NULL;
		b->free = 1;
	}
	if (last)
		last->next = b;
	return (b);
}

void		ft_split_block(t_memblock *block, size_t size)
{
	t_memblock	*new_block;

	new_block = (t_memblock *)(block->data + size);
	new_block->size = block->size - size - BLOCK_SIZE;
	new_block->next = block->next;
	new_block->free = 1;
	block->size = size;
	block->next = new_block;
}

void		*ft_large_alloc(size_t size)
{
	t_memblock	*new_block;
	size_t		s;

	s = size;
	size = ALIGN_SIZE_4096(size);
	new_block = mmap(0, size + BLOCK_SIZE, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	new_block->size = size;
	new_block->alloc_size = s;
	new_block->next = LARGE_HEAP;
	LARGE_HEAP = new_block;
	return (new_block->data);
}

void		ft_remove_large_alloc(t_memblock *block, t_memblock *prev)
{
	if (prev == block)
		LARGE_HEAP = block->next;
	else
		prev->next = block->next;
	munmap((void *)block, block->size);
}
