/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 14:56:06 by rcompain          #+#    #+#             */
/*   Updated: 2025/10/22 12:21:06 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	delet_back(char const *s1, char const *set, size_t len)
{
	size_t	j;

	j = 0;
	while (set[j] && len > 0)
	{
		if (s1[len - 1] == set[j])
		{
			len--;
			j = 0;
		}
		else
			j++;
	}
	return (len);
}

static char	*delet_front(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (set[j])
	{
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	s1 = &s1[i];
	return ((char *)s1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size_dest;
	size_t	len;
	char	*dest;
	char	*new;

	if (!s1 || !set)
		return (NULL);
	dest = delet_front(s1, set);
	size_dest = ft_strlen(dest);
	len = delet_back(dest, set, size_dest);
	if (len == 0)
	{
		new = (char *)malloc(1);
		if (!new)
			return (NULL);
		new[0] = '\0';
		return (new);
	}
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (!new)
		return (NULL);
	ft_strlcpy(new, dest, len + 1);
	return (new);
}
