/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 20:35:56 by rcompain          #+#    #+#             */
/*   Updated: 2025/10/22 00:43:40 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	size_t	intlen(int n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	size_t		len;
	long int	nbr;
	char		*s;

	nbr = (long int)n;
	len = intlen(nbr);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	if (nbr == 0)
		s[0] = '0';
	if (nbr < 0)
	{
		s[0] = '-';
		nbr = nbr * -1;
	}
	s[len] = '\0';
	while (nbr > 0)
	{
		len--;
		s[len] = (nbr % 10) + '0';
		nbr = nbr / 10;
	}
	return (s);
}
