/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#ifndef SRC_MYTEAMS_DATABASE_EXISTENCE
#define SRC_MYTEAMS_DATABASE_EXISTENCE

#include <stdbool.h>
#include <uuid/uuid.h>
#include "client.h"

bool db_user_exists(const client_t *client);
bool db_user_exists_str(const char *id);
bool db_team_exists(const uuid_t team);
bool db_team_exists_str(const char *team);
bool db_channel_exists(const uuid_t team, const uuid_t channel);
bool db_channel_exists_str(const uuid_t team, const char *channel);
bool db_thread_exists_str(const uuid_t team, const uuid_t channel,
    const char *thread);
bool db_thread_exists(const uuid_t team, const uuid_t channel,
    const uuid_t thread);

#endif
