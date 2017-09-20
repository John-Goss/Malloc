#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>
# include <sys/mman.h>
# include <unistd.h>
# include "libft/INCLUDES/libft.h"
# include <pthread.h>

# define LOCK_INIT g_zone.locked
# define META_BLOCK_SIZE sizeof(t_block)
# define META_ZONE_SIZE sizeof(t_zone)
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
    int             free;
    struct s_block  *prev;
    struct s_block  *next;
}                   t_block;

typedef struct      s_zone
{
    size_t          size;
    int             locked;
    struct s_block  *firstBlock;
    struct s_zone   *prev;
    struct s_zone   *next;
}                   t_zone;

extern t_zone           g_zone;
extern pthread_mutex_t	g_locker;

void    *ft_malloc(size_t size);
void    *ft_calloc(size_t count, size_t size);
void	*ft_realloc(void *ptr, size_t size);

void	ft_free(void *ptr);

int     ZoneInit(void);
int     Init(void);

#endif
