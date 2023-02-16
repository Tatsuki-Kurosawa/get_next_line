#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd_1;
	int	fd_2;
	int	fd_3;
	int	fd_4;
	int	fd_5;

	fd_1 = open("./test.txt", O_RDONLY);
	fd_2 = open("./test_2.txt", O_RDONLY);
	fd_3 = open("./test_3.txt", O_RDONLY);
	fd_4 = open("./test_4.txt", O_RDONLY);
	fd_5 = open("./test_5.txt", O_RDONLY);
	printf("fd_1: %d\n", fd_1);
	printf("fd_2: %d\n", fd_2);
	printf("fd_3: %d\n", fd_3);
	printf("fd_4: %d\n", fd_4);
	printf("fd_5: %d\n", fd_5);
}
