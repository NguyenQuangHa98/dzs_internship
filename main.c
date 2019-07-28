#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>

#include "utilities.h"
#include "thread_get_key.h"
#include "thread_compare.h"
#include "variable_get_char.h"

#define FILE_NAME_SIZE 30
#define LV1_MAX_SCORE 5
#define LV2_MAX_SCORE 15
#define LV1_UTIME 1500000
#define LV2_UTIME 1000000
#define LV3_UTIME 500000

int dead_time = 1;
char evil_pos = 0;
int counter = 0;

void render_map(char *file_name);
void wait_and_check(int level, int random_pos, int score_temp, time_t begin_time);
void print_info(time_t begin_time);

int main()
{
	int random_pos, score_temp;
	char *file_name;
	int level = 1;
	time_t begin_time, elapsed_time;

	/* create new thread to get key typed by player */
	pthread_t keyboard, sound_thread, detection_sound_thread;
	pthread_create(&keyboard, NULL, thread_keyboard, NULL);
	pthread_create(&sound_thread, NULL, play_bg_sound, NULL);
	pthread_create(&detection_sound_thread, NULL, play_detection_sound, NULL);

	/* starting timer */
	begin_time = time(NULL);

	while(1)
	{	
		/* reset evil position */
		evil_pos = 0;

		/* print 9 empty boxes, player's score and time left */
		render_map("textart");

		/* print scores and time left */
		print_info(begin_time);

		sleep(1);

		/* calculate elapsed time */
		elapsed_time = time(NULL) - begin_time;
		if(elapsed_time >= 60)
		{
			if(elapsed_time == 60)
			{
				render_map("textart");
				print_info(begin_time);
			}

			/* print final score and new record (if any) */
			printf("Timeout! Your final scores: %d\n", counter);

			int record;
			char record_str[3];
			FILE *rc_fp = fopen("record.txt", "r");
			fgets(record_str, sizeof(record_str), rc_fp);
			record = atoi(record_str);
			if(counter > record)
			{
				fclose(rc_fp);
				rc_fp = fopen("record.txt", "w");
				printf("Congratulations!!! You made a new record!!!\n");
				snprintf(record_str, sizeof(record_str), "%d", counter);
				fputs(record_str, rc_fp);
			}
			else
				printf("Try harder to break the current record (%d)\n", record);
			fclose(rc_fp);

			dead_time = 0;
			pthread_join(keyboard, NULL);
			return 0;
		}

		/* print 1 evil and 8 empty boxes */

		/* randomize a position of evil */
		srand(time(NULL));
		random_pos = (rand() % 9) + 1;

		/* create file name correspoding the above position */
		file_name = (char*)malloc(FILE_NAME_SIZE * sizeof(char));
		snprintf(file_name, FILE_NAME_SIZE, "%s%d", "textart", random_pos);

		/* get current score to check if then it increase or not */
		score_temp = counter;

		/* get appropriate file and print to console*/
		render_map(file_name);
		free(file_name);

		/* print scores and time left */
		print_info(begin_time);

		/* update current position of evil */
		evil_pos = random_pos + 48;

		/* update level based on scores that player achieved */
		if(counter >= LV1_MAX_SCORE && counter < LV2_MAX_SCORE && level < 2)
			level = 2;
		else if(counter >= LV2_MAX_SCORE && level < 3)
			level = 3;

		/* wait for tapping from player and check that input */
		wait_and_check(level, random_pos, score_temp, begin_time);
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

void wait_and_check(int level, int random_pos, int score_temp, time_t begin_time)
{
	char file_name[FILE_NAME_SIZE];
	int level_time[3] = {LV1_UTIME, LV2_UTIME, LV3_UTIME};
	struct timeval start, current;
	gettimeofday(&start, NULL);

	while(1)
	{
		gettimeofday(&current, NULL);
		if(current.tv_sec * 1000000 + current.tv_usec >= start.tv_sec * 1000000 + start.tv_usec + level_time[level - 1])
			break;

		if(counter != score_temp)
		{
			if(counter > score_temp)
			{
				/* create file name */
				snprintf(file_name, FILE_NAME_SIZE, "%s%d", "textart_heart", random_pos);
				/* render map to screen */
				render_map(file_name);
				/* print score and time left to screen */
				print_info(begin_time);
			}
			score_temp = counter;
		}
	}
}

void print_info(time_t begin_time)
{
	printf("\nScores: %d\n", counter);
	printf("Time left: %ld\n", 60 - (time(NULL) - begin_time));
}
