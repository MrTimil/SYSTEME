#include "message.h"

// Romain BOISSON
// Emile PAQUETTE

// PROJET SYSTEME PERIODIC 

// Fonctions 

/*
*	Permet d'envoyer une chaîne de caractères via un descripteur de fichier
*	@param : int fd un flux 
*	@param : char *str une chaine de caractère
*/
int send_string(int fd,char *str){
	assert(fd>=0);
	size_t s_str = strlen(str);
	char string_len[256];
	sprintf(string_len,"%lu",s_str);
	if(write(fd,string_len,sizeof(size_t))==sizeof(size_t)){
		if(write(fd, str, s_str) == s_str){
			return 0;
		}
		return -2;
	}
	return -1;
}

/*
* Reçoit une chaîne de caractères via un descripteur de fichier
* @param int fd un flux 
*
*/
char *recv_string(int fd){
	assert(fd>=0);
	char taille[5] ;
	taille[4] = '\0';
	
	size_t readed=0;	
	do{
		readed += read(fd, &taille + readed , sizeof(size_t)-readed);
	}while( readed < 4);
	size_t readed_m=0;
	size_t s_msg = atoi(taille);
	char *msg = malloc(sizeof(char) * s_msg );
	do{
		readed_m = read(fd, msg + readed_m , s_msg-readed_m);
	}while( readed_m < s_msg);
	
	return msg;

}

/*
* Envoie un tableau de chaînes de caractères
* @param int fd un flux
* @param char *argv[] un tableau de chaine de caractère 
*/
int send_argv(int fd, char *argv[]){
	assert(fd>=0);
	int i = 0;
	size_t s_argv=0;
	while(argv[i] != NULL){
		s_argv++;
		i++;
	}
	i=0;
	char string_len[256];
	sprintf(string_len,"%lu",s_argv);
	printf("\n%s\n",string_len);
	if(write(fd,string_len,sizeof(size_t))==sizeof(size_t)){	
		while(i < s_argv){
			if(send_string(fd,argv[i])!=0){
				return -1;
			}
			++i;
		}
	}
	return 0;
}

/*
* Permet de recevoir un message 
* @param int fd un flux
*/
char **recv_argv(int fd){
	assert(fd>=0);
	char taille[5] ;
	taille[4] = '\0';
	size_t readed=0;	
	do{
		readed = read(fd, &taille + readed , sizeof(size_t)-readed);
	}while( readed < 4);
	size_t readed_argv=0;	
	size_t s_argv = atoi(taille);
	char **argv = malloc(sizeof(char) * s_argv);
	do{
		argv[readed_argv] = recv_string(fd);
		readed_argv++;
	}while( readed_argv < s_argv);
	return argv;
}



