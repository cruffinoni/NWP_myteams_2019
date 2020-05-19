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

uerror_t release_event_team(const client_t *client, const char **arg)
{
    char *real_name = remove_quotes(arg[1]);
    uerror_t err = ERR_NONE;

    if (server_event_team_created(db_get_uuid_str(real_name), real_name,
        uid_to_string(client->id)) < 0)
        err = _DISPLAY_PERROR("api - server_event_team_created");
    free(real_name);
    return (err);
}

uerror_t release_event_channel(const client_t *client, const char **arg)
{
    char *real_name = remove_quotes(arg[1]);
    uerror_t err = ERR_NONE;

    if (server_event_channel_created(uid_to_string(client->context[TEAM]),
        db_get_uuid_str(real_name), real_name) < 0)
        err = _DISPLAY_PERROR("api - server_event_team_created");
    free(real_name);
    return (err);
}

uerror_t release_event_thread(const client_t *client, const char **arg)
{
    char *input = remove_quotes(arg[1]);
    uerror_t err = ERR_NONE;

    if (server_event_thread_created(
        uid_to_string(client->context[CHANNEL]),
        uid_to_string(client->context[THREAD]),
        uid_to_string(client->id), input) < 0)
        err = _DISPLAY_PERROR("api - server_event_team_created");
    free(input);
    return (err);
}

uerror_t release_event_comment(const client_t *client, const char **arg)
{
    char *input = remove_quotes(arg[1]);
    uerror_t err = ERR_NONE;

    if (server_event_thread_new_message(
        uid_to_string(client->context[THREAD]),
        uid_to_string(client->id), input) < 0)
        err = _DISPLAY_PERROR("api - server_event_team_created");
    free(input);
    return (err);
}
