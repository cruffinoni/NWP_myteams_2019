/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <string.h>
#include "client/commands.h"
#include "server/database.h"

static uerror_t create_team(const int client, const char **args)
{
    if (strlen(args[1]) > MAX_NAME_LENGTH)
        return (send_reply(client, ARGUMENT_TOO_LONG,
            "The team's name is too long. The max' is %i", MAX_NAME_LENGTH));
    if (strlen(args[2]) > MAX_DESCRIPTION_LENGTH)
        return (send_reply(client, ARGUMENT_TOO_LONG,
            "The team's description is too long. The max' is %i",
            MAX_DESCRIPTION_LENGTH));
    if (db_team_exists_str(args[1]))
        return (send_reply(client, ID_ALREADY_EXISTS,
            "The team's name '%s' is already taken", args[1]));
    if (db_create_team(args[1], args[2]) != ERR_NONE)
        return (send_reply(client, INTERNAL_ERROR, NULL));
    else
        return (send_reply(client, OK, NULL));
}

uerror_t create_command(server_t *server, const int client, const char **args)
{
    if (!IS_CONNECTED(server->client[client]))
        return (send_reply(client, NOT_CONNECTED, NULL));
    if (uuid_is_null(server->client[client]->context[CONTEXT_TEAM]))
        return (create_team(client, args));
    return (send_reply(client, OK, NULL));
}
