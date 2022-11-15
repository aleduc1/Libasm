#include "libasm.h"

void		ft_check_write(void)
{
	int ret = 0;
	printf("---------------- Ft_write ------------------\n");

	printf("\033[36mLibasm\033[00m\n");
	ret = ft_write(1, "Hello world!\n", 14);
	printf("With correct fd -> ret value = %d,  error value = %d : %s\n", ret, errno, strerror(errno));
	printf("\033[36mLibc\033[00m\n");
	ret = write(1, "Hello world!\n", 14);
	printf("With correct fd -> ret value = %d,  error value = %d : %s\n\n", ret, errno, strerror(errno));

	printf("\033[36mLibasm\033[00m\n");
	ret = ft_write(-1, "Hello world!\n", 13);
	printf("With wrong fd -> ret value = %d,  error value = %d : %s\n", ret, errno, strerror(errno));
	errno = 0;
	printf("\033[36mLibc\033[00m\n");
	ret = write(-1, "Hello world!\n", 13);
	printf("With wrong fd -> ret value = %d,  error value = %d : %s\n\n", ret, errno, strerror(errno));
	errno = 0;

	printf("\033[36mLibasm\033[00m\n");
	ret = ft_write(1, "", 1);
	printf("With empty buffer -> ret value = %d,  error value = %d : %s\n", ret, errno, strerror(errno));
	printf("\033[36mLibc\033[00m\n");
	ret = write(1, "", 1);
	printf("With empty buffer -> ret value = %d,  error value = %d : %s\n\n", ret, errno, strerror(errno));
}

void		ft_check_read(void)
{
	int			ret;
	char		buf[5000];

	printf("----------------- Ft_read ------------------\n");

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
	printf("With wrong fd -> ret value = %d,  error value = %d : %s\n", ret, errno, strerror(errno));
	errno = 0;
}

void		ft_check_strlen(void)
{
	printf("---------------- Ft_strlen -----------------\n");

	printf("\033[36mLibasm\033[00m\n");
	printf("%d\n", ft_strlen("Hello word"));
	printf("\033[36mLibc\033[00m\n");
	printf("%ld\n\n", strlen("Hello word"));

	printf("\033[36mLibasm\033[00m\n");
	printf("%d\n", ft_strlen("a"));
	printf("\033[36mLibc\033[00m\n");
	printf("%ld\n\n", strlen("a"));

	printf("\033[36mLibasm\033[00m\n");
	printf("%d\n", ft_strlen("Test"));
	printf("\033[36mLibc\033[00m\n");
	printf("%ld\n\n", strlen("Test"));
}

void		ft_check_strcpy(void)
{
	char	dst[] = "Bonjour";
	char	src[] = "Hello";
	printf("---------------- Ft_strcpy -----------------\n");

	printf("\033[36mLibasm\033[00m\n");
	ft_strcpy(dst, src);
	printf("return : %s\n", dst);
// ToDo Important, strcpy doesnt work when we deal with its return value, ill give it up for now but it isnt a functional complete function !!!
//	printf("return : %s\n\n", ft_strcpy(dst, src));
//	printf("\033[36mLibc\033[00m\n");
//	printf("return : %s\n\n", strcpy(dst, src));
//
// ToDo test with empty strings on src then dst, when the return value will work
//	printf("\033[36mLibasm\033[00m\n");
//	printf("return : %s\n", ft_strcpy(empty, full));
//	printf("\033[36mLibc\033[00m\n");
//	printf("return : %s\n\n", strcpy(empty, full));
//
//	printf("\033[36mLibasm\033[00m\n");
//	printf("return : %s\n", ft_strcpy(full, empty));
//	printf("\033[36mLibc\033[00m\n");
//	printf("return : %s\n", strcpy(full, empty));
}

void		ft_check_strcmp(void)
{
	char	empty[] = "";
	char	filled[] = "Hello World !";
	printf("---------------- Ft_strcmp -----------------\n");
	/* Same test */
	printf("\033[36mLibasm\033[00m\n");
	printf("return : %d\n", ft_strcmp("Hello", "Hello"));
	printf("\033[36mLibc\033[00m\n");
	printf("return : %d\n\n", strcmp("Hello", "Hello"));

	/* Lower test */
	printf("\033[36mLibasm\033[00m\n");
	printf("return : %d\n", ft_strcmp("abcd", "abce"));
	printf("\033[36mLibc\033[00m\n");
	printf("return : %d\n\n", strcmp("abcd", "abce"));

	/* Higher test */
	printf("\033[36mLibasm\033[00m\n");
	printf("return : %d\n", ft_strcmp("abce", "abcd"));
	printf("\033[36mLibc\033[00m\n");
	printf("return : %d\n\n", strcmp("abce", "abcd"));

	/* With one empty test */
	printf("\033[36mLibasm\033[00m\n");
	printf("return : %d\n", ft_strcmp(filled, empty));
	printf("\033[36mLibc\033[00m\n");
	printf("return : %d\n\n", strcmp(filled, empty));
	printf("\033[36mLibasm\033[00m\n");
	printf("return : %d\n", ft_strcmp(empty, filled));
	printf("\033[36mLibc\033[00m\n");
	printf("return : %d\n\n", strcmp(empty, filled));

	/* With two empty test */
	printf("\033[36mLibasm\033[00m\n");
	printf("return : %d\n", ft_strcmp("", ""));
	printf("\033[36mLibc\033[00m\n");
	printf("return : %d\n\n", strcmp("", ""));

}

//void		ft_check_strdup(void)
//{
//	char	dup[] = "New Malloc";
//	char	dup1[] = "little";
//	char	dup2[] = "Very big malloc, libasm is a project that was very interesting to me at the time and I am doing a test of my function with a rather large sentence without any goal, but here I fill as I can thank you for ignoring this sentence, there even punctuation or spelling, this is a crash test !";
//	printf("---------------- Ft_strdup -----------------\n");
//	printf("\033[36mresultat : libasm\033[00m\n");
//	printf("return : |%s|\n", ft_strdup(dup));
//	printf("\033[36mresultat : libc\033[00m\n");
//	printf("return : |%s|\n\n", strdup(dup));
//	printf("\033[36mresultat : libasm\033[00m\n");
//	printf("return : |%s|\n", ft_strdup(dup1));
//	printf("\033[36mresultat : libc\033[00m\n");
//	printf("return : |%s|\n\n", strdup(dup1));
//	printf("\033[36mresultat : libasm\033[00m\n");
//	printf("return : |%s|\n", ft_strdup(dup2));
//	printf("\033[36mresultat : libc\033[00m\n");
//	printf("return : |%s|\n\n", strdup(dup2));
//}

int			main(void)
{
//	ft_check_write();
//	ft_check_read();
//	ft_check_strlen();
//	ft_check_strcpy();
	ft_check_strcmp();
//	ft_check_strdup();
	return (0);
}
