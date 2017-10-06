/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memorydump.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jle-quer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/03 11:24:01 by jle-quer          #+#    #+#             */
/*   Updated: 2017/10/04 18:12:47 by jle-quer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

/*
**	dump_block(t_block *block, int lock)
**	@param1: the block that you would dump
**	@param2: the bool for thread locking; if lock == 1 the treads will lock
*/

void		dump_block(t_block *block, int lock)
{
	char	*ptr;

	if (lock)
		pthread_mutex_lock(&g_locker);
	ptr = block->data;
	while (ptr < block->data + block->size)
	{
		ft_putnbr_base((int)(*ptr), 16);
		ft_putstr(" ");
		++ptr;
	}
	if (lock)
		pthread_mutex_unlock(&g_locker);
}

void		dump_zone(t_type type)
{
	t_block	*heap_start;

	pthread_mutex_lock(&g_locker);
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
			print_alloc_info(heap_start);
			dump_block(heap_start, 0);
			write(1, "\n", 1);
		}
		heap_start = heap_start->next;
	}
	pthread_mutex_unlock(&g_locker);
}

char		digit(int nb, int maj)
{
	if (nb < 10)
		return ('0' + nb);
	if (maj)
		return ('A' + nb % 10);
	return ('a' + nb % 10);
}

void		ft_putnbr_base(intmax_t nb, int base)
{
	if (nb > 9)
		ft_putnbr_base(nb / base, base);
	ft_putchar(digit(nb % base, 1));
}
