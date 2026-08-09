/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 16:06:16 by rcompain          #+#    #+#             */
/*   Updated: 2025/12/20 15:17:02 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s, int free_s)
{
	size_t	size;
	char	*dup;

	size = ft_strlen((char *)s) + 1;
	dup = (char *)malloc(sizeof(char) * (size));
	if (dup)
		dup = ft_memcpy(dup, s, size);
	if (free_s == 1)
		ft_freenull((void *)s);
	return (dup);
}
