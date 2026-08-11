/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_valid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:32:58 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/05 10:06:28 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../librt.h"

int	double_valid(char *s)
{
	int		i;
	int		dot_count;
	double	d;

	if (!s || ft_strlen(s) > 20 || ft_strlen(s) == 0
		|| (s[0] == '-' && ft_strlen(s) == 1))
		return (0);
	i = 0;
	dot_count = 0;
	if (s[i] == '-')
		i++;
	while (ft_isdigit(s[i]) || s[i] == '.')
	{
		if (s[i] == '.')
			dot_count++;
		i++;
	}
	if (s[i] || dot_count > 1)
		return (0);
	d = ft_atod(s);
	if (isinf(d))
		return (0);
	return (1);
}
