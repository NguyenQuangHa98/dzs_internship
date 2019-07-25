#include "variable_get_char.h"

static VAR_GET_C *p_var = NULL;

static struct termios oldt, newt;

void VGC_init()
{
	
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
}

void VGC_restore_init()
{
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
}

VAR_GET_C *VGC_ctor(void)
{
	VAR_GET_C *p_var;
	int s;
	p_var = (VAR_GET_C*)malloc(sizeof(VAR_GET_C));
	if(NULL != p_var)
	{
		s = pthread_mutex_init(&p_var->c_mutex,NULL);
		p_var->c_get = 0;
		if(0 != s )
		{
			free(p_var);
			return NULL;
		}
		s = pthread_cond_init(&p_var->c_cond,NULL);
		if( 0 != s )
		{
			free(p_var);
			return NULL;
		}
	}
	return p_var;
}

VAR_GET_C *VGC_get_var_c(void)
{
	if(NULL == p_var)
	{
		p_var = VGC_ctor();
	}
	return p_var;
}
//VAR_GET_C VGC_rele(VAR_GET_C *p_var)

void VGC_set_var(VAR_GET_C *p_var,char c)
{
	pthread_mutex_lock(&p_var->c_mutex);
	p_var-> c_get = c;
	//printf("%c-%d",c,p_var);
	pthread_mutex_unlock(&p_var->c_mutex);
	pthread_cond_signal(&p_var->c_cond);
}

char VGC_get_var(VAR_GET_C *p_var)
{
	char c;
	//printf("get var 1- %d\n",p_var);
	pthread_mutex_lock(&p_var->c_mutex);
	//printf("get var 2");
	pthread_cond_wait(&p_var->c_cond,&p_var->c_mutex);
	c = p_var->c_get;
	//printf("%c\n",c);
	pthread_mutex_unlock(&p_var->c_mutex);
	return c;
}

char VGC_getchar(void)
{
	char c = 0;
	do
	{
		c = getchar();
		//printf("%c\n",c);
	}
	while(c < '1' || c > '9');
	return c;
}
