/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:44:00 by rcompain          #+#    #+#             */
/*   Updated: 2026/04/13 12:12:09 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_array(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	if (!*s)
	{
		free(s);
		return ;
	}
	while (s[i])
	{
		s[i] = ft_freenull(s[i]);
		i++;
	}
	s = ft_freenull(s);
}
