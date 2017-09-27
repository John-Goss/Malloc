#include "malloc.h"

static void	PrintAddress(void *addr)
{
    //write(1, "0x", 2);
    //ft_putnbr((size_t)addr, 16);
    printf("0x%09X", (unsigned int)addr);
}

static void	PrintAllocInfo(t_block *block)
{
/*  PrintAddress((void *)(block->data));
    write(1, " - ", 3);
    PrintAddress((void *)(block->data + block->size));
    write(1, " : ", 3);
    //ft_putnbr((int)(block->allocSize), 10);
    printf("%zu", block->allocSize);
    write(1, " octets\n", 8);
*/
    printf("0x%09X - 0x%09X : %zu octets\n",(unsigned int)block->data, (unsigned int)(block->data + block->size), block->allocSize);
}

static void	PrintMemory(t_block *block, unsigned int *total)
{
    printf("0x%09X\n", (unsigned int)block);
    //write(1, "\n", 1);
    while (block)
    {
        if (block->free == 0)
        {
            PrintAllocInfo(block);
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
    printf("Total : %u octets\n", total);
}
