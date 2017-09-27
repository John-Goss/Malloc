 #include "malloc.h"

void    *AllocZone(t_block *last, size_t blockSize, t_type type, size_t allocSize)
{
    t_block *block;
    
    block = FindFreeBlock(&last, blockSize, type);
    if (block && ((block->size - blockSize) >= (META_BLOCK_SIZE + 8)))
        SplitBlock(block, blockSize);
    else if (!block)
    {
        block = ExtendHeap(last, (type == TINY ? TINY_HEAP_SIZE : SMALL_HEAP_SIZE));
        if (!block)
            return (NULL);
        return (AllocZone(block, blockSize, type, allocSize));
    }
    if (block)
    {
        block->allocSize = allocSize;
        block->free = 0;
    }
    return (block->data);
}

void    *AllocLargeZone(size_t size)
{
    t_block *block;
    size_t  alignSize;
    
    alignSize = ALIGN_BLOCK_SIZE_4096(size);
    block = mmap(0, alignSize + META_BLOCK_SIZE, PROT_READ | PROT_WRITE,
                 MAP_ANON | MAP_PRIVATE, -1, 0);
    block->size = size;
    block->allocSize = alignSize;
    block->next = LARGE_HEAP;
    LARGE_HEAP = block;
    return (block->data);
}

void    *ExtendHeap(t_block *last, size_t size)
{
    t_block *new;
    
    new = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (new)
    {
        new->size = size - META_BLOCK_SIZE;
        new->free = 1;
        if (last)
            last->next = new;
    }
    return (new);
}

void    SplitBlock(t_block *block, size_t size)
{
    t_block	*new_block;
    
    new_block = (t_block *)(block->data + size);
    new_block->size = block->size - size - META_BLOCK_SIZE;
    new_block->next = block->next;
    new_block->free = 1;
    block->size = size;
    block->next = new_block;
}

void    *FindFreeBlock(t_block **last, size_t blockSize, t_type type)
{
    t_block *block;
    
    if (type == TINY)
        block = (t_block *)TINY_HEAP;
    else if (type == SMALL)
        block = (t_block *)SMALL_HEAP;
    else
        block = (t_block *)LARGE_HEAP;
    while (block && !(block->free && block->size >= blockSize))
    {
        *last = block;
        block = block->next;
    }
    return (block);
}
