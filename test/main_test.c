#include "libasm.h"

void		ft_check_write(void)
{
	int ret = 0;
	printf("\n---------------- Ft_write ------------------\n");

	printf("\033[36mLibasm\033[00m\n");
	ret = ft_write(1, "ZA WARUDO!\n", 11);
	printf("With correct fd -> ret value = %d,  error value = %d : %s\n", ret, errno, strerror(errno));
	printf("\033[36mLibc\033[00m\n");
	ret = write(1, "ZA WARUDO!\n", 11);
	printf("With correct fd -> ret value = %d,  error value = %d : %s\n\n", ret, errno, strerror(errno));

	printf("\033[36mLibasm\033[00m\n");
	ret = ft_write(-1, "ZA WARUDO!\n", 11);
	printf("With wrong fd -> ret value = %d,  error value = %d : %s\n", ret, errno, strerror(errno));
	errno = 0;
	printf("\033[36mLibc\033[00m\n");
	ret = write(-1, "ZA WARUDO!\n", 11);
	printf("With wrong fd -> ret value = %d,  error value = %d : %s\n\n", ret, errno, strerror(errno));
	errno = 0;

	printf("\033[36mLibasm\033[00m\n");
	ret = ft_write(1, "", 1);
	printf("With empty buffer -> ret value = %d,  error value = %d : %s\n", ret, errno, strerror(errno));
	printf("\033[36mLibc\033[00m\n");
	ret = write(1, "", 1);
	printf("With empty buffer -> ret value = %d,  error value = %d : %s\n", ret, errno, strerror(errno));
}

void		ft_check_read(void)
{
	int		ret;
	char	buf[5000];

	printf("\n----------------- Ft_read ------------------\n");

	printf("\033[36mLibasm\033[00m\n");
	ret = ft_read(0, buf, 42);
	buf[ret] = '\0';
	printf("With correct fd -> ret value = %d,  error value = %d : %s\n", ret, errno, strerror(errno));
	printf("\033[36mLibc\033[00m\n");
	ret = read(0, buf, 42);
	buf[ret] = '\0';
	printf("With correct fd -> ret value = %d,  error value = %d : %s\n\n", ret, errno, strerror(errno));

	printf("\033[36mLibasm\033[00m\n");
	ret = 0;
	ret = ft_read(-1, buf, 50);
	buf[ret] = '\0';
	printf("With wrong fd -> ret value = %d,  error value = %d : %s\n", ret, errno, strerror(errno));
	errno = 0;
	printf("\033[36mLibc\033[00m\n");
	ret = 0;
	ret = read(-1, buf, 50);
	buf[ret] = '\0';
	printf("With wrong fd -> ret value = %d,  error value = %d : %s\n\n", ret, errno, strerror(errno));
	errno = 0;

	printf("\033[36mLibasm\033[00m\n");
	ret = ft_read(0, "", 42);
	buf[ret] = '\0';
	printf("With empty buffer -> ret value = %d,  error value = %d : %s\n", ret, errno, strerror(errno));
	errno = 0;
	printf("\033[36mLibc\033[00m\n");
	ret = read(0, "", 42);
	buf[ret] = '\0';
	printf("With empty buffer -> ret value = %d,  error value = %d : %s\n", ret, errno, strerror(errno));
	errno = 0;
}

void		ft_check_strlen(void)
{
	printf("\n---------------- Ft_strlen -----------------\n");

	printf("Regular size test : \033[36mLibasm -> \033[00m%ld\033[36m & Libc -> \033[00m%ld\n", ft_strlen("Hello world"), strlen("Hello world"));

	printf("One byte test : \033[36mLibasm -> \033[00m%ld\033[36m & Libc -> \033[00m%ld\n", ft_strlen("a"), strlen("a"));

	printf("No byte test : \033[36mLibasm -> \033[00m%ld\033[36m & Libc -> \033[00m%ld\n", ft_strlen(""), strlen(""));
}

void		ft_check_strcpy(void)
{
	char	*ret = malloc(20);
	char	dst[] = "Bonjour";
	char	dstdup[] = "Bonjour";
	printf("\n---------------- Ft_strcpy -----------------\n");

	printf("Standard test : \033[36mLibasm -> \033[00m%s\033[36m & Libc -> \033[00m%s\n", ft_strcpy(dst, "Hello"), strcpy(dstdup, "Hello"));

	printf("Empty string on src test : \033[36mLibasm -> \033[00m%s\033[36m & Libc -> \033[00m%s\n", ft_strcpy(dst, ""), strcpy(dst, ""));

	free(ret);
	*ret = 0;
}

void		ft_check_strcmp(void)
{
	char	empty[] = "";
	char	filled[] = "Hello World !";
	printf("\n---------------- Ft_strcmp -----------------\n");

	printf("Same test : \033[36mLibasm -> \033[00m%d\033[36m & Libc -> \033[00m%d\n", ft_strcmp("Hello" , "Hello"), strcmp("Hello" , "Hello"));

	printf("Lower test : \033[36mLibasm -> \033[00m%d\033[36m & Libc -> \033[00m%d\n", ft_strcmp("abcd", "abce"), strcmp("abcd", "abce"));

	printf("Higher test : \033[36mLibasm -> \033[00m%d\033[36m & Libc -> \033[00m%d\n", ft_strcmp("abce", "abcd"), strcmp("abce", "abcd"));

	printf("With one empty test : \033[36mLibasm -> \033[00m%d\033[36m & Libc -> \033[00m%d\n", ft_strcmp(filled, empty), strcmp(filled, empty));
	printf("With other empty test : \033[36mLibasm -> \033[00m%d\033[36m & Libc -> \033[00m%d\n", ft_strcmp(empty, filled), strcmp(empty, filled));

	printf("With two empty test : \033[36mLibasm -> \033[00m%d\033[36m & Libc -> \033[00m%d\n", ft_strcmp("", ""), strcmp("", ""));
}

void		ft_check_strdup(void)
{
	char	str[] = "KONO WA DIO DA !!";
	char	empty[] = "";
	char	big[] = "ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA ! ORA-ORA !";
	printf("\n---------------- Ft_strdup -----------------\n");
	printf("Regular test : \033[36mLibasm -> \033[00m%s\033[36m & Libc -> \033[00m%s\n", ft_strdup(str), strdup(str));
	printf("Big test : \033[36mLibasm -> \033[00m%s\033[36m & Libc -> \033[00m%s\n", ft_strdup(big), strdup(big));
	printf("Empty test : \033[36mLibasm -> \033[00m%s\033[36m & Libc -> \033[00m%s\n", ft_strdup(empty), strdup(empty));
}

int			main(void)
{
	ft_check_write();
//	ft_check_read();
	ft_check_strlen();
//	ft_check_strcpy();
//	ft_check_strcmp();
//	ft_check_strdup();
	return (0);
}
