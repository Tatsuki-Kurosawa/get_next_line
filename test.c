#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// readの返り値が-1になった時、次回のreadによる読み込みは読み込めなかったその続きから行われる
int	main(void)
{
	int		fd_1;
	ssize_t	num_of_byte;
	char	*str;
	size_t	buf;
	int		i;

	fd_1 = open("./test.txt", O_RDONLY);
	printf("fd_1: %d\n", fd_1);
	str = (char *)malloc(sizeof(char) * (5 + 1));
	if (!str)
		return (0);
	i = 0;
	buf = -1;
	while (i < 3)
	{
		if (i == 0 || i == 2)
			buf = 3;
		else
			buf = 0;
		printf("%d回目の読み込み\n", i + 1);
		num_of_byte = read(fd_1, str, buf);
		str[num_of_byte] = '\0';
		printf("num_of_byte: %zd\n", num_of_byte);
		if (num_of_byte == -1)
			printf("num_of_byteは-1でした\n");
		else if (num_of_byte == 0)
		{
			printf("ファイルのお終いまで読みました\n");
			if (!str)
				printf("strはnullです\n");
			else
				printf("strはnullじゃないです\n");
			// printf("str: %s\n", str);
		}
		else
		{
			printf("num_of_byteは0より大きいです\n");
			printf("str: %s\n", str);
		}
		printf("\n");
		i++;
	}
	return (0);
}

// headファイルで書くべきことは？
// readの返り値が-1だった時、その後の読み込みはどうなるか？続きから読み込まれるのか: OK
// free()は何をfreeしてるのか
// main関数が終了しない限り、他関数でmallocした領域はfreeされないのか？
// →プログラムが終了したわけではないので、freeの必要がありそう
// 改行前だけを取り出す？
// ダブルポインタを使う？←あり