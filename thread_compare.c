#include"thread_compare.h"

//extern char evil_pos;
//extern int counter;
//extern int dead_time;

void function_compare(char from_key,char from_view );

void *thread_compare(void *arg)
{	
	VAR_GET_C *p_var = (VAR_GET_C*)arg;
	
	char get_from_key;

	while(1)
	{
		get_from_key =  VGC_get_var(p_var);
		//printf("\n thread compare %c \n",get_from_key);
		function_compare(get_from_key,M_get_evil());
	}
	
}

void function_compare(char from_key,char from_view )
{
	if( 0 == from_view) return;
	if(from_key == from_view)  M_set_count(1);
	else if(M_get_count() > 0) M_set_count(-1);
} 
