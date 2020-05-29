/*
** EPITECH PROJECT, 2020
** server
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_MYTEAMS_SERVER
#define SRC_MYTEAMS_SERVER

#include <stdbool.h>
#include <stdio.h>
#include "communication/codes.h"
#include "socket.h"
#include "client.h"
#include "error.h"
#include "myteams/logging_server.h"

#define _UNUSED_ __attribute__((unused))

bool ACTIVE_SERVER;

typedef struct server_s {
    int socket;
    client_t *client[MAX_CONNECTION];
    fd_set active_fd;
} server_t;

uerror_t create_server(server_t **server, const int ac, const char **av);
void free_server(server_t *server);

#define _PRINT_SERVER(...)  { \
    printf("\x1B[1;31m");   \
    printf(__VA_ARGS__);    \
    printf("\x1B[1;0m");    \
}
#define _PRINT_CLIENT(...)  { \
    printf("\x1B[1;34m");   \
    printf(__VA_ARGS__);    \
    printf("\x1B[1;0m");    \
}

uerror_t send_reply(const int client, const codes_t code,
    const char *fmt, ...);

#define GET_CLIENT_ID(s, c) (s->client[c]->id)
#define GET_CLIENT_NAME(s, c) (s->client[c]->name)

#endif
