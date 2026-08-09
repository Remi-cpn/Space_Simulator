/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:42:04 by rcompain          #+#    #+#             */
/*   Updated: 2025/10/22 00:43:25 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned const char	*src_tmp;
	unsigned char		*dest_tmp;

	i = 0;
	src_tmp = (unsigned const char *)src;
	dest_tmp = (unsigned char *)dest;
	while (i < n)
	{
		dest_tmp[i] = src_tmp[i];
		i++;
	}
	return (dest);
}
