/*
** EPITECH PROJECT, 2020
** server
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_MYTEAMS_SERVER
#define SRC_MYTEAMS_SERVER

#include <stdio.h>
#include "socket.h"
#include "client.h"
#include "error.h"

static const int INVALID_FD = -1;

typedef struct server_s {
    int socket;
    client_t *client[MAX_CONNECTION];
    fd_set active_fd;
} server_t;

uerror_t create_server(server_t **server, const int ac, const char **av);
void free_server(server_t *server);

#define _PRINT_SERVER(...) printf("\x1B[1;31m" __VA_ARGS__); printf("\x1B[0m")
#define _PRINT_CLIENT(...) printf("\x1B[1;34m" __VA_ARGS__); printf("\x1B[0m")

#endif
