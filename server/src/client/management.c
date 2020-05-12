/*
** EPITECH PROJECT, 2020
** server
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "socket.h"
#include "error.h"
#include "client.h"

uerror_t create_client(client_t *this)
{
    this = malloc(sizeof(client_t));
    if (this == NULL)
        return (ERR_MALLOC);
    this->socket = INVALID_SOCKET;
    memset(this->name, 0, MAX_NAME_LENGTH);
    this->context = malloc(sizeof(client_context_t));
    if (this->context == NULL)
        return (ERR_MALLOC);
    this->context->type = CONTEXT_NONE;
    return (ERR_NONE);
}

void free_client(client_t *this)
{
    if (this == NULL)
        return;
    if (this->context != NULL)
        free(this->context);
    if (this->socket != INVALID_SOCKET)
        if (close(this->socket))
            _DISPLAY_PERROR("free_server - close");
}
