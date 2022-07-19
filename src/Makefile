CC = gcc
FLAGS = -Wall -Werror -Wextra
.PHONY: all clean state_sort

all: clean state_sort state_search clear_state

clean:
	rm -rf ../build/*

state_sort: state_sort.c
	$(CC) $(FLAGS) -o ../build/Quest_1 state_sort.c

state_search: state_search.c
	$(CC) $(FLAGS) -o ../build/Quest_2 state_search.c

clear_state: clear_state.c
	$(CC) $(FLAGS) -o ../build/Quest_3 clear_state.c