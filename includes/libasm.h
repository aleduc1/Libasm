#ifndef LIBASM_H
# define LIBASM_H

#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

extern	ssize_t ft_read(int fd, void *buf, size_t count);
extern	ssize_t ft_write(int fd, const void *buf, size_t count);
size_t	ft_strlen(const char *s);
char		*ft_strcpy(char *dest, const char *src);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s);

#endif
