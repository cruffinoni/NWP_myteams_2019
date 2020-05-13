/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** socket.h
*/

#ifndef NWP_MYTEAMS_2019_SOCKET_H
#define NWP_MYTEAMS_2019_SOCKET_H

#include "socket.h"

typedef struct socket_s
{
    int sock_fd;
    int port;
    char *ip;
} socket_t;

socket_t *init_client_connection(char **av);

#endif