/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** commands.h
*/

#ifndef NWP_MYTEAMS_2019_COMMANDS_H
#define NWP_MYTEAMS_2019_COMMANDS_H

#include "socket.h"

#define _UNUSED_ __attribute__((unused))

int help(socket_t *socket, char **args);
int login(socket_t *socket, char **args);
int logout(socket_t *socket, char **args);
int users(socket_t *socket, char **args);
int user(socket_t *socket, char **args);
int send(socket_t *socket, char **args);
int messages(socket_t *socket, char **args);
int subscribe(socket_t *socket, char **args);
int subscribed(socket_t *socket, char **args);
int unsubscribe(socket_t *socket, char **args);
int use(socket_t *socket, char **args);
int create(socket_t *socket, char **args);
int list(socket_t *socket, char **args);
int info(socket_t *socket, char **args);

#endif
