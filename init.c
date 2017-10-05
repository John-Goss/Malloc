/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:00:36 by jle-quer          #+#    #+#             */
/*   Updated: 2017/09/28 16:03:32 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_zone			g_zone = {NULL, NULL, NULL, 0};
pthread_mutex_t	g_locker;

int	init(void)
{
	if (LOCK_INIT == 1)
		return (0);
	LOCK_INIT = 1;
	pthread_mutex_init(&g_locker, NULL);
	return (heap_init());
}

int	heap_init(void)
{
	t_block *tmp;

	if (TINY_HEAP || SMALL_HEAP)
		return (0);
	TINY_HEAP = mmap(0, TINY_HEAP_SIZE, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!TINY_HEAP)
		return (1);
	tmp = (t_block *)TINY_HEAP;
	tmp->size = TINY_HEAP_SIZE - META_BLOCK_SIZE;
	tmp->free = 1;
	tmp->next = NULL;
	SMALL_HEAP = mmap(0, SMALL_HEAP_SIZE, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_PRIVATE, -1, 0);
	if (!SMALL_HEAP)
		return (1);
	tmp = (t_block *)SMALL_HEAP;
	tmp->size = SMALL_HEAP_SIZE - META_BLOCK_SIZE;
	tmp->free = 1;
	tmp->next = NULL;
	LARGE_HEAP = NULL;
	return (0);
}

int	in_my_address_range(size_t address)
{
	t_block	*tmp;

	tmp = TINY_HEAP;
	while (tmp)
	{
		if (address == (size_t)tmp)
			return (1);
		tmp = tmp->next;
	}
	tmp = SMALL_HEAP;
	while (tmp)
	{
		if (address == (size_t)tmp)
			return (1);
		tmp = tmp->next;
	}
	tmp = LARGE_HEAP;
	while (tmp)
	{
		if (address == (size_t)tmp)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
