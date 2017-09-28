/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:16:35 by jle-quer          #+#    #+#             */
/*   Updated: 2017/09/28 17:36:21 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*alloc_zone(t_block *last, size_t blocksize, t_type type,
		size_t allocated_size)
{
	t_block	*block;

	block = find_free_block(&last, blocksize, type);
	if (block && ((block->size - blocksize) >= (META_BLOCK_SIZE + 8)))
		split_block(block, blocksize);
	else if (!block)
	{
		block = extend_heap(last, (type == TINY ?
					TINY_HEAP_SIZE : SMALL_HEAP_SIZE));
		if (!block)
			return (NULL);
		return (alloc_zone(block, blocksize, type, allocated_size));
	}
	if (block)
	{
		block->allocsize = allocated_size;
		block->free = 0;
	}
	return (block->data);
}

void	*alloc_large_zone(size_t size)
{
	t_block	*block;
	size_t	alignsize;

	alignsize = ALIGN_BLOCK_SIZE_4096(size);
	block = mmap(0, alignsize + META_BLOCK_SIZE, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	block->size = size;
	block->allocsize = alignsize;
	block->next = LARGE_HEAP;
	LARGE_HEAP = block;
	return (block->data);
}

void	*extend_heap(t_block *last, size_t size)
{
	t_block	*new;

	new = mmap(0, size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
	if (new)
	{
		new->size = size - META_BLOCK_SIZE;
		new->free = 1;
		if (last)
			last->next = new;
	}
	return (new);
}

void	split_block(t_block *block, size_t size)
{
	t_block	*new_block;

	new_block = (t_block *)(block->data + size);
	new_block->size = block->size - size - META_BLOCK_SIZE;
	new_block->next = block->next;
	new_block->free = 1;
	block->size = size;
	block->next = new_block;
}

void	*find_free_block(t_block **last, size_t blocksize, t_type type)
{
	t_block	*block;

	if (type == TINY)
		block = (t_block *)TINY_HEAP;
	else if (type == SMALL)
		block = (t_block *)SMALL_HEAP;
	else
		block = (t_block *)LARGE_HEAP;
	while (block && !(block->free && block->size >= blocksize))
	{
		*last = block;
		block = block->next;
	}
	return (block);
}
