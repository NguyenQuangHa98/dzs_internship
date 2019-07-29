#include"mutex.h"

extern int dead_time;
extern char evil_pos;
extern int counter;

static pthread_mutex_t mutex_count = PTHREAD_MUTEX_INITIALIZER;

static pthread_mutex_t mutex_evil = PTHREAD_MUTEX_INITIALIZER;

static pthread_mutex_t mutex_dead = PTHREAD_MUTEX_INITIALIZER;


void M_set_count(int value)
{
	pthread_mutex_lock(&mutex_count);
	counter += value;
	pthread_mutex_unlock(&mutex_count);
}

int M_get_count()
{
	pthread_mutex_lock(&mutex_count);
	int value = counter;
	pthread_mutex_unlock(&mutex_count);
	return value;
}

void M_set_evil(char value)
{
	pthread_mutex_lock(&mutex_evil);
	evil_pos = value;
	pthread_mutex_unlock(&mutex_evil);
}

char M_get_evil()
{
	pthread_mutex_lock(&mutex_count);
	char value = evil_pos;
	pthread_mutex_unlock(&mutex_count);
	return value;
}

/*
void M_set_dead(int value)
{
	pthread_mutex_lock(&mutex_count);
	dead_time = value;
	pthread_mutex_unlock(&mutex_count);
}

int M_get_dead()
{
	pthread_mutex_lock(&mutex_count);
	int value = dead_time;
	pthread_mutex_unlock(&mutex_count);
	return value;
}
*/
