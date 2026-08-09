/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 21:48:31 by tseche            #+#    #+#             */
/*   Updated: 2026/02/06 10:21:14 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
The  strndup()  function  is  similar,  but copies at most n bytes.
If s is longer than n,
only n bytes are copied, and a terminating null  byte  ('\0')
is added.
*/
char	*ft_strndup(char *src, int start, int finish)
{
	int		i;
	int		size;
	char	*str_dup;

	i = 0;
	size = finish - start + 1;
	str_dup = (char *)malloc(sizeof(char) * (size + 1));
	if (!str_dup)
		return (NULL);
	while (start <= finish)
	{
		str_dup[i] = src[start];
		i++;
		start++;
	}
	str_dup[i] = '\0';
	return (str_dup);
}
