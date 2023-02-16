#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*setstr(int fd, char *str);
char	*join(char *str, char *read_str, ssize_t num_of_byte);
char	*getbeforenewline(char *str);
char	*getafternewline(char *str);
size_t	ft_strlen(const char *c);
size_t	ft_strlcpy(char *dst, const char *src, size_t n);
char	*ft_strchr(const char *str, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);

#endif