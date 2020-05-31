/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** user_gestion.c
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "error.h"
#include "client/utils.h"

void set_client_username(socket_t *socket, char const *username)
{
    size_t i;

    for (i = 0; username[i]; ++i)
        socket->client->name[i] = username[i];
    socket->client->name[i] = '\0';
}

static int disconnect_client(socket_t *params)
{
    if (write(params->sock_fd, "/logout", 7) < 0) {
        printf("Error write\n");
        return (ERR_INIT);
    }
    memset(params->client->name, 0, MAX_NAME_LENGTH);
    return (ERR_NONE);
}

void free_user(socket_t *socket)
{
    if (socket == NULL || socket->client == NULL)
        return;
    if (socket->client->flags == CLIENT_CONNECTED)
        disconnect_client(socket);
    free(socket->client);
    socket->client = NULL;
}
