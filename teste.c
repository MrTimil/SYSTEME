#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <assert.h>
#include <time.h>
#include <fcntl.h>

#define N	1000000

#include "message.h"
// BOISSON Romain 
// PAQUETTE Emile 
// PROJET SYSTEME 

int main(int argc, char *argv[]){
	
	int test = open("log.txt",O_WRONLY | O_CREAT | O_TRUNC,0644);
	
	printf("%d",send_string(test,"My deamon is alive"));
	
	close(test);
	
	test = open("log.txt",O_RDONLY);
	 	
	char *rec;
	rec = recv_string(test);
	printf("Ma chaine la : %s \n",rec);

	close(test);
	
	
	// FIN 
	int i=0;
	
	char *table[3] = {"test","peut etre"};
	while(table[i] != NULL){
		printf("%s",table[i]);
		++i;
	}
	printf("wesh");
	
	test = open("log1.txt",O_WRONLY | O_CREAT | O_TRUNC,0644);
		printf("%d",send_argv(test,table));
	close(test);

	test = open("log1.txt",O_RDONLY);
	char **res  = recv_argv(test);
	
	printf("Ma chaine : %s \n",res[0]);
	printf("Ma chaine : %s \n",res[1]);	
	
	return 0;
}
