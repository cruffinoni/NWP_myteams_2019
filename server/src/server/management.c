/*
** EPITECH PROJECT, 2020
** server
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "server/server.h"
#include "client/users.h"

static uerror_t get_port(const char *argument, long *port)
{
    char *buffer;

    if (!strcmp(argument, "-h") || !strcmp(argument, "--help"))
        return (ERR_EXIT_HELP);
    *port = strtol(argument, &buffer, 10);
    if (strlen(buffer))
        return (ERR_PORT_NOT_NUMBER);
    return (ERR_NONE);
}

static uerror_t create_socket(server_t *this, long port)
{
    sockaddrin_t data;

    this->socket = socket(AF_INET, SOCK_STREAM , 0);
    if (this->socket == -1)
        return (ERR_SOCKET);
    data.sin_family = AF_INET;
    data.sin_addr.s_addr = INADDR_ANY;
    data.sin_port = htons(port);
    if (bind(this->socket, (sockaddr_t *) &data, sizeof(sockaddrin_t)) ||
        listen(this->socket, MAX_CONNECTION))
        return (_DISPLAY_PERROR("server_socket - bind/listen"));
    FD_SET(this->socket, &this->active_fd);
    return (ERR_NONE);
}

void free_server(server_t *server)
{
    if (server == NULL)
        return;
    for (int i = 0; i < MAX_CONNECTION; ++i) {
        if (FD_ISSET(i, &server->active_fd) && i != server->socket)
            send_reply(i, SERVICE_CLOSING, NULL);
        free_client(&server->client[i]);
    }
    if (server->socket != INVALID_SOCKET)
        if (close(server->socket))
            _DISPLAY_PERROR("free_server - close");
    free(server);
}

uerror_t create_server(server_t **server, const int ac, const char **av)
{
    long port = 0;
    uerror_t err;

    if (ac != 2)
        return (ERR_INVALID_ARG_COUNT);
    *server = malloc(sizeof(server_t));
    if (*server == NULL)
        return (ERR_MALLOC);
    FD_ZERO(&(*server)->active_fd);
    (*server)->socket = INVALID_SOCKET;
    for (int i = 0; i < MAX_CONNECTION; ++i)
        (*server)->client[i] = NULL;
    if ((err = get_port(av[1], &port)) != ERR_NONE)
        return (err);
    if ((err = create_socket(*server, port)) != ERR_NONE)
        return (err);
    _PRINT_SERVER("Server's port: %li\n", port);
    return (ERR_NONE);
}

bool is_user_connected_str(const char *name, const server_t *server)
{
    for (ushort i = 0; i < MAX_CONNECTION; ++i)
        if (server->client[i] != NULL && !strcmp(name, server->client[i]->name))
            return (true);
    return (false);
}
