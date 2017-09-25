#include <malloc.h>
#include <libft.h>

void	show_alloc_mem(void)
{
	t_memblock	*b;
	t_ui		total;

	total = 0;
	b = TINY_HEAP;
	write(1, "TINY : ", 7);
	print_memzone(b, &total);
	b = SMALL_HEAP;
	write(1, "SMALL : ", 8);
	print_memzone(b, &total);
	b = LARGE_HEAP;
	write(1, "LARGE : ", 8);
	print_memzone(b, &total);
	write(1, "Total: ", 7);
	ft_putnbr((int)total, 10);
	write(1, " octets\n", 8);
}

void	print_addr(void *addr)
{
	write(1, "0x", 2);
	ft_putnbr((size_t)addr, 16);
}

void	print_memzone(t_memblock *b, t_ui *total)
{
	print_addr(b);
	write(1, "\n", 1);
	while (b)
	{
		if (b->free == 0)
		{
			print_alloc_info(b);
			*total += b->size;
		}
		b = b->next;
	}
}

void	print_alloc_info(t_memblock *b)
{
	print_addr((void *)(b->data));
	write(1, " - ", 3);
	print_addr((void *)(b->data + b->size));
	write(1, " : ", 3);
	ft_putnbr((int)(b->alloc_size), 10);
	write(1, " octets\n", 8);
}
