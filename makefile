all: prog3_server

prog3_server: prog3_server.o syscalls.o prog3_funcs.o
	gcc -o prog3_server prog3_server.o syscalls.o prog3_funcs.o

syscalls.o: syscalls.h syscalls.c
	gcc -g -Wall -Wextra -Wwrite-strings -c syscalls.c

prog3_funcs.o: prog3_funcs.h prog3_funcs.c
	gcc -g -Wall -Wextra -Wwrite-strings -c prog3_funcs.c

prog3_server.o: globaldefs.h prog3_server.c
	gcc -g -Wall -Wextra -Wwrite-strings -c prog3_server.c

clean:
	 rm -f *.o
	 rm  prog3_server


