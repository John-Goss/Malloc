/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:06:13 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/04 18:14:57 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	print_addr(void *addr)
{
	write(1, "0x", 2);
	ft_putnbr_base((size_t)addr, 16);
}

static void	print_memzone(t_block *b, size_t *total)
{
	print_addr(b);
	write(1, "\n", 1);
	while (b)
	{
		if (b->free == 0)
		{
			print_alloc_info(b);
			*total += b->size;
		}
		b = b->next;
	}
}

void		print_alloc_info(t_block *block)
{
	print_addr((void *)(block->data));
	write(1, " - ", 3);
	print_addr((void *)(block->data + block->size));
	write(1, " : ", 3);
	ft_putnbr_base((block->size), 10);
	write(1, " octets\n", 8);
}

void		show_alloc_mem(void)
{
	t_block	*b;
	size_t	total;

	total = 0;
	pthread_mutex_lock(&g_locker);
	b = TINY_HEAP;
	write(1, "TINY : ", 7);
	print_memzone(b, &total);
	b = SMALL_HEAP;
	write(1, "SMALL : ", 8);
	print_memzone(b, &total);
	b = LARGE_HEAP;
	write(1, "LARGE : ", 8);
	print_memzone(b, &total);
	write(1, "Total : ", 8);
	ft_putnbr_base(total, 10);
	write(1, " octets\n", 8);
	pthread_mutex_unlock(&g_locker);
}
