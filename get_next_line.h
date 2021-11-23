#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 100
#endif

char	*get_next_line(int fd);

char	*ft_strjoin(char const *s1, char const *s2);

size_t	ft_strlen(const char *c);

char	*ft_strchr(const char *s, int c);

#endif