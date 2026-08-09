/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:11:39 by rcompain          #+#    #+#             */
/*   Updated: 2025/10/22 00:51:16 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	size_src;
	char	*src_tmp;

	i = 0;
	src_tmp = (char *)src;
	size_src = ft_strlen(src);
	if (size == 0)
		return (size_src);
	while (i < size - 1 && src_tmp[i])
	{
		dst[i] = src_tmp[i];
		i++;
	}
	dst[i] = '\0';
	return (size_src);
}
