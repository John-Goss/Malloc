#ifndef MALLOC_H
# define MALLOC_H
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# define TINY_HEAP g_malloc.tiny_heap
# define SMALL_HEAP g_malloc.small_heap
# define TINY_HEAP_SIZE (getpagesize() * 64)
# define SMALL_HEAP_SIZE (getpagesize() * 512)
# define TINY_ALLOC_LIMIT (1024)
# define SMALL_ALLOC_LIMIT ((1024 * 16))
# define LARGE_HEAP g_malloc.large_heap
# define ALLOC_MIN (sizeof(int) * 2)
# define ALIGN_SIZE_8(x) (((((x) - 1) >> 3) << 3) + 8)
# define ALIGN_SIZE_4096(x) (((((x) -1) >> 12) << 12) + 4096)
# define BLOCK_SIZE (sizeof(t_memblock) - sizeof(char *))
# define LOCK_INIT g_malloc.locked

typedef unsigned int	t_ui;

typedef struct			s_memblock
{
	t_ui				size;
	t_ui				alloc_size;
	t_ui				free;
	struct s_memblock	*next;
	char				data[1];
}						t_memblock;

typedef struct			s_malloc
{
	void				*tiny_heap;
	void				*small_heap;
	void				*large_heap;
	int					locked;
}						t_malloc;

extern t_malloc			g_malloc;
extern pthread_mutex_t	g_locker;

typedef enum			e_alloc_type
{
	TINY,
	SMALL,
	LARGE,
	NONE
}						t_alloc_type;

t_alloc_type			get_alloc_type(size_t size);
t_alloc_type			get_block_type(t_memblock *block);
void					ft_merge_blocks(t_memblock *block, t_memblock *prev);
t_memblock				*ft_is_valid_block(t_memblock *block);
void					dump_memory(void);
void					ft_free(void *addr);
void					*ft_realloc(void *addr, size_t size);
void					ft_remove_large_alloc(t_memblock *block,
		t_memblock *prev);

void					*malloc_unsafe(size_t size);
void					free_unsafe(void *addr);
void					*realloc_unsafe(void *addr, size_t size);
void					print_memzone(t_memblock *b, t_ui *total);
void					print_addr(void *addr);
void					show_alloc_mem(void);
void					print_alloc_info(t_memblock *b);
void					dump_zone(t_alloc_type type);

t_memblock				*ft_find_block(t_memblock **last, size_t size,
		t_alloc_type type);
t_memblock				*ft_extend_heap(t_memblock *last, size_t size);
void					ft_split_block(t_memblock *block, size_t size);
void					*ft_large_alloc(size_t size);
void					*ft_alloc(t_memblock *last, size_t block_size,
		t_alloc_type type, size_t alloc_size);
void					*ft_malloc(size_t size);
int						ft_init_malloc(void);
void					*calloc(size_t count, size_t size);
void					*reallocf(void *ptr, size_t size);

void					*malloc(size_t size);
void					free(void *addr);
void					*realloc(void *addr, size_t size);

#endif
