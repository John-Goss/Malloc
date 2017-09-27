#include "malloc.h"

void	*malloc(size_t size)
{
    void	*ptr;
    
    if (Init() || size == 0)
        return (NULL);
    pthread_mutex_lock(&g_locker);
    ptr = ExecMalloc(size);
    pthread_mutex_unlock(&g_locker);
    return (ptr);
}

void	*ExecMalloc(size_t size)
{
    size_t	aligned;
    
    aligned = ALIGN_BLOCK_SIZE_8(size);
    if (size <= TINY_ALLOC_LIMIT)
        return (AllocZone(TINY_HEAP, aligned, TINY, size));
    if (size <= SMALL_ALLOC_LIMIT)
        return (AllocZone(SMALL_HEAP, aligned, SMALL, size));
    return (AllocLargeZone(size));
}

void	*calloc(size_t count, size_t size)
{
    void	*block;
    
    block = malloc(count * size);
    ft_bzero(block, count * size);
    return (block);
}
