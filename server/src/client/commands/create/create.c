/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include <string.h>
#include "server/database.h"
#include "client/commands.h"
#include "utils.h"

static uerror_t release_event(const client_t *client,
    const client_context_type_t type, const char **arg, const uerror_t prev)
{
    static uerror_t (*func_ptr[])(const client_t *, const char **) = {
        &release_event_team, &release_event_channel, &release_event_thread,
        &release_event_comment,
    };
    if (prev != ERR_NONE)
        return (prev);
    return (func_ptr[type](client, arg));
}

static uerror_t create_team(const client_t *client, const char **args)
{
    char *real_name;
    uerror_t err;

    if (strlen(args[1]) > MAX_NAME_LENGTH)
        return (send_reply(client->socket, ARGUMENT_TOO_LONG, NULL));
    if (args[2] != NULL && strlen(args[2]) > MAX_DESCRIPTION_LENGTH)
        return (send_reply(client->socket, ARGUMENT_TOO_LONG, NULL));
    if ((real_name = remove_quotes(args[1])) == NULL)
        return (send_reply(client->socket, INTERNAL_ERROR, NULL));
    if (db_team_exists_str(real_name)) {
        free(real_name);
        return (send_reply(client->socket, TEAM_ALREADY_EXISTS, NULL));
    }
    if (db_create_team(args[1], args[2]) != ERR_NONE)
        err = send_reply(client->socket, INTERNAL_ERROR, NULL);
    else
        err = send_reply(client->socket, OK, "Team created <%s:%s>",
            real_name, db_get_uuid_str(real_name));
    free(real_name);
    return (release_event(client, TEAM, args, err));
}

static uerror_t create_channel(const client_t *this, const char **args)
{
    char *real_name;
    uerror_t err;

    if (strlen(args[1]) > MAX_NAME_LENGTH)
        return (send_reply(this->socket, ARGUMENT_TOO_LONG, NULL));
    if (strlen(args[2]) > MAX_DESCRIPTION_LENGTH)
        return (send_reply(this->socket, ARGUMENT_TOO_LONG, NULL));
    if ((real_name = remove_quotes(args[1])) == NULL)
        return (send_reply(this->socket, INTERNAL_ERROR, NULL));
    if (db_channel_exists_str(this->context[TEAM], real_name)) {
        free(real_name);
        return (send_reply(this->socket, TEAM_ALREADY_EXISTS, NULL));
    }
    if (db_create_channel(this->context[TEAM], args[1], args[2]) != ERR_NONE)
        err = send_reply(this->socket, INTERNAL_ERROR, NULL);
    else
        err = send_reply(this->socket, OK, "Channel created <%s:%s>",
            real_name, db_get_uuid_str(real_name));
    free(real_name);
    return (release_event(this, CHANNEL, args, err));
}

static uerror_t create_thread(const client_t *this, const char **args)
{
    char *real_name;
    uerror_t err;

    if (strlen(args[1]) > MAX_NAME_LENGTH)
        return (send_reply(this->socket, ARGUMENT_TOO_LONG, NULL));
    if (strlen(args[2]) > MAX_DESCRIPTION_LENGTH)
        return (send_reply(this->socket, ARGUMENT_TOO_LONG, NULL));
    if ((real_name = remove_quotes(args[1])) == NULL)
        return (send_reply(this->socket, INTERNAL_ERROR, NULL));
    if (db_thread_exists_str(this->context[TEAM], this->context[CHANNEL],
        real_name)) {
        free(real_name);
        return (send_reply(this->socket, TEAM_ALREADY_EXISTS, NULL));
    }
    if (db_create_thread(this, args[1], args[2]) != ERR_NONE)
        err = send_reply(this->socket, INTERNAL_ERROR, NULL);
    else
        err = send_reply(this->socket, OK, "Thread created <%s:%s>",
            real_name, db_get_uuid_str(real_name));
    free(real_name);
    return (release_event(this, THREAD, args, err));
}

uerror_t create_command(server_t *server, const int client, const char **args)
{
    uerror_t err;

    if (!IS_CONNECTED(server->client[client]))
        return (send_reply(client, NOT_CONNECTED, NULL));
    if (uuid_is_null(server->client[client]->context[THREAD]) &&
        tab_len((char **) args) != 3)
        return (send_reply(client, INVALID_ARG_COUNT, "2 arguments required"));
    if (uuid_is_null(server->client[client]->context[TEAM]))
        return (create_team(server->client[client], args));
    if (uuid_is_null(server->client[client]->context[CHANNEL]))
        return (create_channel(server->client[client], args));
    if (uuid_is_null(server->client[client]->context[THREAD]))
        return (create_thread(server->client[client], args));
    if (strlen(args[1]) > MAX_BODY_LENGTH)
        return (send_reply(client, ARGUMENT_TOO_LONG, NULL));
    if (db_create_comment(server->client[client]->id,
        server->client[client]->context, args[1]) != ERR_NONE)
        err = send_reply(client, INTERNAL_ERROR, NULL);
    else
        err = send_reply(client, OK, NULL);
    return (release_event(server->client[client], INVALID, args, err));
}
