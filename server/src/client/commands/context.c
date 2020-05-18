/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <string.h>
#include "error.h"
#include "client.h"
#include "client/users.h"
#include "server/server.h"
#include "server/database.h"
#include "utils.h"

static bool check_existing_params(const client_context_type_t type,
    const client_t *client)
{
    switch (type) {
        case CONTEXT_TEAM:
            return (db_team_exists(client->context[CONTEXT_TEAM]));
        case CONTEXT_CHANNEL:
            return (db_channel_exists(client->context[CONTEXT_TEAM],
                client->context[CONTEXT_CHANNEL]));
        case CONTEXT_THREAD:
            return (db_thread_exists(client->context[CONTEXT_TEAM],
                client->context[CONTEXT_CHANNEL],
                client->context[CONTEXT_THREAD]));
        default:
            _PRINT_CLIENT("[%i] Invalid context type: %i\n", client->socket,
                type);
            return (false);
    }
}

uerror_t use_context(server_t *server, const int client, const char **args)
{
    if (!IS_CONNECTED(server->client[client]))
        return (send_reply(client, NOT_CONNECTED, NULL));
    if (tab_len((char **) args) == 0) {
        reset_client_context(server->client[client]);
        return (send_reply(client, OK, NULL));
    }
    for (ushort i = 1, k = 0; args[i] != NULL; ++i, ++k) {
        if (uuid_parse(args[i], server->client[client]->context[k]) < 0)
            return (send_reply(client, INVALID_ID_PROVIDED, NULL));
        _PRINT_CLIENT("For context %i using id '%s' -> '%s'\n", i, args[i],
            uid_to_string(server->client[client]->context[k]));
        if (!check_existing_params(k, server->client[client])) {
            reset_client_context(server->client[client]);
            return (send_reply(client, ID_DOESNT_EXISTS,
                "ID '%s' is invalid nor doesn't exists", args[i]));
        }
    }
    return (send_reply(client, OK, NULL));
}

// use db7ec69b-eb29-37ef-876d-2e2ef553e92e