/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcompain <rcompain@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:09:13 by rcompain          #+#    #+#             */
/*   Updated: 2025/12/23 13:11:52 by rcompain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * This function scans the given string until it finds the first
 * occurrence of '\n'. If no newline is found, the function returns -1.
 */
static int	gnl_strchr(const char *save)
{
	size_t	i;

	if (save[0] == 0)
		return (-1);
	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] != '\n')
		return (-1);
	return (i);
}

/**
 * This function creates a new string containing the characters
 * up to (and including) the first newline character found in `*save`.
 * The remaining part of the string after that line is kept in `*save`
 * for the next call.
 */
static char	*ft_new_line(char **save)
{
	char	*new_line;
	size_t	size_nl;

	size_nl = gnl_strchr(*save) + 1;
	if (size_nl == 0)
		size_nl = ft_strlen(*save);
	new_line = ft_calloc((size_nl + 1), sizeof(char));
	if (!new_line)
		return (NULL);
	ft_strlcpy(new_line, *save, size_nl + 1);
	*save = ft_substr(*save, size_nl, ft_strlen(*save) - size_nl, 1);
	if (!*save)
		return (NULL);
	return (new_line);
}

/**
 * This function reads chunks of data from the given file descriptor
 * and appends them to the saved buffer until a newline character ('\n')
 * or the end of file is reached. It then extracts and returns the next line.
 */
static char	*gnl_read(int fd, char **save)
{
	char	*buffer;
	int		back;
	char	*new_line;

	while (gnl_strchr(*save) < 0)
	{
		buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (!buffer)
			return (NULL);
		back = read(fd, buffer, BUFFER_SIZE);
		if (back <= 0)
		{
			free(buffer);
			if (*save && *save[0] != '\0' && back >= 0)
				break ;
			free(*save);
			*save = NULL;
			return (NULL);
		}
		*save = ft_strjoin(*save, buffer, 1, 1);
		if (!*save)
			return (NULL);
	}
	new_line = ft_new_line(save);
	return (new_line);
}

/**
 * This is the main function of get_next_line_bonus. It reads data
 * from the given file descriptor and returns the next line,
 * including the newline character ('\n') if present.
 *
 * It supports multiple file descriptors by storing separate buffers
 * for each one in a static array.
 */
char	*ft_get_next_line(int fd)
{
	char		*new_line;
	static char	*save[1024] = {NULL, NULL};

	if (fd < 0 || fd >= 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!save[fd])
	{
		save[fd] = ft_calloc(1, sizeof(char));
		if (!save[fd])
			return (NULL);
	}
	if (gnl_strchr(save[fd]) >= 0)
		new_line = ft_new_line(&save[fd]);
	else
		new_line = gnl_read(fd, &save[fd]);
	return (new_line);
}
