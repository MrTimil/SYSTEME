#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>
#include <assert.h>
#include <time.h>

#include "message.h" 

#define N	1000000

// Romain BOISSON
// Emile PAQUETTE

// PROJET SYSTEME PERIODIC 
 
int main(int argc, char *argv[]){

	// vérification des arguments
	test();	
	if (argc != 2){
		printf("Le programme a besoin d'un argument : le nombre de secondes depuis EPOCH");
		exit(EXIT_FAILURE);
	}

	time_t t1;
	t1 = atoi(argv[1]);
	
	if (t1 == (time_t)-1){
		perror("time");
		exit(EXIT_FAILURE);
	}
	
	printf("%s",ctime(&t1));
	return EXIT_SUCCESS;
}
