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

#define N	1000000

// Romain BOISSON
// Emile PAQUETTE

// PROJET SYSTEME PERIODIC 

int main(int argc, char *argv[]){
	if(fork()==0){
		setsid();
		if(fork()==0){
			chdir("/");
			umask(0);
			fclose(stdin);
			fclose(stderr);
			fclose(stdout);
			execv("./period",argv);
		}else{
			exit(0) ;
		}
	}else{
		wait(NULL);
	}
	return 0;
}
