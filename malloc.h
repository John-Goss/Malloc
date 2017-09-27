#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include <stdio.h>
//# include "libft/INCLUDES/libft.h"
# include <pthread.h>

# define LOCK_INIT g_zone.locked
# define TINY_HEAP g_zone.tinyHeap
# define SMALL_HEAP g_zone.smallHeap
# define LARGE_HEAP g_zone.largeHeap
# define META_BLOCK_SIZE (sizeof(t_block) - sizeof(char *))
# define TINY_HEAP_SIZE (getpagesize() * 64)
# define SMALL_HEAP_SIZE (getpagesize() * 512)
# define TINY_ALLOC_LIMIT (1024)
# define SMALL_ALLOC_LIMIT ((1024 * 16))
# define ALLOC_MIN (sizeof(int) * 2)
# define ALIGN_BLOCK_SIZE_8(x) (((((x) - 1) >> 3) << 3) + 8)
# define ALIGN_BLOCK_SIZE_4096(x) (((((x) - 1) >> 12) << 12) + 4096)

typedef enum        e_type
{
    TINY,
    SMALL,
    LARGE,
    NONE
}                   t_type;

typedef struct      s_block
{
    size_t          size;
    size_t          allocSize;
    int             free;
    struct s_block  *next;
    char            data[1];
}                   t_block;

typedef struct      s_zone
{
    void			*tinyHeap;
    void			*smallHeap;
    void			*largeHeap;
    int				locked;
}                   t_zone;

extern t_zone           g_zone;
extern pthread_mutex_t	g_locker;

void    *malloc(size_t size);
void	*ExecMalloc(size_t size);
void    *calloc(size_t count, size_t size);
void	*realloc(void *ptr, size_t size);
void	*ExecRealloc(void *addr, size_t size);
void	*reallocf(void *ptr, size_t size);
void	free(void *ptr);
void	ExecFree(void *ptr);
void    *LockedMalloc(size_t size);
void    *FindFreeBlock(t_block **last, size_t blockSize, t_type type);
t_block *IsValidBlock(t_block *ptr);
void    *AllocZone(t_block *last, size_t blockSize, t_type type, size_t allocSize);
void    *AllocLargeZone(size_t size);
void    *ExtendHeap(t_block *last, size_t size);
void    SplitBlock(t_block *block, size_t size);
void    MergeBlocks(t_block *block, t_block *prev);
void    RemoveLargeAlloc(t_block *block, t_block *prev);
t_type	GetBlockType(t_block *block);
t_type	GetAllocType(size_t size);

int     HeapInit(void);
int     Init(void);

void	show_alloc_mem(void);

#endif
