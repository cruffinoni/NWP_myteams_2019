/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include <string.h>
#include "server/server.h"
#include "error.h"
#include "client.h"
#include "server/database.h"

uerror_t show_user_info(server_t *server, const int client, const char **args)
{
    client_t user;
    uerror_t err;

    if (!IS_CONNECTED(server->client[client]))
        return (send_reply(client, NOT_CONNECTED, NULL));
    memset(user.name, 0, MAX_NAME_LENGTH);
    if ((err = db_get_user_infos(args[1], &user)) != ERR_NONE) {
        send_reply(client, INTERNAL_ERROR, NULL);
        return (err);
    }
    if (strlen(user.name) == 0)
        return (send_reply(client, OK, "User <%s> not found", args[1]));
    else
        return (send_reply(client, OK, "User <%s:%s>", user.name, args[1]));
}

uerror_t show_all_users(server_t *server, const int client, const char **args)
{
    uerror_t err;
    db_user_list_t *list = NULL;
    db_user_list_t *tmp = NULL;

    if (!IS_CONNECTED(server->client[client]))
        return (send_reply(client, NOT_CONNECTED, NULL));
    if ((err = db_get_all_users(&list)) != ERR_NONE) {
        send_reply(client, INTERNAL_ERROR, NULL);
        return (err);
    }
    tmp = list;
    // Determine the format of the returned data
    while (tmp != NULL) {
        send_reply(client, OK, "User <%s:%s>", tmp->client.name, uid_to_string(tmp->client.id));
        tmp = tmp->next;
    }
    db_destroy_user_list(list);
    return (ERR_NONE);
}
