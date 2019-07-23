#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#include "thread_get_key.h"

int dead_time = 1;

char evil_pos;
int counter = 0;
int main()
{
	int map[10], random_pos;
	char *file_name, *buff;
	FILE *fp;
	time_t begin_time;
	// double elapsed_time;

	/* create new thread to get key typed by player */
	pthread_t keyboard;
	pthread_create(&keyboard, NULL, thread_keyboard, NULL);

	/* starting timer */
	begin_time = time(NULL);

	while(1)
	{
		/* calculate elapsed time */
		// elapsed_time = difftime(time(NULL), begin_time);
		if(difftime(time(NULL), begin_time) >= 60)
		{
			// print something...
			dead_time = 0;
			pthread_exit(NULL);
		}
		
		/* print 9 empty boxes */
		system("clear");
		evil_pos = 0;

		buff = (char*)malloc(1000000 * sizeof(char));
		fp = fopen("textart", "r");
		fread(buff, 1, 1000000, fp);
		printf("%s", buff);

		printf("\n%d\n", counter);
		printf("%d\n", 60 - (int)difftime(time(NULL), begin_time));

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
		snprintf(file_name, 30, "%s%d", "textart", random_pos);

		// get appropriate file to print to console
		system("clear");
		buff = (char*)malloc(1000000 * sizeof(char));
		fp = fopen(file_name, "r");
		fread(buff, 1, 1000000, fp);
		printf("%s", buff);

		printf("\n%d\n", counter);
		printf("%d\n", 60 - (int)difftime(time(NULL), begin_time));

		// update current position of evil
		evil_pos = random_pos + 48;

		free(file_name);
		free(buff);
		fclose(fp);

		// time of sleep based on scores that player achieved
		if(counter < 5)
			usleep(2000000);
		else if(counter < 10)
			usleep(1500000);
		else if(counter < 20)
			usleep(1000000);
		else
			usleep(500000);
	}
	return 0;
}
