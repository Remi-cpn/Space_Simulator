/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 09:47:23 by rcompain          #+#    #+#             */
/*   Updated: 2025/10/22 01:40:03 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_head;
	t_list	*new_elem;
	void	*data;

	if (!lst || !f || !del)
		return (NULL);
	new_elem = NULL;
	new_head = NULL;
	while (lst)
	{
		data = f(lst->content);
		new_elem = ft_lstnew(data);
		if (!new_elem || !data)
		{
			del(data);
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		ft_lstadd_back(&new_head, new_elem);
		lst = lst->next;
	}
	return (new_head);
}
