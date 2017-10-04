/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:51:36 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/04 11:33:06 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*malloc(size_t size)
{
	void	*ptr;

	if (init())
		return (NULL);
	pthread_mutex_lock(&g_locker);
	ptr = exec_malloc(size);
	pthread_mutex_unlock(&g_locker);
	return (ptr);
}

void	*exec_malloc(size_t size)
{
	size_t	aligned;

	if (size == 0)
		size = ALLOC_MIN;
	aligned = ALIGN_BLOCK_SIZE_8(size);
	if (size <= TINY_ALLOC_LIMIT)
		return (alloc_zone(TINY_HEAP, aligned, TINY, size));
	if (size <= SMALL_ALLOC_LIMIT)
		return (alloc_zone(SMALL_HEAP, aligned, SMALL, size));
	return (alloc_large_zone(size));
}

void	*calloc(size_t count, size_t size)
{
	void	*block;

	block = malloc(count * size);
	if (block)
		ft_bzero(block, count * size);
	return (block);
}
