

all:
	gcc -Wall -Werror -Wextra -std=c11 -c *.c 
	gcc -o test *.o
	./test
	rm *.o
	rm test

debug:
	gcc -Wall -Werror -Wextra -std=c11 -c -g *.c
	gcc -o test *.o