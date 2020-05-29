/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include "server/database.h"
#include "client/commands.h"
#include "utils.h"

static uerror_t release_event_team(const client_t *client, const char **arg)
{
    char *real_name = remove_quotes(arg[1]);
    uerror_t err = ERR_NONE;

    if (server_event_team_created(db_get_uuid_str(real_name), real_name,
        uid_to_string(client->id)) < 0)
        err = _DISPLAY_PERROR("api - release_event_team");
    free(real_name);
    return (err);
}

static uerror_t release_event_channel(const client_t *client, const char **arg)
{
    char *real_name = remove_quotes(arg[1]);
    uerror_t err = ERR_NONE;

    if (server_event_channel_created(uid_to_string(client->context[TEAM]),
        db_get_uuid_str(real_name), real_name) < 0)
        err = _DISPLAY_PERROR("api - release_event_channel");
    free(real_name);
    return (err);
}

static uerror_t release_event_thread(const client_t *client, const char **arg)
{
    char *input = remove_quotes(arg[1]);
    uerror_t err = ERR_NONE;
    uuid_name_t thread_name = {0};
    uuid_name_t channel_name = {0};
    uuid_name_t user_id = {0};

    _PRINT_SERVER("release event thread");
    uuid_unparse_lower(client->context[CHANNEL], channel_name);
    uuid_unparse_lower(client->context[THREAD], thread_name);
    uuid_unparse_lower(client->id, user_id);
    if (server_event_thread_created(channel_name, thread_name,
        user_id, input) < 0)
        err = _DISPLAY_PERROR("api - release_event_thread");
    free(input);
    return (err);
}

static uerror_t release_event_comment(const client_t *client, const char **arg)
{
    char *input = remove_quotes(arg[1]);
    uerror_t err = ERR_NONE;
    uuid_name_t thread_name = {0};

    uuid_unparse_lower(client->context[THREAD], thread_name);
    if (server_event_thread_new_message(thread_name,
        uid_to_string(client->id), input) < 0)
        err = _DISPLAY_PERROR("api - release_event_comment");
    free(input);
    return (err);
}

uerror_t release_event(const client_t *client,
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
