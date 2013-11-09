all: ptab.c com.c procs.c proc1.c proc2.c 
	gcc -o OSsim procs.c com.c ptab.c -I /usr/pkg/share/x11-links/include -L /usr/pkg/share/x11-links/lib -lX11 -lm -g
	gcc -o proc1 proc1.c
	gcc -o proc2 proc2.c

clean: 
	rm OSprocs
	rm proc1
	rm proc2

object: ptab.c com.c procs.c
	gcc -c procs.c com.c ptab.c -I /usr/pkg/share/x11-links/include -L /usr/pkg/share/x11-links/lib -lX11 -lm -g
	gcc -c testStudent.c

test: ptab.o com.o procs.o testStudent.o
	gcc testStudent.o procs.o ptab.o com.o -o test -I /usr/pkg/share/x11-links/include -L /usr/pkg/share/x11-links/lib -lX11 -lm -g

