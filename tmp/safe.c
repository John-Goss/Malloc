#include <malloc.h>

static int	init(void)
{
	if (LOCK_INIT == 1)
		return (0);
	LOCK_INIT = 1;
	pthread_mutex_init(&g_locker, NULL);
	return (ft_init_malloc());
}

void		*malloc(size_t size)
{
	void	*ptr;

	if (init() || size == 0)
		return (NULL);
	pthread_mutex_lock(&g_locker);
	ptr = malloc_unsafe(size);
	pthread_mutex_unlock(&g_locker);
	return (ptr);
}

void		free(void *addr)
{
	if (init())
		return ;
	pthread_mutex_lock(&g_locker);
	free_unsafe(addr);
	pthread_mutex_unlock(&g_locker);
}

void		*realloc(void *addr, size_t size)
{
	void	*ptr;

	if (init() || size == 0)
		return (NULL);
	pthread_mutex_lock(&g_locker);
	ptr = realloc_unsafe(addr, size);
	pthread_mutex_unlock(&g_locker);
	return (ptr);
}
