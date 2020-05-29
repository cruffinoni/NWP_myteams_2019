/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <string.h>
#include "server/database.h"
#include "client/commands.h"

static uerror_t list_teams(const client_t *this)
{
    uerror_t err;
    db_listing_t *list = NULL;
    db_listing_t *tmp = NULL;

    if ((err = db_list_teams(&list)) != ERR_NONE) {
        send_reply(this->socket, INTERNAL_ERROR, NULL);
        return (err);
    }
    tmp = list;
    while (tmp != NULL) {
        err = send_reply(this->socket, OK, "Team <%s:%s><%s>", tmp->name,
            tmp->id, tmp->description);
        if (err != ERR_NONE) {
            db_destroy_listing(list);
            return (err);
        }
        tmp = tmp->next;
    }
    db_destroy_listing(list);
    return (ERR_NONE);
}

static uerror_t list_channel(const client_t *this)
{
    uerror_t err;
    db_listing_t *list = NULL;
    db_listing_t *tmp = NULL;

    if ((err = db_list_channel(&list, uid_to_string(this->context[TEAM])))
        != ERR_NONE) {
        send_reply(this->socket, INTERNAL_ERROR, NULL);
        return (err);
    }
    tmp = list;
    while (tmp != NULL) {
        err = send_reply(this->socket, OK, "Channel <%s:%s><%s>", tmp->name,
            tmp->id, tmp->description);
        if (err != ERR_NONE) {
            db_destroy_listing(list);
            return (err);
        }
        tmp = tmp->next;
    }
    db_destroy_listing(list);
    return (ERR_NONE);
}

static uerror_t list_thread(const client_t *this)
{
    uerror_t err;
    db_listing_t *list = NULL;
    db_listing_t *tmp = NULL;

    if ((err = db_list_thread(&list, this->context)) != ERR_NONE) {
        send_reply(this->socket, INTERNAL_ERROR, NULL);
        return (err);
    }
    tmp = list;
    while (tmp != NULL) {
        err = send_reply(this->socket, OK, "Thread <%s:%s><%s>", tmp->name,
            tmp->id, tmp->description);
        if (err != ERR_NONE) {
            db_destroy_listing(list);
            return (err);
        }
        tmp = tmp->next;
    }
    db_destroy_listing(list);
    return (ERR_NONE);
}

static uerror_t list_comment(const client_t *this)
{
    uerror_t err;
    db_listing_t *list = NULL;
    db_listing_t *tmp = NULL;

    if ((err = db_list_comment(&list, this->context)) != ERR_NONE) {
        send_reply(this->socket, INTERNAL_ERROR, NULL);
        return (err);
    }
    tmp = list;
    while (tmp != NULL) {
        err = send_reply(this->socket, OK, "Comment <%s:%s><%s>", tmp->name,
            tmp->id, tmp->description);
        if (err != ERR_NONE) {
            db_destroy_listing(list);
            return (err);
        }
        tmp = tmp->next;
    }
    db_destroy_listing(list);
    return (ERR_NONE);
}

uerror_t list_cmd(server_t *server, const int client,
    _UNUSED_ const char **args)
{
    static uerror_t (*ptr_list[])(const client_t *) = {
        &list_teams, &list_channel, &list_thread,
    };
    if (!IS_CONNECTED(server->client[client]))
        return (send_reply(client, NOT_CONNECTED, NULL));
    for (int i = 0; i < INVALID; ++i)
        if (uuid_is_null(server->client[client]->context[i]))
            return (ptr_list[i](server->client[client]));
    return (list_comment(server->client[client]));
}
