#include "includes.h"


int		valid_map(char *line, validmap_t *map)
{
	int i;
	int x;
	int count;

	i = 0;
	x = 0;
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
			else
				return (0);
		}
		
		printf("\nlinewidth -> %d,\n",map->line_width);
		printf("colm_nums: %d\n\n",count);
		printf("Nums->\n");
		for(int x = 0;x < count;x++)
			printf("%d-",map->colum_nums[x]);
		printf("\nSpaces->\n");
		for(int x = 0;x < count;x++)
			printf("%d-",map->colum_spaces[x]);
		printf("\n\n");
		map->m_top = 1;
	}
	else
	{
		if (map->colum_spaces[0] > 0)
			i = -1;
		
		while(map->colum_spaces[x] != 0 || map->colum_nums[x] != 0)
		{
			printf("%d , %d\n",map->colum_spaces[x], map->colum_nums[x]);
			//Comprueba la existencia de 1
			if(map->colum_spaces[x] != 0)
			{
					i = i + map->colum_spaces[x] + 1;
					printf("line2s i %d->%c\n",i ,line[i]);
					if(!(line[i] == '1' || line[i] == ' '))
						return (0);
			}
			if(map->colum_nums[x] != 0)
			{
					i = i + map->colum_nums[x] - 1;
					printf("line2n i %d->%c\n",i ,line[i]);
					if(!(line[i] == '1' || line[i] == ' '))
						return (0);
			}
			x++;
		}
		//printf("\n\n");
		i = 0;
		init_map_checking_params(map);

		while(line[i] != '\0')
		{
			if(line[i] == ' ' || (line[i] >= '0' && line[i] <= '2') || ft_strchr("NSEW",line[i]))
			{
				if (line[i + 1] == ' ')
				{
					if(line[i] != '1' && line[i] != ' ')
						return (0);
				}
				while (line[i] == ' ')
				{
					map->colum_spaces[count]++;
					i++;
				}
				if(line[i] != '1')
					return (0);
				while (((line[i] >= '0' && line[i] <= '2') || ft_strchr("NSEW",line[i])) && line[i] != '\0')
				{
					map->colum_nums[count]++;
					map->line_width++;
					i++;
				}
				count++;
			}
			else
				return (0);
			//printf("char %d ->%c;\n",i,line[i]);
		}
		//printf("line2->%c\n",line[map->colum_spaces[1]]);
		//return(0);
	}
	return(1);
}