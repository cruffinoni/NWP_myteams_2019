/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <string.h>
#include "client.h"
#include "server/database/database.h"

bool db_team_exists(const uuid_t team)
{
    uuid_name_t team_name = {0};

    uuid_unparse_lower(team, team_name);
    return (db_path_exists(DB_TEAM_PATH, team_name));
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
    uuid_name_t team_name = {0};
    uuid_name_t channel_name = {0};

    uuid_unparse_lower(channel, channel_name);
    uuid_unparse_lower(team, team_name);
    return (db_path_exists(DB_CHANNEL_PATH, team_name, channel_name));
}

bool db_channel_exists_str(const uuid_t team, const char *channel)
{
    uuid_name_t team_name = {0};

    uuid_unparse_lower(team, team_name);
    return (db_path_exists(DB_CHANNEL_PATH, team_name,
        db_get_uuid_str(channel)));
}
