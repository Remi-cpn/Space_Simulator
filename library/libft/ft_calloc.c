/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:44:55 by rcompain          #+#    #+#             */
/*   Updated: 2025/10/22 00:57:23 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tmp;

	if (size == 0 || nmemb == 0)
	{
		tmp = malloc(0);
		if (!tmp)
			return (NULL);
		return (tmp);
	}
	if (nmemb != 0 && size > ((size_t) - 1) / nmemb)
		return (NULL);
	tmp = malloc(size * nmemb);
	if (!tmp)
		return (NULL);
	ft_memset(tmp, 0, nmemb * size);
	return (tmp);
}
