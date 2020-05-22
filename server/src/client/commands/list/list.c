/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include <string.h>
#include "server/database.h"
#include "client/commands.h"
#include "utils.h"

uerror_t list_cmd(server_t *server, const int client, const char **args)
{
    uerror_t err;
    db_listing_t *list = NULL;
    db_listing_t *tmp = NULL;

    if (!IS_CONNECTED(server->client[client]))
        return (send_reply(client, NOT_CONNECTED, NULL));
    if ((err = db_get_all_users(&list)) != ERR_NONE) {
        send_reply(client, INTERNAL_ERROR, NULL);
        return (err);
    }
    tmp = list;
    // Determine the format of the returned data
    while (tmp != NULL) {
        send_reply(client, OK, "User <%s:%s>", tmp->client.name,
            uid_to_string(tmp->client.id));
        tmp = tmp->next;
    }
    db_destroy_listing(list);
    return (ERR_NONE);
}
