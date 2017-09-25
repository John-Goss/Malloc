#include <malloc.h>
#include <stdlib.h>
#include <libft.h>

void		*realloc_unsafe(void *addr, size_t size)
{
	t_memblock	*block;
	t_memblock	*prev;

	if (addr == NULL)
		return (malloc_unsafe(size));
	if ((prev = ft_is_valid_block((t_memblock *)(addr - BLOCK_SIZE))) == NULL)
		return (NULL);
	block = (prev == (addr - BLOCK_SIZE)) ? prev : prev->next;
	if (block->next && block->next->free == 1 &&
			block->next->size + block->size >= size &&
			get_block_type(block) == get_alloc_type(size))
	{
		block->size += block->next->size + BLOCK_SIZE;
		block->alloc_size += size;
		block->next = block->next->next;
		ft_split_block(block, size);
		return (block);
	}
	if ((block = malloc_unsafe(size)))
	{
		ft_memmove(block, addr, (prev == addr - BLOCK_SIZE) ?
				prev->size : prev->next->size);
		free_unsafe(addr);
	}
	return (block);
}

void		free_unsafe(void *addr)
{
	t_memblock		*block;
	t_memblock		*prev;

	if (addr == NULL)
		return ;
	block = (t_memblock *)(addr - BLOCK_SIZE);
	prev = ft_is_valid_block(block);
	if (prev != NULL && block->free == 0)
	{
		block->free = 1;
		if (block->size > SMALL_ALLOC_LIMIT)
			return (ft_remove_large_alloc(block, prev));
		ft_merge_blocks(block, prev);
	}
}

void		*malloc_unsafe(size_t size)
{
	size_t	aligned;

	aligned = ALIGN_SIZE_8(size);
	if (size <= TINY_ALLOC_LIMIT)
		return (ft_alloc(TINY_HEAP, aligned, TINY, size));
	if (size <= SMALL_ALLOC_LIMIT)
		return (ft_alloc(SMALL_HEAP, aligned, SMALL, size));
	return (ft_large_alloc(size));
}

void		*calloc(size_t count, size_t size)
{
	void	*block;

	block = malloc(count * size);
	ft_bzero(block, count * size);
	return (block);
}

void		*reallocf(void *ptr, size_t size)
{
	void	*alloc;

	alloc = realloc(ptr, size);
	if (alloc == NULL)
		free(ptr);
	return (alloc);
}
