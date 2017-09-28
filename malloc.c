/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 17:51:36 by jle-quer          #+#    #+#             */
/*   Updated: 2017/09/28 18:29:14 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_malloc(size_t size)
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

	block = ft_malloc(count * size);
	if (block)
		ft_bzero(block, count * size);
	return (block);
}

int		main(void)
{
    int i = 0;
    char *str1 = NULL;
    while (i < TINY_HEAP_SIZE)
    {
        i += 1000;
        str1 = ft_malloc(1000);
    }
    char *str2;
    str2 = ft_malloc(1000);
    ft_free(str2);
    ft_free(str1);
//    char	*str2 = ft_malloc(TINY_HEAP_SIZE - 1);
//    char	*str3 = ft_malloc(TINY_ALLOC_LIMIT - 1);
//    char    *str4 = ft_malloc(TINY_ALLOC_LIMIT);
//    //ft_free(str3);
    //ft_free(str2);
    t_block *tiny_heap = (t_block *)g_zone.tiny_heap;
//    int i = 0;
//    while (tiny_heap)
//    {
//        i++;
//        ft_printf("Address of Block : %p\nBlock->free : %d\nBlock->size : %d\nBlock->allocSize : %d\n\n", tiny_heap->data, tiny_heap->free, tiny_heap->size, tiny_heap->allocsize);
//
//        tiny_heap = tiny_heap->next;
//    }
//    ft_printf("Number of blocks : %d\nMeta Block Size : %d\n", i, META_BLOCK_SIZE);
    show_alloc_mem();
    return 0;
}
