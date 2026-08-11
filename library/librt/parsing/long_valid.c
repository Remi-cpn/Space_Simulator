/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:35:09 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/05 10:07:09 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../librt.h"

int	long_valid(char *s)
{
	int	i;

	if (!s || ft_strlen(s) > 20 || ft_strlen(s) == 0
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
		if ((ft_strlen(&s[1]) == 19 && ft_strncmp(&s[1], P_LONG_MIN, 19) <= 0)
			|| ft_strlen(&s[1]) < 19)
			return (1);
	}
	else
	{
		if ((ft_strlen(s) == 19 && ft_strncmp(s, P_LONG_MAX, 19) <= 0)
			|| ft_strlen(s) < 19)
			return (1);
	}
	return (0);
}
