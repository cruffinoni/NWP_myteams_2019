/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <string.h>
#include "server/database/database.h"
#include "client/commands.h"

uerror_t db_display_list(const int client, const char *title,
    const db_listing_t *list)
{
    const db_listing_t *tmp = list;
    uerror_t err;

    while (tmp != NULL) {
        if (strlen(tmp->description)) {
            err = send_reply(client, LISTING, "%s <%s:%s><%s>", title,
                tmp->name, tmp->id, tmp->description);
        } else {
            err = send_reply(client, LISTING, "%s <%s:%s>", title, tmp->name,
                tmp->id);
        }
        if (err != ERR_NONE)
            return (err);
        tmp = tmp->next;
    }
    return (ERR_NONE);
}
