#include "malloc.h"

void	ft_free(void *ptr)
{
    if (Init())
        return;
    pthread_mutex_lock(&g_locker);
    ExecFree(ptr);
    pthread_mutex_unlock(&g_locker);
}

void	ExecFree(void *ptr)
{
    t_block *block;
    t_block *prev;
    
	if (ptr == NULL)
		return;
    block = (t_block *)(ptr - META_BLOCK_SIZE);
    prev = IsValidBlock(block);
    if (prev != NULL && block->free == 0)
    {
        block->free = 1;
        if (block->size > SMALL_ALLOC_LIMIT)
            return (RemoveLargeAlloc(block, prev));
        MergeBlocks(block, prev);
    }
}

t_block  *IsValidBlock(t_block *block)
{
    t_block *prev;
    t_block *tmp;
    
    if (block == NULL)
        return (NULL);
    if (block->size <= TINY_ALLOC_LIMIT)
        tmp = (t_block *)TINY_HEAP;
    else if (block->size <= SMALL_ALLOC_LIMIT)
        tmp = (t_block *)SMALL_HEAP;
    else
        tmp = (t_block *)LARGE_HEAP;
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
