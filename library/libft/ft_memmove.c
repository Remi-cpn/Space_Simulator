/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 13:51:23 by rcompain          #+#    #+#             */
/*   Updated: 2025/10/22 00:43:17 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dest_tmp;
	unsigned char	*src_tmp;

	dest_tmp = (unsigned char *)dest;
	src_tmp = (unsigned char *)src;
	if (dest_tmp < src_tmp)
		ft_memcpy(dest, src, n);
	else
	{
		while (n > 0)
		{
			n--;
			dest_tmp[n] = src_tmp[n];
		}
	}
	return (dest);
}
