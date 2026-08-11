/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_valid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:34:32 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/05 10:07:00 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../librt.h"

int	int_valid(char *s)
{
	int	i;

	if (!s || ft_strlen(s) > 11 || ft_strlen(s) == 0
		|| (s[0] == '-' && ft_strlen(s) == 1))
		return (0);
	i = 0;
	if (s[i] == '-')
		i++;
	while (ft_isdigit(s[i]))
		i++;
	if (s[i])
		return (0);
	if (s[0] == '-')
	{
		if ((ft_strlen(&s[1]) == 10 && ft_strncmp(&s[1], P_INT_MIN, 10) <= 0)
			|| ft_strlen(&s[1]) < 10)
			return (1);
	}
	else
	{
		if ((ft_strlen(s) == 10 && ft_strncmp(s, P_INT_MAX, 10) <= 0)
			|| ft_strlen(s) < 10)
			return (1);
	}
	return (0);
}
