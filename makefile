CFLAGS= -g -Wall -std=c99
LDFLAGS = -g -std=c99
TARGET=now when periodic launch_deamon teste period

all: $(TARGET)

teste: teste.o libmessage.so message.h
	gcc -g -o teste teste.o -lmessage -L${PWD}
teste.o:teste.c
	gcc -c $(CFLAGS) -o teste.o teste.c 

period: period.o libmessage.so message.h
	gcc -g -o teste teste.o -lmessage -L${PWD}
period.o:period.c
	gcc -c $(CFLAGS) -o period.o period.c 
	
now: now.o 
	gcc -g -o now now.o
now.o: now.c 
	gcc -c $(CFLAGS) -o now.o now.c

when: when.o 
	gcc -g -o when when.o
when.o: when.c 
	gcc -c $(CFLAGS) -o when.o when.c

periodic: periodic.o libmessage.so message.h
	gcc -g -o periodic periodic.o -lmessage -L${PWD}
periodic.o: periodic.c 
	gcc -c $(CFLAGS) -o periodic.o periodic.c

launch_deamon: launch_deamon.o 
	gcc -g -o launch_deamon launch_deamon.o
launch_deamon.o: launch_deamon.c 
	gcc -c $(CFLAGS) -o launch_deamon.o launch_deamon.c
	
message.o : message.c message.h
	gcc -c message.c -o message.o -fPIC

libmessage.so : message.o 
	gcc -shared -o libmessage.so $^
	export LD_LIBRARY_PATH=${PWD}
	
clean:
	rm -f *.o
mrproper: clean
	rm -f now
	rm -f when 
	rm -f periodic
	rm -f libmessage.so


