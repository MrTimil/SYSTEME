all: now when clean 

now: now.o 
	gcc -g -o now now.o

now.o: now.c 
	gcc -c -Wall -g -o now.o now.c

when: when.o 
	gcc -g -o when when.o

when.o: when.c 
	gcc -c -Wall -g -o when.o when.c

clean:
	rm -f *.o
mrproper: clean
	rm -f now
	rm -f when 
