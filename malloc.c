#include "malloc.h"

static void			*add_to_list(t_list_heap *head, size_t size)
{
	t_list_heap	*tmp;

	if (head == NULL)
		return (NULL);
	tmp = head->tiny_next;
	while (tmp && tmp->tiny_next)
		tmp = tmp->tiny_next;
	if (head->tiny_next + TINY_MAX < tmp + META_BLOCK_SIZE - 1 + size + META_BLOCK_SIZE)
	{
		write(2, "Not enough space\n", 17);
		return (NULL);
	}
	tmp->tiny_next = tmp + META_BLOCK_SIZE  + tmp->size;
	tmp = tmp->tiny_next;
	tmp->size = getpagesize() * TNY;
	tmp->free = 0;
	tmp->tiny_next = NULL;
	return (tmp);
}
/*
** Checks wether a free block exists in the allocated heap list
** TODO: implement merge
*/
static void			*find_free_block(t_list_heap *head, size_t size)
{
	t_list_heap	*tmp;

	if (head == NULL)
		return (NULL);
	//check if size is tiny, medium or large
	// if size == tiny head = head->tiny_next
	tmp = head->tiny_next;
	while (tmp && tmp->tiny_next)
	{
		if (tmp->free == 1 && tmp->size >= size)
			return (tmp);
		tmp = tmp->tiny_next;
	}
	return (NULL);
}

/*
** First memory allocating using mmap(2)
** Allocates more than requested to avoid system calls
** Has a pointer to tiny allocated list
** TODO: add medium list
*/

static t_list_heap	*create_head()
{
	if ((list_head = mmap(NULL, getpagesize() * 100 * TINY + META_BLOCK_SIZE,
	PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == (void*) -1)
	{
		write(2, "mmap(2) error\n", 14);
		return NULL;
	}
	list_head->size = getpagesize() * 100 * TINY; // + medium
	list_head->free = 0;
	list_head->tiny_next = (t_list_heap *)(list_head + META_BLOCK_SIZE);
	list_head->tiny_next->size = getpagesize() * TNY;
	list_head->tiny_next->free = 1;
	list_head->tiny_next->tiny_next = NULL;
	return (list_head);
}

t_list_heap	*list_head = NULL;

void				*malloc(size_t size)
{
	t_list_heap	*list_meta;
	void		*list_space;

	if (!list_head && (list_head = create_head()) == NULL)
		return (NULL);
	if ((list_meta = find_free_block(list_head, size)) != NULL)// si espace free dispo
	{
		list_meta->free = 0;
		list_space = list_meta + META_BLOCK_SIZE;
	}
	else// appel a mmap(2)
	{
		if ((list_meta = add_to_list(list_head, size)) == NULL)
			return (NULL);
		list_space = list_meta + META_BLOCK_SIZE;
	}
	if (list_space != NULL)
		write(1, "YEEES\n", 6);
	return (list_space);
}
