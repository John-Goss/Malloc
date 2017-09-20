#include "malloc.h"

int	Init(void)
{
    if (LOCK_INIT == 1)
        return (0);
    LOCK_INIT = 1;
    pthread_mutex_init(&g_locker, NULL);
    return (ZoneInit());
}

int    ZoneInit(void)
{
    if (g_zone.firstBlock)
        return (1);
    g_zone.firstBlock = mmap(0, TINY_HEAP_SIZE, PROT_READ | PROT_WRITE,
                        MAP_ANON | MAP_PRIVATE, -1, 0);
    if (!g_zone.firstBlock)
        return (1);
    g_zone.prev = NULL;
    g_zone.firstBlock->size = TINY_HEAP_SIZE - META_ZONE_SIZE;
    g_zone.next = mmap(0, SMALL_HEAP_SIZE, PROT_READ | PROT_WRITE,
                       MAP_ANON | MAP_PRIVATE, -1, 0);
    if (!g_zone.next)
        return (1);
    g_zone.firstBlock->next->size = SMALL_HEAP_SIZE - META_ZONE_SIZE;
    g_zone.next->prev = &g_zone;
    return (0);
}
/*
void    InitZone(size_t size)
{
    g_zone.size = 0;
    g_zone.block = NULL;
    g_zone.prev = NULL;
    g_zone.next = NULL;
    
    if (size <= TINY_ALLOC_LIMIT)
    {
        AllocTiny();
    }
    else if (size <= SMALL_ALLOC_LIMIT)
    {
        AllocSmall();
    }
    else
    {
        AllocLarge();
    }
    
}
*/
