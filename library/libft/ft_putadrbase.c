/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadrbase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 18:25:29 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/11 15:14:25 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putadrbase_rec(unsigned long int nbr, char *base)
{
	unsigned int	len_base;
	int				count;

	count = 0;
	len_base = ft_strlen(base);
	if (nbr >= len_base)
		count += ft_putadrbase_rec(nbr / len_base, base);
	count += ft_putchar(base[(nbr % len_base)]);
	return (count);
}

int	ft_putadrbase(uintptr_t nbr)
{
	unsigned long int	nbr_long;
	int					count;

	count = 0;
	if (nbr == 0)
	{
		count += write(1, "(nil)", 5);
		return (count);
	}
	write(1, "0x", 2);
	nbr_long = nbr;
	count = ft_putadrbase_rec(nbr_long, "0123456789abcdef");
	return (count + 2);
}
