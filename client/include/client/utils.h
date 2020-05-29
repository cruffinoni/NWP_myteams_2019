/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** utils.h
*/

#ifndef NWP_MYTEAMS_2019_UTILS_H
#define NWP_MYTEAMS_2019_UTILS_H

#include "socket.h"

#define LENGTH_UUID     36

int init_user(socket_t *socket, char *server_response, char const *username);
void free_user(socket_t *socket);

int send_server_message(int sock_fd, char **args);
long get_status_code(char *server_response);
char *get_server_response(socket_t *params);

#endif
