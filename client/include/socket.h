/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** socket.h
*/

#ifndef NWP_MYTEAMS_2019_SOCKET_H
#define NWP_MYTEAMS_2019_SOCKET_H

#include <stdbool.h>
#include "client.h"
#include "socket.h"

#define MAX_CONNECTION      FD_SETSIZE

bool ACTIVE_SERVER;

typedef struct socket_s
{
    int sock_fd;
    long port;
    char *ip;
    client_t *client;
    fd_set server_set;
} socket_t;

socket_t *init_client_connection(char **av);

#endif