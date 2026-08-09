/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 19:05:18 by rcompain          #+#    #+#             */
/*   Updated: 2025/10/20 21:01:09 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	struct s_list	*chain;

	chain = malloc(sizeof(struct s_list));
	if (!chain)
		return (NULL);
	chain->content = content;
	chain->next = NULL;
	return (chain);
}
