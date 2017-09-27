#include "malloc.c"

static void	PrintAddress(void *addr)
{
    write(1, "0x", 2);
    ft_putnbr((size_t)addr, 16);
}

static void	print_alloc_info(t_block *block)
{
    PrintAddress((void *)(block->data));
    write(1, " - ", 3);
    PrintAddress((void *)(block->data + block->size));
    write(1, " : ", 3);
    ft_putnbr((int)(block->allocSize), 10);
    write(1, " octets\n", 8);
}

static void	PrintMemory(t_block *block, unsigned int *total)
{
    PrintAddress(block);
    write(1, "\n", 1);
    while (block)
    {
        if (block->free == 0)
        {
            print_alloc_info(block);
            *total += block->size;
        }
        block = block->next;
    }
}

void        show_alloc_mem(void)
{
    t_block         *tmp;
    unsigned int	total;
    
    total = 0;
    tmp = TINY_HEAP;
    write(1, "TINY : ", 7);
    PrintMemory(tmp, &total);
    tmp = SMALL_HEAP;
    write(1, "SMALL : ", 8);
    PrintMemory(tmp, &total);
    tmp = LARGE_HEAP;
    write(1, "LARGE : ", 8);
    PrintMemory(tmp, &total);
    ft_printf("Total : %u octets\n", total);
}
