/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:29:21 by rcompain          #+#    #+#             */
/*   Updated: 2025/10/22 12:15:26 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		len_little;
	const char	*p;

	i = 0;
	len_little = ft_strlen(little);
	if (little[0] == '\0')
		return ((char *)big);
	while (i < len && big[i])
	{
		p = &big[i];
		if (big[i] == little[0] && len_little <= len - i)
		{
			if (!ft_memcmp(p, little, len_little))
				return ((char *)p);
		}
		i++;
	}
	return (NULL);
}
