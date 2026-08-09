/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 04:10:20 by rcompain          #+#    #+#             */
/*   Updated: 2025/11/07 12:38:23 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdarg.h>

static int	ft_putnbr_unsigned(long int n)
{
	int		count;

	count = 0;
	if (n < 0)
		n = 4294967295 - n;
	if (n > 9)
		count += ft_putnbr_unsigned(n / 10);
	count += ft_putchar((n % 10) + '0');
	return (count);
}

static void	ft_choice(char c, va_list ap, int *count)
{
	if (c == 'c')
		*count += ft_putchar((char)va_arg(ap, int));
	if (c == 's')
		*count += ft_putstr(va_arg(ap, char *));
	if (c == 'p')
		*count += ft_putadrbase((uintptr_t)(va_arg(ap, void *)));
	if (c == 'd' || c == 'i')
		*count += ft_putnbr(va_arg(ap, int));
	if (c == 'u')
		*count += ft_putnbr_unsigned(va_arg(ap, unsigned int));
	if (c == 'x')
		*count += ft_putnbrbase(va_arg(ap, unsigned int), "0123456789abcdef");
	if (c == 'X')
		*count += ft_putnbrbase(va_arg(ap, unsigned int), "0123456789ABCDEF");
	if (c == '%')
		*count += ft_putchar('%');
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	char		*p;
	int			count;

	count = 0;
	va_start(ap, str);
	while (*str)
	{
		if (*str == '%')
		{
			p = ft_strchr("cspdiuxX%", (int)*(str + 1));
			if (*(str + 1) != '\0' && p != NULL)
			{
				ft_choice(*p, ap, &count);
				str++;
			}
			else
				count += ft_putchar('%');
		}
		else
			count += ft_putchar(*str);
		str++;
	}
	va_end(ap);
	return (count);
}
