/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:25:29 by rcompain          #+#    #+#             */
/*   Updated: 2025/11/07 13:40:37 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putnbrbase_rec(long long int nbr, char *base)
{
	unsigned int	len_base;
	int				count;

	count = 0;
	len_base = ft_strlen(base);
	if (nbr < 0)
	{
		write(1, "-", 1);
		nbr *= -1;
		count++;
	}
	if (nbr >= len_base)
		count += ft_putnbrbase_rec(nbr / len_base, base);
	count += ft_putchar(base[(nbr % len_base)]);
	return (count);
}

int	ft_putnbrbase(int nbr, char *base)
{
	unsigned long long int	nbr_long;
	int						count;

	nbr_long = (unsigned int)nbr;
	count = ft_putnbrbase_rec(nbr_long, base);
	return (count);
}
