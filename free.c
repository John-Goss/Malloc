#include <sys/mman.h>
#include <stdlib.h>

void	free(void *ptr)
{
	if (ptr == NULL || !ptr)
		return;
	munmap(ptr, sizeof(ptr));
	if (ptr || ptr != NULL)
		ptr = NULL;
}
