/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 18:14:24 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/04 18:48:33 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	if (init())
		return (NULL);
	pthread_mutex_lock(&g_locker);
	if (ptr && size == 0)
	{
		exec_free(ptr);
		ptr = NULL;
		ptr = exec_malloc(ALLOC_MIN);
	}
	else if (ptr == NULL)
		ptr = exec_malloc(size);
	else
		ptr = exec_realloc(ptr, size);
	pthread_mutex_unlock(&g_locker);
	return (ptr);
}

void	*exec_realloc(void *ptr, size_t size)
{
	t_block	*b;
	t_block	*prev;
	size_t	aligned;

	aligned = ALIGN_BLOCK_SIZE_8(size);
	if (!in_my_address_range((size_t)ptr - META_BLOCK_SIZE) ||
		(prev = is_valid_block((t_block *)(ptr - META_BLOCK_SIZE))) == NULL)
		return (NULL);
	b = (prev == (ptr - META_BLOCK_SIZE)) ? prev : prev->next;
	if (b->next && b->next->free == 1 && b->next->size + b->size >= aligned &&
		get_block_type(b) == get_alloc_type(aligned))
	{
		b->size += b->next->size + META_BLOCK_SIZE;
		b->allocsize += size;
		b->next = b->next->next;
		split_block(b, aligned);
		return (b);
	}
	if ((b = exec_malloc(size)))
	{
		ft_memmove(b, ptr, (prev == ptr - META_BLOCK_SIZE) ?
				prev->allocsize : prev->next->allocsize);
		exec_free(ptr);
	}
	return (b);
}

void	*reallocf(void *ptr, size_t size)
{
	void	*new;

	new = realloc(ptr, size);
	if (new == NULL)
		free(ptr);
	return (new);
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
