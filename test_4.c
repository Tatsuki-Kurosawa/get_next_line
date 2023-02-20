#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*string_1;
	char	*string_2;
	char	**str_1;
	char	**str_2;

	str_1 = (char **)malloc(sizeof(char *) * (2 + 1));
	if (!str_1)
		return (0);
	string_1 = (char *)malloc(sizeof(char) * 3);
	if (!string_1)
		return (0);
	string_2 = (char *)malloc(sizeof(char) * 3);
	if (!string_2)
		return (0);
	string_1 = "abc";
	string_2 = "def";
	str_1[0] = string_1;
	str_1[1] = string_2;
	str_1[2] = NULL;
	printf("str_1[0]: %s\n", str_1[0]);
	printf("str_1[1]: %s\n", str_1[1]);
	str_2 = str_1;
	printf("str_2[0]: %s\n", str_2[0]);
	printf("str_2[1]: %s\n", str_2[1]);
	return (0);
}
