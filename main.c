#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int		fd_1;
	int		fd_2;
	char	*line_1;
	char	*line_2;
	size_t	i;

	i = 0;
	fd_1 = open("./test_1.txt", O_RDONLY);
	fd_2 = open("./test_2.txt", O_RDONLY);
	while (i < 2)
	{
		printf("%lu回目\n", i + 1);
		line_1 = get_next_line(fd_1);
		line_2 = get_next_line(fd_2);
		printf("line_1|%s|\n", line_1);
		printf("line_2|%s|\n", line_2);
		i ++;
	}
	return (0);
}

// gcc -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c  -g -fsanitize=address -fsanitize=undefined
// gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line_bouns.c get_next_line_utils_bonus.c -g -fsanitize=address -fsanitize=undefined
// gcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c -g -fsanitize=address -fsanitize=undefined
// gcc -Wall -Wextra -Werror -D BUFFER_SIZE=1 main.c get_next_line_bonus.c get_next_line_utils_bonus.c -g -fsanitize=address -fsanitize=undefined

// setline関数でmalloc失敗した場合、strもfreeする必要があるか？
// →初回で失敗した場合、（static変数をfreeするとどうなるか？）