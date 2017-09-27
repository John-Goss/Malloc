#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
    void	*new;
    
    if (Init() || size == 0)
        return (NULL);
    pthread_mutex_lock(&g_locker);
    new = ExecRealloc(ptr, size);
    pthread_mutex_unlock(&g_locker);
    return (ptr);
}

void	*ExecRealloc(void *ptr, size_t size)
{
    t_block	*block;
    t_block	*prev;
    
    if (ptr == NULL)
        return (ExecMalloc(size));
    if ((prev = IsValidBlock((t_block *)(ptr - META_BLOCK_SIZE))) == NULL)
        return (NULL);
    block = (prev == (ptr - META_BLOCK_SIZE)) ? prev : prev->next;
    if (block->next && block->next->free == 1 &&
        block->next->size + block->size >= size &&
        GetBlockType(block) == GetAllocType(size))
    {
        block->size += block->next->size + META_BLOCK_SIZE;
        block->allocSize += size;
        block->next = block->next->next;
        SplitBlock(block, size);
        return (block);
    }
    if ((block = ExecMalloc(size)))
    {
        //TODO: changes memove by ft_memmove
        memmove(block, ptr, (prev == ptr - META_BLOCK_SIZE) ?
                   prev->size : prev->next->size);
        ExecFree(ptr);
    }
    return (block);
}

void	*reallocf(void *ptr, size_t size)
{
    void	*alloc;
    
    alloc = realloc(ptr, size);
    if (alloc == NULL)
        free(ptr);
    return (alloc);
}

t_type	GetBlockType(t_block *block)
{
    if (block->size < TINY_ALLOC_LIMIT)
        return (TINY);
    if (block->size < SMALL_ALLOC_LIMIT)
        return (SMALL);
    return (LARGE);
}

t_type	GetAllocType(size_t size)
{
    if (size < TINY_ALLOC_LIMIT)
        return (TINY);
    if (size < SMALL_ALLOC_LIMIT)
        return (SMALL);
    return (LARGE);
}
