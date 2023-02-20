/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kurosawaitsuki <kurosawaitsuki@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 16:57:53 by kurosawaits       #+#    #+#             */
/*   Updated: 2023/02/20 23:19:02 by kurosawaits      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

static void	free_memory(char **newline)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		printf("free_memory_in: %p, %d\n", newline[i], i);
		free(newline[i]);
		newline[i] = NULL;
		i++;
	}
	printf("free_memory_out: %p\n", newline);
	free(newline);
	newline = NULL;
}

// return_ptrはmallocにより確保、つまりヒープ領域
// read_strはmallocにより確保、つまりヒープ領域、けどこれはfreeしない
// strはsetlineからのjoin関数により確保、つまりヒープ領域
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

// read_strはmallocにより確保、つまりヒープ領域
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
		if (ft_strchr(str, '\n'))
			break ;
	}
	free(read_str);
	read_str = NULL;
	return (str);
}
// strにはjoin関数によって取得されたヒープ領域が代入される.

// 
// 42　がstrに入る
static char	**get_new_line(char *str)
{
	char	**newline;
	char	*newline_ptr;
	size_t	len;

	newline = (char **)malloc(sizeof(char *) * (2 + 1));
	if (!newline)
		return (NULL);
	newline_ptr = ft_strchr(str, '\n');
	if (!newline_ptr)
	{
		newline[0] = ft_substr(str, 0, ft_strlen(str));
		newline[1] = NULL;
	}
	else
	{
		len = newline_ptr - str;
		newline[0] = ft_substr(str, 0, len + 1);
		newline[1] = ft_substr(str, len + 1, ft_strlen(newline_ptr) - 1);
	}
	newline[2] = NULL;
	return (newline);
}
// newline[0]やnewline[1]をfreeしなくてはならない
// newlineはmallocで確保されたヒープ領域を返す

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
		return (NULL);
	return_ptr = new_line[0];
	str = new_line[1];
	free_memory(new_line);
	return (return_ptr);
}
// 渡したところをfreeして、他の変数がもう一度アクセスしようとしているからこうなる

	// str = getafternewline(return_ptr);
	// if (!str)
	// 	return (return_ptr);
	// return_ptr = getbeforenewline(return_ptr);
	// if (!return_ptr)
	// 	return (NULL);

// static char	*getbeforenewline(char *str)
// {
// 	char	*before_newline;
// 	char	*newline_ptr;
// 	size_t	len;

// 	newline_ptr = ft_strchr(str, '\n');
// 	if (!newline_ptr)
// 		len = ft_strlen(str);
// 	else
// 		len = newline_ptr - str;
// 	before_newline = ft_substr(str, 0, len);
// 	if (!before_newline)
// 		return (NULL);
// 	return (before_newline);
// }

// static char	*getafternewline(char *str)
// {
// 	char	*newline_ptr;
// 	char	*after_newline;
// 	size_t	len;

// 	newline_ptr = ft_strchr(str, '\n');
// 	if (!newline_ptr)
// 		return (NULL);
// 	len = ft_strlen(newline_ptr);
// 	if (len == 1)
// 		after_newline = ft_substr("\n", 0, ft_strlen("\n"));
// 	else
// 		after_newline = ft_substr(newline_ptr, 1, len - 1);
// 	if (!after_newline)
// 		return (NULL);
// 	return (after_newline);
// }


// 改行文字も出力する行に加える

int	main(void)
{
	int		fd;
	char	*line;
	size_t	i;

	i = 0;
	fd = open("./test.txt", O_RDONLY);
	while (i < 5)
	{
		// printf("%lu回目\n", i + 1);
		line = get_next_line(fd);
		printf("203|%s|\n", line);
		i ++;
	}
	return (0);
}

// gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c  -g -fsanitize=address -fsanitize=undefined
// gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -g -fsanitize=address -fsanitize=undefined