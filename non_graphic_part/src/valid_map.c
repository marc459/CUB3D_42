#include "includes.h"


int		valid_map(char *line, archparams_t *arch)
{
	int i;

	i = 0;
	while (line[i] == ' ' && line[i] != '\0')
			i++;

	return(1);
}