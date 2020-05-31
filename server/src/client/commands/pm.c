/*
** EPITECH PROJECT, 2020
** NWP_myteams_2019
** File description:
** TODO: CHANGE DESCRIPTION.
*/

#include <stdlib.h>
#include <string.h>
#include "error.h"
#include "client.h"
#include "server/server.h"
#include "server/database/database.h"
#include "server/notification.h"
#include "utils.h"

static uerror_t check_local_uid(server_t *s, const int c, const char **av)
{
    uuid_t local;

    if (uuid_parse(av[1], local) < 0) {
        send_reply(c, INTERNAL_ERROR, NULL);
        return (_DISPLAY_PERROR("uuid_parse - commands/pm.c"));
    }
    if (!uuid_compare(local, s->client[c]->id))
        return (send_reply(c, INVALID_SYNTAX, NULL));
    if (!db_user_exists_str(av[1])) {
        send_reply(c, ID_DOESNT_EXISTS, "User <%s> doesn't exists", av[1]);
        return (ERR_LOCAL);
    }
    if (tab_len((char **) av) > 2 && strlen(av[2]) >= MAX_BODY_LENGTH) {
        send_reply(c, BODY_TOO_LONG, NULL);
        return (ERR_LOCAL);
    }
    return (ERR_NONE);
}

uerror_t send_private_message(server_t *s, const int c, const char **av)
{
    uerror_t err;

    if (!IS_CONNECTED(s->client[c]))
        return (send_reply(c, NOT_CONNECTED, NULL));
    if ((err = check_local_uid(s, c, av)) != ERR_NONE)
        return (err != ERR_LOCAL ? err : ERR_NONE);
    if ((err = db_send_pm(s->client[c], av[1], av[2])) != ERR_NONE) {
        send_reply(c, INTERNAL_ERROR, NULL);
        return (err);
    }
    server_event_private_message_sended(uid_to_string(s->client[c]->id),
        av[1], av[2]);
    if ((err = db_notify_user(s, av[1], "New PM from <%s:%s>: <%s>",
        s->client[c]->name, uid_to_string(s->client[c]->id), av[2])))
        return (err);
    return (send_reply(c, OK, NULL));
}

uerror_t list_private_message(server_t *s, const int c, const char **av)
{
    uerror_t err;
    char *str = NULL;

    if (!IS_CONNECTED(s->client[c]))
        return (send_reply(c, NOT_CONNECTED, NULL));
    if ((err = check_local_uid(s, c, av)) != ERR_NONE)
        return (err != 0);
    if ((err = db_get_all_message(s->client[c]->id, av[1], &str)) != ERR_NONE) {
        send_reply(c, INTERNAL_ERROR, NULL);
        return (err);
    }
    err = send_reply(c, LISTING, "List:\n%s", str);
    free(str);
    return (err);
}
