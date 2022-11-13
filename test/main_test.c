#include <errno.h>
#include <stdio.h>

extern int ft_write();

int	main(void) {
	int ret;

	ret = 0;
	ret = ft_write(1, "Hello world!\n", 13);
	if (ret < 0) {
		perror("Something went wrong");
		return (errno);
	}
	ret = ft_write(-1, "Hello world!\n", 13);
	if (ret < 0) {
		perror("Something went wrong");
		return (errno);
	}
	return (0);
}
