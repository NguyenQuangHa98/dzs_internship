#include "thread_get_key.h"

//VAR_GET_C *p_get_c = NULL;
extern int dead_time;
extern int counter;
extern char evil_pos;
void function_compare(char from_key,char from_view );

void *thread_keyboard(void *arg)
{   
    int c;   
    static struct termios oldt, newt;

    /*tcgetattr gets the parameters of the current terminal
    STDIN_FILENO will tell tcgetattr that it should write the settings
    of stdin to oldt*/
    tcgetattr( STDIN_FILENO, &oldt);
    /*now the settings will be copied*/
    newt = oldt;

    /*ICANON normally takes care that one line at a time will be processed
    that means it will return if it sees a "\n" or an EOF or an EOL*/
    newt.c_lflag &= ~(ICANON|ECHO);          

    /*Those new settings will be set to STDIN
    TCSANOW tells tcsetattr to change attributes immediately. */
    tcsetattr( STDIN_FILENO, TCSANOW, &newt);

    /*This is your part:
    I choose 'q' to end input. Notice that EOF is also turned off
    in the non-canonical mode*/
	
	/*create get_c object */
	//p_get_c = VGC_get_var_c();

	/*create the thread to count */
	while(0 != dead_time)
	{
		c = getchar();
		if(c >=  '1' && c <= '9')
		{	
			/*VGC_set_var(p_get_c,c);*/
			function_compare(c,evil_pos);
		}
	}                 

    /*restore the old settings*/
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
	return NULL;
}

void function_compare(char from_key,char from_view )
{
	if(from_key == from_view)
		counter++;	
	else if(counter > 0)
		counter--;
}
