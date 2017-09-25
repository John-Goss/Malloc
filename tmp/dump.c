#include <malloc.h>
#include <libft.h>

static void	dump_block(t_memblock *block)
{
	char	*ptr;

	ptr = block->data;
	while (ptr < block->data + block->size)
	{
		ft_putnbr((int)(*ptr), 16);
		ft_putstr(" ");
		++ptr;
	}
}

void		dump_zone(t_alloc_type type)
{
	t_memblock	*heap_start;

	if (type == TINY)
		heap_start = TINY_HEAP;
	else if (type == SMALL)
		heap_start = SMALL_HEAP;
	else
		heap_start = LARGE_HEAP;
	while (heap_start)
	{
		if (heap_start->free == 0)
		{
			print_alloc_info(heap_start);
			dump_block(heap_start);
			ft_putendl("");
		}
		heap_start = heap_start->next;
	}
}
