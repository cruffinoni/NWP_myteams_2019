/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <string.h>
#include "server/server.h"
#include "error.h"
#include "client.h"
#include "server/database/database.h"

uerror_t show_user_info(server_t *server, const int client, const char **args)
{
    char name[MAX_NAME_LENGTH];
    uerror_t err;

    if (!IS_CONNECTED(server->client[client]))
        return (send_reply(client, FORBIDDEN, NULL));
    memset(name, 0, MAX_NAME_LENGTH);
    if ((err = db_get_user_infos(args[1], name)) != ERR_NONE) {
        send_reply(client, INTERNAL_ERROR, NULL);
        return (err);
    }
    if (strlen(name) == 0)
        return (send_reply(client, OK, "User <%s> not found", args[1]));
    else
        return (send_reply(client, OK, "User <%s:%s>", name, args[1]));
}

uerror_t show_all_users(server_t *server, const int client,
    _UNUSED_ const char **args)
{
    uerror_t err;
    db_listing_t *list = NULL;
    db_listing_t *tmp = NULL;

    if (!IS_CONNECTED(server->client[client]))
        return (send_reply(client, FORBIDDEN, NULL));
    if ((err = db_list_users(&list)) != ERR_NONE) {
        send_reply(client, INTERNAL_ERROR, NULL);
        return (err);
    }
    tmp = list;
    if ((err = send_reply(client, START_LISTING, NULL)) != ERR_NONE)
        return (err);
    while (tmp != NULL) {
        send_reply(client, LISTING, "User <%i:%s:%s>",
            is_user_connected_str(tmp->name, server),
            tmp->name, tmp->id);
        tmp = tmp->next;
    }
    db_destroy_listing(list);
    return (send_reply(client, END_LISTING, NULL));
}
