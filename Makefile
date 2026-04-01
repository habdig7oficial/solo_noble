compile: 
	gcc trigger.c -o trigger

run: compile
	./trigger

check: compile
	valgrind --leak-check=full ./trigger