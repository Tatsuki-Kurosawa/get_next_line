/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kurosawaitsuki <kurosawaitsuki@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:57:53 by kurosawaits       #+#    #+#             */
/*   Updated: 2023/02/26 21:12:03 by kurosawaits      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*join(char *str, char *read_str, ssize_t num_of_byte)
{
	char	*return_ptr;

	if (num_of_byte == 0)
		return (str);
	else
	{
		if (!str)
			return_ptr = ft_substr(read_str, 0, ft_strlen(read_str));
		else
		{
			return_ptr = ft_strjoin(str, read_str);
			free(str);
		}
		return (return_ptr);
	}
}

static char	*setline(int fd, char *str)
{
	char	*read_str;
	ssize_t	num_of_byte;

	read_str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + (size_t)1));
	if (!read_str)
		return (NULL);
	num_of_byte = 1;
	while (num_of_byte)
	{
		num_of_byte = read(fd, read_str, BUFFER_SIZE);
		if (num_of_byte == -1)
		{
			free(str);
			free(read_str);
			return (NULL);
		}
		read_str[num_of_byte] = '\0';
		str = join(str, read_str, num_of_byte);
		if (!str || ft_strchr(str, '\n'))
			break ;
	}
	free(read_str);
	return (str);
}

static char	**get_new_line(char *str)
{
	char	**newline;

	newline = (char **)malloc(sizeof(char *) * (2 + 1));
	if (!newline)
	{
		free(str);
		return (NULL);
	}
	if (!(ft_strchr(str, '\n')))
	{
		if (ft_strlen(str) == 0 && *str == '\0')
			newline[0] = NULL;
		else
			newline[0] = ft_substr(str, 0, ft_strlen(str));
		newline[1] = NULL;
	}
	else
	{
		newline[0] = ft_substr(str, 0, ft_strchr(str, '\n') - str + 1);
		newline[1] = ft_substr(str, ft_strchr(str, '\n') - str + 1, \
		ft_strlen(ft_strchr(str, '\n')) - 1);
	}
	newline[2] = NULL;
	free(str);
	return (newline);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*return_ptr;
	char		**new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str = setline(fd, str);
	if (!str)
		return (NULL);
	new_line = get_new_line(str);
	if (!new_line)
	{
		free(str);
		return (NULL);
	}
	return_ptr = new_line[0];
	str = new_line[1];
	free(new_line);
	return (return_ptr);
}
