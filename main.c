#include "malloc.h"

int	main(void)
{
	char *ptr;
	for (int i = 0; i < 1024; ++i)
	{
		ptr = malloc(1024);
		ptr[0] = 42;
		free(ptr);
	}
	show_alloc_mem();
	return (0);
}
