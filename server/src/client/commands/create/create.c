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

static uerror_t create_team(const client_t *client, const server_t *server,
    const char **args)
{
    char *team;

    if (strlen(args[1]) > MAX_NAME_LENGTH)
        return (send_reply(client->socket, ARGUMENT_TOO_LONG, NULL));
    if (args[2] != NULL && strlen(args[2]) > MAX_DESCRIPTION_LENGTH)
        return (send_reply(client->socket, ARGUMENT_TOO_LONG, NULL));
    if ((team = remove_quotes(args[1])) == NULL)
        return (send_reply(client->socket, INTERNAL_ERROR, NULL));
    if (db_team_exists_str(team)) {
        free(team);
        return (send_reply(client->socket, TEAM_ALREADY_EXISTS, NULL));
    }
    if (db_create_team(args[1], args[2]) != ERR_NONE)
        send_reply(client->socket, INTERNAL_ERROR, NULL);
    else
        send_reply(client->socket, OK, "Team created <%s:%s>",
            team, db_get_uuid_str(team));
    free(team);
    return (release_event(client, server, TEAM, args));
}

static uerror_t create_channel(const client_t *this, const server_t *server,
    const char **args)
{
    char *channel;

    if (strlen(args[1]) > MAX_NAME_LENGTH)
        return (send_reply(this->socket, ARGUMENT_TOO_LONG, NULL));
    if (strlen(args[2]) > MAX_DESCRIPTION_LENGTH)
        return (send_reply(this->socket, ARGUMENT_TOO_LONG, NULL));
    if ((channel = remove_quotes(args[1])) == NULL)
        return (send_reply(this->socket, INTERNAL_ERROR, NULL));
    if (db_channel_exists_str(this->context[TEAM], channel)) {
        free(channel);
        return (send_reply(this->socket, CHANNEL_ALREADY_EXISTS, NULL));
    }
    if (db_create_channel(this->context[TEAM], channel, args[2]) != ERR_NONE)
        send_reply(this->socket, INTERNAL_ERROR, NULL);
    else
        send_reply(this->socket, OK, "Channel created <%s:%s>",
            channel, db_get_uuid_str(channel));
    free(channel);
    return (release_event(this, server, CHANNEL, args));
}

static uerror_t create_thread(const client_t *this, const server_t *server,
    const char **args)
{
    char *thread;

    if (strlen(args[1]) > MAX_NAME_LENGTH)
        return (send_reply(this->socket, ARGUMENT_TOO_LONG, NULL));
    if (strlen(args[2]) > MAX_DESCRIPTION_LENGTH)
        return (send_reply(this->socket, ARGUMENT_TOO_LONG, NULL));
    if ((thread = remove_quotes(args[1])) == NULL)
        return (send_reply(this->socket, INTERNAL_ERROR, NULL));
    if (db_thread_exists_str(this->context[TEAM], this->context[CHANNEL],
        thread)) {
        free(thread);
        return (send_reply(this->socket, THREAD_ALREADY_EXISTS, NULL));
    }
    if (db_create_thread(this, thread, args[2]) != ERR_NONE)
        send_reply(this->socket, INTERNAL_ERROR, NULL);
    else
        send_reply(this->socket, OK, "Thread created <%s:%s>",
            thread, db_get_uuid_str(thread));
    free(thread);
    return (release_event(this, server, THREAD, args));
}

static uerror_t create_comment(const client_t *this, const server_t *server,
    const char **args)
{
    if (strlen(args[1]) > MAX_BODY_LENGTH)
        return (send_reply(this->socket, ARGUMENT_TOO_LONG, NULL));
    if (db_create_comment(this, args[1]) != ERR_NONE)
        send_reply(this->socket, INTERNAL_ERROR, NULL);
    else
        send_reply(this->socket, OK, NULL);
    return (release_event(this, server, INVALID, args));
}

uerror_t create_command(server_t *server, const int client, const char **args)
{
    static uerror_t (*ptr_func[])(const client_t *, const server_t *,
        const char **) = {
        &create_team, &create_channel, &create_thread
    };

    if (!IS_CONNECTED(server->client[client]))
        return (send_reply(client, NOT_CONNECTED, NULL));
    if (uuid_is_null(server->client[client]->context[THREAD]) &&
        tab_len((char **) args) != 3)
        return (send_reply(client, INVALID_ARG_COUNT, "2 arguments required"));
    for (int i = 0; i < INVALID; ++i)
        if (uuid_is_null(server->client[client]->context[i]))
            return (ptr_func[i](server->client[client], server, args));
    return (create_comment(server->client[client], server, args));
}
