/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <string.h>
#include "error.h"
#include "client.h"
#include "server/server.h"

uerror_t disconnect_client(server_t *server,
    const int client, _UNUSED_ const char **args)
{
    if (!IS_CONNECTED(server->client[client]))
        return (send_reply(client, NOT_CONNECTED, NULL));
    _PRINT_SERVER("[%i] User <%s:%s> logged out\n", client, server->client[client]->name,
        uid_to_string(server->client[client]->id));
    server_event_user_logged_out(uid_to_string(server->client[client]->id));
    uuid_clear(server->client[client]->id);
    server->client[client]->flags &= ~CLIENT_CONNECTED;
    return (send_reply(client, DISCONNECTED, NULL));
}

uerror_t login_client(server_t *server, const int client, const char **args)
{
    if (IS_CONNECTED(server->client[client]))
        return (send_reply(client, ALREADY_LOGGED, NULL));
    strcpy(server->client[client]->name, args[1]);
    server->client[client]->flags |= CLIENT_CONNECTED;
    uuid_generate_md5(server->client[client]->id, server->client[client]->id,
        server->client[client]->name, MAX_NAME_LENGTH);
    server_event_user_logged_in(uid_to_string(server->client[client]->id));
    _PRINT_SERVER("[%i] User <%s:%s> logged in\n", client, server->client[client]->name,
        uid_to_string(server->client[client]->id));
    return (send_reply(client, LOGIN_SUCCESSFUL, "Logged successfully: <%s>",
        uid_to_string(server->client[client]->id)));
}
