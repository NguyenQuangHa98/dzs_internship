#ifndef VARIABLE_GET_CHAR_H
#define VARIABLE_GET_CHAR_H

#include<pthread.h>
#include <termios.h>    //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO
#include <stdlib.h>
#include <stdio.h>

typedef struct VAR_GET_C
{
	char c_get;
	pthread_mutex_t c_mutex;
	pthread_cond_t c_cond;
}VAR_GET_C;

VAR_GET_C *VGC_get_var_c(void); 
VAR_GET_C VGC_free(VAR_GET_C *p_var);

char VGC_getchar(void);
void VGC_set_var(VAR_GET_C *p_var,char c);
char VGC_get_var(VAR_GET_C *p_var);
void VGC_init();
void VGC_restore_init();

#endif
