#include "malloc.h"

void	ft_free(void *ptr)
{
    t_block *block;
    
    block = NULL;
	if (ptr == NULL || !ptr)
		return;
    IsValidBlock(((t_block **)&ptr), &block, TINY);
    if (block == NULL)
        return;
    block->free = 1;
    printf("PTR = [%p]\n\n", ptr - META_BLOCK_SIZE + 8);
    printf ("Block = [%p]\n", block);
    printf ("Block->data = [%p]\n", block->data);
}

void    IsValidBlock(t_block **ptr, t_block **dst, t_type type)
{
    t_block *ref;
    t_block *tmp;
    
    ref = *ptr;
    if (type == TINY)
        tmp = (t_block *)TINY_HEAP;
    else if (type == SMALL)
        tmp = (t_block *)SMALL_HEAP;
    else if (type == LARGE)
        tmp = (t_block *)LARGE_HEAP;
    else
        return;
    printf("TMP : %p\nREF : %p\n", tmp->data, ref);
    while (tmp)
    {
        if ((void *)tmp->data == (void *)ref && tmp->free == 0)
            *dst = tmp;
        tmp = tmp->next;
    }
    IsValidBlock(ptr, dst, type + 1);
    return;
}
