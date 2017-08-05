#include "malloc.h"

static void			*add_to_list(t_head *head, t_list_heap *tmp, size_t size)
{
	if (head == NULL)
		return (NULL);
	write(1, "Could not find free block, try to append...\n", 44);
	if (size < TINY - META_SIZE &&
	((char *)(tmp + 1) + TNY + TINY  < (char *)head->tiny + TINY_MAX))
	{
		write(1, "Adding element to allocated list...\n", 36);
		tmp->next = (t_list_heap *)(char *)(tmp + 1) + TNY;
		tmp->next->next = NULL;
		return (tmp->next);
	}
	write(2, "Not enough space\n", 17);
	return (NULL);
}
/*
** Checks wether a free block exists in the allocated heap list
** TODO: implement merge
** TODO: handle medium
*/
static void			*find_free_block(t_head *head, size_t size)
{
	t_list_heap	*tmp;

	if (head == NULL)
		return (NULL);
	//check if size is tiny, medium or large
	// if size == tiny head = head->tiny_next
	write(1, "Search for free block...\n", 25);
	if (size < TINY - META_SIZE)
	{
		write(1, "in tiny\n", 8);
		tmp = head->tiny;
		while (tmp && tmp->next)
		{
			if (tmp->free == 1)
				return (tmp);
			tmp = tmp->next;
		}
		return add_to_list(head, tmp, size);
	}
	return (NULL);
}

/*
** First memory allocating using mmap(2)
** Allocates more than requested to avoid system calls
** Has a pointer to tiny and meduim allocated lists
** TODO: add medium list
*/

static t_head		*create_head()
{
	if ((head = mmap(NULL,
					TINY_MAX + META_HEAD_SIZE,
					PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == (void*) -1)
	{
		write(2, "mmap(2) error\n", 14);
		return NULL;
	}
	write(1, "Creating head...\n", 17);
	head->size = TINY_MAX;
	head->medium = NULL;
	head->tiny = (t_list_heap *)(head + 1);
	head->tiny->free = 1;
	head->tiny->next = NULL;
	return (head);
}

t_head				*head = NULL;

void				*malloc(size_t size)
{
	t_list_heap	*addr_meta;
	void		*sp;

	if (!head && (head = create_head()) == NULL)
		return (NULL);
	if ((addr_meta = find_free_block(head, size)) != NULL)// si espace free dispo
	{
		addr_meta->free = 0;
		return (addr_meta + 1);
	}
	if ((sp = mmap(NULL, size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == (void*) -1)
	{
		write(2, "mmap(2) error\n", 14);
		return (NULL);
	}
	write(1, "mmap done\n", 10);
	return (sp);
}
