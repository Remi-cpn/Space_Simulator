/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 15:55:19 by tseche            #+#    #+#             */
/*   Updated: 2026/08/10 23:24:43 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>
#include "./libft.h"

void	*ft_realloc(void *p, size_t old_size, size_t new_size, size_t bit)
{
	void	*ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		free(p);
		return (NULL);
	}
	ptr = malloc(new_size * bit);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, new_size * bit);
	if (!p)
		return (ptr);
	copy_size = new_size;
	if (old_size < new_size)
		copy_size = old_size;
	ft_memcpy(ptr, p, copy_size * bit);
	free(p);
	return (ptr);
}
