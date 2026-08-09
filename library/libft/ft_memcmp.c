/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:09:42 by rcompain          #+#    #+#             */
/*   Updated: 2025/10/22 02:27:17 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*tmp1;
	unsigned char	*tmp2;	

	i = 0;
	tmp1 = (unsigned char *)s1;
	tmp2 = (unsigned char *)s2;
	if (i == n)
		return (0);
	while (i < n - 1 && tmp1 && tmp2 && tmp1[i] == tmp2[i])
		i++;
	return (tmp1[i] - tmp2[i]);
}
