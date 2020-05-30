/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/


#ifndef SRC_MYTEAMS_SERVER_DATABASE_NOTIFICATION
#define SRC_MYTEAMS_SERVER_DATABASE_NOTIFICATION

#include "server/server.h"

uerror_t db_notify_team_subscriber(const server_t *server,
    const uuid_t team, const char *fmt, ...);
uerror_t db_notify_user(const server_t *server, const char *dest,
    const char *fmt, ...);

#endif
