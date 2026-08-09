/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 22:27:52 by rcompain          #+#    #+#             */
/*   Updated: 2025/12/20 15:13:34 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordlen(char const *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static void	free_all(char **s, size_t len)
{
	size_t	i;

	i = 0;
	while (i <= len)
	{
		free(s[i]);
		i++;
	}
	free(s);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**new;
	size_t	n_len;

	if (!s)
		return (NULL);
	n_len = ft_count_word(s, c);
	new = ft_calloc((n_len + 1), sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < n_len)
	{
		while (*s == c)
			s++;
		new[i] = ft_substr(s, 0, wordlen(s, c), 0);
		if (!new[i])
		{
			free_all(new, n_len);
			return (NULL);
		}
		s += wordlen(s, c);
		i++;
	}
	return (new);
}
