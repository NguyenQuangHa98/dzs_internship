CC = gcc

game: main.c thread_get_key.c thread_compare.c variable_get_char.c utilities.c mutex.c
	$(CC) -pthread -o game main.c thread_get_key.c thread_compare.c variable_get_char.c utilities.c mutex.c
