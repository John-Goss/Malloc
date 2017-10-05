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

void		dump_block(t_block *block)
{
	char	*ptr;

	ptr = block->data;
	while (ptr < block->data + block->size)
	{
		ft_putnbr_base((int)(*ptr), 16);
		ft_putstr(" ");
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
			print_alloc_info(heap_start);
			dump_block(heap_start);
			write(1, "\n", 1);
		}
		heap_start = heap_start->next;
	}
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
