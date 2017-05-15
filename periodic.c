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
#include <fcntl.h>
#include <time.h>

#define N	1000000
#define BUFSIZE 256 
#define LONGSIZE 11

// Romain BOISSON
// Emile PAQUETTE

// PROJET SYSTEME PERIODIC 
 
int i=0; 
char buf[BUFSIZE];

// Fonction 


// affichage du synopsis
void usage(){
	printf("Usage : ./periodic start period cmd [args]\n");
	exit(-1);
}

// permet de réaliser l'execution du fichier now et de récuperer la sortie standard de now 
long read_Now(){
	FILE *f;
	f = popen("./now","r");
	if(f==NULL){
		fprintf(stderr,"Erreur lors de l'ouverture de now");
	}
	
	if (fread(buf,sizeof(long), BUFSIZE, f)<0){
		fprintf(stderr,"Erreur lors de la lecture de now");
	}
	
	// fermeture de f 
	if(pclose(f) <0){
		perror("close");
		exit(EXIT_FAILURE); 
	}
	return atol(buf);
}
// permet de lire le PID dans le fichier period.pid
long read_PID(){
	int f = open("/tmp/period.pid", O_RDONLY);
	if(f == -1){
		fprintf(stderr,"Erreur lors de l'ouverture de /tmp/period.pid\n");
		exit(EXIT_FAILURE);
	}
	
	if (read(f,buf, BUFSIZE)<0){
		fprintf(stderr,"Erreur lors de la lecture de /tmp/period.pid\n");
	}
	
	// fermeture de f 
	if(close(f) <0){
		perror("close");
		exit(EXIT_FAILURE); 
	}
	
	return atoi(buf);
}

// Main 

int main(int argc, char *argv[]){

	char *endptr;

	//-----------------------------
	//  Gestion des arguments 
	//-----------------------------

	if(argc == 3){
		usage();	
	}

	// lecture du fichier NOW pour récupérer la date de départ 
	long now = read_Now();
	printf("Now : %ld",now);
		
	// Instant de départ choisi avec un + suivi d'un nb de seconde 
	if(argv[1][0]=='+'){
		long nbSec =0;
		nbSec = strtol(argv[1],&endptr,0);
		printf("nbSec = %ld\n",nbSec);
		nbSec += now;
		printf("nbSecStart = %ld\n",nbSec);
	}else if(argv[1][0]=='n'){
		// utilisation du Now, mais on récupère la date de départ dans tout les cas	
	}else{
		// nombre de seconde depuis epoch 
		int nbSec = atoi(argv[1]);
		printf("NB SEC DEPUIS EPOCH : %d",nbSec);
	}

	pid_t pid = read_PID();
	if(kill(pid, SIGUSR1)){
		perror("kill"); 
		exit(EXIT_FAILURE);
	}

	// 4.3 
	long s_period;
	if(argv[2] < 0 || strcmp(argv[2],endptr)==0){
		fprintf(stderr,"La période doit etre positive");
	}else{
		s_period = strtol(argv[2],&endptr,0);
	}

	char dateDepart[LONGSIZE];
	sprintf(dateDepart,"%ld",now);

	char period[LONGSIZE];
	sprintf(period,"%ld",s_period);

	// open du .fifo 

	int f = open("/tmp/period.fifo", O_WRONLY);
	if(f == -1){
		fprintf(stderr,"Erreur lors de l'ouverture de /tmp/period.fifo");		
		exit(EXIT_FAILURE);
	}
	// envoi des données 
	send_string(f,dateDepart); 
	send_string(f,period);
	send_string(f,argv+3);

	// vérification de la bonne fermeture du flux
	if (close(f)<0){
		fprintf(stderr,"Erreur lors de la fermeture de /tmp/period.fifo");
	}

	// EX 5 
	//5.1
	if(kill(pid, SIGUSR2)){
		fprintf(stderr,"erreur lors de l'envoi du signal SIGUSR2");
		exit(EXIT_FAILURE);
	}

	//5.2

	int fd = open("/tmp/period.fifo", O_RDONLY);
	if(fd == -1){
		fprintf(stderr,"Erreur lors de l'ouverture de /tmp/period.fifo\n");
		exit(EXIT_FAILURE);
	}

	if (read(fd,buf, BUFSIZE)<0){
		fprintf(stderr,"Erreur lors de la lecture de /tmp/period.fifo\n");
	}

	char *affichage = recv_string(fd);

	// fermeture de f 
	if(close(fd) <0){
		perror("close");
		exit(EXIT_FAILURE); 
	}
	printf("Ensemble des commandes : %s",affichage);
}


