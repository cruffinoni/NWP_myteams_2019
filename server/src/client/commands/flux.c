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
#include "server/database.h"

uerror_t disconnect_client(server_t *server,
    const int client, _UNUSED_ const char **args)
{
    if (!IS_CONNECTED(server->client[client]))
        return (send_reply(client, NOT_CONNECTED, NULL));
    _PRINT_SERVER("[%i] User <%s:%s> logged out\n", client,
        GET_CLIENT_NAME(server, client),
        uid_to_string(GET_CLIENT_ID(server, client)));
    server_event_user_logged_out(uid_to_string(GET_CLIENT_ID(server, client)));
    uuid_clear(GET_CLIENT_ID(server, client));
    server->client[client]->flags &= ~CLIENT_CONNECTED;
    return (send_reply(client, DISCONNECTED, NULL));
}

uerror_t login_client(server_t *server, const int client, const char **args)
{
    uerror_t err;

    if (IS_CONNECTED(server->client[client]))
        return (send_reply(client, ALREADY_LOGGED, NULL));
    strcpy(GET_CLIENT_NAME(server, client), args[1]);
    server->client[client]->flags |= CLIENT_CONNECTED;
    uuid_generate_md5(GET_CLIENT_ID(server, client), GET_CLIENT_ID(server, client),
        GET_CLIENT_NAME(server, client), MAX_NAME_LENGTH);
    if (!db_user_exists(server->client[client]))
        if ((err = db_create_user(server->client[client])) != ERR_NONE) {
            send_reply(client, INTERNAL_ERROR, NULL);
            return (err);
        }
    server_event_user_logged_in(uid_to_string(GET_CLIENT_ID(server, client)));
    _PRINT_SERVER("[%i] User <%s:%s> logged in\n", client,
        GET_CLIENT_NAME(server, client),
        uid_to_string(GET_CLIENT_ID(server, client)));
    return (send_reply(client, LOGIN_SUCCESSFUL, "Logged successfully: <%s>",
        uid_to_string(GET_CLIENT_ID(server, client))));
}
