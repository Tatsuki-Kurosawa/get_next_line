#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// int	main(void)
// {
// 	static char		*ano_str;
// 	int				fd;
// 	ssize_t			check;
// 	size_t			len;
// 	char			*str;

// 	len = 5;
// 	fd = open("./test.txt", O_RDONLY);
// 	if (fd < 0)
// 		return (0);
// 	str = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!str)
// 		return (0);
// 	check = read(fd, str, len);
// 	if (check < 0)
// 	{
// 		free(str);
// 		return (0);
// 	}
// 	printf("free前\n");
// 	printf("str: %s\n", str);
// 	// ano_str = str;
// 	// printf("ano_str: %s\n", ano_str);
// 	free(str);
// 	printf("free後\n");
// 	printf("str: %s\n", str);
// 	// printf("ano_str: %s\n", ano_str);
// 	return (0);
// }

int	main(void)
{
	size_t	len;
	char	*str_1;
	char	*str_2;

	len = 1;
	str_1 = (char *)malloc(sizeof(char) * len);
	if (!str_1)
		return (0);
	printf("free前\n");
	printf("str_1: %p\n", str_1);
	free(str_1);
	str_1 = NULL;
	printf("free後\n");
	str_2 = (char *)malloc(sizeof(char) * len);
	if (!str_2)
		return (0);
	printf("str_2: %p\n", str_2);
	*str_2 = 'b';
	*str_1 = 'a';
	printf("str_2: %c\n", *str_2);
	printf("str_1: %c\n", *str_1);
	printf("str_2: %p\n", str_2);
	printf("str_1: %p\n", str_1);
	return (0);
}
// 一度フリーしたはずの領域に

// static変数strにmallocされた領域のアドレスが入るので、これをfreeするのか？
// free関数は他の変数に代入されたアドレスを引数に渡してもfreeされるのか？
// ダングリングポインタ free後、freeしたポインタにNULLを代入する