CC = gcc

game: main.c thread_get_key.c thread_compare.c variable_get_char.c
	$(CC) -lpthread -o game main.c thread_get_key.c thread_compare.c variable_get_char.c
