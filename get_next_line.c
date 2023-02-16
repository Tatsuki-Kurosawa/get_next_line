#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*str;
	char		*return_ptr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	return_ptr = setstr(fd, str);
	if (!return_ptr)
		return (NULL);
	str = getafternewline(return_ptr);
	if (!str)
		return (return_ptr);
	return_ptr = getbeforenewline(return_ptr);
	if (!return_ptr)
		return (NULL);
	return (return_ptr);
}

char	*setstr(int fd, char *str)
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
			return (NULL);
		}
		else
			str = join(str, read_str, num_of_byte);
		if (!str)
			break ;
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (str);
}

char	*join(char *str, char *read_str, ssize_t num_of_byte)
{
	char	*return_ptr;

	if (num_of_byte == 0)
		return_ptr = NULL;
	else
	{
		if (!str)
			return_ptr = ft_substr(read_str, 0, ft_strlen(read_str));
		else
			return_ptr = ft_strjoin(str, read_str);
		return (return_ptr);
	}
}

char	*getbeforenewline(char *str)
{
	char	*before_newline;
	char	*newline_ptr;
	size_t	len;

	newline_ptr = ft_strchr(str, '\n');
	if (!newline_ptr)
		len = ft_strlen(str);
	else
		len = newline_ptr - str;
	before_newline = ft_substr(str, 0, len);
	if (!before_newline)
		return (NULL);
	return (before_newline);
}

char	*getafternewline(char *str)
{
	char	*newline_ptr;
	char	*after_newline;
	size_t	len;

	newline_ptr = ft_strchr(str, '\n');
	if (!newline_ptr)
		return (NULL);
	len = ft_strlen(newline_ptr);
	if (len == 1)
		after_newline = ft_substr("\n", 0, ft_strlen("\n"));
	else
		after_newline = ft_substr(newline_ptr, 1, len - 1);
	if (!after_newline)
		return (NULL);
	return (after_newline);
}

int	main(void)
{
	int		fd;
	char	*line;
	size_t	i;

	i = 0;
	fd = open("./test.txt", O_RDONLY);
	while (i < 5)
	{
		line = get_next_line(fd);
		printf("145|%s|\n", line);
		i ++;
	}
	return (0);
}

// gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c  -g -fsanitize=address -fsanitize=undefined
// gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c -g -fsanitize=address -fsanitize=undefined
