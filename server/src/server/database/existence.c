/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <string.h>
#include "client.h"
#include "server/database.h"

bool db_team_exists(const uuid_t team)
{
    return (db_path_exists(DB_TEAM_PATH, uid_to_string(team)));
}

bool db_team_exists_str(const char *team)
{
    uuid_t local;

    uuid_clear(local);
    uuid_generate_md5(local, local, team, strlen(team));
    return (db_path_exists(DB_TEAM_PATH, uid_to_string(local)));
}

bool db_channel_exists(const uuid_t team, const uuid_t channel)
{
    return (db_path_exists(DB_CHANNEL_PATH, uid_to_string(team),
        uid_to_string(channel)));
}

bool db_channel_exists_str(const uuid_t team, const char *channel)
{
    return (db_path_exists(DB_CHANNEL_PATH, uid_to_string(team), channel));
}
