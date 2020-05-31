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
        case TEAM:
            return (db_team_exists(client->context[TEAM]));
        case CHANNEL:
            return (db_channel_exists(client->context[TEAM],
                client->context[CHANNEL]));
        case THREAD:
            return (db_thread_exists(client->context[TEAM],
                client->context[CHANNEL], client->context[THREAD]));
        default:
            _PRINT_CLIENT("[%i] Invalid context type: %i\n", client->socket,
                type);
            return (false);
    }
}

uerror_t set_context(server_t *s, const int c, const char **args)
{
    if (!IS_CONNECTED(s->client[c]))
        return (send_reply(c, NOT_CONNECTED, NULL));
    if (tab_len((char **) args) == 1) {
        reset_client_context(s->client[c]);
        return (send_reply(c, CLIENT_CONTEXT_RESET, NULL));
    }
    for (ushort i = 1, k = 0; args[i] != NULL; ++i, ++k) {
        if (uuid_parse(args[i], s->client[c]->context[k]) < 0)
            return (send_reply(c, INVALID_ID_PROVIDED, NULL));
        if (k > TEAM && !db_user_is_subscribed(s->client[c],
            s->client[c]->context[TEAM])) {
            reset_client_context(s->client[c]);
            return (send_reply(c, FORBIDDEN, NULL));
        }
        if (!check_existing_params(k, s->client[c])) {
            reset_client_context(s->client[c]);
            return (send_reply(c, ID_DOESNT_EXISTS,
                "ID '%s' is invalid nor doesn't exists", args[i]));
        }
    }
    return (send_reply(c, OK, NULL));
}
