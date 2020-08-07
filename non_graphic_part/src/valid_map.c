#include "includes.h"


int		valid_map(char *line, validmap_t *map)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (map->m_top == 0)
	{
		while(line[i] != '\0')
		{
			if(line[i] == ' ' || line[i] == '1')
			{
				while (line[i] == ' ')
				{
					map->colum_spaces[count]++;
					i++;
				}
				while (line[i] == '1')
				{
					map->colum_nums[count]++;
					map->line_width++;
					i++;
				}
				count++;
			}
			i++;
		}
		
		printf("\nlinewidth -> %d,\n",map->line_width);
		printf("colm_nums: %d\n",count);
		printf("Unos->\n");
		for(int x = 0;x < count;x++)
			printf("%d-",map->colum_nums[x]);
		printf("\nespaces->\n");
		for(int x = 0;x < count;x++)
			printf("%d-",map->colum_spaces[x]);
		printf("\n");
		map->m_top = 1;
	}
	
	return(1);
}