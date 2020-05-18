/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include <string.h>
#include "client/commands.h"
#include "server/database.h"
#include "utils.h"

static uerror_t create_team(const int client, const char **args)
{
    char *real_name;

    _PRINT_SERVER("create_team is called\n");
    if (strlen(args[1]) > MAX_NAME_LENGTH)
        return (send_reply(client, ARGUMENT_TOO_LONG, NULL));
    if (strlen(args[2]) > MAX_DESCRIPTION_LENGTH)
        return (send_reply(client, ARGUMENT_TOO_LONG, NULL));
    if ((real_name = remove_quotes(args[1])) == NULL)
        return (send_reply(client, INTERNAL_ERROR, NULL));
    if (db_team_exists_str(real_name)) {
        free(real_name);
        return (send_reply(client, TEAM_ALREADY_EXISTS, NULL));
    }
    free(real_name);
    if (db_create_team(args[1], args[2]) != ERR_NONE)
        return (send_reply(client, INTERNAL_ERROR, NULL));
    else
        return (send_reply(client, OK, NULL));
}

static uerror_t create_channel(const client_t *this, const char **args)
{
    char *real_name;

    _PRINT_SERVER("create_channel is called\n");
    if (strlen(args[1]) > MAX_NAME_LENGTH)
        return (send_reply(this->socket, ARGUMENT_TOO_LONG, NULL));
    if (strlen(args[2]) > MAX_DESCRIPTION_LENGTH)
        return (send_reply(this->socket, ARGUMENT_TOO_LONG, NULL));
    if ((real_name = remove_quotes(args[1])) == NULL)
        return (send_reply(this->socket, INTERNAL_ERROR, NULL));
    if (db_channel_exists_str(this->context[CONTEXT_TEAM], args[1])) {
        free(real_name);
        return (send_reply(this->socket, TEAM_ALREADY_EXISTS, NULL));
    }
    free(real_name);
    if (db_create_channel(this->context[CONTEXT_TEAM],
        args[1], args[2]) != ERR_NONE)
        return (send_reply(this->socket, INTERNAL_ERROR, NULL));
    else
        return (send_reply(this->socket, OK, NULL));
}

uerror_t create_command(server_t *server, const int client, const char **args)
{
    if (!IS_CONNECTED(server->client[client]))
        return (send_reply(client, NOT_CONNECTED, NULL));
    if (uuid_is_null(server->client[client]->context[CONTEXT_TEAM]))
        return (create_team(client, args));
    if (uuid_is_null(server->client[client]->context[CONTEXT_CHANNEL]))
        return (create_channel(server->client[client], args));
    return (send_reply(client, OK, NULL));
}
