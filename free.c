#include "malloc.h"

/*
** Actually frees only if size is big enough
** to minimize syscall
*/
void	free(void *ptr)
{
	t_link_heap	*meta;

	if (ptr == NULL || !ptr)
		return;
	meta = ptr - META_BLOCK_SIZE;
	//if meta->size >...
	//else if{
	meta->free = 1;
}
