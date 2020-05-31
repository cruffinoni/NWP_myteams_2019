/*
** EPITECH PROJECT, 2019
** NWP_myteams_2019
** File description:
** logout.c
*/

#include <string.h>
#include <uuid/uuid.h>
#include "error.h"
#include "socket.h"
#include "client/utils.h"
#include "myteams/logging_client.h"

int logout_success(socket_t *socket, _UNUSED_ char *server_resonse)
{
    char *user_id = uid_to_string(socket->client->id);

    if (user_id == NULL)
        return (ERR_INIT);
    if (client_event_loggedout(user_id, socket->client->name) == -1)
        return (ERR_INIT);
    socket->client->flags = CLIENT_NONE;
    memset(socket->client->name, 0, MAX_NAME_LENGTH);
    uuid_clear(socket->client->id);
    for (client_context_type_t t = 0; t < MAX; ++t)
        uuid_clear(socket->client->context[t]);
    return (ERR_NONE);
}

