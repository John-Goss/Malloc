/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:51:36 by jle-quer          #+#    #+#             */
/*   Updated: 2017/09/28 17:53:00 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_malloc(size_t size)
{
	void	*ptr;

	if (size == 0)
		size = ALLOC_MIN;
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

int		main(void)
{
	char	*str = ft_malloc(100);
    char	*str2 = ft_malloc(100);
    char	*str3 = ft_malloc(100);
    //ft_free(str);
    //ft_free(str3);
    t_block *tiny_heap = (t_block *)g_zone.tiny_heap;
    int i = 0;
    while (tiny_heap)
    {
        i++;
        ft_printf("Address of Block : %p\nBlock->free : %d\nBlock->size : %d\nBlock->allocSize : %d\n\n", tiny_heap->data, tiny_heap->free, tiny_heap->size, tiny_heap->allocsize);

        tiny_heap = tiny_heap->next;
    }
    ft_printf("Number of blocks : %d\nMeta Block Size : %d\n", i, META_BLOCK_SIZE);
    return 0;
}
