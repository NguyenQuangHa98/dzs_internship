#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // for random()
#include <pthread.h>

#include "thread_get_key.h"

char evil_pos;
int counter = 0;
int main()
{
	int map[10], random_pos;
	char temp[2];
	char *file_name, *buff;
	FILE *fp;
	// create new thread to get key typed by player
	pthread_t keyboard;
	pthread_create(&keyboard, NULL, thread_keyboard, NULL);

	while(1)
	{
		/* print 9 empty boxes */
		system("clear");
		evil_pos = 0;

		buff = (char*)malloc(1000000 * sizeof(char));
		fp = fopen("textart", "r");
		fread(buff, 1, 1000000, fp);
		printf("%s", buff);

		printf("\n%d\n", counter);

		free(buff);
		fclose(fp);	

		sleep(1);

		/* print 1 evil and 8 empty boxes */

		/* randomize a position of evil */
		memset(map, 0, sizeof(map));
		srand(time(0));
		random_pos = (rand() % 9) + 1;
		map[random_pos] = 1;

		/* create file name correspoding the above position */
		file_name = (char*)malloc(30 * sizeof(char));
		strcpy(file_name, "textart");
		temp[0] = (char)(random_pos + 48);
		temp[1] = '\0';
		strcat(file_name, temp);

		// get appropriate file to print to console
		system("clear");
		buff = (char*)malloc(1000000 * sizeof(char));
		fp = fopen(file_name, "r");
		fread(buff, 1, 1000000, fp);
		printf("%s", buff);

		printf("\n%d\n", counter);


		// update current position of evil
		evil_pos = random_pos + 48;

		free(file_name);
		free(buff);
		fclose(fp);
	
		// sleep(1);
		usleep(500000);
	}
	return 0;
}
