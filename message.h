#ifndef MESSAGE_H
#define MESSAGE_H

// Romain BOISSON
// Emile PAQUETTE

// PROJET SYSTEME PERIODIC 

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>

int send_string(int fd,char *str);
char *recv_string(int fd);
int send_argv(int fd, char *argv[]);
char **recv_argv(int fd);

#endif
