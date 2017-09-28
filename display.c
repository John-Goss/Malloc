/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:06:13 by jle-quer          #+#    #+#             */
/*   Updated: 2017/09/28 16:09:07 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	print_block_alloc_info(t_block *block)
{
	ft_printf("%p - %p : %zu octets\n", block->data,
              (block->data + block->size), block->allocsize);
}

static void	print_memory(t_block *block, unsigned int *total)
{
	ft_printf("%p\n", block);
	while (block)
	{
		if (block->free == 0)
		{
			print_block_alloc_info(block);
			*total += block->size;
		}
		block = block->next;
	}
}

void		show_alloc_mem(void)
{
	t_block			*tmp;
	unsigned int	total;

	total = 0;
	tmp = TINY_HEAP;
	write(1, "TINY : ", 7);
	print_memory(tmp, &total);
	tmp = SMALL_HEAP;
	write(1, "SMALL : ", 8);
	print_memory(tmp, &total);
	tmp = LARGE_HEAP;
	write(1, "LARGE : ", 8);
	print_memory(tmp, &total);
	ft_printf("Total : %u octets\n", total);
}
