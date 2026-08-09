/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:25:49 by rcompain          #+#    #+#             */
/*   Updated: 2025/12/20 15:07:42 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len, int free_s)
{
	size_t	len_s;
	size_t	i;
	char	*sub;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start >= len_s)
		len = 0;
	if (len + start > len_s && len > 0)
		len = len_s - start;
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (sub)
	{
		i = 0;
		while (i < len)
			sub[i++] = s[start++];
		sub[i] = '\0';
	}
	if (free_s == 1)
		ft_freenull((void *)s);
	return (sub);
}
