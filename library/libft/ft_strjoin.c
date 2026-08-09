/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:30:11 by rcompain          #+#    #+#             */
/*   Updated: 2025/12/20 15:09:48 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, int free_s1, int free_s2)
{
	size_t	size_s1;
	size_t	size_s2;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	dest = (char *)malloc(size_s1 + size_s2 + 1);
	if (dest)
	{
		ft_memcpy(dest, s1, size_s1);
		ft_memcpy(dest + size_s1, s2, size_s2);
		dest[size_s1 + size_s2] = '\0';
	}
	if (free_s1 == 1)
		ft_freenull((void *)s1);
	if (free_s2 == 1)
		ft_freenull((void *)s2);
	return (dest);
}
