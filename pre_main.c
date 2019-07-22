#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // for random()

#include "utilities.h"
int main()
{
	int i, j, x, y, x_rand, y_rand;
	get_cur_pos(&x, &y);

	int map[3][3];

	while(1)
	{
		memset(map, 0, sizeof(map));
		
		for(i = 0; i < 3; i++)
		{
f			for(j = 0; j < 3; j++)
			{
				coord_print(textart_empty_box, x + 16 * i, y + 40 * j);
			}
		}
		sleep(1); getchar();


		srand(time(0));
		x_rand = rand() % 3;
		y_rand = rand() % 3;
		map[x_rand][y_rand] = 1;
		system("clear");

		for(i = 0; i < 3; i++)
		{
			for(j = 0; j < 3; j++)
			{
				if(map[i][j] == 0)
					coord_print(textart_empty_box, x + 16 * i, y + 40 * j);
				else
					coord_print(textart_devil, x + 16 * i, y + 40 * j);
			}
		}
		sleep(1); getchar();
	}
	return 0;
}
