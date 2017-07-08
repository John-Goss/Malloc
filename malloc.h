/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csellier <csellier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/08 14:08:39 by csellier          #+#    #+#             */
/*   Updated: 2017/07/08 18:27:47 by csellier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft/libft.h"
// formate par adresse croissante //
void	show_alloc_mem();

void	free(void *ptr);
void	*malloc(size_t size);
void	*realloc(void *ptr, size_t size);

