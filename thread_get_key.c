#include "thread_get_key.h"

static VAR_GET_C *p_get_c = NULL;
//extern int dead_time;

void *thread_keyboard(void *arg)
{   
	pthread_t thread_id;
	int status;
	char get_key;
	/*create get_c object */
	p_get_c = VGC_get_var_c();
    VGC_init();
	
	/*create thread compare */
	status = pthread_create(&thread_id,NULL,thread_compare,(void*)p_get_c);
	if(0 != status)
	{
		printf("pthread_create() error number= %d \n",status);
	}

	/*create the thread to count */
	while(1)
	{
		get_key = VGC_getchar();	
		VGC_set_var(p_get_c,get_key);
	}

    /*restore the old settings*/
    /*tcsetattr( STDIN_FILENO, TCSANOW, &oldt);*/
	pthread_cancel(thread_id);
	VGC_restore_init();
	//printf("adc\n");
	return NULL;
}
