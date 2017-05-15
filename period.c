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

// Romain BOISSON
// Emile PAQUETTE

// PROJET SYSTEME PERIODIC 

// handler du signal SIGUSR1 

/* 
* Permet de réaliser un traitememt suite a la réception du signal SIGUSR1
* @param int signal le numéro du signal
*/ 
void gereSignauxSIGUSR1(int signal){
	 printf("Je receptionne le signal %d\n",signal);
	 
	int f = open("/tmp/period.fifo", O_RDONLY);
	if(f == -1){
		fprintf(stderr,"Erreur lors de l'ouverture de /tmp/period.fifo\n");
		exit(EXIT_FAILURE);
	}
	recv_argv(f);
	
	char *entrer = recv_string(f);
	
		
	printf("Nouvelle commande : %s",entrer);	
	
	// fermeture de f 
	if(close(f) <0){
		perror("close");
		exit(EXIT_FAILURE); 
	}
	
	exit(EXIT_SUCCESS);
}

// handler du signal SIGUSR2 
/* 
* Permet de réaliser un traitememt suite a la réception du signal SIGUSR1
* @param int signal le numéro du signal
*/ 
void gereSignauxSIGUSR2(int signal){
	 printf("Je receptionne le signal %d\n",signal);
	 
	int fd = open("/tmp/period.fifo", O_RDONLY);
	if(fd == -1){
		fprintf(stderr,"Erreur lors de l'ouverture de /tmp/period.fifo\n");
		exit(EXIT_FAILURE);
	}
	
	// envoie de l'ensemble des entrées de la table 
	// MODIFIER QUAND ON CONNAITRA LE FORMAT DE LA TABLE 
	/* int x = send_string(fd,);
		if(x ==0){
			fprintf(stderr,"Erreur lors de l'envoie");
			exit(EXIT_FAILURE);
		}
	*/
		
	// fermeture de fd
	if(close(fd) <0){
		fprintf(stderr,"close");
		exit(EXIT_FAILURE); 
	}
	exit(EXIT_SUCCESS);
}

int main(int argc, char *argv[]){
	
	// on gère SIGUSR1 
	struct sigaction action;
	
	action.sa_handler = gereSignauxSIGUSR1;
	sigemptyset(&action.sa_mask);
	action.sa_flags= 0;
	
	// installation du handler pour le signal SIGUSR1
	int verif = sigaction(SIGUSR1, &action, NULL);
	
	// erreur si verif == -1 
	if(verif == -1){
		fprintf(stderr,"Erreur signal SIGUSR1");
	}else{
		gereSignauxSIGUSR1(verif);
	}
	
	// on gère SIGUSR2
	struct sigaction action2;
	
	action2.sa_handler = gereSignauxSIGUSR2;
	sigemptyset(&action2.sa_mask);
	action2.sa_flags= 0;
	
	// installation du handler pour le signal SIGUSR1
	int verif2 = sigaction(SIGUSR2, &action2, NULL);
	
	// erreur si verif == -1 
	if(verif2 == -1){
		fprintf(stderr,"Erreur signal SIGUSR2");
	}else{
		gereSignauxSIGUSR2(verif2);
	}
}


