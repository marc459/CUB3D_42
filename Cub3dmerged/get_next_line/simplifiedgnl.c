#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include "../src/includes.h"

char *ft_strjoint(char *s, char c)
{
    char *dest;
    int i;
	
	i = 0;
    dest = malloc(ft_strlen(s) + 2);
    while (s[i] != '\0')
    {
        dest[i] = s[i];
        i++;
    }
    dest[i] = c;
    dest[i + 1] = '\0';
    free(s);
    return (dest);
}

int get_next_line(int fd, char **line)
{
    int ret;
    char buf[2];

    if (fd < 0 || line == NULL || !(*line = ft_strdup("")))
        return (-1);
    while ((ret = read(fd, buf, 1)) > 0)
    {
        if (buf[0] == '\n')
            break;
        *line = ft_strjoint(*line, buf[0]);
    }
    return (ret);
}
