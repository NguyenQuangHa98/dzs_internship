#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>


#include "thread_get_key.h"
#include "thread_compare.h"
#include "variable_get_char.h"

void render_map(char *file_name);
void stop_and_check(int level, int random_pos, int score_temp, time_t begin_time);

int dead_time = 1;
char evil_pos = 0;
int counter = 0;
int main()
{
	int random_pos, score_temp;
	char *file_name;
	int level = 1;

	/* create new thread to get key typed by player */
	pthread_t keyboard;
	pthread_create(&keyboard, NULL, thread_keyboard, NULL);

	/* starting timer */
	time_t begin_time = time(NULL);

	while(1)
	{	
		/* reset evil position */
		evil_pos = 0;

		/* print 9 empty boxes, player's score and time left */
		render_map("textart");
		printf("\n%d\n", counter);
		printf("%d\n", 60 - (int)difftime(time(NULL), begin_time));

		sleep(1);

		/* calculate elapsed time */
		if(difftime(time(NULL), begin_time) >= 60)
		{	
			// print something...
			dead_time = 0;
			pthread_exit(NULL);
		}

		/* print 1 evil and 8 empty boxes */

		/* randomize a position of evil */
		srand(time(NULL));
		random_pos = (rand() % 9) + 1;

		/* create file name correspoding the above position */
		file_name = (char*)malloc(30 * sizeof(char));
		snprintf(file_name, 30, "%s%d", "textart", random_pos);

		/* get current score to check if it increase or not */
		score_temp = counter;

		/* get appropriate file and render to console*/
		render_map(file_name);
		free(file_name);
		printf("\n%d\n", counter);
		printf("%d\n", 60 - (int)difftime(time(NULL), begin_time));

		/* update current position of evil */
		evil_pos = random_pos + 48;

		/* update level based on scores that player achieved */
		if(counter >= 5 && counter < 15 && level < 2)
			level = 2;
		else if(counter >= 15 && level < 3)
			level = 3;
		
		//sleep_based_level(level);
		stop_and_check(level, random_pos, score_temp, begin_time);
	}
	return 0;
}

void render_map(char *file_name)
{
		FILE *fp;
		char *buff = (char*)malloc(1000000 * sizeof(char));

		system("clear");

		buff = (char*)malloc(1000000 * sizeof(char));
		fp = fopen(file_name, "r");
		fread(buff, 1, 1000000, fp);
		printf("%s", buff);
		
		free(buff);
		fclose(fp);
}

void stop_and_check(int level, int random_pos, int score_temp, time_t begin_time)
{
	char file_name[30];
	static int level_time[3] = {1500000, 1000000, 500000};
	struct timeval start, current;
	gettimeofday(&start, NULL);

	while(1)
	{
		gettimeofday(&current, NULL);
		if(current.tv_sec * 1000000 + current.tv_usec >= start.tv_sec * 1000000 + start.tv_usec + level_time[level - 1])
			break;
		if(counter > score_temp)
		{
			score_temp = counter;
			/* create file name */
			snprintf(file_name, 30, "%s%d", "textart_heart", random_pos);
			/* render map to screen */
			render_map(file_name);
			/* print score and time left to screen */
			printf("\n%d\n", counter);
			printf("%d\n", 60 - (int)difftime(time(NULL), begin_time));
		}
	}
}
