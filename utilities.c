#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>
#include <pthread.h>

//extern int counter;
///extern int dead_time;
void *play_bg_sound()
{
	system("mpg321 ultimate-power1m.mp3 >/dev/null 2>&1");
	pthread_exit(NULL);
}

void *play_detection_sound()
{
	int old_score = M_get_count();  //counter;
	while(1)
	{
		if(M_get_count() != old_score)
		{	
			if(M_get_count() > old_score)	
				system("aplay ting.wav >/dev/null 2>&1 &");
			old_score = M_get_count();
		}
	}
	pthread_exit(NULL);
}



/*
void set_cur_pos(int x, int y);
void get_cur_pos(int *x, int *y);
void coord_print(const char *str, int x, int y);

void set_cur_pos(int x, int y)
{
	printf("\033[%d;%dH", x + 1, y + 1);
}

void get_cur_pos(int *x, int *y)
{
	int i = 0, j = 0;
	char ch;
	char *x_str = (char*)malloc(10 * sizeof(char));
	char *y_str = (char*)malloc(10 * sizeof(char));

	struct termios term, restore;
	tcgetattr(0, &term);
	tcgetattr(0, &restore);
	term.c_lflag &= ~(ICANON|ECHO);
	tcsetattr(0, TCSANOW, &term);

	write(1, "\033[6n", 4);

	do
	{
		read(0, &ch, 1);
		// when meet the first digit, iterate and push that digits to y until  meet character ";"
		if(isdigit(ch) != 0)
		{
			while(ch != ';')
			{
				x_str[i] = ch;
				i++;
				read(0, &ch, 1);
			}
			x_str[i] = '\0';
			// now ch is ';' character
			read(0, &ch, 1);
			while(ch != 'R')
			{
				y_str[j] = ch;
				j++;
				read(0, &ch, 1);
			}
			y_str[j] = '\0';
		}
	} while(ch != 'R');

	*x = atoi(x_str);
	*y = atoi(y_str);

	tcsetattr(0, TCSANOW, &restore);
	return;
}

void coord_print(const char *str, int x, int y)
{
	int i = 0;
	while(str[i] != '\0')
	{
		set_cur_pos(x, y);
		while(str[i] != '\n')
		{
			putchar(str[i]);
			i++;
		}
		i++; x++;
	}
}
*/


