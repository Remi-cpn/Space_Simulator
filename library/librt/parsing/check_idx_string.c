/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_idx_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 14:13:43 by rcompain          #+#    #+#             */
/*   Updated: 2026/05/05 10:06:02 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../librt.h"

bool	check_idx_string_tab(char **s, int idx)
{
	int	i;

	i = 0;
	while (i <= idx)
	{
		if (!s[i])
			return (false);
		i++;
	}
	if (s[i])
		return (false);
	return (true);
}
