/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tseche <tseche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 08:34:39 by rcompain          #+#    #+#             */
/*   Updated: 2026/02/10 16:26:41 by tseche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_tmp;

	if (!lst || !new)
		return ;
	lst_tmp = *lst;
	if (!*lst)
		*lst = new;
	else
	{
		lst_tmp = ft_lstlast(*lst);
		lst_tmp->next = new;
	}
}
