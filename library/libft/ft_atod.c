/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/12 13:30:24 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/12 13:34:36 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	get_sign(const char *s, int *i)
{
	int	sign;

	sign = 1;
	if (s[*i] == '-' || s[*i] == '+')
	{
		if (s[*i] == '-')
			sign *= -1;
		(*i)++;
	}
	return (sign);
}

double	ft_atod(const char *s)
{
	int		i;
	double	result;
	double	dec;
	int		sign;

	i = 0;
	result = 0.0;
	dec = 0.1;
	sign = 1;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '-' || s[i] == '+')
		sign = get_sign(s, &i);
	while (s[i] >= '0' && s[i] <= '9')
		result = result * 10.0 + (s[i++] - '0');
	if (s[i] == '.')
	{
		i++;
		while (s[i] >= '0' && s[i] <= '9')
		{
			result += (s[i++] - '0') * dec;
			dec *= 0.1;
		}
	}
	return (result * sign);
}
