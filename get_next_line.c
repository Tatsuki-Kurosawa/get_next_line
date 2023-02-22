/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kurosawaitsuki <kurosawaitsuki@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:57:53 by kurosawaits       #+#    #+#             */
/*   Updated: 2023/02/22 18:23:39 by kurosawaits      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

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
			str = NULL;
		}
		return (return_ptr);
	}
}

static char	*setline(int fd, char *str)
{
	char	*read_str;
	ssize_t	num_of_byte;

	read_str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_str)
		return (NULL);
	num_of_byte = 1;
	while (num_of_byte)
	{
		num_of_byte = read(fd, read_str, BUFFER_SIZE);
		read_str[num_of_byte] = '\0';
		if (num_of_byte == -1)
		{
			free(read_str);
			read_str = NULL;
			return (NULL);
		}
		else
			str = join(str, read_str, num_of_byte);
		if (!str || ft_strchr(str, '\n'))
			break ;
	}
	free(read_str);
	read_str = NULL;
	return (str);
}

// new_lineとnewline[0]とnewline[1]はmalloc確保しているのでfreeする必要あり
static char	**get_new_line(char *str)
{
	char	**newline;
	char	*new_ptr;

	newline = (char **)malloc(sizeof(char *) * (2 + 1));
	if (!newline)
	{
		free(newline);
		return (NULL);
	}
	new_ptr = ft_strchr(str, '\n');
	if (!new_ptr)
	{
		if (ft_strlen(str) == 0 && *str == '\0')
			newline[0] = NULL;
		else
			newline[0] = ft_substr(str, 0, ft_strlen(str));
		newline[1] = NULL;
	}
	else
	{
		newline[0] = ft_substr(str, 0, new_ptr - str + 1);
		newline[1] = ft_substr(str, new_ptr - str + 1, ft_strlen(new_ptr) - 1);
	}
	newline[2] = NULL;
	free(str);
	return (newline);
}
// ft_substrとft_strlenがNULLの場合どうなるか？

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
	if (!str)
		free(new_line[1]);
	free(new_line);
	return (return_ptr);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	size_t	i;

// 	i = 0;
// 	fd = open("./test.txt", O_RDONLY);
// 	while (i < 2)
// 	{
// 		printf("%lu回目\n", i + 1);
// 		line = get_next_line(fd);
// 		printf("|%s|\n", line);
// 		i ++;
// 	}
// 	return (0);
// }

// gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c  -g -fsanitize=address -fsanitize=undefined
// gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -g -fsanitize=address -fsanitize=undefined
// gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 get_next_line.c get_next_line_utils.c -g -fsanitize=address -fsanitize=undefined