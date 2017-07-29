#include "malloc.h"

t_link_heap	*link_head = NULL;

/*
** Calls to mmap(2) 's system if no free space available in malloc list
*/
static void			*system_call(t_link_heap *head, size_t size)
{
	t_link_heap	*new;

// Les operations sont repetees (voir first_request) en prevision de
// l'implementation des differentes sizes

	if (head == NULL)
		return (NULL);
	if ((new = mmap(NULL, size + META_BLOCK_SIZE, PROT_READ | PROT_WRITE,
	MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
	{
		write(2, "mmap(2) error: request failed\n", 30);
		return (NULL);
	}
	new->free = 0;
	new->size = size;
	new->next = NULL;
	while (head->next)
		head = head->next;
	head->next = new;
	return (new);
}

/*
** Checks wether or not a free block exists in the allocated heap list
*/
static void			*find_free_block(t_link_heap *list, size_t size)
{
	if (list == NULL)
		return (NULL);
	while (list)
	{
		if (list->free == 1 && list->size >= size + META_BLOCK_SIZE)
			return (list);
		else
			list = list->next;
	}
	return NULL;
}

/*
** First memory allocating using mmap(2)
** Allocates more than requested to avoid system calls
*/
static t_link_heap	*first_request()
{
	t_link_heap	*ptr;

	if ((ptr = mmap(NULL, 10000 + META_BLOCK_SIZE, PROT_READ | PROT_WRITE,
	MAP_ANONYMOUS, -1, 0)) == MAP_FAILED)
	{
		write(2, "mmap(2) error: request failed\n", 30);
		return NULL;
	}
	ptr->size = 10000;
	ptr->free = 0;
	ptr->next = NULL;
	return (ptr);
}

/*
** libc malloc
*/
void				*ft_malloc(size_t size)
{
	t_link_heap	*link_meta;
	void		*link_space;

	if (!link_head)// premier appel du process a malloc
	{
		if ((link_head = first_request()) == NULL)
			return (NULL);
		link_space = link_head + META_BLOCK_SIZE;
	}
	else if ((link_meta = find_free_block(link_head, size)) != NULL)// si espace free dispo
	{
		link_meta->free = 0;
		link_space = link_meta + META_BLOCK_SIZE;
	}
	else// appel a mmap(2)
	{
		if ((link_meta = system_call(link_head, size)) == NULL)
			return (NULL);
		link_space = link_meta + META_BLOCK_SIZE;
	}
	return (link_space);
}






