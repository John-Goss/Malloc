/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memorydump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 11:24:01 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/03 11:24:02 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	dump_block(t_block *block)
{
	char	*ptr;

	ptr = block->data;
	while (ptr != (block->data + block->allocsize))
	{
		ft_printf("[%X] ", *ptr);
		++ptr;
	}
}

void		dump_zone(t_type type)
{
	t_block	*heap_start;

	if (type == TINY)
		heap_start = TINY_HEAP;
	else if (type == SMALL)
		heap_start = SMALL_HEAP;
	else
		heap_start = LARGE_HEAP;
	while (heap_start)
	{
		if (heap_start->free == 0)
		{
			print_block_alloc_info(heap_start);
			dump_block(heap_start);
			write(1, "\n", 1);
		}
		heap_start = heap_start->next;
	}
}
