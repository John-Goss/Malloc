/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 18:14:24 by jle-quer          #+#    #+#             */
/*   Updated: 2017/09/28 18:28:55 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	if (init())
		return (NULL);
	pthread_mutex_lock(&g_locker);
	if (ptr && size == 0)
	{
		exec_free(ptr);
		new = exec_malloc(ALLOC_MIN);
	}
	else if (ptr == NULL)
		new = exec_malloc(size);
	else
		new = exec_realloc(ptr, size);
	pthread_mutex_unlock(&g_locker);
	return (ptr);
}

void	*exec_realloc(void *ptr, size_t size)
{
	t_block	*block;
	t_block	*prev;

	if ((prev = is_valid_block((t_block *)(ptr - META_BLOCK_SIZE))) == NULL)
		return (NULL);
	block = (prev == (ptr - META_BLOCK_SIZE)) ? prev : prev->next;
	if (block->next && block->next->free == 1 &&
		block->next->size + block->size >= size &&
		get_block_type(block) == get_alloc_type(size))
	{
		block->size += block->next->size + META_BLOCK_SIZE;
		block->allocsize += size;
		block->next = block->next->next;
		split_block(block, size);
		return (block);
	}
	if ((block = exec_malloc(size)))
	{
		if (block)
			ft_memmove(block, ptr, (prev == ptr - META_BLOCK_SIZE) ?
					prev->size : prev->next->size);
		exec_free(ptr);
	}
	return (block);
}

void	*reallocf(void *ptr, size_t size)
{
	void	*alloc;

	alloc = realloc(ptr, size);
	if (alloc == NULL)
		free(ptr);
	return (alloc);
}

t_type	get_block_type(t_block *block)
{
	if (block->size < TINY_ALLOC_LIMIT)
		return (TINY);
	if (block->size < SMALL_ALLOC_LIMIT)
		return (SMALL);
	return (LARGE);
}

t_type	get_alloc_type(size_t size)
{
	if (size < TINY_ALLOC_LIMIT)
		return (TINY);
	if (size < SMALL_ALLOC_LIMIT)
		return (SMALL);
	return (LARGE);
}
