#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern int ft_write();
extern int ft_read();

int	main(void) {
	int		fd		= open("test/main_test.c", O_RDONLY);
	char	*buff	= calloc(sizeof(char), 50 + 1);
	int		ret		= ft_read(fd, buff, 50);

	/* Test our ft_read asm module */
	printf("ft_read tests\n");
	printf("With correct fd -> ret value = %d,  error value = %d : %s\n", ret, errno, strerror(errno));
	printf("What we read : %s\n", buff);
	ret = ft_read(-1, buff, 50);
	printf("With wrong fd -> ret value = %d,  error value = %d : %s\n\n", ret, errno, strerror(errno));
	free(buff);
	*buff = 0;
	errno = 0;


	/* Test our ft_write asm module */
	printf("ft_write tests\n");
	ret = ft_write(1, "Hello world!\n", 14);
	printf("With correct fd -> ret value = %d,  error value = %d : %s\n", ret, errno, strerror(errno));
	ret = ft_write(-1, "Hello world!\n", 13);
	printf("With wrong fd -> ret value = %d,  error value = %d : %s\n", ret, errno, strerror(errno));
	errno = 0;

	return (0);
}
