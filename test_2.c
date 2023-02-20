// 定義していない変数を渡すことはできるのか？
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

// int	judge(char *read_str)
// {
// 	int	i;
// 	int	judgement;

// 	judgement = 0;
// 	free(read_str);
// 	read_str = (char *)malloc(sizeof(char) * (3 + 1));
// 	if (!read_str)
// 		return (judgement);
// 	i = 0;
// 	while (i < 3)
// 	{
// 		read_str[i] = 'a';
// 		i++;
// 	}
// 	read_str[i] = '\0';
// 	if (read_str)
// 	{
// 		judgement = 1;
// 		printf("read_str: %s\n", read_str);
// 	}
// 	return (judgement);
// }

// int	main(void)
// {
// 	char	*read_str;
// 	int		judgement;
// 	int		return_value;

// 	read_str = (char *)malloc(sizeof(char) * 1);
// 	if (!read_str)
// 		return (0);
// 	read_str[0] = '\0';
// 	judgement = judge(read_str);
// 	printf("judgement: %d\n", judgement);
// 	return_value = printf("%A\n", "abcdefg");
// 	printf("%d\n", return_value);
// }

int	main(void)
{
	int	num;

	num = -1;
	printf("%u\n", num);
	printf("usigned int の最大値 = %u\n\n", UINT_MAX);

}

// 文字列をunsigned long型にキャストするとどうなるか？
// アドレスは16進表示、unsigned longにキャストすることは、10進数にキャストするということ