/*
** EPITECH PROJECT, 2020
** server
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "server/server.h"
#include "socket.h"
#include "error.h"
#include "client.h"

void reset_client_context(client_t *client)
{
    for (client_context_type_t i = 0; i < CONTEXT_MAX; ++i)
        uuid_clear(client->context[i]);
}

uerror_t create_client(const int socket, client_t **this)
{
    *this = malloc(sizeof(client_t));
    if (*this == NULL)
        return (ERR_MALLOC);
    (*this)->socket = INVALID_SOCKET;
    memset((*this)->name, 0, MAX_NAME_LENGTH);
    (*this)->socket = socket;
    (*this)->flags = CLIENT_NONE;
    uuid_clear((*this)->id);
    reset_client_context(*this);
    _PRINT_SERVER("[%i] Connection established\n", socket);
    return (send_reply(socket, SERVICE_READY, NULL));
}

void free_client(client_t **this)
{
    if (*this == NULL)
        return;
    if ((*this)->socket != INVALID_SOCKET)
        if (close((*this)->socket))
            _DISPLAY_PERROR("free_server - close");
    free(*this);
    *this = NULL;
}
