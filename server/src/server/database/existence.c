/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "client.h"
#include "server/database.h"

bool db_team_exists(const uuid_t team)
{
    return (db_path_exists(DB_TEAM_PATH, uid_to_string(team)));
}

bool db_team_exists_str(const char *team)
{
    return (db_path_exists(DB_TEAM_PATH, team));
}

bool db_channel_exists(const uuid_t team, const uuid_t channel)
{
    return (db_path_exists(DB_CHANNEL_PATH, uid_to_string(team),
        uid_to_string(channel)));
}

bool db_thread_exists(const uuid_t team, const uuid_t channel,
    const uuid_t thread)
{
    return (db_path_exists(DB_THREAD_PATH, uid_to_string(team),
        uid_to_string(channel), uid_to_string(thread)));
}
