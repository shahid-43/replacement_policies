# Complete This!
	
main: main.o policy.o workload.o
	gcc main.o policy.o workload.o -o main

main.o:main.c 
	gcc -c main.c

policy.o:policy.c 
	gcc -c policy.c

checker.o:checker.c 
	gcc -c checker.c

workload.o:workload.c 
	gcc -c workload.c

clean:
	rm -f main *.o

