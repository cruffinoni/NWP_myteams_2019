/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include "client.h"
#include "server/database.h"

bool db_user_exists(const client_t *client)
{
    return (db_path_exists(DB_USER_PATH, uid_to_string(client->id)));
}

bool db_user_exists_str(const char *id)
{
    return (db_path_exists(DB_USER_PATH, id));
}
