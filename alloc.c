#include "malloc.h"
/*
int    AllocZone(t_type type, size_t size)
{
    t_block *block;
    t_block *tmp;
    size_t  allocateSize;
    
    if (type == LARGE)
        return (AllocLargeZone(size));
    allocateSize = ALIGN_BLOCK_SIZE_8(type = TINY ? TINY_HEAP_SIZE : SMALL_HEAP_SIZE + sizeof(t_zone));
    block = NULL;
    tmp = g_zone.firstBlock;
    block = mmap(0, allocateSize, PROT_READ | PROT_WRITE,
                        MAP_ANON | MAP_PRIVATE, -1, 0);
    if (block != NULL)
    {
        block->size = allocateSize;
        block->free = 1;
        block->prev = NULL;
        block->next = NULL;
        if (tmp == NULL)
        {
            g_zone.firstBlock = block;
        }
        else
        {
            while (tmp->next)
            {
                tmp->next = block;
                block->prev = tmp;
            }
        }
        return (0);
    }
    return (1);
}

int    AllocLargeZone(size_t size)
{
    t_block *block;
    t_block *tmp;
    size_t  allocateSize;
    
    allocateSize = ALIGN_BLOCK_SIZE_4096(size + sizeof(t_zone));
    block = NULL;
    tmp = NULL;
    block = mmap(0, allocateSize, PROT_READ | PROT_WRITE,
                 MAP_ANON | MAP_PRIVATE, -1, 0);
    if (block != NULL)
    {
        block->size = allocateSize;
        block->free = 1;
        block->prev = NULL;
        block->next = NULL;
        g_zone.firstBlock = block;
        return (0);
    }
    return (1);
}*/
