/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdio.h>
#include <stdlib.h>
#include "server/database.h"
#include "client/commands.h"
#include "utils.h"

uerror_t db_notify_team_subscriber(const server_t *server,
    const uuid_t team, const char *fmt, ...)
{
    char *message = NULL;
    va_list list;
    uerror_t err = ERR_NONE;

    va_start(list, fmt);
    if (vasprintf(&message, fmt, list) < 0) {
        va_end(list);
        return (_DISPLAY_PERROR("vasprintf - db_notify_subscriber"));
    }
    va_end(list);
    for (int i = 0; i < MAX_CONNECTION; ++i) {
        if (FD_ISSET(i, &server->active_fd) && i != server->socket &&
            db_user_is_subscribed(server->client[i], team))
            err = send_reply(i, NOTIFICATION, message);
        if (err != ERR_NONE) {
            free(message);
            return (err);
        }
    }
    free(message);
    return (ERR_NONE);
}

static uerror_t look_for_user(const server_t *server, const char *dest,
    const char *message)
{
    uuid_t local_id;
    uerror_t err = ERR_NONE;

    uuid_parse(dest, local_id);
    for (int i = 0; i < MAX_CONNECTION; ++i) {
        if (!FD_ISSET(i, &server->active_fd) || i == server->socket)
            continue;
        if (!uuid_compare(server->client[i]->id, local_id))
            err = send_reply(i, NOTIFICATION, message);
        if (err != ERR_NONE)
            return (err);
    }
    return (ERR_NONE);
}

uerror_t db_notify_user(const server_t *server, const char *dest,
    const char *fmt, ...)
{
    char *message = NULL;
    va_list list;
    uerror_t err;

    va_start(list, fmt);
    if (vasprintf(&message, fmt, list) < 0) {
        va_end(list);
        return (_DISPLAY_PERROR("vasprintf - db_notify_user"));
    }
    va_end(list);
    err = look_for_user(server, dest, message);
    free(message);
    return (err);
}
