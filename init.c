#include "malloc.h"

t_zone          g_zone = {NULL, NULL, NULL, 0};
pthread_mutex_t	g_locker;

int	Init(void)
{
    if (LOCK_INIT == 1)
        return (0);
    LOCK_INIT = 1;
    pthread_mutex_init(&g_locker, NULL);
    return (HeapInit());
}

int HeapInit(void)
{
    t_block *tmp;
    
    if (TINY_HEAP || SMALL_HEAP)
        return (0);
    TINY_HEAP = mmap(0, TINY_HEAP_SIZE, PROT_READ | PROT_WRITE,
                        MAP_ANON | MAP_PRIVATE, -1, 0);
    if (!TINY_HEAP)
        return (1);
    tmp = (t_block *)TINY_HEAP;
    tmp->size = TINY_HEAP_SIZE - META_BLOCK_SIZE;
    tmp->free = 1;
    tmp->next = NULL;
    SMALL_HEAP = mmap(0, SMALL_HEAP_SIZE, PROT_READ | PROT_WRITE,
                       MAP_ANON | MAP_PRIVATE, -1, 0);
    if (!SMALL_HEAP)
        return (1);
    tmp = (t_block *)SMALL_HEAP;
    tmp->size = SMALL_HEAP_SIZE - META_BLOCK_SIZE;
    tmp->free = 1;
    tmp->next = NULL;
    LARGE_HEAP = NULL;
    return (0);
}
