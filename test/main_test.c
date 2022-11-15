#include "libasm.h"

void		ft_check_write(void)
{
	int ret = 0;
	printf("============================================\n");
	printf("================ Ft_write ==================\n");
	printf("============================================\n\n");


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

	printf("============================================\n");
	printf("================= Ft_read ==================\n");
	printf("============================================\n\n");

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
	printf("============================================\n");
	printf("================ Ft_strlen =================\n");
	printf("============================================\n\n");

	printf("\033[36mLibasm\033[00m\n");
	printf("%d\n", ft_strlen("Hello word"));
	printf("\033[36mLibc\033[00m\n");
	printf("%d\n\n", strlen("Hello word"));

	printf("\033[36mLibasm\033[00m\n");
	printf("%d\n", ft_strlen("a"));
	printf("\033[36mLibc\033[00m\n");
	printf("%d\n\n", strlen("a"));

	printf("\033[36mLibasm\033[00m\n");
	printf("%d\n", ft_strlen("Test"));
	printf("\033[36mLibc\033[00m\n");
	printf("%d\n\n", strlen("Test"));
}


void		ft_check_strcpy(void)
{
	char	str1[] = "Bonjour";
	char	str2[] = "Hello";
	char	str3[] = "libc most power full";
	char	str4[] = "libasm is for the ";
	char	str5[] = "petit";
	char	str6[] = "grand";
	char	str7[] = "";
	printf("============================================\n");
	printf("================ Ft_strcpy =================\n");
	printf("============================================\n\n");

	printf("\033[36mLibasm\033[00m\n");
	printf("return : %s\n", ft_strcpy(str1, str2));
	printf("\033[36mLibc\033[00m\n");
	printf("return : %s\n\n", strcpy(str1, str2));

	printf("\033[36mLibasm\033[00m\n");
	printf("return : %s\n", ft_strcpy(str3, str4));
	printf("\033[36mLibc\033[00m\n");
	printf("return : %s\n\n", strcpy(str3, str4));

	printf("\033[36mLibasm\033[00m\n");
	printf("return : %s\n", ft_strcpy(str5, str6));
	printf("\033[36mLibc\033[00m\n");
	printf("return : %s\n\n", strcpy(str5, str6));

	printf("\033[36mLibasm\033[00m\n");
	printf("return : %s\n", ft_strcpy(str6, str7));
	printf("\033[36mLibc\033[00m\n");
	printf("return : %s\n\n", strcpy(str6, str7));

	printf("\033[36mLibasm\033[00m\n");
	printf("return : %s\n", ft_strcpy(str7, str6));
	printf("\033[36mLibc\033[00m\n");
	printf("return : %s\n\n", strcpy(str7, str6));
}

//void		ft_check_strcmp(void)
//{
//	char	strcmp1[] = "";
//	char	strcmp2[] = "Hello World !";
//	printf("============================================\n");
//	printf("================ Ft_strcmp =================\n");
//	printf("============================================\n\n");
//	printf("\033[36mresultat : libasm\033[00m\n");
//	printf("return : [%d]\n", ft_strcmp("Hello", "Hello"));
//	printf("\033[36mresultat : libc\033[00m\n");
//	printf("return : [%d]\n\n", strcmp("Hello", "Hello"));
//	printf("\033[36mresultat : libasm\033[00m\n");
//	printf("return : [%d]\n", ft_strcmp("abcd", "abce"));
//	printf("\033[36mresultat : libc\033[00m\n");
//	printf("return : [%d]\n\n", strcmp("abcd", "abce"));
//	printf("\033[36mresultat : libasm\033[00m\n");
//	printf("return : [%d]\n", ft_strcmp(strcmp2, strcmp1));
//	printf("\033[36mresultat : libc\033[00m\n");
//	printf("return : [%d]\n\n", strcmp(strcmp2, strcmp1));
//}

//void		ft_check_strdup(void)
//{
//	char	dup[] = "New Malloc";
//	char	dup1[] = "little";
//	char	dup2[] = "Very big malloc, libasm is a project that was very interesting to me at the time and I am doing a test of my function with a rather large sentence without any goal, but here I fill as I can thank you for ignoring this sentence, there even punctuation or spelling, this is a crash test !";
//	printf("============================================\n");
//	printf("================ Ft_strdup =================\n");
//	printf("============================================\n\n");
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
	ft_check_write();
	ft_check_read();
	ft_check_strlen();
	ft_check_strcpy();
//	ft_check_strcmp();
//	ft_check_strdup();
	return (0);
}
