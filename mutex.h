#ifndef MUTEX_H
#define MUTEX_H

#include<pthread.h>


void M_set_count(int value);
int M_get_count();

void M_set_evil(char value);
char M_get_evil();

//void M_set_dead(int value);
//int M_get_dead();

#endif
