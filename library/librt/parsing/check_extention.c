/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_extention.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 15:47:00 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/05 16:28:23 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../librt.h"

bool	check_extention(char *str, char *key)
{
	int	size_str;
	int	size_key;

	if (!str || (!key || !key[0]))
		return (false);
	size_str = ft_strlen(str);
	size_key = ft_strlen(key);
	if (size_str < size_key)
		return (false);
	while (size_key > 0)
	{
		if (str[size_str - 1] != key[size_key - 1])
			return (false);
		size_key--;
		size_str--;
	}
	return (true);
}
