/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** user_gestion.c
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <uuid/uuid.h>
#include "error.h"
#include "client/utils.h"

static int get_user_uuid(client_t *client, char const *server_response)
{
    int i;
    char *tmp_uuid = malloc(sizeof(char) * (LENGTH_UUID + 1));

    if (tmp_uuid == NULL)
        return (ERR_INIT);
    memset(tmp_uuid, 0, LENGTH_UUID + 1);
    for (i = 0; server_response[i] && server_response[i] != '<'; ++i);
    ++i;
    for (int x = 0; x < LENGTH_UUID; ++x, ++i)
        tmp_uuid[x] = server_response[i];
    if (uuid_parse(tmp_uuid, client->id) < 0) {
        printf("Error uuid_parse()\n");
        free(tmp_uuid);
        return (ERR_INIT);
    }
    free(tmp_uuid);
    return (ERR_NONE);
}

int init_user(socket_t *socket, char *server_response, char const *username)
{
    size_t i;

    socket->client = malloc(sizeof(client_t));
    if (socket->client == NULL)
        return (ERR_INIT);
    for (i = 0; username[i]; ++i)
        socket->client->name[i] = username[i];
    socket->client->name[i] = '\0';
    if (get_user_uuid(socket->client, server_response) == ERR_INIT)
        return (ERR_INIT);
    socket->client->socket = socket->sock_fd;
    socket->client->flags = CLIENT_CONNECTED;
    socket->client->context = NULL;
    return (ERR_NONE);
}

void free_user(socket_t *socket)
{
    if (socket == NULL || socket->client == NULL)
        return;
    if (socket->client->context != NULL)
        free(socket->client->context);
    free(socket->client);
    socket->client = NULL;
}
